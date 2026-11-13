/* func_80175218 — shared body (overlay slot 0x80128158, h_exact 8361e4e9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* $v0 at exit: result of guess_NextStep; no byte-neutral return: `return 0;` moved `move v0,zero` at +0x3C, ov_SC03_126 objdump */
s32 func_80175218(void * param_1)
{
    s32 i = D_80078EC0 - 1;

    D_80182908[i](param_1);
    ((void (*)(s32))guess_NextStep)(param_1);
}
