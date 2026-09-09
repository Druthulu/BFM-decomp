/* func_8012EFB8 — shared body (overlay slot 0x80128158, h_exact 26e46daf). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 aF8012EFB8() __asm__("func_8012EFB8");
s32 aF8012EFB8(param_1, param_2)
    void *param_1;
    void *param_2;
{
    extern u8 D_800AF648;
    s32 *m;
    s32 flag;
    m = (s32 *)&D_800AF648;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
    gte_ldv0(param_1);
    gte_rtps();
    gte_stsxy(param_2);
    gte_stflg(&flag);
    return flag;
}
