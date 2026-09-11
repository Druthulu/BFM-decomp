s32 func_8002FF0C(s32 a0, s32 a1) {
    /* block scope: src/800_b.c declares this symbol `extern s16 D_800A46D2[]`
     * further down the TU, and the ARRAY spelling materialises the address into
     * a register (`la`) for both the store and the re-read -- the target keeps
     * two independent %hi/%lo accesses, which only the scalar spelling emits. */
    extern s16 D_800A46D2;
    s32 b;
    s32 i;
    s32 idx24;
    s32 j12;
    s32 v1;
    s16 t;
    s16 r;
    s16 *q;
    u8  *w;
    u8  *base;
    s32 res;

    if (D_800A46CC == 0) {
        b = D_80064D49[a0].unk00;
        i = b * 24;
        v1 = *(s16 *)((u8 *)D_800A4644 + i);
        if (v1 != 0 && v1 != D_80064D4A[a0 * 12]) {
            t = *(s16 *)((u8 *)D_800A4648 + i);
            *(s16 *)((u8 *)D_800C532A + t * 4) = -1;
            *(s16 *)((u8 *)D_800A4644 + i) = 0;
            *(s16 *)((u8 *)D_800A4648 + i) = 0;
        }
        idx24 = (b * 3) << 3;
        if (D_800A4650[idx24] == 0) {
            t = *(s16 *)((u8 *)D_800A4640 + idx24);
            *(s16 *)((u8 *)D_800C5328 + t * 4) = -1;
            func_80031A98();
        }
        q = D_800A46CE;
        j12 = a0 * 12;
        *q = b;
        *(s16 *)((u8 *)D_800A4640 + idx24) = a0;
        D_800A46D0 = a0;
        D_800A46BC = a1;
        *(s32 *)((u8 *)D_800A464C + idx24) = a1;
        if (D_80064D4E[j12] != 0) {
            D_800A4EF6 = D_80064D4E[j12];
        }
        r = func_80041A80(a1, -1, *(s32 *)((u8 *)D_800A463C + idx24));
        D_800A46D2 = r;
        base = (u8 *)q - 0x96;
        w = idx24 + base;
        *(s16 *)(w + 0xA) = r;
        if (r == -1 || func_800419B0(D_800A46D2) == -1) {
            D_800A4650[idx24] = 1;
            return 1;
        }
        D_800A46CC = 1;
    }
    res = 0;
    switch (D_800A46CC) {
    case 1:
        res = func_80030730();
        break;
    case 2:
        res = func_80030A14();
        break;
    }
    if (res != 0) {
        s16 *p = &D_800A46D2;
        func_800415A8(*p);
        *p = -1;
        *(s16 *)((u8 *)D_800A4642 + *(s16 *)D_800A46CE * 24) = -1;
        return 1;
    }
    return 0;
}
