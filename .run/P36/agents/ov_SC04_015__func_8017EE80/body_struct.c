void func_8017EE80(s32 a0)
{
    struct { s16 x, y, z, last; } *e;
    struct { u16 h[8]; s32 w; } buf;
    s32 obj;
    s32 slot;
    s32 i;

    e = (void *)D_80188838[*(s16 *)(a0 + 0x70)];
    if (e == 0) {
        return;
    }
    for (;;) {
        obj = ((s32 (*)(void))func_8012C194)();
        if (obj != 0) {
            i = 0;
            slot = (s32)&D_801C8C64;
            while (i < 0x20) {
                if (*(s16 *)slot == 0) {
                    break;
                }
                i += 1;
                slot += 0x1C;
            }
            if (i == 0x20) {
                goto next;
            }
            *(s32 *)(slot + 0xC) = obj;
            func_8001CC3C(obj, 0, 0, 0);
            *(s32 *)(obj + 0x20) = (s32)D_801886BC;
            *(u8 *)(obj + 0x27) = 0x4C;
            *(u16 *)(obj + 0x2C) = 0xC020;
            *(u16 *)(obj + 0x1A) = 0x2000;
            *(u16 *)(obj + 0x18) = 0x2000;
            *(u32 *)(obj + 4) |= 0x50000000;
            func_80128EA8(obj, slot + 0x14, (s32)D_801886C8);
            *(u16 *)(slot + 0x0) = 1;
            *(u16 *)(slot + 0x4) = e->x;
            *(u16 *)(slot + 0x6) = e->y;
            *(u16 *)(slot + 0x8) = e->z;
            *(s32 *)(slot + 0x10) = a0;
            buf.h[0] = e->x;
            buf.h[1] = e->y;
            buf.h[2] = e->z;
            buf.h[3] = 0x3DB;
            buf.h[5] = 0;
            buf.h[4] = 0;
            buf.w = 0;
            buf.h[7] = 0;
            buf.h[6] = 0x7FFF;
            func_8012C51C(&buf, a0);
        }
next:
        if (e->last == -1) {
            break;
        }
        e++;
    }
}
