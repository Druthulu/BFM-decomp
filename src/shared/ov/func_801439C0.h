/* func_801439C0 — shared body (overlay slot 0x80128158, h_exact 2b1fec6d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_ZeroMemory(void *a0, s32 a1);
extern void guess_FreeActor(void *a0);
/* $v0 at exit: leftover of void guess_FreeActor (a0 != 0), else untouched; no byte-neutral return: `return 0;` inserts `move v0,zero` at +0x28 (+1 insn), ov_SC02_027 objdump */
s32 func_801439C0(u8 *a0) {
    if (a0 != 0) {
        guess_ZeroMemory(*(void **)(a0 + 0xCC), 0x38);
        guess_FreeActor(a0);
    }
}
