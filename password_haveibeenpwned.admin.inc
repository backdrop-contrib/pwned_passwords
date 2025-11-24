<?php

/**
 * @file
 * Admin UI for password_haveibeenpwned.
 */

/**
 * Admin settings form for Password Have I Been Pwned?
 */
function password_haveibeenpwned_admin_settings($form, &$form_state) {
  $config = config('password_haveibeenpwned.settings');
  $form = array();
  $form['#config'] = 'password_haveibeenpwned.settings';

  $options = array(
    PASSWORD_HAVEIBEENPWNED_IGNORE => t('Ignore'),
    PASSWORD_HAVEIBEENPWNED_WARN => t('Warn'),
    PASSWORD_HAVEIBEENPWNED_BLOCK => t('Block'),
  );
  $hibp_api = array(
    '!hibp_api' => l(
    t('HIBP API'),
    'https://haveibeenpwned.com/API/v3#PwnedPasswords'),
  );
  $hibp_padding = array(
    '!hibp_padding' => l(
      t('HIBP documentation on padding'),
      'https://www.troyhunt.com/enhancing-pwned-passwords-privacy-with-padding/'),
  );

  $form['policy_wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Policies'),
    '#description' => t('These policies determine the action the Password Have I Been Pwned? module should take when it detects a password which has been compromised in a breach.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['policy_wrapper']['password_haveibeenpwned_login_policy'] = array(
    '#type' => 'radios',
    '#title' => t('Login policy'),
    '#description' => 'A compromised password is provided at login. (Default: Warn)',
    '#options' => $options,
    '#default_value' => $config->get('password_haveibeenpwned_login_policy'),
  );
  $form['policy_wrapper']['password_haveibeenpwned_check_failed_login'] = [
    '#type' => 'checkbox',
    '#title' => t('Check failed login attempts?'),
    '#description' => t('Should the password be checked when the login attempt fails? (Default: no)'),
    '#default_value' => $config->get('password_haveibeenpwned_check_failed_login'),
  ];
  $form['policy_wrapper']['password_haveibeenpwned_change_policy'] = array(
    '#type' => 'radios',
    '#title' => t('Password change policy'),
    '#description' => 'A compromised password is provided when the user changes their password. (Default: Block)',
    '#options' => $options,
    '#default_value' => $config->get('password_haveibeenpwned_change_policy'),
  );
  $form['policy_wrapper']['password_haveibeenpwned_register_policy'] = array(
    '#type' => 'radios',
    '#title' => t('Registration policy'),
    '#description' => 'A compromised password is provided when the user registers. (Default: Block)',
    '#options' => $options,
    '#default_value' => $config->get('password_haveibeenpwned_register_policy'),
  );

  $messages_token_help = t('Available variables are: [password_haveibeenpwned:hibp_link], [password_haveibeenpwned:password_reset].');

  $form['user_messages'] = array(
    '#type' => 'fieldset',
    '#title' => t('User Messages'),
    '#description' => t('Messages displayed to users when compromised passwords are detected.') . '<br />' . $messages_token_help,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['user_messages']['password_haveibeenpwned_message_warning'] = array(
    '#type' => 'textarea',
    '#title' => t('Warning'),
    '#default_value' => _password_haveibeenpwned_message_text('warning', FALSE),
    '#rows' => 3,
  );
  $form['user_messages']['password_haveibeenpwned_message_login_warning'] = array(
    '#type' => 'textarea',
    '#title' => t('Login warning'),
    '#default_value' => _password_haveibeenpwned_message_text('login_warning', FALSE),
    '#rows' => 3,
  );
  $form['user_messages']['password_haveibeenpwned_message_login_blocked'] = array(
    '#type' => 'textarea',
    '#title' => t('Login blocked'),
    '#default_value' => _password_haveibeenpwned_message_text('login_blocked', FALSE),
    '#rows' => 3,
  );
  $form['user_messages']['password_haveibeenpwned_message_register_blocked'] = array(
    '#type' => 'textarea',
    '#title' => t('Registration blocked'),
    '#default_value' => _password_haveibeenpwned_message_text('register_blocked', FALSE),
    '#rows' => 3,
  );
  $form['user_messages']['password_haveibeenpwned_message_change_blocked'] = array(
    '#type' => 'textarea',
    '#title' => t('Password change blocked'),
    '#default_value' => _password_haveibeenpwned_message_text('change_blocked', FALSE),
    '#rows' => 3,
  );

  $form['password_threshold'] = array(
    '#type' => 'fieldset',
    '#title' => t('Password threshold'),
    '#description' => t('The !hibp_api responds with a count of how many times a given password appears in the HIBP database. Higher counts indicate more commonly used (/ breached) passwords.', $hibp_api),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['password_threshold']['password_haveibeenpwned_password_threshold'] = array(
    '#type' => 'textfield',
    '#title' => t('Threshold'),
    '#description' => t('Passwords with a count above this threshold will be treated as compromised.'),
    '#default_value' => $config->get('password_haveibeenpwned_password_threshold'),
  );
  $form['password_threshold']['examples'] = array(
    '#type' => 'item',
    '#title' => 'Examples',
    '#markup' => password_haveibeenpwned_password_threshold_examples(),
  );

  $form['api_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('API settings'),
    '#description' => t('How the module interacts with the !hibp_api.', $hibp_api),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['api_settings']['password_haveibeenpwned_api_url'] = array(
    '#type' => 'textfield',
    '#title' => t('HIBP API URL'),
    '#description' => t('URL the module sends API calls to.'),
    '#default_value' => $config->get('password_haveibeenpwned_api_url'),
  );
  $form['api_settings']['password_haveibeenpwned_ua'] = array(
    '#type' => 'textfield',
    '#title' => t('User Agent'),
    '#description' => t('The UA the module sends to the HIBP API.'),
    '#default_value' => $config->get('password_haveibeenpwned_ua'),
  );
  $form['api_settings']['password_haveibeenpwned_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeout'),
    '#description' => t('The timeout setting (in seconds) for API calls.'),
    '#default_value' => $config->get('password_haveibeenpwned_timeout'),
  );
  $form['api_settings']['password_haveibeenpwned_failed_check_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Assume password is bad if check fails'),
    '#description' => t('If a call to the HIBP API fails, should the module treat the password as if it is compromised? (Default: no)'),
    '#default_value' => $config->get('password_haveibeenpwned_failed_check_default'),
  );
  $form['api_settings']['password_haveibeenpwned_add_padding'] = array(
    '#type' => 'checkbox',
    '#title' => t('Ask HIBP API to Add Padding'),
    '#description' => t('See: !hibp_padding (Default: yes)', $hibp_padding),
    '#default_value' => $config->get('password_haveibeenpwned_add_padding'),
  );

  return system_settings_form($form);
}

/**
 * Provide some example passwords and their HIBP counts.
 *
 * @return string
 *   A themed list of example passwords with HIBP counts.
 */
function password_haveibeenpwned_password_threshold_examples() {
  if ($cache = cache_get(__FUNCTION__)) {
    $list = $cache->data;
  }
  else {
    $passwords = array(
      '12345',
      'monkey',
      'cheese',
      'changeme',
      'dictionary',
      '!@#$%^&',
      'qwerty',
      'admin',
      'backdrop',
      'correcthorsebatterystaple',
      'phprules',
      'joomla12345',
      '1wordpress',
      'ohnoes!!',
    );
    $list = array();
    foreach ($passwords as $password) {
      $list[$password] = (int) password_haveibeenpwned_check_password($password, TRUE);
    }
    arsort($list);
    cache_set(__FUNCTION__, $list, 'cache', CACHE_TEMPORARY);
  }

  $items = array();
  foreach ($list as $password => $count) {
    $items[] = 'Password: "' . $password . '", count: ' . number_format($count);
  }
  return theme_item_list(
    array(
    'items' => $items,
    'title' => '',
    'type' => 'ul',
    'attributes' => array(),
  )
  );
}
