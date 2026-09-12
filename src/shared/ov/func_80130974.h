/* func_80130974 — shared body (overlay slot 0x80128158, h_exact 69c020fd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int func_8012BEE8(int);
extern void func_80166244();
extern void func_801319E0(int);
extern s32 func_80131CA8();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
void func_80130974(int param_1) {
    short sVar1;
    if ((*(unsigned int *)(param_1 + 0xb4) & 0x8000) != 0) {
        sVar1 = *(short *)(*(int *)(param_1 + 0x20) + 0x18);
        if (sVar1 < 0x1000) {
            *(short *)(*(int *)(param_1 + 0x20) + 0x18) = sVar1 + 0x400;
            *(short *)(*(int *)(param_1 + 0x20) + 0x1c) =
                *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x1c) + 0x400;
        }
        if (func_8012BEE8(param_1) != 0) {
            ((void (*)(int))func_80166244)(param_1);
            func_801319E0(param_1);
            return;
        }
    }
    func_80131CA8(param_1, 0x2b);
}
