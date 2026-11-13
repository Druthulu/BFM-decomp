/* func_80144A04 — shared body (overlay slot 0x80128158, h_exact 1f4b4940). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80144A04(s32 *a0);
/* $v0 at exit: result of an indirect call; no byte-neutral return: `return 0;` moved `move v0,zero` at +0x1C, ov_MAIN_012 objdump */
s32 func_80144A04(s32 *a0) {
    void (*fp)(void);
    fp = (void (*)(void))*(s32 *)((s32)a0 + 0xDC);
    fp();
}
