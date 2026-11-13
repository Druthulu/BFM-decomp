/* func_8015BE94 — shared body (overlay slot 0x80128158, h_exact 05b43533). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80161124(void *a0);
    extern void guess_NextStep(void *a0);
/* $v0 at exit: result of guess_NextStep; no byte-neutral return: `return 0;` moved `move v0,zero` at +0x1C, ov_MAIN_012 objdump */
    s32 func_8015BE94(s32 *a0)
{
        ((void (*)(s32 *))func_80161124)(a0);
        ((s32 (*)(s32))guess_NextStep)((s32)a0);
    }
