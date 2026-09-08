/* func_8012C438 — shared body (overlay slot 0x80128158, h_exact 26de808c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8001CFDC(s32 a, s32 b);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern u8 D_80078EAE;
s32 func_8012C438(s32 a0, s32 a1) {
    s32 v;
    *(s32*)(a0 + 0x78) = a1;
    if (D_80078EAE == 0) {
        v = (*(s16*)(a1 + 0x0) * 24) / 16;
    } else {
        v = *(u16*)(a1 + 0x0);
    }
    *(s16*)(a0 + 0x76) = v;
    *(s16*)(a0 + 0x5C) = *(u16*)(a1 + 0x2);
    if (*(s32*)(a1 + 0x4) != 0) {
        *(s32*)(a0 + 0x20) = ((s32 (*)(s32, s32))func_8001CFDC)(0x26, 0x85);
        if (*(s32*)(a0 + 0x20) == 0) {
            func_8012CAE4((void *)a0);
            return 0;
        }
        func_8001C810(*(s32*)(a0 + 0x20), *(s32*)(a1 + 0x4));
    }
    if (*(s32*)(a1 + 0x8) != 0) {
        *(s32*)(a0 + 0x58) = *(s32*)(a1 + 0x8) | 0x60000000;
    }
    return 1;
}
