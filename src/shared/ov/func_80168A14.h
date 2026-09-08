/* func_80168A14 — shared body (overlay slot 0x80128158, h_exact 2fb7442f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_80168A14(s32 *a0) {
    func_80168BDC((s32)a0, 8, 1, 2);
    func_80146A6C(3, (s32)a0,
                  *(s16 *)((u8 *)a0 + 0x6),
                  *(s16 *)((u8 *)a0 + 0xA),
                  *(s16 *)((u8 *)a0 + 0xE),
                  -5, 0xC0009C00);
    *(u16 *)((u8 *)a0 + 0x2) += 1;
}
