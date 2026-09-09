/* func_80139BE0 — shared body (overlay slot 0x80128158, h_exact 429047be). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80139BE0(int param_1)
{

    extern unsigned char D_8017F090[];
    int v;

    if ((*(unsigned int *)(param_1 + 8) & 0x2000) == 0) {
        int t = *(unsigned char *)(param_1 + 0x22) & 0x60;
        int h = *(unsigned short *)(param_1 + 0x18);
        unsigned int idx;

        __asm__("" : "=r"(t) : "0"(t));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B headers2)
        idx = (unsigned char)t;
        if (h < 7) {
            if (h >= 2) {
                v = D_8017F090[idx >> 5];
            } else {
                v = D_8017F090[0];
            }
        } else {
            v = D_8017F090[0];
        }
        *(short *)(param_1 + 0x2e) = 3;
        *(short *)(param_1 + 0x2c) = v;
    }
    *(short *)(param_1 + 0x34) = *(short *)(param_1 + 0x2c) * 6;
    {
        int x = *(short *)(param_1 + 0x2e);
        *(short *)(param_1 + 0x36) = x * 12 + (x - 1) * 2;
    }
}
