extern u16 D_80126B66;

void func_801809E4(s32 a0) {
    s32 v0;
    s16 a2;
    s16 t8c;
    s32 p20;
    s32 frame_pad[2];

    if (*(s32 *)(a0 + 0x1C) != 0) {
        *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) - 1;
        return;
    }
    *(u16 *)(a0 + 6) = 0;
    *(s16 *)(a0 + 0xA) = -0x500;
    v0 = *(s16 *)&D_80126B66;
    a2 = v0;
    t8c = *(s16 *)(a0 + 0x8C);
    if (v0 < t8c) {
        *(s16 *)(a0 + 0xE) = a2 - 0x200;
        return;
    }
    *(s16 *)(a0 + 0xE) = t8c - 0x200;
    p20 = *(s32 *)(a0 + 0x20);
    *(u32 *)(p20 + 4) = *(u32 *)(p20 + 4) & 0x7FFFFFFF;
    *(u16 *)(a0 + 2) = 1;
    (void)&frame_pad;
}
