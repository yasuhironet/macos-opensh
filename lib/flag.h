
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

#ifndef __FLAG_H__
#define __FLAG_H__

#ifndef FLAG_SET
#define FLAG_CHECK(V,F)      ((V) & (F))
#define FLAG_SET(V,F)        (V) = (V) | (F)
#define FLAG_CLEAR(V,F)      (V) = (V) & ~(F)
#endif /*FLAG_SET*/

#endif /*__FLAG_H__*/
