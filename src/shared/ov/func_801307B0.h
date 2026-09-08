/* func_801307B0 — shared body (overlay slot 0x80128158, h_exact b47c4a6b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801312D0(s32 a0, void *a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8002D4C8(s32 a0, s32 a1);
void func_801307B0(s32 a0) {
    s16 local[3];
    *(s8 *)(a0 + 0xC1) = 0x10;
    *(s16 *)(a0 + 0x5C) = 0;
    func_801312D0(a0, &local[0]);
    func_80146A6C(0x10, (void *)a0,
                  (s16)(*(u16 *)(a0 + 0x6) + (u16)local[0]),
                  (s16)(*(u16 *)(a0 + 0xA) + (u16)local[1]),
                  (s16)(*(u16 *)(a0 + 0xE) + (u16)local[2]),
                  0, 0);
    *(s32 *)(a0 + 0x1C) = 0x1E;
    *(s32 *)(a0 + 0x18) = 0;
    *(s32 *)(a0 + 0x10) = 0;
    func_8002D4C8(0x531, 0);
}
