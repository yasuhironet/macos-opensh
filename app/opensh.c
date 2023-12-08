
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

#include <includes.h>

#include "termio.h"
#include "vector.h"
#include "shell.h"
#include "command.h"
#include "command_shell.h"
#include "debug_cmd.h"

#include "shell_fselect.h"

void
opensh_shell_keyfunc_ctrl_d (struct shell *shell)
{
  if (shell->cursor == 0 && shell->end == 0)
    {
      (*exit_cmd.cmdfunc) ((void *)shell, 1, (char **)"exit");
      return;
    }

  /* Delete one character */
  if (shell->cursor < shell->end)
    shell_delete_string (shell, shell->cursor, shell->cursor + 1);
}

void
shell_set_prompt_cwd (struct shell *shell)
{
  char buf[MAXPATHLEN];
  char prompt[MAXPATHLEN * 2];

  getcwd (buf, sizeof (buf));
  snprintf (prompt, sizeof (prompt), "[%s]> ", buf);

  shell_set_prompt (shell, prompt);
}

DEFINE_COMMAND (chdir,
               "(cd|chdir) (|<FILENAME>)",
               "change current working directory.\n"
               "change current working directory.\n"
               "filename\n")
{
  int ret = 0;
  struct shell *shell = (struct shell *) context;
  char *target;

  if (argc > 1)
    {
      target = argv[1];
      fprintf (shell->terminal, "chdir: %s\n", target);
    }
  else
    {
      target = getenv ("HOME");
      fprintf (shell->terminal, "chdir: home: %s\n", target);
    }

  ret = chdir (target);
  if (ret)
    fprintf (shell->terminal, "chdir failed: %s\n", strerror (errno));

  shell_set_prompt_cwd (shell);
}

DEFINE_COMMAND (pwd,
               "pwd",
               "print current working directory.\n")
{
  struct shell *shell = (struct shell *) context;
  char buf[MAXPATHLEN];
  getcwd (buf, sizeof (buf));
  fprintf (shell->terminal, "cwd: %s\n", buf);
}

DEFINE_COMMAND (list,
               "(ls|list) (|<FILENAME>)",
               "list files in the directory.\n"
               "list files in the directory.\n"
               "directory name\n")
{
  struct shell *shell = (struct shell *) context;
  char buf[MAXPATHLEN], dir[MAXPATHLEN];
  if (argc > 1)
    snprintf (buf, sizeof (buf), "%s", argv[1]);
  else
    getcwd (buf, sizeof (buf));
  snprintf (dir, sizeof (dir), "%s/", buf);
  fprintf (shell->terminal, "dir: %s\n", dir);
  file_ls_candidate (shell->terminal, dir);
}

DEFINE_COMMAND (open,
               "open <FILENAME>",
               "open.\n"
               "filename\n")
{
  struct shell *shell = (struct shell *) context;
  char command[1024];
  char *filename;

  filename = strstr (shell->command_line, argv[1]);
  if (! filename)
    {
      fprintf (shell->terminal, "something went wrong.\n");
      return;
    }

  snprintf (command, sizeof (command), "open \"%s\"", filename);
  system (command);
}

DEFINE_COMMAND (terminal,
               "terminal",
               "open a new terminal window.\n")
{
  struct shell *shell = (struct shell *) context;
  char command[1024];

  snprintf (command, sizeof (command),
            "osascript -e \"tell app \\\"Terminal\\\""
            " to do script \\\"cd $PWD\\\"\"");
  fprintf (shell->terminal, "system: %s\n", command);
  system (command);
}

DEFINE_COMMAND (launch_shell,
               "launch shell (|sh|bash|csh|dash|ksh|tcsh|zsh)",
               "launch a command.\n"
               "launch a shell.\n"
               "launch a system shell: check /private/var/select/sh.\n"
               "launch a bash shell.\n"
               "launch a csh shell.\n"
               "launch a dash shell.\n"
               "launch a ksh shell.\n"
               "launch a tcsh shell.\n"
               "launch a zsh shell.\n"
               )
{
  struct shell *shell = (struct shell *) context;
  char command[1024];

  if (argc > 2)
    snprintf (command, sizeof (command), "%s", argv[2]);
  else
    snprintf (command, sizeof (command), "%s", getenv ("SHELL"));

  termio_reset ();
  fprintf (shell->terminal, "system: %s\n", command);
  system (command);
  fprintf (shell->terminal, "system: done: %s\n", command);
  termio_start ();
}

DEFINE_COMMAND (edit_vi,
               "(vi|vim) <FILENAME>",
               "edit a file with vi.\n"
               "edit a file with vim.\n"
               "filename\n")
{
  struct shell *shell = (struct shell *) context;
  char command[1024];
  char *filename;

  filename = strstr (shell->command_line, argv[1]);
  if (! filename)
    {
      fprintf (shell->terminal, "something went wrong.\n");
      return;
    }

  snprintf (command, sizeof (command), "%s \"%s\"", argv[0], filename);

  termio_reset ();
  fprintf (shell->terminal, "system: %s\n", command);
  system (command);
  fprintf (shell->terminal, "system: done: %s\n", command);
  termio_start ();
}

int
main (int argc, char **argv)
{
  struct shell *shell;

  debug_cmd_init ();

  command_shell_init ();

  shell = command_shell_create ();
  shell_set_prompt_cwd (shell);
  shell_set_terminal (shell, 0, 1);

  INSTALL_COMMAND2 (shell->cmdset, chdir);
  INSTALL_COMMAND2 (shell->cmdset, list);

  INSTALL_COMMAND2 (shell->cmdset, debug);
  INSTALL_COMMAND2 (shell->cmdset, show_debug);

  INSTALL_COMMAND (shell->cmdset, pwd);
  INSTALL_COMMAND (shell->cmdset, open);
  INSTALL_COMMAND2 (shell->cmdset, terminal);
  INSTALL_COMMAND2 (shell->cmdset, launch_shell);
  INSTALL_COMMAND2 (shell->cmdset, edit_vi);

  shell_install (shell, '>', fselect_keyfunc_start);
  shell_install (shell, CONTROL ('D'), opensh_shell_keyfunc_ctrl_d);

  termio_init ();
  shell_fselect_init ();

  shell_clear (shell);
  shell_prompt (shell);

  while (shell_running (shell))
    shell_read (shell);

  termio_finish ();

  return 0;
}

