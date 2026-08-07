<?php
/**
 * @file
 * Admin UI for pwned_passwords.
 */

/**
 * Admin settings form for pwned_passwords
 */
function pwned_passwords_admin_settings($form, &$form_state) {
  $config = config('pwned_passwords.settings');
  $form = array();
  $form['#config'] = 'pwned_passwords.settings';

  $options = array(
    PWNED_PASSWORDS_IGNORE => t('Ignore'),
    PWNED_PASSWORDS_WARN => t('Warn'),
    PWNED_PASSWORDS_BLOCK => t('Block'),
  );
  $hibp_api_link = array(
    '!hibp_api_link' => l(
    t('HIBP API'),
    'https://haveibeenpwned.com/API/v3#PwnedPasswords'),
  );
  $hibp_padding = array(
    '!hibp_padding' => l(
      t('HIBP documentation on padding'),
      'https://www.troyhunt.com/enhancing-pwned-passwords-privacy-with-padding/'),
  );

  $hibp_passwords_link = array(
    '!hibp_passwords_link' => l(
    t('HIBP Passwords'),
    'https://haveibeenpwned.com/Passwords'),
  );

  $form['top'] = array(
    '#markup' => t('Settings for checking passwords with !hibp_passwords_link database.', $hibp_passwords_link),
  );

  $form['policy_wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Policies'),
    '#description' => t('These policies determine the action the module should take when it detects a password that has been compromised in a breach.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['policy_wrapper']['pwned_passwords_hibp_validate_first'] = [
    '#type' => 'checkbox',
    '#title' => t('Validate first with HIBP check?'),
    '#description' => t('Combined with Block policies may reduce user information disclosure risk when HIBP check validate is first. (Default: no)'),
    '#default_value' => $config->get('hibp_validate_first'),
  ];

  $form['policy_wrapper']['pwned_passwords_login_policy'] = array(
    '#type' => 'radios',
    '#title' => t('Login policy'),
    '#description' => 'A compromised password is provided at login. (Default: Warn)',
    '#options' => $options,
    '#default_value' => $config->get('login_policy'),
  );
  $form['policy_wrapper']['pwned_passwords_check_failed_login'] = [
    '#type' => 'checkbox',
    '#title' => t('Check failed login attempts?'),
    '#description' => t('Should the password be checked when the login attempt fails? (Default: no)'),
    '#default_value' => $config->get('check_failed_login'),
  ];
  $form['policy_wrapper']['pwned_passwords_change_policy'] = array(
    '#type' => 'radios',
    '#title' => t('Password change policy'),
    '#description' => 'A compromised password is provided when the user changes their password. (Default: Block)',
    '#options' => $options,
    '#default_value' => $config->get('change_policy'),
  );
  $form['policy_wrapper']['pwned_passwords_register_policy'] = array(
    '#type' => 'radios',
    '#title' => t('Registration policy'),
    '#description' => 'A compromised password is provided when the user registers. (Default: Block)',
    '#options' => $options,
    '#default_value' => $config->get('register_policy'),
  );

  $messages_token_help = t('Available variables are: [pwned_passwords:hibp_link], [pwned_passwords:password_reset].');

  $form['user_messages'] = array(
    '#type' => 'fieldset',
    '#title' => t('User Messages'),
    '#description' => t('Messages displayed to users when compromised passwords are detected.') . '<br />' . $messages_token_help,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['user_messages']['pwned_passwords_message_warning'] = array(
    '#type' => 'textarea',
    '#title' => t('Warning'),
    '#default_value' => _pwned_passwords_message_text('warning', FALSE),
    '#rows' => 3,
  );
  $form['user_messages']['pwned_passwords_message_login_warning'] = array(
    '#type' => 'textarea',
    '#title' => t('Login warning'),
    '#default_value' => _pwned_passwords_message_text('login_warning', FALSE),
    '#rows' => 3,
  );
  $form['user_messages']['pwned_passwords_message_login_blocked'] = array(
    '#type' => 'textarea',
    '#title' => t('Login blocked'),
    '#default_value' => _pwned_passwords_message_text('login_blocked', FALSE),
    '#rows' => 3,
  );
  $form['user_messages']['pwned_passwords_message_register_blocked'] = array(
    '#type' => 'textarea',
    '#title' => t('Registration blocked'),
    '#default_value' => _pwned_passwords_message_text('register_blocked', FALSE),
    '#rows' => 3,
  );
  $form['user_messages']['pwned_passwords_message_change_blocked'] = array(
    '#type' => 'textarea',
    '#title' => t('Password change blocked'),
    '#default_value' => _pwned_passwords_message_text('change_blocked', FALSE),
    '#rows' => 3,
  );

  $form['password_threshold'] = array(
    '#type' => 'fieldset',
    '#title' => t('Password threshold'),
    '#description' => t('The !hibp_api_link responds with a count of how many times a given password appears in the HIBP database. Higher counts indicate more commonly used (/ breached) passwords.', $hibp_api_link),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['password_threshold']['pwned_passwords_password_threshold'] = array(
    '#type' => 'textfield',
    '#title' => t('Threshold'),
    '#description' => t('Passwords with a count above or equal to this threshold will be treated as compromised.'),
    '#default_value' => $config->get('password_threshold'),
  );
  $form['password_threshold']['examples'] = array(
    '#type' => 'item',
    '#title' => t('Examples with count'),
    '#markup' => pwned_passwords_password_threshold_examples(),
  );

  $form['api_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('API settings'),
    '#description' => t('How the module interacts with the !hibp_api_link.', $hibp_api_link),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['api_settings']['pwned_passwords_hibp_api_url'] = array(
    '#type' => 'textfield',
    '#title' => t('HIBP API URL'),
    '#description' => t('URL the module sends API calls to.'),
    '#default_value' => $config->get('hibp_api_url'),
  );
  $form['api_settings']['pwned_passwords_hibp_ua'] = array(
    '#type' => 'textfield',
    '#title' => t('User Agent'),
    '#description' => t('The UA the module sends to the HIBP API.'),
    '#default_value' => $config->get('hibp_ua'),
  );
  $form['api_settings']['pwned_passwords_hibp_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeout'),
    '#description' => t('The timeout setting (in seconds) for API calls.'),
    '#default_value' => $config->get('hibp_timeout'),
  );
  $form['api_settings']['pwned_passwords_hibp_failed_check_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Assume password is bad if check fails'),
    '#description' => t('If a call to the HIBP API fails, should the module treat the password as if it is compromised? (Default: no)'),
    '#default_value' => $config->get('hibp_failed_check_default'),
  );
  $form['api_settings']['pwned_passwords_hibp_add_padding'] = array(
    '#type' => 'checkbox',
    '#title' => t('Ask HIBP API to Add Padding'),
    '#description' => t('See: !hibp_padding (Default: yes)', $hibp_padding),
    '#default_value' => $config->get('hibp_add_padding'),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Submit handler for admin_settings form.
 */
function pwned_passwords_admin_settings_submit($form, $form_state) {
  $values = $form_state['values'];
  $config = config('pwned_passwords.settings');
  $config->set('hibp_validate_first', (bool) $values['pwned_passwords_hibp_validate_first']);
  $config->set('hibp_add_padding', (bool) $values['pwned_passwords_hibp_add_padding']);
  $config->set('hibp_api_url', $values['pwned_passwords_hibp_api_url']);
  $config->set('hibp_timeout', $values['pwned_passwords_hibp_timeout']);
  $config->set('hibp_ua', $values['pwned_passwords_hibp_ua']);
  $config->set('hibp_failed_check_default', (bool) $values['pwned_passwords_hibp_failed_check_default']);
  $config->set('password_threshold', $values['pwned_passwords_password_threshold']);
  $config->set('check_failed_login', (bool) $values['pwned_passwords_check_failed_login']);
  $config->set('login_policy', $values['pwned_passwords_login_policy']);
  $config->set('change_policy', $values['pwned_passwords_change_policy']);
  $config->set('register_policy', $values['pwned_passwords_register_policy']);
  $config->set('message_warning', $values['pwned_passwords_message_warning']);
  $config->set('message_login_warning', $values['pwned_passwords_message_login_warning']);
  $config->set('message_login_blocked', $values['pwned_passwords_message_login_blocked']);
  $config->set('message_register_blocked', $values['pwned_passwords_message_register_blocked']);
  $config->set('message_change_blocked', $values['pwned_passwords_message_change_blocked']);

  $config->save();
  backdrop_set_message(t('Pwned passwords configuration saved.'));
}

/**
 * Provide some example passwords and their HIBP counts.
 *
 * @return string
 *   A themed list of example passwords with HIBP counts.
 */
function pwned_passwords_password_threshold_examples() {
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
      'hfuwe3ty49yfHH**',
    );
    $list = array();
    foreach ($passwords as $password) {
      $list[$password] = (int) pwned_passwords_check_password($password, TRUE);
    }
    arsort($list);
    cache_set(__FUNCTION__, $list, 'cache', CACHE_TEMPORARY);
  }

  $items = array();
  foreach ($list as $password => $count) {
    $items[] = 'Password: "' . $password . '", count: ' . number_format($count);
  }
  return theme('item_list',
    array(
      'items' => $items,
      'title' => '',
      'type' => 'ul',
      'attributes' => array(),
    )
  );
}
