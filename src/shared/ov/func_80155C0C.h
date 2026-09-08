/* func_80155C0C — shared body (overlay slot 0x80128158, h_exact d62d91b5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern u8 D_800D4DD4[];
void func_80155C0C(s32 *a0) {
    u8 sp10[0x40];
    (void)sp10;
    a0[0x44 / 4] |= 2;
    if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
        func_80154274(a0, (s32)D_800D4DD4);
        func_80146CA0(a0);
    }
}
