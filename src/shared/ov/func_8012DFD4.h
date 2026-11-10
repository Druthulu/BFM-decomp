/* func_8012DFD4 — shared body (overlay slot 0x80128158, h_exact ffa5782a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012E014(s32 arg0);
extern void func_8012E138();  // K&R: 0 of 1 args (P37 rung D t4_HD7)
/* $v0 at exit: leftover of void func_8012E014 or void func_8012E138; no byte-neutral return: `return 0;` puts `move v0,zero` at +0x34 and moves `addiu sp` into the jr delay slot +0x3C, ov_SC02_027 objdump */
s32 func_8012DFD4(u8 *a0) {
    if (a0[0x74]) {
        ((void (*)(void))func_8012E014)();
    } else {
        func_8012E138();
    }
}
