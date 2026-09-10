void func_80141874(void) {

    extern u16 D_8011511C;
    extern u16 D_80115116;
    extern void (*D_8019182C[])(void);
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 → store retires early */  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_8019182C[D_80115112];
    fp();
    func_80141C04();
    D_80115116 += 1;
}
