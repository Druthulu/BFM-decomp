/* func_80156ECC — shared body (overlay slot 0x80128158, h_exact 4f7da89f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80156ECC(int param_1, int param_2, int param_3, int param_4, int param_5) {
    extern void func_80156FA8(s16 *param_1, s16 *param_2, s16 *param_3);
    extern void func_80147478(s32 a0);
    extern void func_80149350(s32 arg0);
    unsigned short uVar1;
    func_80156FA8(param_3, param_4, param_5);
    ((s32 (*)(s32))func_80147478)(param_1);
    ((s32 (*)(s32, s32, s32))func_80149350)(param_1, param_2, param_2);
    uVar1 = *(unsigned short *)(param_3 + 6);
    if (*(short *)(param_3 + 6) == 0) {
        ((s32 (*)(s32, s32, s32))func_80149350)(param_1, param_3, param_3);
        *(unsigned short *)(param_3 + 6) = uVar1;
    }
    uVar1 = *(unsigned short *)(param_4 + 6);
    if (*(short *)(param_4 + 6) == 0) {
        ((s32 (*)(s32, s32, s32))func_80149350)(param_1, param_4, param_4);
        *(unsigned short *)(param_4 + 6) = uVar1;
    }
    uVar1 = *(unsigned short *)(param_5 + 6);
    if (*(short *)(param_5 + 6) == 0) {
        ((s32 (*)(s32, s32, s32))func_80149350)(param_1, param_5, param_5);
        *(unsigned short *)(param_5 + 6) = uVar1;
    }
}
