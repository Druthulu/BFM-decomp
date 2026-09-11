void func_8017F368(u16 *a0, s32 a1)
{

    extern s32 D_800A651C[][5];
    extern u16 D_801914BC[];
    extern u16 D_8019153C[];
    extern u16 D_801915DC[][4];
    extern u16 D_801915DE[][4];
    extern u16 D_801915E0[][4];
    extern u16 D_801915E2[][4];

    u16 pad0[16];   /* dead: locals begin at sp+0x30, va must land at sp+0x50 */
    SVECTOR va[4];  /* sp+0x50 — outer quad, 4 x SVECTOR */
    SVECTOR vb[4];  /* sp+0x70 — inner quad, 4 x SVECTOR */
    s32 sxy[8];     /* sp+0x90 — [0..3] RotNclip4, [4..7] RotTransPers4 */
    s16 idx[4];     /* sp+0xB0 */
    s32 p;          /* sp+0xB8 */
    s32 otz;        /* sp+0xBC */
    s32 flag;       /* sp+0xC0 */

    u16 attr;
    s32 type;
    u8 type2;
    u16 *p1;
    u16 *p2;
    s32 i;
    u8 *pk;
    s32 j;

    func_8012E32C();

    attr = a0[3];
    type = attr & 0xFF;
    type2 = type;
    if ((attr & 0xF00) == 0x200) {
        func_8017F750(a0, a1);
        return;
    }

    p1 = (u16 *)((u8 *)D_801914BC + type * 0x20);
    for (i = 0; i < 4; i++, p1 += 4) {
        va[i].vx = a0[0] + p1[0];
        va[i].vy = a0[1] + p1[1];
        va[i].vz = a0[2] + p1[2];
    }

    if (RotNclip4((s32)&va[0], (s32)&va[1], (s32)&va[2], (s32)&va[3],
                  &sxy[0], &sxy[1], &sxy[2], &sxy[3], &p, &otz, &flag) <= 0) {
        return;
    }

    otz -= 0x10;
    if (otz < 0) {
        return;
    }
    if (otz >= 0x1000) {
        return;
    }

    p2 = (u16 *)((u8 *)D_8019153C + type2 * 0x20);
    for (i = 0; i < 4; i++, p2 += 4) {
        vb[i].vx = a0[0] + p2[0];
        vb[i].vy = a0[1] + p2[1];
        vb[i].vz = a0[2] + p2[2];
    }

    RotTransPers4((s32)&vb[0], (s32)&vb[1], (s32)&vb[2], (s32)&vb[3],
                  &sxy[4], &sxy[5], &sxy[6], &sxy[7], &p, &flag);

    pk = func_80010A08(0xA8);

    for (j = 0; j < 4; j++) {
        idx[0] = D_801915DC[j][0];
        idx[1] = D_801915DE[j][0];
        idx[2] = D_801915E0[j][0];
        idx[3] = D_801915E2[j][0];
        *(s32 *)(pk + 0x4) = a1 & -(idx[0] < 4);
        *(s32 *)(pk + 0xC) = a1 & -(idx[1] < 4);
        *(s32 *)(pk + 0x14) = a1 & -(idx[2] < 4);
        *(s32 *)(pk + 0x1C) = a1 & -(idx[3] < 4);
        pk[7] = 0x3A;
        *(u32 *)(pk + 0x0) = 0x08000000;
        *(s32 *)(pk + 0x8) = sxy[idx[0]];
        *(s32 *)(pk + 0x10) = sxy[idx[1]];
        *(s32 *)(pk + 0x18) = sxy[idx[2]];
        *(s32 *)(pk + 0x20) = sxy[idx[3]];
        AddPrim(D_800A651C[(u16)D_800B9A02][0] + (otz * 4), pk);
        pk += 0x24;
    }

    *(s32 *)(pk + 0x4) = a1;
    pk[7] = 0x2A;
    *(u32 *)(pk + 0x0) = 0x05000000;
    *(s32 *)(pk + 0x8) = sxy[0];
    *(s32 *)(pk + 0xC) = sxy[1];
    *(s32 *)(pk + 0x10) = sxy[2];
    *(s32 *)(pk + 0x14) = sxy[3];
    AddPrim(D_800A651C[(u16)D_800B9A02][0] + (otz * 4), pk);
    func_8012E28C(otz, 1);
}
