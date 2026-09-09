/* func_80132144 — shared body (overlay slot 0x80128158, h_exact cdad8179). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80132144(s32 param_1)
{
    extern int D_8017F004;

    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(((int)param_1) + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(((int)param_1));
    } else {
        ((void(*)(int, int))func_8001C214)(v0, 0);
        *(int *)(((int)param_1) + 0x58) = (int)&D_8017F004;
        *(short *)(((int)param_1) + 0x5c) = 0x80;
        *(unsigned short *)(((int)param_1) + 2) += 1;
    }
}
