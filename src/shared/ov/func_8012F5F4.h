/* func_8012F5F4 — shared body (overlay slot 0x80128158, h_exact 98a010f2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80131B14();
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern s32 func_80131A34(s32, s32);
extern s32 func_80131CA8();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
void func_8012F5F4(s32 arg0) {
    *(u8 *)(arg0 + 0xC1) = 1;
    if ((*(s32 *)(arg0 + 0xC4) & 2) != 0) {
        func_80131CA8(arg0, 3);
        return;
    }
    ((void (*)(s32))func_80131B14)(arg0);
    if (*(s16 *)(arg0 + 0x76) < 1) {
        func_80131E00((struct S80131E00 *)arg0, 0xC);
        return;
    }
    if (func_80131A34(arg0, 4) != 0) {
        *(u8 *)(arg0 + 0xC2) = 0;
    } else {
        *(s16 *)(arg0 + 0x98) = 0;
        *(u8 *)(arg0 + 0xC2) = 1;
        *(s32 *)(arg0 + 0x1C) = 0x10;
    }
    func_80131CA8(arg0, 3);
}
