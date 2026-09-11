void func_801A5094(void)
{
    Vec16_801A5094 vec0;
    Vec32_801A5094 vec1;
    s32 flag;
    s32 p;
    s32 r;

    vec0.vx = (rand() % 320) - 160;
    vec0.vy = -((rand() & 0x7F) + 0x40);
    vec0.vz = -((rand() & 0x3F) + 0x20);

    RotTransSV((s32)&vec0, (s32)&vec0, &flag);

    p = (s32)func_801290DC(0x2E, (u8 *)&vec0);
    if (p != 0) {
        *(u16 *)(*(s32 *)(p + 0x20) + 0x2C) = 0xC020;
        vec1.vx = 0;
        vec1.vy = 0;
        r = rand();
        vec1.vz = -(((r & 7) + 0x20) << 16);
        ApplyRotMatrixLV(&vec1, (void *)(p + 0x10));
        D_801F8747[0] = 1;
        __asm__ __volatile__(""); // !FAKE: barrier D_801F8747 store vs D_801F8744 load — sched.c:753-778 memrefs_conflict_p calls two distinct SYMBOL_REFs independent; the byte at 0x801F8747 IS D_801F8744+3 (one 4-byte object split by symbolization); plain C D_801F8744[3] = 1 needs no barrier (body_symbol.c) (P36 S104 e8 minimum-lever)
        *(s32 *)(p + 0x34) = *(s32 *)D_801F8744;
        *(s16 *)(p + 0x30) = 6;
    }
}
