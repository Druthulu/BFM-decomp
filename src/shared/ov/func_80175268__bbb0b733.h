/* func_80175268 — shared body (overlay slot 0x80128158, h_exact bbb0b733). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* $v0 at exit: result of an indirect call; no byte-neutral return: `return 0;` moved `move v0,zero` at +0x48, ov_SC03_126 objdump */
s32 func_80175268(s32 param_1)
{

    extern VoidFn D_80182920[];
    *(u32 *)(param_1 + 0x44) |= 2;
    (*(VoidFn *)((s32)D_80182920 + ((D_80078EC0 - 1) << 2)))();
}
