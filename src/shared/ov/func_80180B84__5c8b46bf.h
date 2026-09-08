/* func_80180B84 — shared body (overlay slot 0x80128158, h_exact 5c8b46bf). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014659C(void);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80162CCC();
extern u16 D_800DF2E0;
extern s32 D_8018F510;
extern s32 D_8018F56C[];
void func_80180B84(int param_1) {
    s32 iVar1;
    iVar1 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32, void *))func_8001C810)(iVar1, &D_800DF2E0);
        *(s32 **)(iVar1 + 0x80) = &D_8018F510;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        *(u16 *)(iVar1 + 0x2c) = *(u16 *)(iVar1 + 0x2c) | 0xb0;
        *(s32 *)(param_1 + 0x58) = (s32)&D_8018F56C[*(s32 *)(param_1 + 0x50) * 2];
        *(u16 *)(iVar1 + 0x1c) = 0;
        *(u16 *)(iVar1 + 0x1a) = 0;
        *(u16 *)(iVar1 + 0x18) = 0;
        ((void (*)(s32))func_80146CA0)(param_1);
    } else {
        ((void (*)(s32))func_80162CCC)(param_1);
    }
}
