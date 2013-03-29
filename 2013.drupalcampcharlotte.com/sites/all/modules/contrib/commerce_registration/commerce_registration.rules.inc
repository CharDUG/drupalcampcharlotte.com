<?php
/**
 * @file
 * Commerce Registration rules file.
 */

/**
 * Implements hook_rules_condition_info().
 */
function commerce_registration_rules_condition_info() {
  $conditions = array();

  $conditions['commerce_registration_order_has_registration'] = array(
    'label' => t('Line Item product is register enabled.'),
    'group' => t('Commerce Registration'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_line_item',
        'label' => t('Commerce Line Item'),
        'description' => t('The Commerce Line Item that should be checked for a register enabled product.'),
      ),
    ),
  );
  $conditions['commerce_registration_item_has_registration_capacity'] = array(
    'label' => t('Product is available for registration'),
    'group' => t('Commerce Registration'),
    'parameter' => array(
      'commerce_line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('Commerce Line Item'),
        'description' => t('The Commerce Line Item containing the product to check if registrations are available. Checks open date, closing date, and capacity.'),
      ),
    ),
    'callbacks' => array(
      'execute' => 'commerce_registration_item_can_register',
    ),
  );

  return $conditions;
}

/**
 * Implements hook_rules_action_info().
 */
function commerce_registration_rules_action_info() {
  $actions = array();

  $actions['commerce_registration_set_state'] = array(
    'label' => t('Set all Registrations to a specific state'),
    'group' => t('Commerce Registration'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Commerce Order'),
        'description' => t('All registrations on this order will have their state changed.'),
      ),
      'registration_state' => array(
        'type' => 'list<integer>',
        'label' => t('Registration State'),
        'description' => t('Registrations will be set to this state.'),
        'options list' => 'commerce_registration_get_states',
      ),
    ),
  );

  return $actions;
}

/**
 * @defgroup commerce_registration_rules_conditions Rules Conditions
 * @{
 * Condition callbacks for Commerce Registration rules.
 */

/**
 * Condition callback.
 *
 * Checks the commerce line item to see if the product is register enabled.
 *
 * @param CommerceLineItem $line_item
 *   The Commerce Line Item to check for a register enabled product.
 *
 * @return bool
 *   Boolean TRUE if the line item product is register enabled.
 */
function commerce_registration_order_has_registration($line_item) {
  $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
  if (!in_array($line_item_wrapper->type->value(), commerce_product_line_item_types())) {
    return FALSE;
  }
  $id = $line_item_wrapper->commerce_product->product_id->value();
  $settings = registration_entity_settings('commerce_product', $id);
  return !empty($settings);
}

/**
 * Condition callback.
 *
 * Checks if the line item product has registration capacity left. Capacity is
 * only taken if an order is paid for in full.
 *
 * @param CommerceLineItem $line_item
 *   Commerce Line Item to check the product for registration capacity.
 *
 * @return bool
 *   Boolean TRUE if the product has registration capacity.
 */
function commerce_registration_item_can_register($line_item) {
  $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
  if (!in_array($line_item_wrapper->type->value(), commerce_product_line_item_types())) {
    return FALSE;
  }
  $id = $line_item_wrapper->commerce_product->product_id->value();
  $settings = registration_entity_settings('commerce_product', $id);
  if (empty($settings)) {
    return FALSE;
  }
  $room = (int) $settings['capacity'];
  if ($room != 0) {
    $room -= (int) registration_event_count('commerce_product', $id);
  }
  $room = ($settings['capacity'] == 0 ? TRUE : ($room > 0 ? TRUE : FALSE));
  return ($settings['status'] == 1 && $room);
}

/**
 * @} End of "defgroup commerce_registration_rules_conditions".
 */

/**
 * @defgroup commerce_registration_rules_actions Rules Actions
 * @{
 * Action callbacks for Commerce Registration rules.
 */

/**
 * Action callback.
 *
 * Sets all registrations on an order to a given state.
 */
function commerce_registration_set_state($order, $registration_state) {
  $regs = db_select('registration', 'r')
    ->fields('r')
    ->condition('order_id', $order->order_id)
    ->execute();
  foreach ($regs as $row) {
    $registration = registration_load($row->registration_id);
    $key = array_keys($registration_state);
    $registration->state = (int) $registration_state[$key[0]];
    registration_save($registration);
  }
}

/**
 * @} End of "defgroup commerce_registration_rules_actions".
 */

/**
 * Rules helper. Return options list of registration states.
 */
function commerce_registration_get_states() {
  $states = registration_states();
  foreach ($states as $id => $state) {
    $options[$id] = $state->label;
  }
  return $options;
}
