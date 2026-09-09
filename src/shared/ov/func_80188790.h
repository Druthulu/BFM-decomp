/* func_80188790 — shared body (overlay slot 0x80128158, h_exact 61b78167). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 rand(void);
extern u8 *func_8012913C(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern s32 D_80126B58;
void func_80188790(s32 a0) {
    s32 kind;
    register u16 *tp __asm__("$19");  // !FAKE: pin $19 — NEEDED DIFFERS (P36 rung B headers2)
    s32 s4;
    u8 *v1;
    s32 r0;
    s32 r2;
    s32 r3;
    s32 s1;
    s32 fE;
    r0 = rand();
    tp = (u16 *)&D_80126B58;
    __asm__ __volatile__("" : "=r"(tp) : "0"(tp));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B headers2)
    s4 = *(s32 *)(a0 + 0x1C);
    kind = (r0 & 1) ? 0xF : 0xE;
    v1 = func_8012913C(kind);
    if (v1 != 0) {
        r2 = rand();
        s1 = r2 - (r2 / 256) * 256;
        r3 = rand();
        fE = tp[7] + (r3 % 640) - 0x290;
        *(u16 *)(v1 + 0xE) = fE;
        if (s4 & 1) {
            *(u16 *)(v1 + 0x6) = s1 + 0x7A;
            *(u16 *)(v1 + 0xA) = tp[5] - 0xE0;
        } else {
            *(u16 *)(v1 + 0x6) = s1 - 0xF8;
            *(u16 *)(v1 + 0xA) = tp[5] - 0xC0;
        }
        *(u16 *)(v1 + 0x36) = tp[5] - 0x50;
    }
    if (func_8012BEE8(a0) == 1) {
        func_8012C218((void *)a0);
    }
}
