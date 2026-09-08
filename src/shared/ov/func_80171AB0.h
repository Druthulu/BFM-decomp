/* func_80171AB0 — shared body (overlay slot 0x80128158, h_exact 081f4c97). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014C568(s16 *a0, s16 *a1);
extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);
s16 func_80171AB0(s32 param_1, void * _arg1)
{
    short sVar1;
    sVar1 = ((short (*)(void))func_8014C568)();
    sVar1 = ((short (*)(int, int, int))func_80012B04)((int)*(short *)(*(int *)(param_1 + 0x20) + 0x12), (int)sVar1, 4);
    *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) + sVar1 & 0xfff;
    return (int)sVar1;
}
