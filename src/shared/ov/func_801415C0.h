/* func_801415C0 — shared body (overlay slot 0x80128158, h_exact 5a2a3909). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_800291B4(s32 arg);
extern void func_800291A0(s32, s32);
extern s32 func_800291DC(s32);
extern void func_800291C8(s32, s32);
void func_801415C0(s32 param_1, s32 param_2) {
    register s32 a __asm__("$16");  /* $s0: param_2 raw -> sext -> *2+0x14 */  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B headers1)
    register s32 b __asm__("$17");  /* $s1: param_1 sext / *2+0x14 */  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B headers1)
    s32 c;  /* $s2: param_2 sext + 0x2F   */
    s32 d;  /* $s3: param_1 sext + 0x2F   */
    s32 e;  /* $s4: 291B4(d)&0xFF / 291DC(b) */
    a = param_2;
    b = (s16)param_1;
    d = b + 0x2F;
    e = func_800291B4(d) & 0xFF;
    a = (s16)a;
    c = a + 0x2F;
    func_800291A0(d, func_800291B4(c) & 0xFF);
    func_800291A0(c, e);
    b = b * 2 + 0x14;
    e = func_800291DC(b);
    a = a * 2 + 0x14;
    func_800291C8(b, (s16)func_800291DC(a));
    func_800291C8(a, (s16)e);
}
