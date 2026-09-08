/* func_80172414 — shared body (overlay slot 0x80128158, h_exact a63c026a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80161C24(s32, s32);
extern void func_8014C010(s32 a0, s32 a1);
extern u16 D_800B99DA;
void func_80172414(s32 a0) {
    if (*(u16 *)(a0 + 0xB8) & 0x2000) {
        func_80161C24(a0, *(u16 *)(a0 + 0x16E));
    }
    if (*(s32 *)(a0 + 0x2C) < (s32)0xFFF90000) {
        if ((D_800B99DA & 7) == 0) {
            func_8014C010(a0, 2);
        }
    }
}
