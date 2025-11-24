# Pwned passwords

Have I Been Pwned?

This is a Backdrop port of the Drupal 7 password_haveibeenpwned module
from the Drupal 7.x-2.1 release. The name has been changed to pwned_passwords
the name used for the Drupal 8/9 module for brevity and readability.

This module adds additional checks/validation for user passwords against the
Have I Been Pwned - Pwned Passwords API ( https://haveibeenpwned.com/Passwords )

This port attempts to preserve behavior from the D7 module while adapting
hook signatures and APIs for Backdrop and uses backdrop_http_request() if
available, otherwise falls back to cURL.

This module checks user passwords using Troy Hunt's excellent Have I Been Pwned
(HIBP) service.

Specifically, it uses the Pwned Passwords V3 API which means that only the first
five characters of the hash of each password is checked using the HIBP API
(over https).

The module has configurable options for login, registration, and password change.
Options can block the use of compromised ("pwned") passwords, emit a warning,
or do nothing (ignore). By default pwned passwords are blocked at login,
registration or password change.

There is also a configurable threshold based on the count for each pwned
password returned by the API; higher counts indicate more commonly breached
passwords.

** Please test on a staging server before deploying to production.

Requirements:
-------------
- PHP 7.4 (Not tested with lower versions)
- Backdrop 1.x
- It is not necessary to register for an API at the HIBP website.

Instructions:
-------------
- Install and enable the module.
- Check the Configuration page to setup.

Credits:
--------
- Thanks to [Koen Verheyen](https://www.drupal.org/u/koen-verheyen) for the
  original implementation.
- Created for Drupal 7 by [mcdruid](https://www.drupal.org/u/mcdruid)
- Ported to Backdrop by [izmeez](https://github.com/izmeez/)
