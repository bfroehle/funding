<?php

/**
 * @file
 * Funding application type editing UI.
 */

/**
 * UI controller.
 */
class FundingApplicationTypeUIController extends EntityDefaultUIController {
  
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage funding applications, including fields.';
    return $items;
  }
}

/**
 * Generates the funding application type editing form.
 */
function funding_application_type_form($form, &$form_state, $funding_application_type, $op = 'edit') {
  if ($op == 'clone') {
    $funding_application_type->label .= ' (cloned)';
    $funding_application_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $funding_application_type->label,
    '#description' => t('The human-readable name of this funding application type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($funding_application_type->type) ? $funding_application_type->type : '',
    '#maxlength' => 32,
    '#disabled' => $funding_application_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'funding_application_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this funding application type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save funding application type'),
    '#weight' => 40,
  );

  if (!$funding_application_type->isLocked() && $op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete funding application type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('funding_application_type_form_submit_delete')
    );
  }
  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function funding_application_type_form_submit(&$form, &$form_state) {
  $funding_application_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  $funding_application_type->save();
  $form_state['redirect'] = 'admin/funding/applications';
}

/**
 * Form API submit callback for the delete button.
 */
function funding_application_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/funding/applications/manage/' . $form_state['funding_application_type']->type . '/delete';
}
