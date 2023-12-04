
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

#ifndef __LOG_H__
#define __LOG_H__

struct loginfo
{
  int flags;
  int facility;
  int maskpri;
  FILE *fp;
};

extern struct loginfo log_default;

/* flags */
#define LOGINFO_FILE   0x01
#define LOGINFO_STDOUT 0x02
#define LOGINFO_STDERR 0x04
#define LOGINFO_SYSLOG 0x08

#define LOG_INDEX_FILE   0
#define LOG_INDEX_STDOUT 1
#define LOG_INDEX_STDERR 2
#define LOG_INDEX_SYSLOG 3
#define LOG_INDEX_MAX    4

int log_getmask ();
void log_setmask (int mask);

void log_debug (const char *format, ...);
void log_info (const char *format, ...);
void log_notice (const char *format, ...);
void log_warn (const char *format, ...);

#endif /*__LOG_H__*/
