
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

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdint.h>

#include "flag.h"

extern uint64_t debug_config;

#define DEBUG_SHELL   (1ULL << 0)
#define DEBUG_COMMAND (1ULL << 1)
#define DEBUG_TERMIO  (1ULL << 2)

//if (FLAG_CHECK (debug_config, DEBUG_SHELL))

struct debug_type
{
  uint64_t flag;
  const char *name;
};

#endif /*__DEBUG_H__*/
