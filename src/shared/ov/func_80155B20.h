/* func_80155B20 — shared body (overlay slot 0x80128158, h_exact 5fa29aa0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int func_80161208();
extern void func_80146D80(s32 *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern u8 D_800D4DA8[];
void func_80155B20(s32 *a0) {
    a0[0x44 / 4] |= 2;
    if (func_80161208() == 0) {
        if (*(u16 *)((char *)a0 + 0xB8) == 0x8000) {
            func_80146D80(a0);
            func_801477E8(a0, 0xFFF00000);
            func_80154274(a0, (s32)D_800D4DA8);
            func_80146CA0(a0);
        }
    }
}
