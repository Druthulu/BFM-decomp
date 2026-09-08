/* func_80149290 — shared body (overlay slot 0x80128158, h_exact 5bcf2335). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149350(s32 arg0);
void func_80149290(s32 a0) {
    volatile s32 a;
    volatile s32 b;
    volatile s32 c;
    a = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
    b = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
    c = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48) = *(s16 *)(a0 + 6);
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C) = *(s16 *)(a0 + 0xA);
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50) = *(s16 *)(a0 + 0xE);
    func_80149350(a0);
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48) = a;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C) = b;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50) = c;
}
