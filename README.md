## License: http://gryftir.mit-license.org/

A simple client to show how to use libcurl with mashape's API

requires libcurl and glib (the latter for unit testing).

to install on ubuntu I believe the following will work

   $ sudo apt-get install libglib2.0-0 libcurl3


Put your mashape.com key in a file called key.txt in the project root to run.  This is necessary for unit testing.

To build:

    $ make

To run tests:

    $ make test

Most Code and thus my Comments are in the get_number-lib.c file



