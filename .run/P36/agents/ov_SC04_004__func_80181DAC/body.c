s32 func_80181DAC(s32 arg0) {
    extern u8 D_801202A0[];
    u8 *pe;
    u16 t;
    s32 count;

    pe = D_801202A0;
    for (count = 0; count < 0x60; count++, pe += 0x10C) {
        if ((s32)pe == arg0) {
            continue;
        }
        switch (*(u16 *)pe) {
        case 0x1FC:
            t = (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) * 9u) >> 9;
            if (func_80181E90((s16 *)arg0, (s16 *)(pe + 4), t) != 0) {
                return (s32)pe;
            }
            break;
        case 0x239:
            t = (u32)(*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) + *(s16 *)(*(s32 *)(pe + 0x20) + 0x18)) >> 6;
            if (func_80181E90((s16 *)arg0, (s16 *)(pe + 4), t) != 0) {
                return (s32)pe;
            }
            break;
        }
    }
    return 0;
}
