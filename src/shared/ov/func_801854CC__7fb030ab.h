/* func_801854CC — shared body (overlay slot 0x80128158, h_exact 7fb030ab). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8001D074(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_8001CD9C(int, void *);
extern u8 D_8018EFF4;
extern u8 D_8018EFF5;
extern u8 D_8018EFF6;
void func_801854CC(void *a0) {
    register void *s1 __asm__("$17");
    register void *s0 __asm__("$16");
    s1 = (void *)((s32 (*)(s32, s32))func_8001D074)(0x3E, 0x7D);
    *(void **)((s32)a0 + 0xCC) = s1;
    if (s1 != 0) {
        s0 = &D_8018EFF4;
        func_800233CC(s0, 0x50);
        func_8001CD9C((s32)s1, s0);
        *(u32 *)((s32)s1 + 4) = *(u32 *)((s32)s1 + 4) | 0x50000040;
    }
    s1 = (void *)((s32 (*)(s32, s32))func_8001D074)(0x3E, 0x7D);
    *(void **)((s32)a0 + 0xD0) = s1;
    if (s1 != 0) {
        s0 = &D_8018EFF4;
        func_800233CC(s0, 0x40);
        func_8001CD9C((s32)s1, s0);
        *(u32 *)((s32)s1 + 4) = *(u32 *)((s32)s1 + 4) | 0x50000040;
    }
    D_8018EFF4 = 0xFF;
    D_8018EFF5 = 0x10;
    D_8018EFF6 = 0x10;
    *(u16 *)((s32)a0 + 0xDC) = 6;
    *(u16 *)((s32)a0 + 0xDE) = 0xFF;
    *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
}
