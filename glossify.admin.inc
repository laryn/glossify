<?php

/**
 * @file
 * Glossify Administration
 *
 * @ingroup glossify
 */


/**
 * Form builder for administrative settings.
 */
function glossify_admin_settings() {
  $conf_key = arg(3);
  if (empty($conf_key)) {
    $conf_key = 'global';
  }
  $configurations = variable_get('glossify_configurations', NULL);
  $configuration = $configurations[$conf_key];
  
  $form['config_id'] = array(
    '#type' => 'hidden',
    '#value' => $conf_key,
  );
  
  if ($conf_key !== 'global') {
    $form['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Configuration name'),
      '#description' => t('The name that will be displayed on the tab.'),
      '#default_value' => $conf_key !== 'add' ? $conf_key : '',
    );
  }
  
  $form['from'] = array(
    '#type' => 'select',
    '#title' => t('Content types to be filtered'),
    '#multiple' => TRUE,
    '#options' => node_get_types('names'),
    '#default_value' => $configuration['from'],
    '#description' => t('Glossify looks into their text for keywords and replaces them with links.'),
  );
  
  $form['to'] = array(
    '#type' => 'select',
    '#title' => t('Target content types.'),
    '#multiple' => TRUE,
    '#options' => node_get_types('names'),
    '#default_value' => $configuration['to'],
    '#description' => t('The source(s) for the keywords.'),
  );
  
  $form['style'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Style of glossary terms.'),
    '#options' => array(
      'hovertip' => t('Hovertips'),
      'links'     => t('Links'),
      'reference' => t('Reference section under content'),
    ),
    '#default_value' => isset($configuration['style']) ? $configuration['style'] : array(),
    '#description' => t('How the glossary should be styled. Note: "hovertip" style requires hovertip.module. If you choose anything other than links - it should work but for now it is untested territory - feedback welcome.'),
  );
  
  $form['switches'] = array(
    '#type' => 'fieldset',
    '#title' => t('Switches'),
    '#collapsible' => TRUE,
  );
  
  $form['switches']['only_first'] = array(
    '#type' => 'checkbox',
    '#title' => t('Only link first occurance of term. On by default. If unchecked all occurences are replaced.'),
    '#default_value' => $configuration['only_first'],
  );

  $form['switches']['unicode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Unicode compatibility.'),
    '#default_value' => $configuration['unicode'],
    '#description' => t('If you get php warnings from this setting, try updating your PCRE PHP-library.'),
  );
  
  $form['switches']['break'] = array(
    '#type' => 'checkbox',
    '#title' => t('Check this to NOT break words.'),
    '#default_value' => $configuration['break'],
    '#description' => t('Example: "ship" will not linkify "shipyard", "starship", ...'),
  );
  
  $form['switches']['case_insensitivity'] = array(
    '#type' => 'checkbox',
    '#title' => t('Case insensitivity.'),
    '#default_value' => $configuration['case_insensitivity'],
    '#description' => t('Example: "drupal" will also linkify "Drupal".'),
  );

  $form['switches']['link_self'] = array(
    '#type' => 'checkbox',
    '#title' => t('Link to self.'),
    '#default_value' => $configuration['link_self'],
  );
  
  $form['switches']['language'] = array(
    '#type' => 'checkbox',
    '#title' => t('Link only to same language.'),
    '#default_value' => $configuration['language'],
  );
  
  $form['switches']['teaser'] = array(
    '#type' => 'checkbox',
    '#title' => t('Link content in teaser'),
    '#default_value' => $configuration['teaser'],
    '#description' => t('Currently disfunctional.'),
  );
  
  $form['methods'] = array(
    '#type' => 'fieldset',
    '#title' => t('Methods'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $form['methods']['use_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Make use of the title field of a node.'),
    '#default_value' => $configuration['methods']['use_title'],
  );
  
  $form['methods']['internal'] = array(
    '#type' => 'fieldset',
    '#title' => t('Internal'),
    '#collapsible' => TRUE,
    '#collapsed' => $configuration['methods']['use_internal']? FALSE : TRUE,
  );
  
  $form['methods']['internal']['use_internal'] = array(
    '#type' => 'checkbox',
    '#title' => t('Attach 2 additional fields to the selected Node types.'),
    '#default_value' => $configuration['methods']['use_internal'],
  );
  
  if (!module_exists('content')) {
    $form['methods']['cck'] = array(
      '#value' => t('If you wish to use CCK Fields for your Keywords get the <a href="http://drupal.org/project/cck">CCK module</a>.'),
    );
  }
  else {
    foreach (array_keys(content_fields()) as $key ) {
      $all_cck_field_names[$key] = $key;
    }
    $all_cck_field_names['none'] = 'none';
    
    $form['methods']['cck'] = array(
      '#type' => 'fieldset',
      '#title' => t('CCK'),
      '#collapsible' => TRUE,
      '#collapsed' => $configuration['methods']['use_cck']? FALSE: TRUE,
    );
    
    $form['methods']['cck']['use_cck'] = array(
      '#type' => 'checkbox',
      '#title' => t('Make use of CCK.'),
      '#description' => t('This is mostly here to provide compatibility with older versions, but it can also be used in conjunction with the module-internal fields.'),
      '#default_value' => $configuration['methods']['use_cck'],
    );
    
    $form['methods']['cck']['keyword_field'] = array(
      '#type' => 'select',
      '#title' => t("CCK field to look into for synonyms of the node's title. For more than 1 content type - use the same cck field please."),
      '#options' => $all_cck_field_names,
      '#default_value' => ((isset($configuration['methods']['keyword_field']) || !empty($configuration['methods']['keyword_field'])) ? $configuration['methods']['keyword_field'] : NULL),
      '#description' => t('Select a CCK field for synonyms.'),
    );

    $form['methods']['cck']['override_field'] = array(
      '#type' => 'select',
      '#title' => t("CCK field to look into for a 'target url override'. For more than 1 content type - use the same cck field please."),
      '#options' => $all_cck_field_names,
      '#default_value' => ((isset($configuration['methods']['override_field']) || !empty($configuration['methods']['override_field'])) ? $configuration['methods']['override_field'] : NULL),
      '#description' => t("Select a CCK field for target override.  After you create the cck field and then put something into it
        Example: 'node/34', 'url_alias', 'http://example.com/path' this will make the target url point to your override path."),
    );
  }
  
  if (!module_exists('taxonomy')) {
    $form['methods']['taxonomy'] = array(
      '#value' => t('In order to use a Vocabulary for your Keywords you need to enable the Taxonomy module.'),
    );
  }
  else {
    $vocabularies = array();
    foreach (taxonomy_get_vocabularies() as $vid => $voc) {
      $vocabularies[$vid] = $voc->name;
    }
    
    $form['methods']['taxonomy'] = array(
      '#type' => 'fieldset',
      '#title' => t('Taxonomy'),
      '#collapsible' => TRUE,
      '#collapsed' => $configuration['methods']['use_taxonomy']? FALSE : TRUE,
    );
    
    $form['methods']['taxonomy']['use_taxonomy'] = array(
      '#type' => 'checkbox',
      '#title' => t('Make use of Taxonomy.'),
      '#description' => t('Note that you also have to attach the selected Vocabulary to the selected content types.'),
      '#default_value' => $configuration['methods']['use_taxonomy'],
    );
    
    $form['methods']['taxonomy']['vocabulary'] = array(
      '#type' => 'select',
      '#title' => t("Vocabulary to look into for synonyms of the node's title."),
      '#multiple' => TRUE,
      '#options' => $vocabularies,
      '#default_value' => $configuration['methods']['vocabulary'],
      '#description' => t('Select a Vocabulary for synonyms.'),
    );
    
    $form['methods']['taxonomy']['link_term'] = array(
      '#type' => 'checkbox',
      '#title' => t('Link to term instead of node.'),
      '#default_value' => $configuration['methods']['link_term'],
    );
  }
  
  $form['excl'] = array(
    '#type' => 'fieldset',
    '#title' => t('Exclude/Include'),
    '#collapsible' => TRUE,
    '#collapsed' => empty($configuration['excl_tags'])? TRUE : FALSE,
  );
  
  $form['excl']['excl_mode'] = array(
    '#type' => 'select',
    '#title' => t('Use Exclude- or Include-Method'),
    '#options' => array(t('Exclude'), t('Include')),
    '#default_value' => $configuration['excl_mode'],
  );
  
  $form['excl']['excl_tags'] = array(
    '#type' => 'textarea',
    '#title' => t('Tags to exclude/include.'),
    '#default_value' => $configuration['excl_tags'],
    '#description' => t('One tag per line, or comma seperated.'),
  );
  
  $form['buttons']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration') );
  
  if (in_array($conf_key, array('add','global'))) {
    $form['buttons']['reset'] = array('#type' => 'submit', '#value' => t('Reset to defaults') );
  }
  if ($conf_key !== 'add' && $conf_key !== 'global') {
    $form['buttons']['delete'] = array('#type' => 'submit', '#value' => t('Delete configuration') );
  }

  if (!empty($_POST) && form_get_errors()) {
    drupal_set_message(t('The settings have not been saved because of the errors.'), 'error');
  }
  
  $form['#validate'][] = 'glossify_admin_settings_validate';
  $form['#submit'][] = 'glossify_admin_settings_submit';
  $form['#theme'] = 'system_settings_form';
  return $form;
}


/**
 * Form validation of administrative settings.
 */
function glossify_admin_settings_validate($form, &$form_state) {
  if ($form_state['values']['config_id'] == 'add' && empty($form_state['values']['name'])) {
    form_set_error('name', t('You must specify a name for the configuration'));
  }
  else {
    if ($form_state['values']['config_id'] == 'add' && in_array(strtolower($form_state['values']['name']), array_keys(variable_get('glossify_configurations', array())))) {
      form_set_error('name', t('This configuration name is already in use.'));
    }
  }
  if (count($form_state['values']['from']) < 1) {
    form_set_error('from', t('You need to select at least one "FROM" content type'));
  }
  if (count($form_state['values']['to']) < 1) {
    form_set_error('to', t('You need to select at least one "TO" content type'));
  }
  if ($form_state['values']['use_title'] + $form_state['values']['use_internal'] + $form_state['values']['use_cck'] + $form_state['values']['use_taxonomy'] == 0) {
    form_set_error('methods', t('You need to select at least one Method.'));
  }
  if (empty($form_state['values']['style']['hovertip']) && empty($form_state['values']['style']['links']) && empty($form_state['values']['style']['reference'])) {
    form_set_error('styles', t('You need to select at least one Style.'));
  }
  
}

 
/**
 * Form evaluation of administrative settings.
 */
function glossify_admin_settings_submit($form, &$form_state) {
  $configurations = variable_get('glossify_configurations', array());
  $goto = 'admin/settings/glossify';
  if ($form_state['clicked_button']['#value'] == t('Delete configuration') && $form_state['values']['config_id'] !== 'global') {
    unset($configurations[$form_state['values']['name']]);
  }
  else {
    $methods = array(
      'use_title' => $form_state['values']['use_title'],
      'use_internal' => $form_state['values']['use_internal'],
      'use_cck' => $form_state['values']['use_cck'],
      'keyword_field' => $form_state['values']['keyword_field'],
      'override_field' => $form_state['values']['override_field'],
      'use_taxonomy' => $form_state['values']['use_taxonomy'],
      'vocabulary' => $form_state['values']['vocabulary'],
      'link_term' => $form_state['values']['link_term'],
    );
    $configuration = array(
      'from' => $form_state['values']['from'],
      'to' => $form_state['values']['to'],
      'only_first' => $form_state['values']['only_first'],
      'unicode' => $form_state['values']['unicode'],
      'teaser' => $form_state['values']['teaser'],
      'style' => $form_state['values']['style'],
      'link_self' => $form_state['values']['link_self'],
      'case_insensitivity' => $form_state['values']['case_insensitivity'],
      'break' => $form_state['values']['break'],
      'language' => $form_state['values']['language'],
      'excl_mode' => $form_state['values']['excl_mode'],
      'excl_tags' => $form_state['values']['excl_tags'],
      'methods' => $methods,
    );
    $name = empty($form_state['values']['name']) ? 'global' : $form_state['values']['name'];
    if (isset($configurations[$name])) {
      $last_methods = $configurations[$name]['methods'];
      $methods_to_update = array();
      if ($last_methods['use_title'] !== $methods['use_title']) {
        $methods_to_update['title'] = $methods['use_title'];
        drupal_set_message('Title-keywords were updated.', 'status');
      }
      if ($last_methods['use_internal'] !== $methods['use_internal']) {
        $methods_to_update['internal'] = $methods['use_internal'];
        drupal_set_message('Internal-keywords were updated.', 'status');
      }
      if (($last_methods['use_cck'] !== $methods['use_cck']) || ($last_methods['keyword_field'] !== $methods['keyword_field']) || ($last_methods['override_field'] !== $methods['override_field'])) {
        $methods_to_update['cck'] = array('use_cck' => $methods['use_cck'], 'keyword_field' => $methods['keyword_field'], 'override_field' => $methods['override_field']);
        drupal_set_message('CCK-keywords were updated.', 'status');
      }
      if (($last_methods['use_taxonomy'] !== $methods['use_taxonomy']) || ($last_methods['vocabulary'] !== $methods['vocabulary']) || ($last_methods['link_term'] !== $methods['link_term'])) {
        $methods_to_update['taxonomy'] = array('use_taxonomy' => $methods['use_taxonomy'], 'vocabulary' => $methods['vocabulary']);
        drupal_set_message('Taxonomy-keywords were updated.', 'status');
      }
      if (count($methods_to_update) > 0) {
        unset($configurations[$name]);
        _update_keywords_for_methods($configuration['to'], $methods_to_update, $name);
      }
    }
    $configurations[$name] = $configuration;
    $goto .= "/$name" ;
  }
  variable_set('glossify_configurations', $configurations);
  menu_rebuild();
  cache_clear_all('*', 'cache_filter', TRUE);
  drupal_goto($goto);
}