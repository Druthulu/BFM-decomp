void aF80183E20(void *a0) {
    extern u16 D_801EFD40;
    extern u16 aEFD24 __asm__("D_801EFD24");
    u16 flags;
    u16 cnt;
    s32 v0;
    s32 v1;
    s32 v1b;
    flags = D_801EFD40;
    if (flags & 0x80) {
        v0 = *(u16 *)((u8 *)a0 + 0x76);
        v1 = *(u16 *)((u8 *)a0 + 0x60);
        *(u16 *)((u8 *)a0 + 0x60) = 0;
        v0 = v0 - v1;
        *(u16 *)((u8 *)a0 + 0x76) = v0;
        v1b = *(s16 *)((u8 *)a0 + 0x76);
        D_801EFD40 = flags & 0xFF7F;
        if (v1b < 0) {
            *(u16 *)((u8 *)a0 + 0x76) = 0;
        }
    }
    cnt = aEFD24;
    if (cnt != 0) {
        cnt = cnt - 1;
        aEFD24 = cnt;
        if (cnt == 0) {
            func_80186AB8();
        }
    }
}
