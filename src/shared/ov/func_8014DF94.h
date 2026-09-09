/* func_8014DF94 — shared body (overlay slot 0x80128158, h_exact ffc0ad5d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014E284(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014E048(s32 a0, u16 *a1, u16 *a2); /* u16*: def lhu semantics (T5b reconcile; ptr param type codegen-neutral for the caller) */
void func_8014DF94(s32 arg0) {
    s16 a[3];
    s16 b[3];
    s32 u88;
    s32 u8C;
    s32 t;
    s32 t2;
    u88 = *(u16 *)(arg0 + 0x88);
    a[0] = u88;
    a[1] = *(u16 *)(arg0 + 0x8A) - 0x10;
    u8C = *(u16 *)(arg0 + 0x8C);
    a[2] = u8C;
    t = *(u16 *)(arg0 + 6);
    b[0] = t;
    b[1] = *(u16 *)(arg0 + 0xA) - 0x10;
    t = t - u88;
    t2 = *(u16 *)(arg0 + 0xE);
    u88 = u88 - t;
    b[0] = t;
    __asm__ __volatile__("" : : : "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B headers1)
    b[0] = u88;
    b[2] = t2;
    __asm__ __volatile__("" : : : "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B headers1)
    t2 = t2 - u8C;
    u8C = u8C - t2;
    b[2] = t2;
    __asm__ __volatile__("" : : : "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B headers1)
    b[2] = u8C;
    if (*(s32 *)(arg0 + 0x170) == 0) {
        func_8014E284(arg0, a, b);
    } else {
        func_8014E048(arg0, a, b);
    }
}
