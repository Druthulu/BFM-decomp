void func_8002D320(void)
{
    /* TU-absent names, block scope */
    extern Slot D_800A4C28[];
    extern void func_8003D3B4(s32, s32);
    extern void func_8003C23C(s32, s32);
    extern void func_8003BE74(s32, s32);
    extern void func_8003B250(s32, void *);

    Slot *s;
    s32 i;

    /* D_800A4C6D is &D_800A4C28[0].unk45: spelled through that symbol so the relocation stays D_800A4C6D+0
     * (the plain `s = D_800A4C28;` compiles to the same instructions with a D_800A4C28+0x45 relocation). */
    s = (Slot *)(D_800A4C6D - 0x45);
    for (i = 0; i < 8; i++, s++) {
        if (s->unk45[0] != 0) {
            if (s->unk44 == 0 || (s->unk04 & 0x60000) == 0) {
                func_8003D3B4(s->unk40, 1);
            }
            s->unk45[0] = 0;
        }
    }

    if ((D_800A2B98 & 0xFF0000) != 0) {
        func_8003C23C(0, D_800A2B98 & 0xFF0000);
        D_800A2B98 = *(u16 *)&D_800A2B98;
    }
    if ((D_800A2BA0 & 0xFF0000) != 0) {
        func_8003BE74(0, D_800A2BA0 & 0xFF0000);
        D_800A2BA0 = *(u16 *)&D_800A2BA0;
    }

    s = D_800A4C28;
    for (i = 0; i < 8; s++, i++) {
        if (s->unk44 != 0) {
            s->unk44 = 0;
            func_8003B250(s->unk40, s);
            s->unk04 = 0;
        }
    }

    if ((D_800C7D20 & 0xFF0000) != 0) {
        func_8003C23C(1, D_800C7D20 & 0xFF0000);
        D_800C7D20 = *(u16 *)&D_800C7D20;
    }
    if ((D_800C7D2C & 0xFF0000) != 0) {
        func_8003BE74(1, D_800C7D2C & 0xFF0000);
        D_800C7D2C = *(u16 *)&D_800C7D2C;
    }
}
