/* func_80163534 — shared body (overlay slot 0x80128158, h_exact dcf9ec7e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80163664(s32, u16, u16, s32, s32, s32, s32, s32, s32, s32, u16, s32, s32);
void func_80163534(a0, a1, a2, a3, a4, a5)
    s32 a0;
    u16 a1;
    u16 a2;
    s32 a3;
    u16 a4;
    u16 *a5;
{
    extern s32 D_80115100;
    extern s32 D_80115200;
    extern s32 D_80115204;
    extern s32 D_80115208;
    extern u16 D_80126B18[];
    extern u16 D_801270B0[];
    extern u16 D_801270B2;
    extern u16 D_801270B4;
    extern u16 D_80126B1A[];
    extern u16 D_80126B1C;
    extern s32 D_80114EB0;
    extern s32 D_80114EC8;
    extern s32 D_8011DAF0;
    extern s32 D_80115298;
    extern s32 D_80126734;
    s32 *p = &D_80115200;
    *p = 0;
    D_80115204 = 0;
    D_80115208 = 0;
    D_801270B0[0] = *(u16 *)(a0 + 0x44) + a5[0];
    D_801270B2 = *(u16 *)(a0 + 0x46) + a5[1];
    D_801270B4 = *(u16 *)(a0 + 0x48) + a5[2];
    D_80126B18[0] = *(u16 *)(a0 + 0x6) + a5[0];
    D_80126B1A[0] = *(u16 *)(a0 + 0xA) + a5[1];
    D_80126B1C = *(u16 *)(a0 + 0xE) + a5[2];
    *p = ((s32 (*)(s32, u16, u16, s32, s32, s32, s32, s32, s32, s32, u16, s32, s32))func_80163664)(a0, a1, a2, (s32)D_801270B0, (s32)D_80126B18,
                               (s32)&D_80114EB0, (s32)&D_80114EC8, (s32)&D_80115100,
                               (s32)&D_8011DAF0, a3, a4, (s32)&D_80115298,
                               (s32)&D_80126734);
}
