<?php
// $Id$

/**
 * @file
 * Searchsense administration callbacks.
 */

/**
 * Form callback for administration form.
 */
function searchsense_admin() {
  $form = array();
  
  $form['searchsense'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search Autocompletion'),
  );
  
  $form['searchsense']['searchsense_block_search'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable autocompletion for search block.'),
    '#default_value' => variable_get('searchsense_block_search', 1),
    '#return_value' => 1,
  );

  $form['searchsense']['searchsense_theme_search'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable autocompletion on theme search form.'),
    '#default_value' => variable_get('searchsense_theme_search', 1),
    '#return_value' => 1,
  );

  $form['searchsense']['searchsense_advanced_search'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable autocompletion on advanced search form.'),
    '#default_value' => variable_get('searchsense_advanced_search', 1),
    '#return_value' => 1,
  );

  $form['searchsense']['searchsense_user_search'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable autocompletion on user search form.'),
    '#default_value' => variable_get('searchsense_user_search', 1),
    '#return_value' => 1,
  );

  $form['searchsense']['searchsense_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of suggestions'),
    '#default_value' => variable_get('searchsense_limit', 10),
  );
  
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  
  $form['buttons']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset to defaults'),
  );
  
  return $form;
}


/**
 * Validation callback for administration form.
 */
function searchsense_admin_settings_validate($form, &$form_state) {
  if (!ctype_digit($form_state['values']['searchsense_limit'])) {
    form_set_error('searchsense_limit', t('The suggestion list limit value must be numeric.'));
  }
}


/**
 * Submission callback for administration form.
 */
function searchsense_admin_settings_submit($form, &$form_state) {
  foreach ($form_state['values']['searchsense'] as $key => $value) {
    variable_set($key, $value);
  }
}


