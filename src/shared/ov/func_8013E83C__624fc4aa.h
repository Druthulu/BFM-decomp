/* func_8013E83C — shared body (overlay slot 0x80128158, h_exact 624fc4aa). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013E83C() {
    extern void func_80141C0C(int);
    extern unsigned short D_80115118;
    extern unsigned short D_80115128;
    extern unsigned short D_8011512E;
    extern unsigned int D_80115130;
    extern unsigned short D_80115158;
    extern unsigned short D_8011515A;
    extern unsigned short D_8011515C;
    extern unsigned short D_8011515E;
    extern unsigned short D_80115162;
    extern unsigned short D_80115166;
    extern void * D_8018E7C0;
    extern void * D_8018E7C4;
    extern unsigned char D_80180290;
    extern unsigned char D_801802A8;
    extern unsigned char D_8018031C;
    extern unsigned char D_80180324;


    D_80115118 = 0;
    D_80115130 = 0;
    if (D_8011511A >= 4) {
        D_8011511A = D_8011511A - 3;
    }
    D_80115158 = 0x106;

    if ((((int(*)(int))func_80029178)(0x1c) & 0xFF) == 0) {
        D_8018E7C0 = &D_80180290;
        D_8018E7C4 = &D_8018031C;
    } else {
        D_8018E7C0 = &D_801802A8;
        D_8018E7C4 = &D_80180324;
    }

    D_8011515A = 0x104;
    D_8011515C = 0x104;
    D_8011515E = 0x129;
    D_80115162 = 0x103;
    D_80115166 = 0x105;
    D_80115128 = 0;
    D_8011512E = 0;

    if (D_80115110 == 3) {
        ((void(*)(int, int))func_8002D4C8)(0x46e, 0);
    } else {
        func_80141C0C(0);
    }
}
