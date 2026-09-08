/* func_80139680 — shared body (overlay slot 0x80128158, h_exact 9c5025b7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 GetTPage(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80052460(s32 a0, s32 a1, s32 a2);
void func_80139680(s32 arg0, u8 * arg1)
{
    s32 buf[10];
    s32 var_s1;
    var_s1 = (s32)*(u16 *)((u8 *)arg0 + 0x12) - (s32)*(u16 *)((u8 *)arg0 + 0x16);
    if (var_s1 < 0) {
        var_s1 += 4;
    }
    *(s32 *)((u8 *)buf + 0x00) = 0;
    *(s16 *)((u8 *)buf + 0x0C) = GetTPage(0, 1, 0x1C0, 0x100);
    *(s16 *)((u8 *)buf + 0x10) = *(u16 *)((u8 *)arg0 + 0x3C);
    *(s16 *)((u8 *)buf + 0x12) = *(u16 *)((u8 *)arg0 + 0x3E);
    *(u8 *)((u8 *)buf + 0x16) = 0x80;
    *(u8 *)((u8 *)buf + 0x15) = 0x80;
    *(u8 *)((u8 *)buf + 0x14) = 0x80;
    {
        u16 idx = *(u16 *)((u8 *)arg0 + 0x14);
        s32 base = *(s16 *)((u8 *)arg0 + 0x30);
        s16 val;
        if (idx < 0x24) {
            val = idx * 6 + base;
        } else {
            val = base + 0xD2;
        }
        *(s16 *)((u8 *)buf + 0x04) = val;
    }
    *(s16 *)((u8 *)buf + 0x06) = *(u16 *)((u8 *)arg0 + 0x32) + var_s1 * 0xC;
    if (var_s1 != 0) {
        *(s16 *)((u8 *)buf + 0x06) = *(s16 *)((u8 *)buf + 0x06) + var_s1 * 2;
    }
    *(s16 *)((u8 *)buf + 0x08) = 0xC;
    *(s16 *)((u8 *)buf + 0x0A) = 0xC;
    *(u8 *)((u8 *)buf + 0x0E) = 0xF0;
    *(u8 *)((u8 *)buf + 0x0F) = 0;
    func_80052460((s32)buf, arg1, (s32)*(u16 *)((u8 *)arg0 + 0x1A));
}
