/* func_8016F0AC — shared body (overlay slot 0x80128158, h_exact 8eaa5e59). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8016F0E4();  // K&R: 0 of 1 args (P37 unalias t4_ua13)
extern void func_80165770(void);
/* $v0 at exit: leftover of void func_80165770; no byte-neutral return: `return 0;` inserts `move v0,zero` at +0x24 (+1 insn), ov_SC03_099 objdump */
s32 func_8016F0AC(void) {
    extern u8 aD80126B58 __asm__("guess_g_PlayerActor"); // Names ledger: config/names.tsv guess_g_PlayerActor
    ((void (*)(void *))func_8016F0E4)(&aD80126B58);
    ((void (*)(void *))func_80165770)(&aD80126B58);
}
