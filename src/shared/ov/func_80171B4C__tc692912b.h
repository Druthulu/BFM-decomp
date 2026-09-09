/* func_80171B4C — shared body (overlay slot 0x80128158, h_text c692912b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80171B4C(arg0, arg1)
s32 arg0;
u8 arg1;
{
    s32 p, ang, idx;
    u8 c;
    p = D_801151D4;
    *(u8 *)(arg0 + 0xA9) = 0x41;
    ang = ratan2(*(s32 *)(p + 0x68) - *(s32 *)(p + 0x5C),
                 *(s32 *)(p + 0x70) - *(s32 *)(p + 0x64));
    idx = ((*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) - ((ang + 0x800) & 0xFFF)) + 0x100) & 0xE00;
    switch (idx / 0x200) {
    case 0: *(u16 *)(arg0 + 0xAA) = 0x1000; break;
    case 1: *(u16 *)(arg0 + 0xAA) = 0x3000; break;
    case 2: *(u16 *)(arg0 + 0xAA) = 0x2000; break;
    case 3: *(u16 *)(arg0 + 0xAA) = 0x6000; break;
    case 4: *(u16 *)(arg0 + 0xAA) = 0x4000; break;
    case 5: *(u16 *)(arg0 + 0xAA) = 0xC000; break;
    case 6: *(u16 *)(arg0 + 0xAA) = 0x8000; break;
    case 7: *(u16 *)(arg0 + 0xAA) = 0x9000; break;
    }
    c = *(u8 *)(arg0 + 0x20C);
    *(u8 *)(arg0 + 0x20C) = c + 1;
    if (c != arg1) {
        return 0;
    }
    func_80146D90(arg0);
    return 1;
}
