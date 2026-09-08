/* func_8012A8B0 — shared body (overlay slot 0x80128158, h_exact 5f61e157). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012AAAC();
void func_8012A8B0(u8 *a0, s32 a1) {
    u16 v0 = *(u16 *)(a0 + 0x72);
    *(s32 *)(a0 + 0x90) = a1;
    *(s32 *)(a0 + 0x94) = 0;
    *(s32 *)(a0 + 0x9C) = 0;
    *(s16 *)(a0 + 0x9A) = 0;
    *(u16 *)(a0 + 0x72) = v0 & 0xF9FF;
    func_8012AAAC();
}
