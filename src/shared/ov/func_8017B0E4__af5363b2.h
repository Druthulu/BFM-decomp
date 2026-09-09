/* func_8017B0E4 — shared body (overlay slot 0x80128158, h_exact af5363b2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017B0E4(int param_1, int param_2)
{
    extern s16 D_8018F98C;
    extern s16 D_8018F98E;
    extern s16 D_8018F990;
    extern s16 D_8018F984;
    extern s16 D_8018F986;
    extern s16 D_8018F988;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_8018F98C, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_8018F98E, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_8018F990, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_8018F984, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_8018F986, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_8018F988, (s32)((s16)param_2));
}
