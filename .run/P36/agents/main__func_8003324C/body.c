void func_8003324C(s32 arg0) {
    u8 *base;
    u8 *e;
    s32 off;
    Ent30D80 *p;
    s32 i;

    off = (u16)arg0 * 0x54;
    base = (u8 *)D_800A46E8;
    e = base + off;

    switch (*(u16 *)e & 0x3F) {
    case 1:
        p = (Ent30D80 *)(base + 0x2A0);
        for (i = 0; i < 8; i++) {
            if ((e + i)[0xE] != 0) {
                (e + i)[0xE] = 0;
                p[i].unk40 = 0;
                if (p[i].unk4E != 0) {
                    func_80030D80(&p[i], 0);
                }
            }
        }
        *(u16 *)e = 0;
        break;
    case 5:
        func_80034650(e, 0);
        break;
    }
}
