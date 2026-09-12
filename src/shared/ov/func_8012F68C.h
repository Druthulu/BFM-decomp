/* func_8012F68C — shared body (overlay slot 0x80128158, h_exact 309768b1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012CBCC(s32 a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80131C78(s32 a0);
extern s32 func_80131CA8();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
void func_8012F68C(s32 arg0) {
    s32 flag;
    u32 cond;
    flag = 0;
    if (!(*(u32 *)(arg0 + 0xC4) & 2) && (*(u32 *)(arg0 + 0xB4) & 1)) {
        if ((u8)((s32 (*)(s32))func_8012CBCC)(arg0) == 2) {
            func_80131E00((struct S80131E00 *)arg0, 0x12);
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
