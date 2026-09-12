/* func_80130898 — shared body (overlay slot 0x80128158, h_exact 5d177039). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80131CA8();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
void func_80130898(u8 *a0) {
    if (*(s32 *)(a0 + 0xB4) & 0x4000) {
        *(s16 *)(a0 + 0xAA) = 0x100;
        *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) & 0xFFFE;
    }
    func_80131CA8((int)a0, 0x28);
}
