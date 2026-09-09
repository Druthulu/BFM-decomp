/* func_80177AD4 — shared body (overlay slot 0x80128158, h_exact c3e9fff4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80177AD4(int param_1, unsigned int param_2) {
    unsigned int c;
    register unsigned int b __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B headers1)
    char *base; short i; int f; int t;
    f = 0x100; i = 0; base = (char *)param_1;
    do {
        c = (param_2 << 16) >> 28;
        b = c;
        if ((c != 0) || (i == 3) || (i == 1)) f = 0;
        param_2 = param_2 << 4; i = i + 1;
        t = *(unsigned short *)(base + 0x1e);
        *(unsigned short *)(base + 0x1e) = f | (t & ~0x100);
        base[0x20] = b * 8 + 8;
        base = base + 0x14;
    } while (i < 4);
}
