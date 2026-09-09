/* func_8015E4B0 — shared body (overlay slot 0x80128158, h_exact dee0300d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015E4B0(s32 param_1)
{
    u16 *psVar1;
    s16 v[3];
    s32 local_10;

    psVar1 = *(u16 **)(param_1 + 0x18c);
    if ((psVar1 != (u16 *)0) && (*psVar1 != 0)) {
        v[0] = D_80181BDC + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0xc);
        v[1] = D_80181BDE + *(s16 *)(*(s32 *)(psVar1 + 0x3c) + 0xe) * 2;
        v[2] = D_80181BE0 + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0x10);
        ((s32 (*)(s32, s16 *, s16 *))func_80149350)(param_1, &v[0], &v[0]);
        ((s32 (*)(s32 *, s32 *))func_80013E94)(&D_80181BE4, &local_10);
        ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x1f, param_1, v[0], v[1], v[2], local_10, 0);
    }
    return;
}
