s32 func_80189C4C(void *a0) {
    void *p0, *p1;
    u16 v;

    p0 = *(void**)((u8*)a0 + 0x20);
    p1 = *(void**)((u8*)a0 + 0x6C);
    v = *(u16*)((u8*)p0 + 0x12);
    p1 = *(void**)((u8*)p1 + 0x20);
    v += 0x800;
    v &= 0xFFF;
    *(u16*)((u8*)p1 + 0x12) = v;
    *(u16*)((u8*)a0 + 0x2) = 2;
    return 2;
}
