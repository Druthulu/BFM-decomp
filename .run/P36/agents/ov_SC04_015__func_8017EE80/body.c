void func_8017EE80(s32 a0)
{
    u8 *e;
    s32 obj;
    s32 slot;
    s32 i;
    u16 buf[10];

    e = (u8 *)D_80188838[*(s16 *)(a0 + 0x70)];
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
            if (i != 0x20) {
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
                *(u16 *)(slot + 0x4) = *(u16 *)e;
                *(u16 *)(slot + 0x6) = *(u16 *)(e + 2);
                *(u16 *)(slot + 0x8) = *(u16 *)(e + 4);
                *(s32 *)(slot + 0x10) = a0;
                buf[0] = *(u16 *)e;
                buf[1] = *(u16 *)(e + 2);
                buf[2] = *(u16 *)(e + 4);
                buf[3] = 0x3DB;
                buf[5] = 0;
                buf[4] = 0;
                *(u32 *)&buf[8] = 0;
                buf[7] = 0;
                buf[6] = 0x7FFF;
                func_8012C51C(buf, a0);
            }
        }
        if (*(s16 *)(e + 6) == -1) {
            break;
        }
        e += 8;
    }
}
