void func_80141874(void) {

    extern u16 D_8011511E;
    extern u16 D_8011511C;
    extern unsigned short D_80115112;
    extern u16 D_80115116;
    extern void (*D_8018B80C[])(void);
    void (**slot)(void);
    void (*fp)(void);
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    slot = &D_8018B80C[D_80115112];
    fp = *slot;
    fp();
    func_80141C04();
    D_80115116 += 1;
}
