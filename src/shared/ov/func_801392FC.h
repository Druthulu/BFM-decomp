/* func_801392FC — shared body (overlay slot 0x80128158, h_exact f712e690). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 GetTPage(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80052460(s32 a0, s32 a1, s32 a2);
void func_801392FC(s32 arg0, s32 arg1, u8 *arg2)
{
    s32 buf[16];
    s32 i;
    s32 acc;
    s32 rem;
    u16 cnt;
    register s32 a1c __asm__("$5");
    *(s32 *)((u8 *)buf + 0x00) = 0;
    *(s16 *)((u8 *)buf + 0x0C) = GetTPage(0, 1,
        *(s16 *)((u8 *)arg0 + 0x38) & 0xFFC0,
        *(s16 *)((u8 *)arg0 + 0x3A) & 0xFF00);
    *(s16 *)((u8 *)buf + 0x10) = *(u16 *)((u8 *)arg0 + 0x3C);
    *(s16 *)((u8 *)buf + 0x12) = *(u16 *)((u8 *)arg0 + 0x3E);
    *(u8 *)((u8 *)buf + 0x16) = 0x80;
    *(u8 *)((u8 *)buf + 0x15) = 0x80;
    *(u8 *)((u8 *)buf + 0x14) = 0x80;
    i = 0;
    cnt = *(volatile u16 *)((u8 *)arg0 + 0x2E);
    if (*(s16 *)((u8 *)arg0 + 0x2E) > 0) {
        s32 c12 = 0xC;
        s32 c12ma = 0xC - arg1;
        acc = 0;
        do {
            rem = (*(u16 *)((u8 *)arg0 + 0x16) + i) % ((s16)cnt + 1);
            *(s16 *)((u8 *)buf + 0x04) = *(u16 *)((u8 *)arg0 + 0x30);
            if (i != 0) {
                *(s16 *)((u8 *)buf + 0x06) = (*(u16 *)((u8 *)arg0 + 0x32) + acc - arg1) + i * 2;
            } else {
                *(s16 *)((u8 *)buf + 0x06) = *(u16 *)((u8 *)arg0 + 0x32);
            }
            if (i == 0) {
                *(s16 *)((u8 *)buf + 0x0A) = c12ma;
            } else {
                *(s16 *)((u8 *)buf + 0x0A) = c12;
            }
            *(u8 *)((u8 *)buf + 0x0E) = 0;
            if (i != 0) {
                s32 t = rem * 12 + *(u8 *)((u8 *)arg0 + 0x3A);
                *(u8 *)((u8 *)buf + 0x0F) = t;
            } else {
                s32 t = rem * 12 + *(u8 *)((u8 *)arg0 + 0x3A) + arg1;
                *(u8 *)((u8 *)buf + 0x0F) = t;
            }
            *(s16 *)((u8 *)buf + 0x08) = *(u16 *)((u8 *)arg0 + 0x34);
            func_80052460((s32)buf, (s32)arg2, *(u16 *)((u8 *)arg0 + 0x1A));
            acc += 0xC;
            i++;
            cnt = *(volatile u16 *)((u8 *)arg0 + 0x2E);
        } while (i < *(s16 *)((u8 *)arg0 + 0x2E));
    }
    if (arg1 != 0) {
        s16 w;
        rem = (*(u16 *)((u8 *)arg0 + 0x16) + i) % (*(s16 *)((u8 *)arg0 + 0x2E) + 1);
        *(s16 *)((u8 *)buf + 0x04) = *(u16 *)((u8 *)arg0 + 0x30);
        *(s16 *)((u8 *)buf + 0x06) = (*(u16 *)((u8 *)arg0 + 0x32) + i * 12) - arg1 + i * 2;
        *(s16 *)((u8 *)buf + 0x0A) = arg1 - 2;
        *(u8 *)((u8 *)buf + 0x0E) = 0;
        {
            s32 t = rem * 12 + *(u8 *)((u8 *)arg0 + 0x3A);
            *(u8 *)((u8 *)buf + 0x0F) = t;
        }
        w = *(s16 *)((u8 *)arg0 + 0x34);
        if (w >= 0xFD) {
            *(s16 *)((u8 *)buf + 0x08) = 0x100;
            func_80052460((s32)buf, (s32)arg2, *(u16 *)((u8 *)arg0 + 0x1A));
            {
                s32 t2;
                *(s16 *)((u8 *)buf + 0x04) = *(u16 *)((u8 *)arg0 + 0x30) + *(u16 *)((u8 *)buf + 0x08);
                *(s16 *)((u8 *)buf + 0x08) = 0x20;
                *(u8 *)((u8 *)buf + 0x0E) = rem << 5;
                t2 = (*(s16 *)((u8 *)arg0 + 0x2E) + 1) * 12 + *(u8 *)((u8 *)arg0 + 0x3A);
                *(u8 *)((u8 *)buf + 0x0F) = t2;
            }
            a1c = (s32)arg2;
            func_80052460((s32)buf, a1c, *(u16 *)((u8 *)arg0 + 0x1A));
        } else {
            *(s16 *)((u8 *)buf + 0x08) = w;
            func_80052460((s32)buf, (s32)arg2, *(u16 *)((u8 *)arg0 + 0x1A));
        }
    }
}
