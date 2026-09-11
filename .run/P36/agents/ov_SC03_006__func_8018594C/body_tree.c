u8 * func_8018594C(s32 a0, s32 a1, s32 a2) {
    s32 s0 = a2;
    register s32 s2 __asm__("$18") = a0;  // !FAKE: pin $18 — NEEDED DIFFERS (P36 rung B tus7)
    u8 *s1;
    u8 *ret;
    register s32 v1 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus7)

    s1 = func_801290DC(0x17, (u8 *)a1);

    if (!s1) {
        return NULL;
    }

    s0 = *(s32 *)((char *)s1 + 0x20);
    func_8001CD50(s0, (s32)(&((u8 *)D_801C5988)[a2 << 6]));

    
    __asm__ volatile("move %0, %1" : "=r"(ret) : "r"(s1));  // !FAKE: instruction move — NEEDED DIFFERS (P36 rung B tus7)

    v1 = 0xC00;
    *(u16 *)((char *)s0 + 0x1E) = v1;
    v1 = 0x1000;
    *(u16 *)((char *)s0 + 0x1A) = v1;
    *(u16 *)((char *)s0 + 0x18) = v1;
    v1 = *(s32 *)((char *)s0 + 0x4);
    *(u16 *)((char *)s0 + 0x12) = s2;
    v1 |= 0x40000000;
    *(s32 *)((char *)s0 + 0x4) = v1;

    return ret;
}
