s32 func_80183CC4(s16 *a0, s32 a1) {
    u8 *obj;
    u8 *sub;

    obj = func_801290DC(0x44, (u8 *)a0);
    if (obj == NULL) {
        return 0;
    }
    sub = *(u8 **)(obj + 0x20);
    *(u32 *)(sub + 0x20) = (u32)&D_801AE958;
    *(u16 *)(sub + 0x28) = 0x290;
    *(u16 *)(sub + 0x2A) = 0x1A0;
    *(u8 *)(sub + 0x27) = 0x70;
    *(u16 *)(sub + 0x1A) = 1;
    *(u16 *)(sub + 0x18) = 1;
    *(u32 *)(sub + 0x4) |= 0x50000000;
    *(u32 *)(obj + 0x1C) = 1;
    *(u32 *)(obj + 0x2C) = a1;
    *(u8 *)(sub + 0x24) = *(u8 *)(sub + 0x25) = *(u8 *)(sub + 0x26) = a1;
    return (s32)obj;
}
