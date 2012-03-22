<?php

/**
 * Impements hook_preprocess_page();
 *
 * If the user is registered this will add the "registered" class to the 
 * body tag. Pretty much if a user has an account they are registered
 * for the camp, so we don't have to worry about querying the uc_signup
 * tables for this info.
 */
function hornet_preprocess_page(&$vars) {
  global $user;

  if ($user->uid) {
    $vars['body_classes'] .= ' registered';
  }
}

