void func_8018003C(s32 arg0)
{
    register s32 s1 __asm__("$17") = arg0;  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B tus8)
    s32 s0;
    s32 v0;
    s32 v1;
    s32 a0;
    register s32 a1 __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus8)
    register s32 a2 __asm__("$6");  // !FAKE: pin $6 — NEEDED DIFFERS (P36 rung B tus8)
    register s32 zr __asm__("$0");  // !FAKE: pin $0 — NEEDED DIFFERS (P36 rung B tus8)

    
    v0 = *(s32 *)(s1 + 0x10);
    v1 = *(s32 *)(s1 + 0x2C);
    a1 = *(s32 *)(s1 + 0x30);
    a2 = *(s32 *)(s1 + 0x34);

    
    s0 = *(s32 *)(s1 + 0x20);

    
    v0 = v0 + v1;
    *(s32 *)(s1 + 0x10) = v0;

    
    v0 = *(s32 *)(s1 + 0x14);
    v1 = *(s32 *)(s1 + 0x18);
    v0 = v0 + a1;
    v1 = v1 + a2;
    *(s32 *)(s1 + 0x14) = v0;
    *(s32 *)(s1 + 0x18) = v1;

    
    ((void (*)(void))func_8012931C)();

    
    a0 = s0 + zr;

    
    v0 = *(u16 *)(s0 + 0x1A);
    v0 = v0 - 0x100;
    *(u16 *)(a0 + 0x1A) = (u16)v0;
    *(u16 *)(a0 + 0x18) = (u16)v0;

    
    if (func_80128ED8(a0, (s32 *)(s1 + 0x24)) != 0) {
        func_801292C8((u8 *)s1);
    } else {
        v0 = *(s32 *)(s1 + 0x1C);
        if (v0 != 0) {
            v0--;
            *(s32 *)(s1 + 0x1C) = v0;
            if (v0 == 0) {
                func_801292C8((u8 *)s1);
            }
        }
    }
}
