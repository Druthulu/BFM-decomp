extern u16 D_800B9A02;
extern u8 D_800A6610[];
extern u8 *D_800A5E60;

void func_8001BC6C(s32 a0, s32 a1)
{
    short *p1 = (short *)a0;
    u8 *p;
    u32 *tbl;
    u32 tblAddr;
    register u32 color __asm__("$5");
    u32 code;
    register short f0 __asm__("$2");
    unsigned short f1;
    short f2;
    unsigned short f3;
    unsigned short x1;
    unsigned short y1;
    short t0;
    u32 val;
    u32 t1v, t2v;
    u32 m24;

    code = 0x100;
    f0 = p1[0];
    f1 = p1[1];
    f2 = p1[2];
    f3 = p1[3];
    p = D_800A5E60;
    x1 = f0 - 0xA0;
    y1 = f1 - 0x78;
    t0 = f0;
    tblAddr = (D_800B9A02 << 14) + (u32)D_800A6610;
    tbl = (u32 *)tblAddr;
    color = (a1 << 16) | ((a1 << 8) | 0x64000000) | a1;

    if (t0 >= 0x80) {
        t0 -= 0x80;
        code = 0x102;
    }

    m24 = 0xFFFFFF;

    *(u8 *)(p + 3) = 5;
    *(u32 *)(p + 4) = code | 0xE1000000;
    *(u8 *)(p + 0xB) = 100;
    *(u32 *)(p + 0xC) = ((u32)y1 << 16) | (u32)x1;
    *(u32 *)(p + 0x10) = (u32)(((s32)((u32)f1 << 16) >> 8) | (s32)t0);
    *(u32 *)(p + 8) = color;
    *(u32 *)(p + 0x14) = ((u32)f3 << 16) | (u32)f2;

    val = *(u32 *)p;
    D_800A5E60 = p + 0x18;
    t1v = tbl[1];
    val = (val & 0xFF000000) | (t1v & m24);
    *(u32 *)p = val;

    t2v = tbl[1];
    t2v = (t2v & 0xFF000000) | ((u32)p & m24);
    tbl[1] = t2v;
}
