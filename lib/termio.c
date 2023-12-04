
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

#include <stdio.h>
#include <string.h>
#include <termios.h>

#include "flag.h"
#include "debug.h"

struct termios termios_old;
struct termios termios_new;

struct flag_name {
  int val;
  char *name;
} c_lflag_name [] =
{
  { ECHOKE,       "ECHOKE" },
  { ECHOE,        "ECHOE" },
  { ECHO,         "ECHO" },
  { ECHONL,       "ECHONL" },
  { ECHOPRT,      "ECHOPRT" },
  { ECHOCTL,      "ECHOCTL" },
  { ISIG,         "ISIG" },
  { ICANON,       "ICANON" },
  { ALTWERASE,    "ALTWERASE" },
  { IEXTEN,       "IEXTEN" },
  { EXTPROC,      "EXTPROC" },
  { TOSTOP,       "TOSTOP" },
  { FLUSHO,       "FLUSHO" },
  { NOKERNINFO,   "NOKERNINFO" },
  { PENDIN,       "PENDIN" },
  { NOFLSH,       "NOFLSH" },
};

void
termio_print_lflags (int c_lflag)
{
  int i;
  int size = sizeof (c_lflag_name) / sizeof (struct flag_name);
  printf ("[");
  for (i = 0; i < size; i++)
    {
      if (c_lflag & c_lflag_name[i].val)
        printf ("%s", c_lflag_name[i].name);
      printf ("|");
    }
  printf ("]\n");
}

void
termio_start ()
{
  if (FLAG_CHECK (debug_config, DEBUG_TERMIO))
    {
      printf ("termios_new: c_lflag: ");
      termio_print_lflags (termios_new.c_lflag);
    }

  /* change terminal settings */
  tcsetattr (0, TCSANOW, &termios_new);
}

void
termio_reset ()
{
  if (FLAG_CHECK (debug_config, DEBUG_TERMIO))
    {
      printf ("termios_old: c_lflag: ");
      termio_print_lflags (termios_old.c_lflag);
    }

  /* change terminal settings */
  tcsetattr (0, TCSANOW, &termios_old);
}

void
termio_init ()
{
  /* save original terminal settings */
  tcgetattr (0, &termios_old);

  if (FLAG_CHECK (debug_config, DEBUG_TERMIO))
    {
      printf ("termios_old: c_lflag: ");
      termio_print_lflags (termios_old.c_lflag);
    }

  /* disable canonical input */
  memcpy (&termios_new, &termios_old, sizeof (termios_new));
  termios_new.c_lflag &= ~(ICANON | ECHO | IEXTEN);
  //termios_new.c_oflag |= ONOCR;

  termio_start ();
}

void
termio_finish ()
{
  termio_reset ();
}

