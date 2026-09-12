/* func_801312D0 — shared body (overlay slot 0x80128158, h_exact aedb85b0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_801312D0(s32 param_1, void *param_2)
{
    extern s32 func_80131CF4();  // K&R: 2 of 2 args (P37 unalias t4_ua6)
    extern M8_801312D0 D_8017EF7C;

    int iVar5;

    iVar5 = func_80131CF4(*(int *)(((int)param_1) + 0xBC), 0x2E);
    if (iVar5 != 0) {
        ((short *)param_2)[2] = 0;
        ((short *)param_2)[0] = 0;
        ((short *)param_2)[1] = (short)iVar5;
    } else {
        *(M8_801312D0 *)((short *)param_2) = D_8017EF7C;
    }
}
