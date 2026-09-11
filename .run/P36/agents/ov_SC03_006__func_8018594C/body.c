u8 *func_8018594C(s16 a0, u8 *a1, s32 a2) {
    u8 *obj;
    u8 *sub;

    obj = func_801290DC(0x17, a1);
    if (obj == NULL) {
        return NULL;
    }

    sub = *(u8 **)(obj + 0x20);
    func_8001CD50((s32)sub, (s32)((u8 *)D_801C5988 + (a2 << 6)));

    *(u16 *)(sub + 0x1E) = 0xC00;
    *(u16 *)(sub + 0x1A) = 0x1000;
    *(u16 *)(sub + 0x18) = 0x1000;
    *(u16 *)(sub + 0x12) = a0;
    *(s32 *)(sub + 0x4) |= 0x40000000;

    return obj;
}
