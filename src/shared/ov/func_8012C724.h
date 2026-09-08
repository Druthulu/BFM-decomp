/* func_8012C724 — shared body (overlay slot 0x80128158, h_exact 7207af3c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012C890(s32 a0, s32 a1, s32 a2);
void func_8012C724(s32 a0, s32 a1) {
    *(u16 *)((s32)a0 + 0xA) |= 0x8000;
    func_8012C890(a0, a1, 0);
}
