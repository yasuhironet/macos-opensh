
#include <includes.h>

#include "termio.h"
#include "vector.h"
#include "command.h"
#include "shell.h"
#include "command_shell.h"

DEFINE_COMMAND(chdir,
               "cd <FILENAME>",
               "change current working directory.\n"
               "filename\n")
{
  struct shell *shell = (struct shell *) context;
  fprintf (shell->terminal, "chdir: %s\n", argv[1]);
  chdir (argv[1]);
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

int
main (int argc, char **argv)
{
  char *prompt = "test prompt> ";
  struct shell *shell;

  command_shell_init ();

  shell = command_shell_create ();
  shell_set_prompt (shell, prompt);
  shell_set_terminal (shell, 0, 1);

  INSTALL_COMMAND (shell->cmdset, chdir);
  INSTALL_COMMAND (shell->cmdset, pwd);

  termio_init ();

  shell_clear (shell);
  shell_prompt (shell);

  while (shell_running (shell))
    shell_read (shell);

  termio_finish ();

  return 0;
}

