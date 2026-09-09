/* func_80140F00 — shared body (overlay slot 0x80128158, h_exact 318e016d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80140F00(void) {
    char *p;
    int r;

    if (D_80115128 == 0) {
        p = (*(char * *)&D_8018021C);
        r = func_800D2CA8(func_80029FE4() + 1, 0x18);
        func_800D2D10(r, 2, p + 4, 1);
        strcpy(p + 0xA, func_8002AAB4());

        p = D_8018023C;
        r = func_800D2CA8(func_8002A26C() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A2B0(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80180240;
        r = func_800D2CA8(func_8002A4B8() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(((int (*)(void))func_8002A4FC)(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80180244;
        r = func_800D2CA8(func_8002A998() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A9DC(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80180248;
        r = func_800D2CA8(func_8002A728() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A76C(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_8018024C;
        r = func_800D2CA8(func_80029FD4(), 4);
        func_800D2D10(r, 7, p + 0x18, -1);
    }
}
