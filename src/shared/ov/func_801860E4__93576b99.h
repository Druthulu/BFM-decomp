/* func_801860E4 — shared body (overlay slot 0x80128158, h_exact 93576b99). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801DF700;
extern s32 D_8018EFDC;
void func_801860E4(void *a0) {
    register s32 s0 __asm__("$16") = (s32)a0;
    s32 s1;
    s32 v0;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    s1 = v0;
    *(s32 *)((s8 *)s0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)s0);
    } else {
        func_8001C214(s1, (s32)&D_801DF700);
        func_8001D0E8(s1, 0x800, 0x800);
        func_8012A828(s0, &D_8018EFDC);
        *(s32 *)((s8 *)s0 + 0x14) = 0xFFFC0000;
        *(s32 *)((s8 *)s0 + 0x48) = 0x20000;
        *(s32 *)((s8 *)s0 + 0x44) = 0;
        *(s32 *)((s8 *)s0 + 0x4C) = 0;
        *(s16 *)((s8 *)s0 + 0xDC) = 0x40;
        *(u16 *)((s8 *)s0 + 0x2) = *(u16 *)((s8 *)s0 + 0x2) + 1;
    }
}
