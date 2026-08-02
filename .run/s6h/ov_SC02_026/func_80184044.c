extern void (*D_801AF974[])(void *);
extern u8 D_801202A0[];

void func_80184044(u8 *s0) {
    u16 v0;
    s32 a0;
    u8 *v1;

    // Call indirect function based on index at s0[2]
    v0 = *(u16 *)(s0 + 0x2);
    ((void (*)(u8 *))D_801AF974[v0])(s0);

    // Check if s0[0] is zero
    v0 = *(u16 *)(s0);
    if (v0 == 0) return;

    // Check if s0[0x100] & 0x1000 is zero
    v0 = *(u16 *)(s0 + 0x100);
    if ((v0 & 0x1000) == 0) return;

    // Search for entry in D_801202A0 table
    v1 = D_801202A0;
    for (a0 = 0; a0 < 0x60; a0++) {
        if (*(u16 *)(v1) == 0x15E) {
            s16 v1_val = *(s16 *)(v1 + 0x6);
            s16 s0_val = *(s16 *)(s0 + 0x6);
            if (s0_val < v1_val + 0xF0) {
                *(s16 *)(s0 + 0x6) = v1_val + 0xF0;
            }
            return;
        }
        v1 += 0x10C;
    }
}
