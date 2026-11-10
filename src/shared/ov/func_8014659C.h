/* func_8014659C — shared body (overlay slot 0x80128158, h_exact 87644ba8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8001CFDC(s32, s32);
/* $v0 at exit: leftover of void func_8001CFDC; no byte-neutral return: `return 0;` puts `move v0,zero` at +0x18 and moves `addiu sp` into the jr delay slot +0x20, ov_SC03_099 objdump */
s32 func_8014659C(void) {
    func_8001CFDC(6, 0x16);
}
