/* func_80130278 — shared body (overlay slot 0x80128158, h_exact bb4d8523). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80131CA8(int a0, int a1);
extern void func_80131170(s32 a0, s32 a1, s32 a2);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
void func_80130278(s32 arg0) {
    s32 flag;
    flag = 0;
    *(u8 *)(arg0 + 0xC1) = 0xB;
    if (*(s32 *)(arg0 + 0xC4) & 1) {
        func_80131E00((struct S80131E00 *)arg0, 0xE);
        return;
    }
    if (*(s32 *)(arg0 + 0xB4) & 0x800) {
        func_80131170(arg0, 0, 0);
        flag = 1;
    }
    if (((s32 (*)(int, int))func_80131CA8)(arg0, 0x2C) != 0) {
        flag = 1;
    }
    if (flag == 0) {
        func_80131E00((struct S80131E00 *)arg0, 6);
    }
}
