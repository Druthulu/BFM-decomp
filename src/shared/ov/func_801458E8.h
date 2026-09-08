/* func_801458E8 — shared body (overlay slot 0x80128158, h_exact c9b05511). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
void func_801458E8(void) {
    D_800AE6B0 = D_800AE6AC | 0x1000000;
    func_800D185C(&D_80078E50);
    D_800B9A0A = 0x3000;
}
