/* func_80131D68 — shared body (overlay slot 0x80128158, h_exact 4640feb0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern s32 func_80131CA8();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
extern void func_8002A04C(s32 a0);
extern void func_8012C218(void *a0);
int func_80131D68(int a0, int a1)
{
    s32 s0 = a0;
    s32 c = a1 & 0xFF;
    if (c == 2 || c == 0x1B) {
        func_80131E00((struct S80131E00 *)s0, 0x12);
        return 1;
    }
    if (c == 0x1A || c == 0x1C) {
        if (((s32 (*)(int, int))func_80131CA8)(s0, 0x11) != 0) {
            return 1;
        }
        if (*(s32 *)(s0 + 0x78) != 0) {
            func_8002A04C(s0);
        }
        func_8012C218((void *)s0);
        return 1;
    }
    return 0;
}
