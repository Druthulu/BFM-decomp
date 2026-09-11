u8 func_80014DEC(s32 a0, s32 a1) {
    s32 v0;
    a0 = a0 & 0xFF;
    v0 = (a0 << 2) + a0;
    v0 = (v0 << 2) - a0;
    v0 = v0 << 2;
    v0 = v0 + (s32)&D_80078D98;
    a1 = a1 & 0xFF;
    v0 = v0 + a1;
    return *(u8 *)(v0 + 0x32);
}
