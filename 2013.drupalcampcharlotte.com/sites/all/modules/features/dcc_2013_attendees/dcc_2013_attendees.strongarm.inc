<?php
/**
 * @file
 * dcc_2013_attendees.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function dcc_2013_attendees_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_default';
  $strongarm->value = 'sites/all/themes/dcc2013/img/user-picture-mask-default.png';
  $export['user_picture_default'] = $strongarm;

  return $export;
}
