<?php

/**
 * Implements hook_views_pre_render().
 * Add jQuery to render user pictures tinted overlay.
 */
function dcc2013_views_pre_render(&$view) {
  if ($view->name == 'dcc_2013_attendees') {
    drupal_add_js(path_to_theme() . '/scripts/user-pictures.js');
  }
}
