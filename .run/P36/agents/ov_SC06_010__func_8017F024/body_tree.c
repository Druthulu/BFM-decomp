void func_8017F024(s32 a0) {
    register s32 *p __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus7)
    s32 self;

    D_8018AFBC[*(u16 *)(a0 + 2)]();
    if (*(u16 *)a0 != 0) {
        __asm__ __volatile__("" : "=r"(self) : "0"(a0));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus7)
        p = *(s32 **)(a0 + 0x20);
        p[1] |= 0x80000000;
        func_8012B2CC(self);
    }
}
