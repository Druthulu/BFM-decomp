void func_80020598(s32 *a0, OBJ598 *a1, MTX_80020248 *a2, MTX_80020248 *a3)
{
    MTX_80020248 lm;
    s16 local[3];
    MTX_80020248 *rm;
    s32 i;
    u32 w;
    s16 v;
    MH h2;
    MH h3;
    register MTX_80020248 *m3 __asm__("$8");  // !FAKE: pin $8 — NEEDED DIFFERS (P36 rung B tus9)
    s32 pad[4];

    h2.p = a2;
    h3.p = a3;
    i = 0;
    rm = D_80074818;
    while (*a0 != 0) {
        switch (i) {
        case 0:
            local[0] = a1[3].h;
            w = *(u32 *)&a1[3];
            local[1] = a1[3].b1 | ((w & 0xF) << 8);
            local[2] = ((w >> 16) & 0xFF) | ((w & 0xF0) << 4);
            func_80020DA4((s32)local, (s32)&lm);
            func_80012558((s32)&lm, 0x800);
            lm.t[0] = (s8)a1->b0;
            lm.t[1] = (s8)a1->b1;
            lm.t[2] = (s8)a1->b2;
            break;
        case 1:
            local[0] = a1[3].h;
            w = *(u32 *)&a1[3];
            local[1] = a1[3].b1 | ((w & 0xF) << 8);
            local[2] = ((w >> 16) & 0xFF) | ((w & 0xF0) << 4);
            func_80020DA4((s32)local, (s32)&lm);
            lm.t[0] = a1->t[0];
            lm.t[1] = a1->t[1];
            lm.t[2] = a1->t[2];
            a1++;
            break;
        default:
            local[0] = a1->h;
            w = *(u32 *)a1;
            local[1] = ((w >> 8) & 0xFF) | ((w & 0xF) << 8);
            local[2] = ((w >> 16) & 0xFF) | ((w & 0xF0) << 4);
            func_80020DA4((s32)local, (s32)&lm);
            lm.t[0] = a1->t[0];
            lm.t[1] = a1->t[1];
            lm.t[2] = a1->t[2];
            a1++;
            if (i == 0x19) {
                v = D_80126C4E;
                local[2] = v;
                local[1] = v;
                local[0] = v;
                func_80020F34((s32)&lm, (s32)local);
            } else if (i == 0x16) {
                v = D_80126D10;
                local[2] = v;
                local[1] = v;
                local[0] = v;
                func_80020F34((s32)&lm, (s32)local);
            } else if (i == 8) {
                v = D_80126D12;
                local[2] = v;
                local[1] = v;
                local[0] = v;
                func_80020F34((s32)&lm, (s32)local);
            }
            break;
        }
        m3 = h2.p;
        gte_SetRotMatrix(m3);
        gte_ldclmv(&lm.m[0][0]);
        gte_rtir();
        gte_stclmv(&rm->m[0][0]);
        gte_ldclmv(&lm.m[0][1]);
        gte_rtir();
        gte_stclmv(&rm->m[0][1]);
        gte_ldclmv(&lm.m[0][2]);
        gte_rtir();
        gte_stclmv(&rm->m[0][2]);
        m3 = h3.p;
        gte_SetRotMatrix(m3);
        gte_ldclmv(&lm.m[0][0]);
        gte_rtir();
        gte_stclmv(&rm[0x40].m[0][0]);
        gte_ldclmv(&lm.m[0][1]);
        gte_rtir();
        gte_stclmv(&rm[0x40].m[0][1]);
        gte_ldclmv(&lm.m[0][2]);
        gte_rtir();
        gte_stclmv(&rm[0x40].m[0][2]);
        gte_SetTransMatrix(m3);
        gte_ldlv0(&lm.t[0]);
        gte_rtv0tr();
        gte_stlvnl(&rm[0x40].t[0]);
        rm++;
        a0++;
        i++;
    }
}
