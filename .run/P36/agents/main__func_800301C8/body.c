int func_800301C8(int entry, s32 a1, s32 a2) {
    /* block scope, exactly as func_8002FF0C does two functions up: src/800_b.c declares this
     * symbol `extern s16 D_800A46D2[]` FURTHER DOWN the TU (L3733), and the ARRAY spelling makes
     * cse cache the address in a callee-saved register (`la $s1`) across the func_800415A8 call
     * for both the read and the write -- the target keeps two independent %hi/%lo accesses,
     * which only the scalar spelling emits. */
    extern s16 D_800A46D2;
    s16 *p;
    s32 bs;
    s16 e;
    s32 b;
    s32 h;
    s32 k;
    s32 k2;
    s32 vab;
    u8  fl;
    s32 ret;
    s32 v;

    if (D_800A46CC == 0) {
        D_800A46C4 = 0;
        D_800A46CE[0] = D_80064D49[entry].unk00;
        D_800A46C0 = a2;
        D_800A46BC = a1;
        b = D_800A46CE[0];
        k = b * 24;
        h = *(s16 *)((u8 *)D_800A4644 + k);
        *(s32 *)((u8 *)D_800A464C + k) = a1;
        if (h != 0) {
            if (h != D_80064D4A[entry * 12]) {
                s32 n = *(s16 *)((u8 *)D_800A4648 + k);
                D_800C532A[n * 2] = -1;
                do {  // !FAKE: do-while — sched1 LOOP-note barrier, sched.c:2058-2074: keeps the zero stores after the D_800C532A store (the Rsc24 field spelling D_800A4640[b].unk04/.unk08 needs none; identical only after linking) (P36 S104 e23 minimum-lever)
                    *(s16 *)((u8 *)D_800A4644 + k) = 0;
                    *(s16 *)((u8 *)D_800A4648 + k) = 0;
                } while (0);
            }
        }
        {
            s32 m3;
            m3 = (b << 1) + b;
            k2 = m3 << 3;
        }
        if (D_800A4650[k2] == 0) {
            s32 n = *(s16 *)((u8 *)D_800A4640 + k2);
            D_800C5328[n * 2] = -1;
            func_80031A98();
            func_800415A8(*(s16 *)((u8 *)D_800A4642 + k2));
        }
        p = &D_800A46D0;
        e = entry;
        *p = e;
        *(s16 *)((u8 *)D_800A4640 + k2) = e;
        D_800A4650[k2] = 1;
        vab = SsVabOpenHeadSticky(a1, -1, *(s32 *)((u8 *)D_800A463C + k2));
        bs = (s32)p - 0x98;
        {
            s32 adr;
            adr = k2 + bs;
            D_800A46D2 = vab;
            *(s16 *)(adr + 0xA) = vab;
        }
        if ((s16)vab == -1) {
            D_800A4650[k2] = 1;
            return 1;
        }
        if (func_80037CD8((void *)func_800301A4) == 0) {
            D_800A46CC = 1;
            return 0;
        }
        fl = D_8006AEF4;
        fl |= 2;
        D_8006AEF4 = fl;
        if (fl & 1) {
            D_800A46CC = 2;
            return 0;
        }
        D_800A46CC = 3;
        return 0;
    } else {
        ret = D_8006AA14[D_800A46CC]();
        if (ret != 0) {
            v = D_800A46D2;
            if (v >= 0) {
                func_800415A8(v);
                D_800A46D2 = -1;
                *(s16 *)((u8 *)D_800A4642 + D_800A46CE[0] * 24) = -1;
            }
        }
        return ret;
    }
}
