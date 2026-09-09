/* func_80173CB4 — shared body (overlay slot 0x80128158, h_exact fc7be8bd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 func_80171AB0(s32 a0, void *a1);
extern void func_8014706C(void *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_801553A8(s32 *a0);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void func_80147324(s32 a0);
extern s32 func_8013767C(s32 a0);
extern void func_80171A1C(u8 *a0);
extern s32 D_801151D4;
extern struct S80126B38 D_80126B38;
extern u8 D_800D5DA8;
extern u8 D_800D5DB8;
extern s32 D_8012750C;
void func_80173CB4(s32 a0) {
    s32 s0 = a0;
    s32 v1 = D_801151D4;
    s16 tmp[4];
    s32 a;
    s32 d;
    tmp[0] = *(s32 *)(v1 + 0x3C);
    tmp[1] = *(s32 *)(v1 + 0x40);
    tmp[2] = *(s32 *)(v1 + 0x44);
    if (func_80171AB0(a0, tmp) != 0) {
        return;
    }
    func_8014706C((void *)s0);
    switch ((u8)(*(u8 *)&D_80126B38)) {
    case 0:
        func_80154274((s32 *)s0, (s32)&D_800D5DA8);
        *(s32 *)(s0 + 0x200) = 0x20;
        a = 0x843;
        goto ld0;
    case 1:
        func_80154274((s32 *)s0, (s32)&D_800D5DA8);
        goto lb8;
    case 2:
        func_80154274((s32 *)s0, (s32)&D_800D5DA8);
        __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B headers1)
        goto lb8;
    case 3:
        func_80154274((s32 *)s0, (s32)&D_800D5DB8);
        func_801553A8((s32 *)s0);
        goto lb8;
    default:
        goto ld8;
    }
lb8:
    func_8016BADC((void *)s0, -0x40, 0x40);
    *(s32 *)(s0 + 0x200) = 0x80;
    a = 0x6A6;
ld0:
    func_80147324(a);
ld8:
    d = D_8012750C;
    if (d != 0) {
        *(s32 *)(s0 + 0x198) = func_8013767C(d);
    } else {
        *(s32 *)(s0 + 0x198) = 0;
    }
    func_80171A1C((u8 *)s0);
}
