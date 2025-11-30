# Pwned passwords

Have I Been Pwned?

Although, this module is a port of the Drupal 7 [password_haveibeenpwned](https://www.drupal.org/project/password_haveibeenpwned)
module it uses the name of the Drupal 8/9/10 module [pwned_passwords](https://www.drupal.org/project/pwned_passwords)
because the name is shorter and makes the code easier to read and with hope to
preserve future feature parity.

The module provides additional checks/validation for user passwords with Troy
Hunt's excellent service [Have I Been Pwned](https://haveibeenpwned.com/) for
email addresses and [Have I Been Pwned Passwords](https://haveibeenpwned.com/Passwords) for passwords.
For further background see [Wikipedia HIBP](https://en.wikipedia.org/wiki/Have_I_Been_Pwned).

Specifically, the module uses the [HIBP Pwned Passwords V3 API](https://haveibeenpwned.com/API/v3#PwnedPasswords)
to check passwords with only the first five characters of the hash over https.

This port attempts to preserve behavior from the Drupal 7 module while adapting
hook signatures and APIs for Backdrop and uses *backdrop_http_request()*.

The module provides configurable options for *user login*, *registration*, and
*password change* to: block, warn, or ignore the use of compromised ("pwned")
passwords

By default pwned passwords are set to warn on *user login* and blocked on
*registration* or *password change*. These are the same defaults used by the
Drupal 7 module.

There is also a configurable threshold based on the count for each pwned
password returned by the API; higher counts indicate more commonly breached
passwords. The default threshold is 1 unlike with Drupal 7 where it is 10.


## Requirements
- It is not necessary to register for an API at the HIBP website.
- PHP 7.4 or above (Not tested with lower versions).


## Installation

**Please test on a staging server before deploying to production.**

- Install this module using the official Backdrop CMS instructions at
  https://docs.backdropcms.org/documentation/extend-with-modules.

- Visit the configuration page under Administration > Configuration >
User accounts > Pwned Passwords (admin/config/people/pwned_passwords) and enter
the required information.


## Documentation
Additional documentation is located in the Wiki:
https://github.com/backdrop-contrib/pwned_passwords/wiki/Documentation.


## Issues
Bugs and Feature Requests should be reported in the Issue Queue:
https://github.com/backdrop-contrib/pwned_passwords/issues.


## Current Maintainers
- [izmeez](https://github.com/izmeez)
- Seeking additional maintainers


## Credits
- Thanks to [Koen Verheyen](https://github.com/verheyenkoen) for the original implementation.
- Created for Drupal 7 by [mcdruid](https://github.com/mcdruid)
- Ported to Backdrop CMS by [izmeez](https://github.com/izmeez/)


## License
<!--
Mention what license this module is released under, and where people can find
it.
-->

This project is GPL v2 software.
See the LICENSE.txt file in this directory for complete text.
