/* func_8012D664 — shared body (overlay slot 0x80128158, h_exact 46ca4ffa). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
int func_8012D664(int arg0, int arg1, int arg2) {
    extern void func_8012F568(s32 param_1, s32 param_2, s32 param_3, s32 param_4, s32 param_5, s32 param_6);
    extern int D_8017EE00;

    struct S8012D664_8012D664 s;
    int ret;
    int t;

    s.a = (*(unsigned short*)&guess_g_PlayerPosX);
    s.b = (*(unsigned short*)&guess_g_PlayerPosY) - 0x40;
    s.c = (*(unsigned short*)&guess_g_PlayerPosZ);
    ret = ((int(*)())func_800132BC)(arg0, &s);
    t = arg1 + 0x20;
    if (ret < t * t) {
        func_8012F568(1, 1, 0, arg2, arg0, &D_8017EE00);
        return 1;
    }
    return 0;
}
