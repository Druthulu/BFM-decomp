void func_800377D8(u8 arg0) {
    s32 *pInt;
    u8  *pSt;
    s32 pos;
    s32 idx;
    s32 ptr;
    s32 nxt;
    u16 *pCnt;
    s32 cnt;

    if (arg0 != 1) goto err;
    if (func_80043994(D_800762A0, 3) == 0) goto err;
    pos = CdPosToInt((CdlLOC *)D_800762A0);
    pInt = &D_8007623C;
    if (pos != *pInt) goto err;
    *pInt = pos + 1;

    switch (gD_80076243) {
    case 1:
        if (func_80043994((void *)gD_80076228, 0x200) == 0) goto err;
        if (sD_80076240 == 0 && *(s32 *)gD_80076228 != 0x7671732E) {
            D_80076298 = 1;
            D_80076250[gD_80076294 * 16] = 2;
            goto err;
        }
        {
        s32 rnxt;
        s32 rcnt;
        pCnt = &hD_80076240;
        rnxt = gD_80076228 + 0x800;
        rcnt = *pCnt + 1;
        *pCnt = rcnt;
        gD_80076228 = rnxt;
        if ((s16)rcnt != 0xE) {
            return;
        }
        }
        if (D_80076248[gD_80076294].unk00 & 0x1000) {
            D_80076250[gD_80076294 * 16] = 1;
            idx = gD_80076294 + 1;
            gD_80076294 = idx;
            if (idx < 5 && (&D_80076251)[idx * 16] != 0) {
                if (D_80076248[idx].unk00 & 0x2000) {
                    gD_80076243 = 1;
                } else {
                    gD_80076243 = 2;
                }
                D_80076298 = 0;
                hD_80076240 = 0;
                gD_80076228 = D_80076244[gD_80076294].unk00;
                gD_80076238 = D_80076244[gD_80076294].unk08;
                return;
            }
            gD_80076243 = 4;
            D_8006AEF4 = D_8006AEF4 & 0xFD;
            return;
        }
        gD_80076243 = 2;
        *pCnt = 0;
        return;

    case 2:
        if (func_80043994((void *)gD_80076228, 0x200) == 0) goto err;
        gD_80076228 = gD_80076228 + 0x800;
        hD_80076240 = hD_80076240 + 1;
        if ((s16)hD_80076240 != 7) {
            return;
        }
        gD_80076243 = 3;
        hD_80076240 = 0;
        if (gD_80076242 != 0) {
            if (func_8003C4F0(0) == 0) {
                return;
            }
            gD_80076242 = 0;
        }
        return;

    case 3:
        if (func_80043994((void *)gD_80076228, 0x200) == 0) goto err;
        hD_80076240 = hD_80076240 + 1;
        if (gD_80076242 != 0) {
            if (func_8003C4F0(0) == 0) goto err;
        }
        if (((s32 (*)(s32))func_8003C498)(gD_80076238) == 0) goto err;
        ptr = gD_80076228;
        if (sD_80076240 == *(s16 *)(ptr - 4)) {
            SpuWrite(ptr, *(s16 *)(ptr - 2));
            gD_80076242 = 1;
            D_8006AEF4 = D_8006AEF4 | 1;
            D_80076250[gD_80076294 * 16] = 1;
            idx = gD_80076294 + 1;
            gD_80076294 = idx;
            if (idx < 5 && (&D_80076251)[idx * 16] != 0) {
                if (D_80076248[idx].unk00 & 0x2000) {
                    gD_80076243 = 1;
                } else {
                    gD_80076243 = 2;
                }
                D_80076298 = 0;
                hD_80076240 = 0;
                gD_80076228 = D_80076244[gD_80076294].unk00;
                gD_80076238 = D_80076244[gD_80076294].unk08;
                return;
            }
            gD_80076243 = 4;
            D_8006AEF4 = D_8006AEF4 & 0xFD;
            return;
        }
        SpuWrite(ptr, 0x800);
        gD_80076242 = 1;
        D_8006AEF4 = D_8006AEF4 | 1;
        gD_80076238 = gD_80076238 + 0x800;
        return;
    }
    return;

err:
    pSt = &gD_80076243;
    if (*pSt == 0) return;
    if (*pSt == 4) return;
    if (*pSt == 5) return;
    *pSt = 5;
    D_8006AEF4 = D_8006AEF4 & 0xFD;
}
