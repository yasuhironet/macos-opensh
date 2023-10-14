## Process this file with automake to produce Makefile.in

SUBDIRS = lib app

INCLUDES = -I$(top_srcdir) -I$(top_srcdir)/lib

noinst_PROGRAMS = zcmdsh

zcmdsh_SOURCES = \
	zcmdsh.c

noinst_HEADERS = \
	includes.h

zcmdsh_LDADD = \
	lib/libzcmdsh.a

