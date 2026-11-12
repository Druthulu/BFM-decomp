/* guess_SwapGameVarSlots — shared body (overlay slot 0x80128158, h_exact 5a2a3909). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_GetGameVarByte(s32 arg);
extern void func_800291A0(s32, s32);
extern s32 func_800291DC(s32);
extern void func_800291C8(s32, s32);
/* guess_SwapGameVarSlots: swaps game-variable bytes 0x2F + a0 and 0x2F + a1 and halfwords 0x14 + 2*a0 and 0x14 + 2*a1
 * Confidence medium, code inference: byte vars 0x2F+a0 <-> 0x2F+a1 (guess_GetGameVarByte / func_800291A0); s16 vars at 0x14+2a0 <-> 0x14+2a1 (func_800291DC / func_800291C8)
 * Names ledger: config/names.tsv guess_SwapGameVarSlots */
void guess_SwapGameVarSlots(s32 param_1, s32 param_2) {
    register s32 a __asm__("$16");  /* $s0: param_2 raw -> sext -> *2+0x14 */  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B headers1) wall:lreg-priority
    register s32 b __asm__("$17");  /* $s1: param_1 sext / *2+0x14 */  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B headers1) wall:lreg-priority
    s32 c;  /* $s2: param_2 sext + 0x2F   */
    s32 d;  /* $s3: param_1 sext + 0x2F   */
    s32 e;  /* $s4: 291B4(d)&0xFF / 291DC(b) */
    a = param_2;
    b = (s16)param_1;
    d = b + 0x2F;
    e = guess_GetGameVarByte(d) & 0xFF;
    a = (s16)a;
    c = a + 0x2F;
    func_800291A0(d, guess_GetGameVarByte(c) & 0xFF);
    func_800291A0(c, e);
    b = b * 2 + 0x14;
    e = func_800291DC(b);
    a = a * 2 + 0x14;
    func_800291C8(b, (s16)func_800291DC(a));
    func_800291C8(a, (s16)e);
}
