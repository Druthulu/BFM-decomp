/* func_801829F8 — shared body (overlay slot 0x80128158, h_exact d45e43ee). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80182BD0();
extern void func_80147324(s32 a0);
extern void func_80182CB4(s32 a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154B4C(u8 *a0, s32 a1);
extern u8 D_8018EC34[];
extern u8 D_8018ED10[];
void func_801829F8(s32 a0) {
    func_80182BD0(a0);
    if (*(u16 *)(a0 + 0xB8) & 0x800) {
        func_80147324(0x4C8);
    }
    if (*(u16 *)(a0 + 0xB8) & 0x1000) {
        func_80147324(0x4C9);
    }
    if (*(u16 *)(a0 + 0xB8) & 0x2000) {
        *(u16 *)(a0 + 0x20E) = 1;
        *(u8 *)(a0 + 0x20C) = 2;
    }
    if (*(u16 *)(a0 + 0xB8) & 0x4000) {
        *(u16 *)(a0 + 0xD4) = *(u16 *)(a0 + 0xD4) + 1;
    }
    if (*(u16 *)(a0 + 0xB8) == 0x8000) {
        func_80182CB4(a0);
        func_80154274((s32 *)a0, (s32)D_8018EC34);
        func_80154B4C((u8 *)a0, (s32)D_8018ED10);
        *(u8 *)(a0 + 0x214) = *(u8 *)(a0 + 0x214) + 1;
    }
}
