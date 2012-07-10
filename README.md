Fizz
=====

Fizz is a C based clone of the Twitter Snowflake (https://github.com/twitter/snowflake/), network service for generating unique ID numbers at high scale with some simple guarantees.

First-level warning
--------------------
I really don't know how to cook C properly, so you should'nt use this code in a real-life projects without of a full checking of the program working process.

Installation
-------------

Fizz uses `libev` internally, so you should have it's header files for compilation.

Looks like you should do something like this:

    ./autogen.sh
    ./configure
    make

Usage
------

    ./fizz worker-id datacenter-id

Example:

    ./fizz 2 125

Both parameters must be an unsigned integers. Currently, fizz binds itself on the port 7000.
You can check it with a `nc localhost 7000`
