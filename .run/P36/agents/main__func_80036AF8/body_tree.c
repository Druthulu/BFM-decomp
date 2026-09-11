void func_80036AF8(CdlLOC *loc, s32 flags) {
    register s32 zr __asm__("$0");  // !FAKE: pin $0 — NEEDED DIFFERS (P36 rung B tus9)
    CdReq req;
    s32 mode;
    s32 n;
    s32 idx;
    s32 lo;
    s16 h;
    s32 drv;
    s32 hi;
    u8 b;
    s32 i;
    s32 ret;
    u8 *rec;
    u8 *rec2;
    u8 *tbl;
    s32 hoff;

    mode = flags + zr;
    if (!(flags & 0x4000)) {
        return;
    }

    n = flags & 0xF;
    idx = n + zr;
    lo = (s32)(flags << 16) >> 20;
    drv = ((s32)(flags << 16) >> 25) & 0x1F;
    hi = drv + zr;
    h = lo & 0x1F;
    if (lo & 1) {
        if (*(u8 *)((u8 *)&D_8006A6A0 + drv * 0x48) != 0) {
            idx = n + 4;
        } else {
            idx = n + 8;
        }
    }

    h = h >> 1;
    rec = (u8 *)*(s32 *)((u8 *)&D_8006A69C + hi * 0x48);
    rec2 = rec + (h << 6);
    b = *(u8 *)(rec2 + (idx << 2) + 1);
    if ((b & 0xF0) == 0) {
        return;
    }

    if (D_8006AEE8 != 0) {
        if ((b & 0xF) == 0) {
            return;
        }
        if ((b & 0xF) == 1) {
            for (i = 0; i < D_8006AEE8; i++) {
                func_80034DFC(*(short *)(&D_80078F10 + i));
                (&D_80078F10)[i] = 0;
            }
            D_8006AEE8 = 0;
        }
    }

    req.f08 = (s32)func_80035270;
    D_800A46BA = 0;
    if (h != 0) {
        ret = CdPosToInt(loc);
        hoff = hi * 0x48;
        tbl = (u8 *)&D_8006A6A4;
        req.f0c = ret + *(s32 *)(tbl + hoff + h * 4);
    } else {
        req.f0c = CdPosToInt(loc);
    }
    req.f10 = (s16)mode;
    req.f1c = (s32)func_80036D24;
    req.f24 = (s32)func_800359B0;
    req.f20 = 0;
    req.f28 = (s32)func_80036FB0;
    ret = func_80034CF0((u8 *)&req);
    if (ret != 0) {
        (&D_80078F10)[D_8006AEE8] = ret;
        D_8006AEE8 = D_8006AEE8 + 1;
    }
    D_800A4F1A = 1;
}
