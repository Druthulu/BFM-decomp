/* func_8012C1B8 — shared body (overlay slot 0x80128158, h_exact 5d72630c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8001CFDC(s32 a, s32 b);
/* $v0 at exit: leftover of void func_8001CFDC; no byte-neutral return: `return 0;` puts `move v0,zero` at +0x18 and moves `addiu sp` into the jr delay slot +0x20, ov_SC02_027 objdump */
s32 func_8012C1B8(void) {
    func_8001CFDC(0x26, 0x85);
}
