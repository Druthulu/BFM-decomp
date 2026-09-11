void func_80185D44(void *a0) {
    s32 v0;
    s32 v1;
    s32 m;
    s16 t;
    u8 *p;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }
    func_8001C214(v0, (s32)D_801A0734);
    m = 0x7FFF0000;
    __asm__("" : "=r"(m) : "0"(m));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus10)
    t = 0x80;
    *(s16 *)((s32)a0 + 0xE0) = t;
    *(s16 *)((s32)a0 + 0xDE) = t;
    *(s16 *)((s32)a0 + 0xDC) = t;
    t = -2;
    *(s16 *)((s32)a0 + 0xE2) = t;
    p = (u8 *)D_801DDBF4;
    v1 = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(v1 + 0x2C) |= 0x80;
    v1 = *(s32 *)((s32)a0 + 0x20);
    *(s32 *)(v1 + 0x80) = (s32)a0 + 0xDC;
    *(s16 *)(p + 0x1A) = 0x800;
    *(s16 *)(p + 0x18) = 0x800;
    m |= 0xFFFF;
    *(s32 *)(p + 4) &= m;
    *(u16 *)((s32)a0 + 2) = *(u16 *)((s32)a0 + 2) + 1;
}
