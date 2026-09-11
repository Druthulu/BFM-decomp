void func_8018C14C(void *a0)
{
    s32 v0;
    s32 v1;
    u16 v[4];
    u16 out[4];

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, (s32)&D_801E81A4);

    v1 = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(v1 + 0x2C) |= 0x10;

    func_8004914C((void *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x34));
    func_800491AC((void *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x34));

    RotTransSV(&D_80194800, v, out);

    *(s16 *)((s32)a0 + 0x6) = v[0];
    {
        register s32 zr __asm__("$0");  // !FAKE: pin $0 ent — keeps ent a second pseudo; a plain copy is merged into the parameter by cse2 (make_regs_eqv cse.c:846-862) and the stores revert to $s0 (P36 S104 e30 minimum-lever)
        s32 ent = (s32)a0 + zr;
        s32 v2;
        s32 t1;
        s32 one;

        do {  // !FAKE: do-while — LOOP notes split sched1 (sched.c:2058-2074) so the li 1 / ori stay below the 0xC4 load, replacing an asm barrier (P36 S104 e30 minimum-lever)
            *(s16 *)(ent + 0xA) = v[1];
            t1 = *(u32 *)(ent + 0xC4);
        } while (0);
        one = 1;
        t1 |= 2;
        v2 = v[2];
        *(u8 *)(ent + 0xC0) = one;
        *(s32 *)(ent + 0xBC) = (s32)&D_80194828;
        *(s16 *)(ent + 0xAE) = -1;
        *(u32 *)(ent + 0xC4) = t1;
        *(s32 *)(ent + 0x58) = (s32)&D_80194808 | 0x40000000;
        *(s32 *)(ent + 0xB4) = 0;
        *(u8 *)(ent + 0xC1) = 0;
        *(s16 *)(ent + 0x5C) = 0;
        *(u8 *)(ent + 0x75) = 2;
        *(s16 *)(ent + 0xE) = v2;

        func_80188650((void *)ent);
    }
}
