<?php
/**
 * @file
 * Checkout pane callback functions.
 */

/**
 * Commerce checkout pane form builder callback.
 */
function commerce_registration_information_checkout_form($form, &$form_state, $checkout_pane, $order) {
  global $user;
  $show_form = FALSE;
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $form = array();
  // Determine if we should create a new entity or if the user has gone back in
  // the checkout process and we should load previously stored values from
  // either the checkout pane or from the order.
  $find_values = isset($form_state['values'][$checkout_pane['pane_id']]['register_entities']);
  $order_values = isset($order->data['register_entities']);
  $override_title = variable_get('commerce_registration_product_title', NULL);
  $hide_email = variable_get('commerce_registration_hide_email_logged_in', FALSE);
  foreach ($order_wrapper->commerce_line_items as $delta => $line_item_wrapper) {
    if (!in_array($line_item_wrapper->type->value(), commerce_product_line_item_types())) {
      continue;
    }
    $id = (int) $line_item_wrapper->commerce_product->product_id->value();
    if (registration_status('commerce_product', $id, TRUE) == 1) {
      $show_form = TRUE;
      $product = $line_item_wrapper->commerce_product;
      $quantity = (int) $line_item_wrapper->quantity->value();
      $prodkey = 'prod-' . $product->sku->value();
      for ($i = 0; $i < $quantity; $i++) {
        // We add a single registration for the quantity of the product being
        // purchased/registered for.
        $label = $i + 1;
        $title = check_plain($product->title->value() . ' - Registrant #' . $label);
        if (isset($override_title)) {
          $title = str_replace('[title]', $product->title->value(), $override_title);
          $title = str_replace('[index]', $label, $title);
        }
        $form[$prodkey][$prodkey . '-reg-' . $i] = array(
          '#type' => 'fieldset',
          '#title' => $title,
          '#collapsible' => TRUE,
          '#tree' => TRUE,
          '#description' => variable_get('commerce_registration_registrant_help', ''),
        );
        $entity = NULL;
        $mail = '';
        $bundle = registration_get_entity_registration_type('commerce_product',
                    $line_item_wrapper->commerce_product->value());
        if ($find_values &&
          isset($form_state['values'][$checkout_pane['pane_id']]['register_entities'][$prodkey][$i])) {
          // The entity exists already, so let's just load it from the
          // form_state.
          $entity = $form_state['values'][$checkout_pane['pane_id']]['register_entities'][$prodkey][$i];
        }
        elseif ($order_values && isset($order->data['register_entities'][$prodkey][$i])) {
          // The entity is not in form_state, but is in the order data, so we
          // load it from there instead.
          $entity = $order->data['register_entities'][$prodkey][$i];
        }
        else {
          // Entity doesn't exist, so we need to create a new registration.
          $entity = commerce_registration_create_product_registration(
            $line_item_wrapper->commerce_product->product_id->value(),
            $bundle,
            $order->order_id
          );
        }
        // -------------------------------------------------------------------------
        // All the following code can be deleted if we use the form builder from ER.
        // -------------------------------------------------------------------------
        $mail = $entity->mail;
        $options = registration_access_people($entity);
        if (count($options) == 0) {
          $form[$prodkey][$prodkey . '-reg-' . $i]['no_reg'] = array(
            '#markup' => t('You do not have permission to register for this item.'),
          );
          $form[$prodkey][$prodkey . '-reg-' . $i]['no_reg_permission'] = array(
            '#type' => 'hidden',
            '#value' => TRUE,
          );
          return $form;
        }
        $tmp_form_state = array();
        $register_form = registration_form($form, $tmp_form_state, $entity);
        // Copy fields from the registration form so we don't duplicate functionality.
        if (isset($register_form['who_message'])) {
          $form[$prodkey][$prodkey . '-reg-' . $i]['who_message'] = $register_form['who_message'];
        }
        $form[$prodkey][$prodkey . '-reg-' . $i]['register_for'] = $register_form['who_is_registering'];
        $find_name = "registration_information[$prodkey][$prodkey-reg-$i][register_for]";
        $form[$prodkey][$prodkey . '-reg-' . $i]['user'] = $register_form['user'];
        $form[$prodkey][$prodkey . '-reg-' . $i]['user']['#states'] = array(
          'visible' => array(
            ':input[name="' . $find_name . '"]' => array('value' => REGISTRATION_REGISTRANT_TYPE_USER),
          ),
        );
        $form[$prodkey][$prodkey . '-reg-' . $i]['anon_mail'] = $register_form['anon_mail'];
        $form[$prodkey][$prodkey . '-reg-' . $i]['anon_mail']['#states'] = array(
          'visible' => array(
            ':input[name="' . $find_name .'"]' => array('value' => REGISTRATION_REGISTRANT_TYPE_ANON),
          ),
        );
        // Attach the entity's fields to the form.
        field_attach_form(
          'registration',
          $entity,
          $form[$prodkey][$prodkey . '-reg-' . $i],
          $form_state
        );
        $fields = &$form[$prodkey][$prodkey . '-reg-' . $i];
        foreach ($fields as $key => $data) {
          if (is_array($data) && drupal_substr($key, 0, 1) != '#') {
            // We set the parents on just fields so we can find them in
            // form_state later; fields in the form array don't start with a #.
            $fields[$key]['#parents'] = array(
              'registration_information',
              $prodkey,
              $prodkey . '-reg-' . $i,
              $key,
            );
          }
        }
        // -------------------------------------------------------------------------
        $form['register_entities'][$prodkey][$i] = array(
          '#type' => 'value',
          '#value' => $entity,
        );
      }
    }
  }
  if (!$show_form) {
    // No register enabled products, so go to next step of checkout process.
    $form['no_reg_products'] = array(
      '#markup' => t('No information required. You may skip this page.'),
    );
  }
  return $form;
}

/**
 * Commerce checkout pane form validation callback.
 */
function commerce_registration_information_checkout_form_validate($form, &$form_state, $checkout_pane, $order) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $ret = TRUE;
  foreach ($order_wrapper->commerce_line_items as $delta => $line_item_wrapper) {
    if (!in_array($line_item_wrapper->type->value(), commerce_product_line_item_types())) {
      continue;
    }
    $id = (int) $line_item_wrapper->commerce_product->product_id->value();
    if (registration_status('commerce_product', $id, TRUE) == 1) {
      $product = $line_item_wrapper->commerce_product;
      $quantity = (int) $line_item_wrapper->quantity->value();
      $emails = array();
      $self_products = array();
      for ($i = 0; $i < $quantity; $i++) {
        $prodkey = 'prod-' . $product->sku->value();
        // 
        // $tmp_form_state['values'] = $form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i;
        // Delete the following when we use ER's validation handler.
        if (isset($form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['no_reg_permission'])) {
          form_set_error("registration_information][" . $prodkey . "]["
              . $prodkey . "-reg-" . $i . "][no_reg",
            t("Unable to continue, you are unable to register for this item. Please remove it from your cart."));
            $ret = FALSE;
          continue;
        }
        $entity = $form_state['values'][$checkout_pane['pane_id']]['register_entities'][$prodkey][$i];
        $type = $form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['register_for'];
        $is_registered = FALSE;
        switch ($type) {
          case REGISTRATION_REGISTRANT_TYPE_ANON:
            $mail = $form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['anon_mail'];
            if (registration_is_registered($entity, $mail)) {
              form_set_error(
                "registration_information][" . $prodkey . "]["
                    . $prodkey . "-reg-" . $i . "][anon_mail",
                  t("The email address entered is already registered for this item.")
              );
              $ret = FALSE;
            }
            elseif (in_array($mail, $emails)) {
              form_set_error(
                "registration_information][" . $prodkey . "]["
                  . $prodkey . "-reg-" . $i . "][anon_mail",
                t("Email addresses must be unique for each registrant."));
              $ret = FALSE;
            }
            else {
              $emails[] = $mail;
            }
            break;
          case REGISTRATION_REGISTRANT_TYPE_USER:
            $account = user_load_by_name($form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['user']);
            if (isset($account)) {
              if (registration_is_registered($entity, NULL, $account->uid)) {
                form_set_error(
                  "registration_information][" . $prodkey . "]["
                      . $prodkey . "-reg-" . $i . "][user",
                  t("That user is already registered for this item.")
                );
                $ret = FALSE;
              }
            }
            else {
              form_set_error(
                "registration_information][$prodkey][$prodkey-reg-$i][user",
                t("Cannot find a user by that username.")
              );
              $ret = FALSE;
            }
            break;
          case REGISTRATION_REGISTRANT_TYPE_ME:
            global $user;
            if (registration_is_registered($entity, NULL, $user->uid)) {
              form_set_error(
                "registration_information][" . $prodkey . "]["
                    . $prodkey . "-reg-" . $i . "][register_for",
                  t("You are already registered for this item.")
              );
              $ret = FALSE;
            }
            if (isset($self_products[$product->product_id->value()])
              && $self_products[$product->product_id->value()] == $user->uid) {
              form_set_error("registration_information][" . $prodkey . "]["
                    . $prodkey . "-reg-" . $i . "][register_for",
                t("You cannot register yourself for the same item more than once."));
              $ret = FALSE;
            }
            else {
              // Set a flag that the current user is registering 'self' for
              // this product.
              $self_products[$product->product_id->value()] = $user->uid;
            }
            break;
        }
        // Let other modules do any field API validation if necessary.
        field_attach_form_validate(
          'registration',
          $entity,
          $form['registration_information'][$prodkey][$prodkey . '-reg-' . $i],
          $form_state
        );
      }
    }
  }
  return $ret;
}

/**
 * Commerce checkout pane form submit callback.
 *
 * @see commerce_registration_entity_update_fields().
 */
function commerce_registration_information_checkout_form_submit($form, &$form_state, $checkout_pane, $order) {
  $order->data['register_entities'] = array();
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  foreach ($order_wrapper->commerce_line_items as $delta => $line_item_wrapper) {
    if (!in_array($line_item_wrapper->type->value(), commerce_product_line_item_types())) {
      continue;
    }
    $id = (int) $line_item_wrapper->commerce_product->product_id->value();
    if (registration_status('commerce_product', $id, TRUE) == 1) {
      $product = $line_item_wrapper->commerce_product;
      $quantity = (int) $line_item_wrapper->quantity->value();
      for ($i = 0; $i < $quantity; $i++) {
        $prodkey = 'prod-' . $product->sku->value();
        if (isset($form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['no_reg_permission'])) {
          continue;
        }
        $entity = &$form_state['values'][$checkout_pane['pane_id']]['register_entities'][$prodkey][$i];
        $type = $form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['register_for'];
        $is_registered = FALSE;
        switch ($type) {
          case REGISTRATION_REGISTRANT_TYPE_ANON:
            $entity->mail = $form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['anon_mail'];
            $entity->user_uid = 0;
            $entity->user = '';
            break;
          case REGISTRATION_REGISTRANT_TYPE_USER:
            $account = user_load_by_name($form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]['user']);
            $entity->mail = $account->mail;
            $entity->user_uid = $account->uid;
            $entity->anon_mail = '';
            break;
          case REGISTRATION_REGISTRANT_TYPE_ME:
            global $user;
            $entity->mail = $user->mail;
            $entity->user_uid = $user->uid;
            $entity->anon_mail = '';
            $entity->user = '';
            break;
        }
        // Notify the field API that values were submitted.
        field_attach_submit(
          'registration',
          $entity,
          $form['registration_information'][$prodkey][$prodkey . '-reg-' . $i],
          $form_state
        );
        // We add the field values to our entity so they are stored properly.
        commerce_registration_entity_update_fields(
          $entity,
          $form_state['values']['registration_information'][$prodkey][$prodkey . '-reg-' . $i]
        );
        $order->data['register_entities'][$prodkey][$i] = $entity;
      }
    }
  }
  // Save the order since we added registration entities to the data array.
  commerce_order_save($order);
}

/**
 * Commerce checkout pane review callback.
 */
function commerce_registration_information_review($form, $form_state, $checkout_pane, $order) {
  $msg = '';
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  foreach ($order_wrapper->commerce_line_items as $delta => $line_item_wrapper) {
    if (!in_array($line_item_wrapper->type->value(), commerce_product_line_item_types())) {
      continue;
    }
    $id = (int) $line_item_wrapper->commerce_product->product_id->value();
    if (registration_status('commerce_product', $id, TRUE) == 1) {
      $product = $line_item_wrapper->commerce_product;
      $quantity = (int) $line_item_wrapper->quantity->value();
      $msg .= '<em>' . $product->title->value() . ' ('
        . format_plural($quantity, '1 registration', '@count registrations')
        . '):</em><br />';
      for ($i = 0; $i < $quantity; $i++) {
        $prodkey = 'prod-' . $product->sku->value();
        $entity = $order->data['register_entities'][$prodkey][$i];
        $l = $i + 1;
        $msg .= "<hr><em><u>" . t("Registrant #@count", array('@count' => $l)) . "</u></em><br />";
        $msg .= "<strong>" . t("Email") . "</strong>: " . check_plain($entity->mail) . "<br />";
        $msg .= drupal_render(field_attach_view('registration', $entity, 'review_pane'));
      }
    }
  }
  return $msg;
}

/**
 * Commerce checkout pane settings form builder.
 */
function commerce_registration_information_settings_form($checkout_pane) {
  $form = array();

  $form['commerce_registration_product_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Product Registration Title'),
    '#description' => t('The text to populate the fieldset label for a registrant\'s information.') . '<br>'
        . t('Available tokens are [title] for the product title, and [index] for a countable index value.'),
    '#default_value' => variable_get('commerce_registration_product_title', ''),
  );

  $form['commerce_registration_registrant_help'] = array(
    '#type' => 'textarea',
    '#title' => t('Product Registration Fieldset Help Text'),
    '#description' => t('The help text to display to the user entering registration information.'),
    '#default_value' => variable_get('commerce_registration_registrant_help', ''),
  );

  $form['commerce_registration_hide_email_logged_in'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide the Email field for logged in users'),
    '#default_value' => variable_get('commerce_registration_hide_email_logged_in', ''),
  );

  return $form;
}

/**
 * Updates the attached entity with field values.
 *
 * Example $values array:
 * @code
 * $values = array(
 *   'field_passport' => array(
 *     'und' => array(
 *       0 => array('value' => 'MY FIELD VALUE')
 *     )
 *   )
 * );
 * @endcode
 *
 * @param stdClass $entity
 *   The referenced entity to update.
 * @param array $values
 *   Array of values to add to the entity.
 */
function commerce_registration_entity_update_fields(&$entity, $values) {
  if (empty($values)) {
    return;
  }
  foreach ($values as $key => $value) {
    $entity->$key = $value;
  }
}

/**
 * Helper function to create a new registration for a product.
 *
 * @param int $product_id
 * @param string $bundle
 * @param int $order_id
 *
 * @return RegistrationEntity
 */
function commerce_registration_create_product_registration($product_id, $bundle, $order_id) {
  global $user;
  $entity = entity_get_controller('registration')->create(array('type' => $bundle));
  $entity->registration_id = 0;
  $entity->entity_type = 'commerce_product';
  $entity->entity_id = $product_id;
  $entity->created = REQUEST_TIME;
  $entity->updated = REQUEST_TIME;
  $entity->author_uid = $user->uid;
  $entity->order_id = $order_id;
  $entity->count = 1;
  return $entity;
}
