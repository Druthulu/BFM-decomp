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
        D_80076244[i].unk00 = (s32)D_800BA320;
        /* scheduling barrier: the slot stores and the D_80065438 load DO disambiguate here
         * (both /s and both varying -> memrefs_conflict_p:614 falls through to
         * find_symbolic_term and the two symbols differ), so without this gcc hoists the
         * D_80065438 load above all the slot stores and permutes the head block.
         * Emits zero instructions. */
        __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory after the unk00 store — sched.c:817 true_dependence via memrefs_conflict_p/find_symbolic_term sched.c:700 (P36 S104 e3 minimum-lever)
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
