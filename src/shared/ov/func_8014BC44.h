/* func_8014BC44 — shared body (overlay slot 0x80128158, h_exact 9c835fc8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_80078EB2;
extern void func_8014BC80(s32 a0, s32 a1);
void func_8014BC44(s32 a0, s32 a1) {
    if (*(s32 *)((s32)a0 + 0x44) & 0x2000000) {
        a1 = D_80078EB2;
    }
    func_8014BC80(a0, a1);
}
