/* func_8017BFEC — shared body (overlay slot 0x80128158, h_exact 1fb2571d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);
void func_8017BFEC(void *a0) {
    if (*(u16 *)(a0 + 0xB8) & 0x8000) {
        func_80154150((s32)a0, 0x27);
        func_80154A74((s32)a0, 0x1F);
        func_80171A1C((u8 *)a0);
        func_80174650((s32)a0);
    }
}
