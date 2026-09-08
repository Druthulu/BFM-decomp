/* func_80173A60 — shared body (overlay slot 0x80128158, h_exact d62e1dd5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014C118(void*, s32, s32);
extern void func_80174684(void *);
extern void func_80173B4C(void*);
void func_80173A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5) {
    extern s32 D_80126B58;
    extern s32 D_80127508;
    extern s16 D_80126B30;
    extern struct S80126B38 D_80126B38;
    extern s16 D_80126B3A;
    extern s16 D_80126B3C;
    extern s16 D_8011F9C8;
    extern s16 D_80126938;
    extern s32 D_8012750C;
    s32 *s1 = &D_80126B58;
    s32 v0;
    if (a2 != 0) {
        D_80127508 = ((s32 (*)(s32, s32, s32))func_8014C118)((s32)s1, a2, (s16)a3);
    } else {
        D_80127508 = 0;
    }
    v0 = s1[8];
    __builtin_memcpy(&D_80126B30, arg5, 8);
    (*(s16 *)&D_80126B38) = a0;
    D_80126B3A = a1;
    D_80126B3C = *(u16 *)(v0 + 0x12);
    func_80174684((void *)func_80173B4C);
    D_8011F9C8 = 0;
    D_80126938 = 0;
    D_8012750C = 0;
}
