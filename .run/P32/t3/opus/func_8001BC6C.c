/* addPrim-style sprite emitter: builds a 0x18-byte SPRT-with-tpage packet at the
 * D_800A5E60 prim-buffer cursor and addPrim()s it onto word [1] of the frame's
 * ordering table (D_800A6610 + D_800B9A02 * 0x4000).  Same idiom as the -O0
 * func_8001212C in src/boot.c. */
typedef struct { u32 addr : 24; u32 len : 8; } PTag_8001BC6C;

extern u16 D_800B9A02;
extern u8 D_800A6610[];
extern u8 *D_800A5E60;

void func_8001BC6C(s32 a0, s32 a1)
{
    short *p1 = (short *)a0;
    u8 *p;
    u32 *ot;
    register u32 color __asm__("$5");
    register short f0 __asm__("$2");
    u32 tag;
    u32 c;
    u32 c2;
    u32 k;
    u32 idx;
    u32 code;
    unsigned short f1;
    short f2;
    unsigned short f3;
    unsigned short x1;
    unsigned short y1;
    short t0;

    code = 0x100;
    c = a1 << 16;
    k = 0x64000000;
    f0 = p1[0];
    f1 = p1[1];
    f2 = p1[2];
    f3 = p1[3];
    p = D_800A5E60;
    x1 = f0 - 0xA0;
    y1 = f1 - 0x78;
    t0 = f0;
    tag = (a1 << 8) | k;
    c2 = c | tag;
    idx = D_800B9A02 << 14;
    color = c2 | a1;
    ot = (u32 *)(idx + (u32)D_800A6610);

    if (t0 >= 0x80) {
        t0 -= 0x80;
        code = 0x102;
    }

    *(u8 *)(p + 3) = 5;
    *(u32 *)(p + 4) = code | 0xE1000000;
    *(u8 *)(p + 0xB) = 100;
    *(u32 *)(p + 0xC) = ((u32)y1 << 16) | (u32)x1;
    *(u32 *)(p + 0x10) = (u32)(((s32)((u32)f1 << 16) >> 8) | (s32)t0);
    *(u32 *)(p + 8) = color;
    *(u32 *)(p + 0x14) = ((u32)f3 << 16) | (u32)f2;
    ((PTag_8001BC6C *)p)->addr = ((PTag_8001BC6C *)(ot + 1))->addr;
    D_800A5E60 = p + 0x18;
    ((PTag_8001BC6C *)(ot + 1))->addr = (u32)p;
}
