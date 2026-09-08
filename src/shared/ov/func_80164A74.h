/* func_80164A74 — shared body (overlay slot 0x80128158, h_exact 3c26b0df). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80148534(s32 a0, s32 a1);
extern void func_80015954(s32 a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
void func_80164A74(s32 *a0) {
    s32 sp10[2];
    s32 sp18[2];
    s32 s1 = a0[0x4C / 4];
    func_80148534((s32)sp10, (s32)sp18);
    func_80015954((s32)sp10, (s32)a0 + 4);
    func_80149374(s1, (s32)a0 + 4);
}
