u8 func_80014DEC(s32 a0, s32 a1) {
    u32 offset;
    a0 &= 0xFF;
    offset = a0 * 76;
    offset = offset + (u32)&D_80078D98;
    a1 &= 0xFF;
    offset = offset + a1;
    return *(u8 *)(offset + 0x32);
}
