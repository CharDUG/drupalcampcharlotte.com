<?php
/**
 * @file
 * Realname module support list.
 */

function realname_supported_modules() {
  $list = array(
    'content_profile' => array(
      'name' => 'Content Profile',
      'types' => TRUE,
      ),
    'profile' => array(
      'name' => 'Core Profile',
      'types' => FALSE,
      ),
    );
  return $list;
}
