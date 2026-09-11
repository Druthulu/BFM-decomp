void func_800335B8(s32 a0, s32 flags) {
    u8 *e = (u8 *)D_800A46E8 + a0 * 0x54;
    u8 *p;
    u8 *rec;
    s32 n;
    s32 i;
    u16 val = flags;

    if ((*(u16 *)e & 0x3F) != 1) {
        return;
    }

    if (flags & 0x1000) {
        n = *(u16 *)(e + 0xC);
        p = (u8 *)D_800A46E8 + 0x2A0;
        for (i = 0; i < 8; i++) {
            if (n == 0) {
                return;
            }
            if ((e + i)[0xE] != 0) {
                rec = p + i * 0x54;
                n--;
                *(u16 *)(rec + 0x48) = flags & 0x7F;
                rec[0x4F] = 1;
            }
        }
    } else if (flags & 0x2000) {
        n = *(u16 *)(e + 0xC);
        p = (u8 *)D_800A46E8 + 0x2A0;
        for (i = 0; i < 8; i++) {
            if (n == 0) {
                return;
            }
            if ((e + i)[0xE] != 0) {
                rec = p + i * 0x54;
                if (rec[0x35] != 0) {
                    rec[0x53] = val & 0x7F;
                }
                n--;
            }
        }
    }
}
