<?php

/**
 * Implementation of hook_default_stylizer_alter().
 */
function features_override_default_stylizer_alter(&$items) {
  features_override_features_default_alter($items, "stylizer");
}
