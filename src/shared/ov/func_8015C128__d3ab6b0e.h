/* func_8015C128 — shared body (overlay slot 0x80128158, h_exact d3ab6b0e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8015C128(s32 param_1) {
    extern void func_8015C6E0(int);
    extern void (*D_80181160[])(int);

    int sp10[3];
    int sp20[3];
    int temp_s0;
    int temp_v0;

    ((void(*)())func_80149FB0)();
    if (((int(*)(int))func_80148AFC)(((int)param_1)) & 0xFF) {
        sp10[0] = 0;
        sp10[1] = 0;
        sp10[2] = -0x4000;
        ((void(*)(int, int *, int *))func_8001382C)(*(short *)(*(int *)(((int)param_1) + 0x20) + 0x12), sp10, sp20);
        *(int *)(((int)param_1) + 0x234) += sp20[0];
        *(int *)(((int)param_1) + 0x238) += sp20[1];
        *(int *)(((int)param_1) + 0x23C) += sp20[2];
    }
    ((void(*)(int, int *, int *))func_8001382C)((short)(-*(unsigned short *)(*(int *)(((int)param_1) + 0x20) + 0x12)),
                  (int *)(((int)param_1) + 0x234), sp20);
    ((void(*)(int, int *))func_80146DB8)(((int)param_1), sp20);
    func_80147A84(((int)param_1));
    ((void(*)(int))func_801473EC)(((int)param_1));
    if (!(D_800B99DA & 3)) {
        ((void(*)(int, int))func_8014C010)(((int)param_1), 1);
        ((void(*)(int))func_80147324)(0x65F);
    }
    if (((int(*)(int))func_8014D738)(((int)param_1)) != 0) {
        D_80181160[*(u16 *)((int)param_1)](((int)param_1));
        func_8015C6E0(((int)param_1));
        return;
    }
    temp_s0 = ((int(*)(int))func_8014CC28)(((int)param_1));
    temp_v0 = ((int(*)(int))func_8014F3E8)(((int)param_1));
    if (temp_v0 != 0) {
        if ((temp_v0 & 0xFF00) != 0x4000) {
            ((void(*)(int, int))func_80146E90)(((int)param_1), 6);
            ((void(*)(int))func_80146CA0)(((int)param_1));
            return;
        }
        if ((temp_v0 & 0x4000) && ((int(*)(int))func_80146E98)(((int)param_1)) != 0) {
            ((void(*)(int, int))func_80147078)(((int)param_1), 4);
            ((void(*)(int))func_8015C0C4)(((int)param_1));
        }
    } else if (temp_s0 == 0) {
        D_80181160[*(u16 *)((int)param_1)](((int)param_1));
        ((void(*)(int, int))func_80147078)(((int)param_1), 3);
        ((void(*)(int))func_8015BE94)(((int)param_1));
    }
}
