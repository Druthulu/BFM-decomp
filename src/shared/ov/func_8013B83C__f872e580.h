/* func_8013B83C — shared body (overlay slot 0x80128158, h_exact f872e580). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013B83C(s32 a0, s32 a1, s32 a2) {
                       /* sizeof 0x1C */
    extern Ent_8013B83C D_801DAA08_e[] __asm__("D_8018FA00");
    extern s32 D_8018FA9C;
    extern s32 D_8018FAA0;
    extern s32 D_8018FAA4;
    extern s32 D_8018FAC8;
    extern s32 D_8018FB18;
    extern s32 D_8018FB20;
    extern s16 D_800B9A0E;
    extern void func_80052D90(s32 a0, void *a1);
    extern void func_8013C08C(void *a0, s32 a1);
    s32 i;

    D_8018FAB8 = 0;
    D_8018FAA4 = 0;
    D_8018FAA0 = 0;
    D_8018FA9C = 0;
    func_80052D90(0, &D_8018FAC8);
    if (a0 == 0) {
        return;
    }
    D_8018FB18 = a2 + 500;
    D_8018FB1C = a2;
    for (i = 0; i < 4; i++) {
        D_801DAA08_e[i].f0 = 0;
        D_801DAA08_e[i].f4 = D_801DAA08_e[i].f6 = D_801DAA08_e[i].f8 = 0x6000;
        D_801DAA08_e[i].fC = 0x100;
        D_801DAA08_e[i].f18 = 0;
    }
    switch (*(u8 *)a0) {
    case 0x42:
        if (D_800B9A0E == 0) {
            func_8013BD74(&D_8018FAB8, a0);
        } else {
            func_8013BD74(&D_8018FAB8, a1);
        }
        D_8018FB20 = 0;
        break;
    case 0x43:
        func_8013C08C(&D_8018FAB8, a0);
        D_8018FB20 = 1;
        break;
    case 0x44:
        func_8013C08C(&D_8018FAB8, a0);
        D_8018FB20 = 2;
        break;
    case 0x45:
        func_8013C08C(&D_8018FAB8, a0);
        D_8018FB20 = 3;
        break;
    case 0x46:
        func_8013C08C(&D_8018FAB8, a0);
        D_8018FB20 = 4;
        break;
    case 0x47:
        func_8013C08C(&D_8018FAB8, a0);
        D_8018FB20 = 5;
        break;
    case 0x48:
        func_8013C08C(&D_8018FAB8, a0);
        D_8018FB20 = 6;
        break;
    case 0x49:
        func_8013C08C(&D_8018FAB8, a0);
        D_8018FB20 = 9;
        break;
    case 0x4A:
        func_8013C08C(&D_8018FAB8, a0);
        D_8018FB20 = 0xC;
        break;
    case 0x4B:
        func_8013C08C(&D_8018FAB8, a0);
        D_8018FB20 = 0xD;
        break;
    case 0x4C:
        func_8013C08C(&D_8018FAB8, a0);
        D_8018FB20 = 0xE;
        break;
    case 0x4D:
        func_8013C08C(&D_8018FAB8, a0);
        D_8018FB20 = 0xF;
        break;
    case 0x4E:
        func_8013C08C(&D_8018FAB8, a0);
        D_8018FB20 = 0x10;
        break;
    }
}
