void func_80015608(s32 arg0, s32 arg1)
{
    u32 *ot;
    u8 *str;
    s32 x0;
    s16 y0;
    s32 flags;
    u8 width;
    u32 code;
    u32 len;
    u32 color;
    u32 yWord;
    s32 *pkt;
    s32 h;

    ot = (u32 *)arg1;
    str = *(u8 **)(arg0 + 8);
    h = *(u16 *)(arg0 + 2);
    x0 = h - (D_800AF7BC >> 1);
    flags = *(u8 *)(arg0 + 0xC);
    h = *(u16 *)(arg0 + 4);
    y0 = h - (D_800AF7BE >> 1);
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
    if (*str != 0) {
        color = code | 0x00808080;
        yWord = y0 << 16;
        do {
            u32 xLow;
            u16 *uv;
            u32 clut;
            u32 mask;
            u32 tag;

            xLow = (u16)x0;
            x0 = width + x0;
            pkt[1] = color;
            pkt[2] = xLow | yWord;
            uv = func_80015908(*str, (u16)flags);
            str++;
            clut = 0x40560000;
            pkt[3] = *uv | clut;
            mask = 0x00FFFFFF;
            tag = *ot & mask;
            tag |= len;
            pkt[0] = tag;
            mask &= (u32)pkt;
            *ot = mask;
            pkt += 4;
        } while (*str != 0);
    }
    D_800A5E60 = (u8 *)pkt;
}
