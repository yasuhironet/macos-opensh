## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/lib

bin_PROGRAMS = opensh

opensh_SOURCES = \
	opensh.c

noinst_HEADERS = \
	opensh.h

opensh_LDADD = \
	$(top_srcdir)/lib/libzcmdsh.a

