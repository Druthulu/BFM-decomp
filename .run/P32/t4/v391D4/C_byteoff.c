void func_800391D4(s32 arg0, s16 arg1, s16 arg2) {
    extern u8 D_800C6DD0[];
    extern u8 D_800C6DD4[];
    extern s32 D_80073140[];
    extern s32 D_800C7D20;
    extern s32 D_800A2B98;
    extern u8 *D_800762B0;
    extern u8 D_800762B4[];

    u8 *base;
    u8 *entry;
    register s32 i __asm__("$7");
    s32 off;
    s32 mask;

    i = 0;
    base = arg0 + arg2 * 0x1A;
    off = 0;
    do {
        __asm__("");
        __asm__("");
        __asm__("");
        __asm__("");
        __asm__("");
        __asm__("");
        __asm__("");
        if (*(base + i + 0x23) != 0 && *(s16 *)&D_800C6DD4[off] == arg1) {
            entry = &D_800C6DD0[(s16)i * 0x60];
            if (entry[0x5A] != 0) {
                s32 off2;
                u8 *base2;
                off2 = *(s16 *)(entry + 6) * 0x1A;
                base2 = *(s32 *)(entry + 0x50);
                *(base2 + off2 + (s16)i + 0x23) = 0;
                entry[0x5A] = 0;
            }
            mask = *(s32 *)((u8 *)D_80073140 + i * 4);
            D_800C7D20 &= ~mask;
            D_800A2B98 |= mask;
            D_800762B0[i] = 2;
            D_800762B4[i] = 0;
        }
        i++;
        off += 0x60;
    } while (i < 0x10);
}
