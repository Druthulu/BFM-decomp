/* func_801736FC — shared body (overlay slot 0x80128158, h_exact 159477ea). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* $v0 at exit: result of an indirect call; no byte-neutral return: `return 0;` moved `move v0,zero` at +0x30, ov_SC03_126 objdump */
s32 func_801736FC(void *a0) {

    extern void (*D_80182870[])(void);
    D_80182870[*(u8 *)((s32)a0 + 0x214)]();
}
