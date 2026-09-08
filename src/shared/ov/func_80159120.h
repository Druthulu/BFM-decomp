/* func_80159120 — shared body (overlay slot 0x80128158, h_exact 3d32b871). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80029504(void);
extern s32 func_801399F0(s32);
extern void func_80139914(s32 a0);
extern s32 func_80029A94(s32);
extern void func_80175454(void);
extern void func_801458E0(void);
extern void func_800298BC(void *);
extern void func_801458E8(void);
extern s32 func_8013767C(s32 a0);
extern void func_8002992C(s32);
extern void func_80145A2C(void);
extern void func_80146C98(s32 *a0, s16 a1);
extern void func_800CF804(void);
extern void func_800CF818(void);
extern u8 D_80078E50;
extern s32 D_80078E8C;
extern u8 D_80110D0C[];
extern u8 D_80110C3C[];
void func_80159120(s32 a0) {
    s32 r;
    s32 v1;
    s32 base;
    func_80029504();
    base = *(s32 *)(a0 + 0x20);
    *(u16 *)(base + 0x12) = (*(u16 *)(base + 0x12) + 0x16) & 0xFFF;
    r = func_801399F0(*(s32 *)(a0 + 0x198));
    if (r == 0) {
        return;
    }
    func_80139914(*(s32 *)(a0 + 0x198));
    *(s32 *)(a0 + 0x198) = 0;
    if (r != 1) {
        if (r == 2) {
            goto L290;
        }
    }
    v1 = *(s16 *)(a0 + 0x244);
    if (v1 != 1) {
        if (v1 == 2) {
            goto L224;
        }
    }
    if (func_80029A94(1) != 0) {
        s32 t;
        func_80175454();
        func_801458E0();
        t = D_80078E8C;
        func_800298BC(&D_80078E50);
        func_801458E8();
        D_80078E8C = t / 2;
        goto L270;
    }
    *(s32 *)(a0 + 0x198) = func_8013767C((s32)D_80110D0C);
    func_80146C98((s32 *)a0, 0xB);
    return;
L224:
    if (func_80029A94(0) != 0) {
        func_80175454();
        func_8002992C(0);
        func_80145A2C();
        goto L270;
    }
    *(s32 *)(a0 + 0x198) = func_8013767C((s32)D_80110D0C);
    func_80146C98((s32 *)a0, 0xB);
    return;
L270:
    func_80146C98((s32 *)a0, 0xC);
    func_800CF804();
    func_800CF818();
    return;
L290:
    *(s32 *)(a0 + 0x198) = func_8013767C((s32)D_80110C3C);
    func_80146C98((s32 *)a0, 0x9);
}
