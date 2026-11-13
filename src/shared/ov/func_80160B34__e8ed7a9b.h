/* func_80160B34 — shared body (overlay slot 0x80128158, h_exact e8ed7a9b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* $v0 at exit: result of an indirect call; no byte-neutral return: `return 0;` moved `move v0,zero` at +0x30, ov_SC03_126 objdump */
s32 func_80160B34(s32 a0) {

    extern void (*D_80181D10[])(void);
    D_80181D10[*(u16 *)((s32)a0 + 0x2)]();
}
