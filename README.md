## License: http://gryftir.mit-license.org/

A simple client to show how to use libcurl with [mashape and the number fact API](https://www.mashape.com/divad12/numbers-1#!documentation)

requires libcurl and glib (the latter for unit testing).

I always use valgrind, and thus make test runs valgrind on my program, but feel free to comment out.

to install on ubuntu I believe the following will work

    $ sudo apt-get install libglib2.0-0 libcurl3


Put your mashape.com key in a file called key.txt in the project root to run.  This is necessary for running the program, and also for running the unit tests.


To build:

    $ make

To run tests:

    $ make test

Most Code and thus my Comments are in the get_number-lib.c file



