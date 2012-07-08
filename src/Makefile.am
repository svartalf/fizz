AUTOMAKE_OPTIONS = foreign

CFLAGS=-std=c99 -Wall -I/usr/include -DVERSION=\"$(VERSION)\" -DPROG="\"$(PACKAGE)\""
LDFLAGS=-L/usr/lib -lev

bin_PROGRAMS = fizz
fizz_SOURCES = generator.c server.c main.c