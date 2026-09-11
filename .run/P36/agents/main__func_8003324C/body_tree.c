void func_8003324C(s32 arg0) {
    u8 *base;
    u8 *e;
    s32 off;
    s32 code;

    off = (u16)arg0 * 0x54;
    base = (u8 *)D_800A46E8;
    e = base + off;
    code = *(u16 *)e & 0x3F;

    switch (code) {
    case 1: {
        register Ent30D80 *p __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
        s32 i;

        i = 0;
        p = (Ent30D80 *)(base + 0x2A0);
        __asm__ ("" :: "r"(base));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)
        for (; i < 8; i++, p++) {
            u8 *q = e + i;

            if (q[0xE] != 0) {
                q[0xE] = 0;
                p->unk40 = 0;
                if (p->unk4E != 0) {
                    func_80030D80(p, 0);
                }
            }
        }
        *(u16 *)e = 0;
        break;
    }
    case 5:
        func_80034650(e, 0);
        break;
    }
}
