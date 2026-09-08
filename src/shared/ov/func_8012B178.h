/* func_8012B178 — shared body (overlay slot 0x80128158, h_exact c8e802f6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
void func_8012B178(s32 a0, s32 a1) {
    s32 sp10[3];
    sp10[2] = a1;
    sp10[1] = 0;
    sp10[0] = 0;
    func_800484EC(*(s32 *)(a0 + 0x20) + 0x34, (s32)sp10, a0 + 0x10);
}
