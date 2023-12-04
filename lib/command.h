
/*
 * Copyright (C) 2007-2023 Yasuhiro Ohara.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __COMMAND_H__
#define __COMMAND_H__

#define COMMAND_WORD_DELIMITERS " "
#define COMMAND_HELP_DELIMITERS "\n"

typedef void (*command_func_t) (void *context, int argc, char **argv);

struct command_node
{
  char *cmdstr;
  char *helpstr;
  command_func_t func;
  char *cmdmem;
  char *helpmem;

  struct vector *cmdvec;
};

struct command_set
{
  struct command_node *root;
};

struct command_header
{
  char *cmdstr;
  char *helpstr;
  command_func_t cmdfunc;
};

#define DEFINE_COMMAND(cmdname, cmdstr, helpstr)             \
  void cmdname ## _func (void *context, int argc, char **argv); \
  struct command_header cmdname ## _cmd =                    \
  {                                                          \
    cmdstr,                                                  \
    helpstr,                                                 \
    cmdname ## _func                                         \
  };                                                         \
  void cmdname ## _func (void *context, int argc, char **argv)

#define ALIAS_COMMAND(aliasname, cmdname, cmdstr, helpstr)   \
  struct command_header aliasname ## _cmd =                  \
  {                                                          \
    cmdstr,                                                  \
    helpstr,                                                 \
    cmdname ## _func                                         \
  };                                                         \

#define INSTALL_COMMAND(cmdset, cmdname)                     \
  command_install (cmdset, cmdname ## _cmd.cmdstr,           \
                   cmdname ## _cmd.helpstr, cmdname ## _cmd.cmdfunc)

#define INSTALL_COMMAND2(cmdset, cmdname)                     \
  command_install2 (cmdset, cmdname ## _cmd.cmdstr,           \
                    cmdname ## _cmd.helpstr, cmdname ## _cmd.cmdfunc)

#define EXTERN_COMMAND(cmdname) \
  extern struct command_header cmdname ## _cmd

struct command_set *command_set_create ();
void command_set_delete (struct command_set *cmdset);

int is_command_match (char *spec, char *word);

void
command_install (struct command_set *cmdset,
                 char *command_line,
                 char *help_string,
                 command_func_t func);
void
command_install2 (struct command_set *cmdset,
                  char *command_line,
                  char *help_string,
                  command_func_t func);

int
command_execute (char *command_line, struct command_set *cmdset,
                 void *context);

char *
command_complete (char *command_line, int point,
                  struct command_set *cmdset);

struct command_node *
command_match_node (char *command_line, struct command_set *cmdset);

int file_spec (char *spec);
void file_ls_candidate (FILE *terminal, char *file_path);

void command_config_add (struct vector *config, int argc, char **argv);
void command_config_clear (struct vector *config);
void command_config_write (struct vector *config, FILE *fp);

#define NODE_SPEC "<0-4294967295>"
#define NODE_SPEC_HELP_STR "specify node id.\n"

#define ROUTING_ALGORITHM_HELP_STR "calculate routing using algorithm.\n"

#define IMPORT_HELP "import information\n"
#define EXPORT_HELP "export information\n"

#endif /*__COMMAND_H__*/
