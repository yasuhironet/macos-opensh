/*
 * Copyright (C) 2007-2023 Yasuhiro Ohara. All rights reserved.
 */

#ifndef __FLAG_H__
#define __FLAG_H__

#ifndef FLAG_SET
#define FLAG_CHECK(V,F)      ((V) & (F))
#define FLAG_SET(V,F)        (V) = (V) | (F)
#define FLAG_CLEAR(V,F)      (V) = (V) & ~(F)
#endif /*FLAG_SET*/

#endif /*__FLAG_H__*/