/* func_80158638 — shared body (overlay slot 0x80128158, h_exact 6a497e0f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80159464();
extern s32 func_8014C98C(void);
extern int func_800D0F8C(int a0);
extern void func_801599A4(void *a0);
extern void func_8016F0E4(void);
extern void func_80159B3C(void *a0);
extern void func_80165718(s32 a0);
extern void func_800D0F4C(s32 a0);
extern void func_8014BB0C(void);
extern void func_8014BDC8(void);
extern void func_8014B2A8(void);
extern s32 func_8013767C(s32 a0);
extern void func_80158814(void *a0);
void func_80158638(void *a0) {
    extern u8 D_800B9A64;
    extern s16 D_80078EB4;
    extern u8 D_800B9A17;
    extern u8 D_80110EC0;
    s32 v1;
    if (D_800B9A64 != 0) {
        return;
    }
    if (*(s32 *)((s32)a0 + 0x44) & 0x10) {
        return;
    }
    if (*(u16 *)((s32)a0 + 0) == 0x1A) {
        return;
    }
    if (*(u16 *)((s32)a0 + 0) == 0x1E) {
        return;
    }
    v1 = *(s32 *)((s32)a0 + 0x1F8);
    if (v1 != 0 && (v1 & 0x08000000) == 0) {
        return;
    }
    if (*(u16 *)&D_80078EB4 != 0) {
        return;
    }
    if (((s16)func_80159464(a0) <= 0 || (s16)func_80159464(a0) >= 6) &&
        func_8014C98C() == 0 && func_800D0F8C(0xA) != 0) {
        func_801599A4(a0);
        ((void (*)(void *))func_8016F0E4)(a0);
        func_80159B3C(a0);
        func_80165718((s32)a0);
        func_800D0F4C(0xA);
        func_8014BB0C();
        func_8014BDC8();
        func_8014B2A8();
        *(s32 *)((s32)a0 + 0x198) = func_8013767C((s32)&D_80110EC0);
        D_800B9A17 = 1;
    } else {
        func_801599A4(a0);
        ((void (*)(void *))func_8016F0E4)(a0);
        func_80158814(a0);
    }
}
