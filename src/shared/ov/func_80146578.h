/* func_80146578 — shared body (overlay slot 0x80128158, h_exact 1d1dcbae). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8001D074(s32 a0, s32 a1);
/* $v0 at exit: leftover of void func_8001D074; no byte-neutral return: `return 0;` puts `move v0,zero` at +0x18 and moves `addiu sp` into the jr delay slot +0x20, ov_SC03_099 objdump */
s32 func_80146578(void) {
    func_8001D074(6, 0x16);
}
