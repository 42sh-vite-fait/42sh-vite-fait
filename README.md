# 42sh-posix [![Build Status](https://travis-ci.org/itheof/42sh-posix.svg?branch=master)](https://travis-ci.org/itheof/42sh-posix)

This is an attempt to create a fully POSIX compliant shell.

### Compilation guide

Clone and initialize the repository:
```bash
$> git clone http://github.com/itheof/42sh-posix.git
$> git submodule update --init --recursive
```

Make the program to debug it and run the tests:
```bash
$> make SAN=yes DEBUG=yes check
```

Or make it for performances:
```bash
$> make PROD=yes
```
