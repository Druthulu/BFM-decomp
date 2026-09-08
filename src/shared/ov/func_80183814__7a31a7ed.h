/* func_80183814 — shared body (overlay slot 0x80128158, h_exact 7a31a7ed). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80171CC4(void *a0, void *a1);
extern void func_80181D0C(void);
extern void func_80181C10(void);
extern void func_80175414(s32 _arg0);
extern void func_801839C4(void *a0);
extern void func_80183BA4();
extern void func_80183C9C(s32 a0);
extern void func_800D1724(s32 a0);
extern s16 D_800B9AAC[];
extern s16 D_801274E8;
extern u8 D_8018EDC8[];
extern u8 D_8018EA48[];
extern s32 D_801E8770;
void func_80183814(void *a0_) {
    register void *a0 __asm__("$17") = a0_;
    s16 state;
    s16 v;
    state = *(s16 *)((s32)a0 + 0xE);
    if (state >= 0x1391) {
        *(u16 *)((s32)a0 + 0xAE) = 0x8080;
        *(u16 *)((s32)a0 + 0xAA) &= 0x5FBF;
        *(u16 *)((s32)a0 + 0xAC) &= 0x5FBF;
        func_80171CC4(a0, D_8018EDC8);
        D_801274E8 = *(u16 *)((s32)a0 + 0x6);
    } else if (state < -0x1700) {
        s16 *p = &D_801274E8;
        *p = (s16)func_80012F74(*p, 0, 10, 1);
    }
    switch (*(s32 *)((s32)a0 + 0x208)) {
    case 0:
        if (*(s16 *)((s32)a0 + 0xE) < 0x1700) {
            func_80181D0C();
            *(s32 *)((s32)a0 + 0x208) += 1;
        }
        break;
    case 1:
        if (*(s16 *)((s32)a0 + 0xE) < 0x1380) {
            func_80181C10();
            *(s32 *)((s32)a0 + 0x208) += 1;
            ((void (*)(void))func_80175414)();
        }
        break;
    }
    if (*(s32 *)((s32)a0 + 0x204) != 0) {
        *(s32 *)((s32)a0 + 0x204) -= 1;
        return;
    }
    func_801839C4(a0);
    func_80183BA4(a0);
    func_80183C9C((s32)a0);
    if ((u32)(*(u16 *)((s32)a0 + 0xE) - 1) < 0xEFF) {
        D_800B9AAC[0] = 0x7FFF;
    }
    v = *(s16 *)((s32)a0 + 0xE);
    if (v < 0 && v < -0x1950) {
        if (D_801E8770 != 0) {
            func_800D1724((s32)D_8018EA48);
        }
    }
}
