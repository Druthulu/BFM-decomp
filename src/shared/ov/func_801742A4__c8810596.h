/* func_801742A4 — shared body (overlay slot 0x80128158, h_exact c8810596). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* $v0 at exit: result of an indirect call; no byte-neutral return: `return 0;` moved `move v0,zero` at +0x30, ov_SC04_008 objdump */
s32 func_801742A4(void *a0) {

    extern void (*D_80182104[])(void);
    D_80182104[*(u8 *)((s32)a0 + 0x214)]();
}
