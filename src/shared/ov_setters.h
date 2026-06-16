/* src/shared/ov_setters.h — shared parameterized bodies for trivial overlay accessors.
 * cookbook §11 source-level dedup ("match once, share many"): the body lives ONCE here and is
 * instantiated IN PLACE (preserving each .c's address order — overlays link functions in source
 * order) at every member's site. The byte-identical overlay pair SC01/005 ≡ SC01/006 (one
 * 0.4.dec, sha1 56760dbe) shares these via config/dedup.us.yaml; tools/dedup_integrate.py
 * byte-gates the share (h_exact). The macros are generic, so the 134-overlay fleet reuses them. */
#ifndef OV_SETTERS_H
#define OV_SETTERS_H
#define SETTER(name, off, ty) void name(void *p, ty v) { *(ty *)((s32)p + (off)) = v; }
#define RETCONST(name, val)   s32  name(void)          { return (val); }
#endif
