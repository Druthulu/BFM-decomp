void func_80015760(Obj_80015760 *obj, s32 *ot)
{
    s32 x0;
    s16 y0;
    s32 flags;
    u32 value;
    u32 digits;
    s32 count;
    u8 digitCount;
    u8 width;
    u32 code;
    u32 len;
    u32 color;
    u32 yWord;
    s32 *pkt;

    x0 = obj->x - (D_800AF7BC >> 1);
    flags = obj->flags;
    y0 = obj->y - (D_800AF7BE >> 1);
    value = obj->value;
    count = flags & 0xF;
    digitCount = count;
    if (count == 0) {
        digitCount = 8;
    }
    if (flags & 0x40) {
        digits = func_80015A74(value);
    } else {
        digits = value;
    }
    width = 8;
    if (flags & 0x80) {
        width = 0x10;
    }
    if (width == 8) {
        code = 0x74000000;
        len = 0x03000000;
    } else {
        code = 0x7C000000;
        len = 0x03000000;
    }
    pkt = (s32 *)D_800A5E60;
    if (digitCount != 0) {
        color = code | 0x00808080;
        yWord = y0 << 16;
        do {
            u32 xLow;
            u32 idx;
            s32 tile;
            u16 *uv;
            u32 clut;
            u32 mask;
            u32 tag;

            xLow = (u16)x0;
            x0 = width + x0;
            idx = (digits >> ((digitCount - 1) << 2)) & 0xF;
            tile = D_80062B78[idx];
            pkt[1] = color;
            digitCount--;
            pkt[2] = xLow | yWord;
            uv = func_80015908(tile, (u16)flags);
            clut = 0x40560000;
            pkt[3] = *uv | clut;
            mask = 0x00FFFFFF;
            tag = *ot & mask;
            tag |= len;
            pkt[0] = tag;
            mask &= (u32)pkt;
            *ot = mask;
            pkt += 4;
        } while (digitCount != 0);
    }
    D_800A5E60 = (u8 *)pkt;
}
