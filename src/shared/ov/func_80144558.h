/* func_80144558 — shared body (overlay slot 0x80128158, h_exact bdf0919a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_8012B200(u8 *a0);
extern u8 D_800D387C[];
extern u8 D_800D3888[];
void func_80144558(u8 *param_1) {
    s32 s0;
    s0 = ((s32 (*)(void))func_8012C194)();
    if (s0 == 0) {
        func_8012CAE4(param_1);
    } else {
        *(s32 *)(param_1 + 0xCC) = s0;
        func_8001CC3C(s0, 0, 0, 0);
        *(s32 *)(s0 + 0x20) = (s32)D_800D387C;
        *(u8 *)(s0 + 0x27) = 0x9C;
        *(u16 *)(s0 + 0x1A) = 0x3000;
        *(u16 *)(s0 + 0x18) = 0x3000;
        *(u32 *)(s0 + 4) = *(u32 *)(s0 + 4) | 0x50000000;
        func_80128EA8(s0, (s32)(param_1 + 0xD0), (s32)D_800D3888);
        *(u16 *)(s0 + 8) = *(u16 *)(param_1 + 6);
        *(u16 *)(s0 + 0xA) = *(u16 *)(param_1 + 0xA);
        *(u16 *)(s0 + 0xC) = *(u16 *)(param_1 + 0xE);
        *(u16 *)(param_1 + 2) = 1;
        func_8012B200(param_1);
    }
}
