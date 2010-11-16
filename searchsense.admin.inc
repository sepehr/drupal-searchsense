<?php
// $Id$

/**
 * @file
 * Searchsense administration callbacks.
 */

/**
 * Form callback for administration form.
 */
function searchsense_admin_settings() {
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

  $form['searchsense_submodule_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['searchsense_submodule_settings'] = array_merge($form['searchsense_submodule_settings'], module_invoke_all('searchsense_settings'));
  
  return system_settings_form($form);
}


/**
 * Validation callback for administration form.
 */
function searchsense_admin_settings_validate($form, &$form_state) {
  if (!ctype_digit($form_state['values']['searchsense_limit'])) {
    form_set_error('searchsense_limit', t('The suggestion limit value must be numeric.'));
  }
}

