/* func_8014ACE8 — shared body (overlay slot 0x80128158, h_exact e5c6980f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014AD30(s32 a0, u16 *a1, s32 a2, s32 a3);
void func_8014ACE8(void *a0, s32 a1, s32 a2) {
    u16 sp[4];
    sp[0] = *(u16 *)((s32)a0 + 0x6);
    sp[1] = *(u16 *)((s32)a0 + 0xA) - 0x20;
    sp[2] = *(u16 *)((s32)a0 + 0xE);
    func_8014AD30((s32)a0, sp, a1, a2);
}
