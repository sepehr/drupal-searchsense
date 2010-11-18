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
  
  $form['searchsense']['searchsense_options'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enable autocompletion for'),
    '#default_value' => variable_get('searchsense_options', array(
      'user',
      'block',
      'theme',
    )),
    '#options' => array(
      'user' => t('User search form'),
      'block' => t('Search block form'),
      'theme' => t('Theme search form'),
      'advanced' => t('Advanced search form'),
    ),
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
  
  return $form;
}


/**
 * Validation callback for administration form.
 */
function searchsense_admin_validate($form, &$form_state) {
  if (!ctype_digit($form_state['values']['searchsense_limit'])) {
    form_set_error('searchsense_limit', t('The suggestion list limit value must be numeric.'));
  }
}


/**
 * Submission callback for administration form.
 */
function searchsense_admin_submit($form, &$form_state) {
  variable_set('searchsense_limit', $form_state['values']['searchsense_limit']);
  variable_set('searchsense_options', $form_state['values']['searchsense_options']);
}


