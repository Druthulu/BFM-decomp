/* func_8015E22C — shared body (overlay slot 0x80128158, h_exact abafb4f2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154274(s32 *a0, s32 a1);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146CA0(void *a0);
extern u8 D_800D4FF4[];
void func_8015E22C(s32 a0) {
    func_80154274((s32 *)a0, (s32)D_800D4FF4);
    *(s32 *)(a0 + 0x234) = 0;
    func_80146994(5, a0, 0xA, 0);
    *(s32 *)(a0 + 0x44) |= 2;
    func_80146CA0((void *)a0);
}
