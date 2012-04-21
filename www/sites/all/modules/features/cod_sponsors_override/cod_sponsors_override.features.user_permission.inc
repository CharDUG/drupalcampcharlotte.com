<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function cod_sponsors_override_user_default_permissions() {
  $permissions = array();

  // Exported permission: view imagecache sponsor_logo_white_community
  $permissions['view imagecache sponsor_logo_white_community'] = array(
    'name' => 'view imagecache sponsor_logo_white_community',
    'roles' => array(),
  );

  // Exported permission: view imagecache sponsor_logo_white_gold
  $permissions['view imagecache sponsor_logo_white_gold'] = array(
    'name' => 'view imagecache sponsor_logo_white_gold',
    'roles' => array(),
  );

  // Exported permission: view imagecache sponsor_logo_white_platinum
  $permissions['view imagecache sponsor_logo_white_platinum'] = array(
    'name' => 'view imagecache sponsor_logo_white_platinum',
    'roles' => array(),
  );

  // Exported permission: view imagecache sponsor_logo_white_silver
  $permissions['view imagecache sponsor_logo_white_silver'] = array(
    'name' => 'view imagecache sponsor_logo_white_silver',
    'roles' => array(),
  );

  return $permissions;
}
