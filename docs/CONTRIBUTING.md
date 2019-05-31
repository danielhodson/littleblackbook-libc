# CONTRIBUTING

Welcome! It's great to have your interest in contributing to the LBB-libc.
There are any number of ways to contribute to the project including updating
documentation, creating artwork, adding new unit tests and targets, or simply filing a bug
report.

In time we will improve the contributing documentation for examples, but for the time
being feel free to just create issues as you feel are needed.
If contributing code please create a feature branch and issue a pull request.

# ROADMAP

This is mostly a wish list of things that are still to be done.
It's not formal and in the future these may be moved into github issues:

* Vagrant updates:
  * Introduce packer templates for building QEMU boxes.
  * Update Vagrant to support QEMU targets.
* Ansible Updates:
  * Support a dynamic inventory for target management
  * Improve group management for what combinations of libc/compiler/platform are used
  * Improve roles so they are platform agnostic - they should make use of tags etc
  * Improve variable management
* Target support:
  * Actually support non-linux/ubuntu targets!!
* Unit Tests:
  * Make use of CTest for building and running unit tests.
  * Make use of CDash for having a dashboard of test results.
  * Create a test library to support common actions like file descriptor redirection,
  signal handling, turning on/off specific tests, and so on.