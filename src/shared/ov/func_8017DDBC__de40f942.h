/* func_8017DDBC — shared body (overlay slot 0x80128158, h_exact de40f942). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);
extern void func_8017D9C8(s32 a0);
extern void func_80171A1C(u8*);
extern s16 D_80126B3C;
void func_8017DDBC(s32 param_1)
{
    if (func_801399F0(*(s32 *)(param_1 + 0x198)) != 0) {
        func_80139914(*(s32 *)(param_1 + 0x198));
        *(s32 *)(param_1 + 0x198) = 0;
        *(s32 *)(param_1 + 0x200) = 0x60;
        func_8017D9C8((s32)D_80126B3C);
        ((void (*)(s32))func_80171A1C)(param_1);
    }
}
