/* func_8013E5E8 — shared body (overlay slot 0x80128158, h_exact 0b4494b1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013E5E8(void)
{

    extern u16 D_8011511E;
    extern u16 D_8011511C;
    extern unsigned short D_80115112;
    extern u16 D_80115116;
    extern void (*D_8017FE78[])(void);
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 -> store retires early */  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers2)
    func_80029444();
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_8017FE78[D_80115112];
    fp();
    func_800190AC();
    func_80141C04();
    D_80115116 += 1;
}
