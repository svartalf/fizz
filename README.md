# Fizz

Fizz is a C based clone of the Twitter Snowflake (https://github.com/twitter/snowflake/), network service for generating unique ID numbers at high scale with some simple guarantees.

## First-level warning

I really don't know how to cook C properly, so you should'nt use this code in a real-life projects without of a full checking of the program working process.

## Installation

Fizz uses `libev` internally, so you should have it's header files for compilation.

Looks like you should do something like this:

    ./autogen.sh
    ./configure
    make

## Usage

    ./fizz [options]

Options:

`-w`, `--worker`: worker ID

`-d`, `--datacenter`: datacenter ID

`-p`, `--port`: port number

Example:

    ./fizz -w 5 -d 251 -p 7953

You can check it with a `nc localhost 7953`
