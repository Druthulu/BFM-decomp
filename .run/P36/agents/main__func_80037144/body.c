void func_80037144(s32 idx) {
    s32 i;
    s32 k;
    s32 t;
    s32 v;
    s32 one;
    s32 ent;

    for (i = 0; i < 5; i++) {
        if (D_80076244[i].unk0D == 0) {
            break;
        }
    }
    if (i < 5) {
        one = 1;
        /* the word at +0 is written through the D_80076240 view (as func_80037028 does): a
         * non-zero offset from its base keeps the store ordered before the table loads below */
        D_80076240[i].unk04 = (s32)D_800BA320;
        D_80076244[i].unk0C = 0;
        D_80076244[i].unk0D = one;
        D_80076244[i].unk04 = idx | 0x2000;
        D_80076244[i].unk0E = 4;
        v = D_800652F0[D_80065438[idx].f0];
        D_800A469C = v;
        D_80076244[i].unk08 = v;
        k = 4;
        if (D_800A46B0 == 0) {
            if (D_800A46A0 == (D_80065438[idx].f0 | 0x4000)) {
                D_80076244[i].unk04 |= 0x1000;
                goto after;
            }
            t = D_800A46A2;
            D_800A46B0 = one;
        } else {
            t = D_800A46A2;
        }
        if (t >= 0) {
            func_800415A8(t);
            D_800A46A2 = -1;
        }
    after:
        if (i == 0) {
            D_8007622C[0] = (s32)D_800BA320;
            ent = D_800A463C[k].unk00;
            D_80076228.v = (s32)D_800BA320;
            D_80076240[0].unk00 = 0;
            D_80076243.v = 1;
            D_80076242.v = 0;
            D_80076294.v = 0;
            D_80076238.v = ent;
        }
    }
    D_8007629C = 0;
}
