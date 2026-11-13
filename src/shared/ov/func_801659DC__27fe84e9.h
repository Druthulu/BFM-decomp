/* func_801659DC — shared body (overlay slot 0x80128158, h_exact 27fe84e9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* $v0 at exit: result of an indirect call; no caller reads $v0 (census unused); void blocked: src/shared/ov/func_801554B8.h also declares it for ov_SC01_077 */
s32 func_801659DC(u8 *a0) {

    extern void (*D_801818A0[])(void);
    D_801818A0[*(u8 *)((s32)a0 + 0x1A0)]();
}
