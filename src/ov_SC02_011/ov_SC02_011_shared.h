#ifndef BFM_OV_SC02_011_SHARED_H
#define BFM_OV_SC02_011_SHARED_H

/* P31 S74 — the declarations that CROSS the
 *   ov_SC02_011_jr_8017AE2C.c -> ov_SC02_011_jr_80183178.c -> ov_SC02_011_jr_80188E3C.c
 * split of overlay ov_SC02_011.
 *
 * Derived from the COMPILER's own errors, never from a regex model of C (R33). Each typedef
 * was MOVED here, never copied (a duplicate typedef is a C89 error). See cookbook §426/§431
 * and config/splat.ov_SC02_011.yaml for why the split exists at all. */

/* --- round 1: names used in ov_SC02_011_jr_80188E3C.c but declared only in the parent TU --- */
/* was: ov_SC02_011_jr_8017AE2C.c:2460 */
extern short D_800B9A02;
/* was: ov_SC02_011_jr_8017AE2C.c:1691 */
extern void RotMatrixYXZ(void *a0, void *a1);

#endif /* BFM_OV_SC02_011_SHARED_H */
