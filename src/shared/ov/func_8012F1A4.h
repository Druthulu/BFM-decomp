/* func_8012F1A4 — shared body (overlay slot 0x80128158, h_exact b845fef5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
void func_8012F1A4(s32 *a0, s32 a1, s32 *a2) {
    func_800484EC((s32)a0, a1, (s32)a2);
    a2[0] += a0[0x14 / 4] << 16;
    a2[1] += a0[0x18 / 4] << 16;
    a2[2] += a0[0x1C / 4] << 16;
}
