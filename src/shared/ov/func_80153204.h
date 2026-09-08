/* func_80153204 — shared body (overlay slot 0x80128158, h_exact 382328a6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149020(s32 *a0);
extern s32 func_80153800(s32 a0);
extern void func_80146D90(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80159B3C(void *a0);
extern void func_80165718(s32 a0);
void func_80153204(s32 *a0) {
    /* reserved stack local sets frame 0x28 (16-byte local region) */
    volatile s32 pad[4];
    func_80149020(a0);
    if (func_80153800((s32)a0) == 0) {
        *(u16 *)((u8 *)a0 + 0x4) = 0;
        *(u16 *)((u8 *)a0 + 0x8) = 0;
        *(u16 *)((u8 *)a0 + 0xC) = 0;
        *(u16 *)((u8 *)a0 + 0x6) = *(u16 *)((u8 *)a0 + 0x88);
        *(u16 *)((u8 *)a0 + 0xA) = *(u16 *)((u8 *)a0 + 0x8A);
        *(u16 *)((u8 *)a0 + 0xE) = *(u16 *)((u8 *)a0 + 0x8C);
        func_80146D90((s32)a0);
        func_8015327C((s32)a0);
        func_80159B3C((s32)a0);
        func_80165718((s32)a0);
    }
}
