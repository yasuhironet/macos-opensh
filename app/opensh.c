
#include <includes.h>

#include "termio.h"
#include "vector.h"
#include "command.h"
#include "shell.h"
#include "command_shell.h"

#include "shell_fselect.h"

void
shell_set_prompt_cwd (struct shell *shell)
{
  char buf[MAXPATHLEN];
  char prompt[MAXPATHLEN * 2];

  getcwd (buf, sizeof (buf));
  snprintf (prompt, sizeof (prompt), "[%s]> ", buf);

  shell_set_prompt (shell, prompt);
}

DEFINE_COMMAND(chdir,
               "cd <FILENAME>",
               "change current working directory.\n"
               "filename\n")
{
  int ret = 0;
  struct shell *shell = (struct shell *) context;
  fprintf (shell->terminal, "chdir: %s\n", argv[1]);
  ret = chdir (argv[1]);
  if (ret)
    fprintf (shell->terminal, "chdir failed: %s\n", strerror (errno));

  shell_set_prompt_cwd (shell);
}

DEFINE_COMMAND(chdir_home,
               "cd",
               "change current directory to home.\n"
               "filename\n")
{
  int ret = 0;
  struct shell *shell = (struct shell *) context;
  char *homedir;
  homedir = getenv ("HOME");
  fprintf (shell->terminal, "chdir: home: %s\n", homedir);
  ret = chdir (homedir);
  if (ret)
    fprintf (shell->terminal, "chdir failed: %s\n", strerror (errno));

  shell_set_prompt_cwd (shell);
}

DEFINE_COMMAND(pwd,
               "pwd",
               "print current working directory.\n")
{
  struct shell *shell = (struct shell *) context;
  char buf[MAXPATHLEN];
  getcwd (buf, sizeof (buf));
  fprintf (shell->terminal, "cwd: %s\n", buf);
}

DEFINE_COMMAND(list,
               "ls",
               "list files in the directory.\n")
{
  struct shell *shell = (struct shell *) context;
  char buf[MAXPATHLEN], dir[MAXPATHLEN];
  getcwd (buf, sizeof (buf));
  snprintf (dir, sizeof (dir), "%s/", buf);
  fprintf (shell->terminal, "dir: %s\n", dir);
  file_ls_candidate (shell->terminal, dir);
}

DEFINE_COMMAND(list_dir,
               "ls <FILENAME>",
               "list files in the directory.\n"
               "directory name\n")
{
  struct shell *shell = (struct shell *) context;
  char dir[MAXPATHLEN];
  snprintf (dir, sizeof (dir), "%s/", argv[1]);
  fprintf (shell->terminal, "dir: %s\n", dir);
  file_ls_candidate (shell->terminal, dir);
}

DEFINE_COMMAND(open,
               "open <FILENAME>",
               "open.\n"
               "filename\n")
{
  struct shell *shell = (struct shell *) context;
  char command[512];

  snprintf (command, sizeof (command), "open %s", argv[1]);
  system (command);
}

int
main (int argc, char **argv)
{
  struct shell *shell;

  command_shell_init ();

  shell = command_shell_create ();
  shell_set_prompt_cwd (shell);
  shell_set_terminal (shell, 0, 1);

  INSTALL_COMMAND (shell->cmdset, chdir);
  INSTALL_COMMAND (shell->cmdset, chdir_home);
  INSTALL_COMMAND (shell->cmdset, pwd);
  INSTALL_COMMAND (shell->cmdset, list);
  INSTALL_COMMAND (shell->cmdset, list_dir);
  INSTALL_COMMAND (shell->cmdset, open);

  shell_install (shell, '>', fselect_keyfunc_start);

  termio_init ();
  shell_fselect_init ();

  shell_clear (shell);
  shell_prompt (shell);

  while (shell_running (shell))
    shell_read (shell);

  termio_finish ();

  return 0;
}

