/* func_80130C08 — shared body (overlay slot 0x80128158, h_exact 88d6ca22). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012CBCC(s32);
extern void func_80131E00(struct S80131E00*, s32);
extern s32 func_8012BEE8(s32 a0);
extern void func_80131C78(s32 a0);
extern void func_80131CA8(int a0, int a1);
void func_80130C08(s32 arg0) {
    s32 flag;
    u32 cond;
    flag = 0;
    if (!(*(u32 *)(arg0 + 0xC4) & 2)) {
        if (*(u32 *)(arg0 + 0xB4) & 0x20000) {
            if (*(u32 *)(arg0 + 0xB4) & 1) {
                if ((u8)((s32 (*)(s32))func_8012CBCC)(arg0) == 2) {
                    ((void (*)(void *, s32))func_80131E00)((void *)arg0, 0x12);
                    return;
                }
                if (*(u8 *)(arg0 + 0xC2) != 0) {
                    cond = func_8012BEE8(arg0);
                } else {
                    cond = *(u16 *)(arg0 + 0x72) & 0x4000;
                }
                if (cond != 0) {
                    flag = 1;
                }
                if (flag != 0) {
                    func_80131C78(arg0);
                }
            }
            func_80131CA8(arg0, 5);
        }
        if (!(*(u32 *)(arg0 + 0xC4) & 2)) {
            goto mode_38;
        }
    }
    func_80131CA8(arg0, 5);
    return;
mode_38:
    func_80131CA8(arg0, 0x38);
}
