void func_801842CC(s32 arg0)
{
    s32 i;
    for (i = 0; i < 0x49; i += 0x18) {
        s32 e = func_80132EF4(arg0, 0x22);
        if (e != 0) {
            s32 t;
            s32 v;
            s32 d;
            s32 z;
            t = *(u16 *)(arg0 + 0x84) & 4;
            z = *(u16 *)(e + 0xE);
            d = i + t * 3 - 0x2A;
            do {  // !FAKE: do-while — its LOOP notes are sched1 barriers (sched.c:2053-2080): the +6 load stays after d, the +E store before the sign extension (P36 S104 e28)
                v = *(u16 *)(e + 0x6);
                z += 0x28;
                *(u16 *)(e + 0xE) = z;
            } while (0);
            v -= d;
            *(u16 *)(e + 0x6) = v;
            v = *(u16 *)(e + 0xA);
            v -= 0x20;
            *(u16 *)(e + 0xA) = v;
            v = (s16)d;
            if (v >= 0) {
                v = v << 7;
            } else {
                v = -(v << 7);
            }
            *(u16 *)(e + 0x34) = v + 0x1000;
            *(s32 *)(e + 0x14) = 0xFFFE0000;
            *(s32 *)(e + 0x18) = 0x30000;
        }
    }
}
