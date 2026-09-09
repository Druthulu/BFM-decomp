#ifndef BFM_OV_SC01_084_SHARED_H
#define BFM_OV_SC01_084_SHARED_H

/* The include environment the original single TU had. Both pieces of the split need the
 * same one; every header below is include-guarded, so the .c files keeping their own
 * copies is harmless. */
#include "common.h"
#include "../shared/engine_prelude.h"

/* P31 S74 — the declarations that CROSS the
 *   src/ov_SC01_084/ov_SC01_084_jr_8017F690.c -> ov_SC01_084_jr_80182A00.c
 * split (cookbook §426/§431; see config/splat.ov_SC01_084.yaml for why the split exists).
 *
 * Derived from the COMPILER's own errors, not from a regex model of C (R33). Each entry was
 * MOVED here, never copied (a duplicate typedef is a C89 error; and a second copy of a decl
 * is a second thing to keep in sync). Decls emit no code => byte-neutral. */

/* was: src/ov_SC01_084/ov_SC01_084_jr_8017F690.c (declared twice there, used in both halves) */
extern void RotMatrixYXZ(void *a0, void *a1);

#endif /* BFM_OV_SC01_084_SHARED_H */
