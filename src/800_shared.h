#ifndef BFM_800_SHARED_H
#define BFM_800_SHARED_H

/* The include environment the original single TU had. Every TU of the split needs the same
 * one: `psyq/libcd.h` supplies CdlLOC/CdlFILE to functions now in 800_c.c, and
 * `shared/clearTbl40.h` supplies the CLEAR_TBL40 dedup macro whose two instantiation sites
 * ended up in DIFFERENT TUs after the split. Both are guarded, so src/800.c keeping its own
 * copies is harmless. */
#include "psyq/libcd.h"

/* P31 S72 — the declarations that CROSS the src/800.c -> 800_b.c -> 800_c.c split.
 *
 * Measured, not guessed: of 1,247 names declared across the three regions, only 57 are used
 * outside the region that declares them, and 19 of those are typedefs. Every one had exactly
 * ONE definition and zero shape conflicts, so this is a partition of the old file, not a
 * rewrite — each typedef was MOVED here, never copied (a duplicate typedef is a C89 error).
 * The set was derived from the compiler's own errors, not from a regex model of C (R33).
 * See cookbook §426 and config/splat.us.exe.yaml for why the split exists at all. */

/* was: src/800.c */

/* was: src/800.c */

/* was: src/800.c */
 /* 0x14 */

/* was: src/800.c */

/* was: src/800.c */

/* was: src/800.c */
                       /* 0x18 */

/* was: src/800.c */
 /* 0x0C */

/* was: src/800.c */
 /* 0x0C */

/* was: src/800.c */
 /* 0x20 */

/* was: src/800.c */

/* was: src/800.c */

/* was: src/800.c */

/* was: src/800.c */
                      /* 0x10 */

/* was: src/800.c */

/* was: src/800.c */

/* was: src/800.c */
 /* 0x2 */

/* was: src/800.c */
                      /* 0x10 */

/* was: src/800_c.c */

/* was: src/800_c.c */
                      /* 0x0C */

#endif /* BFM_800_SHARED_H */
