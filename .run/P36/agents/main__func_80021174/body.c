s32 func_80021174(s32 a0, s32 a1)
{
    struct {
        s16 sx, sy;
        s32 flag;
        s32 otz;
    } r;
    s32 lim;

    if (a0 == 0x7FFF7FFF) {
        return 1;
    }
    gte_SetRotTransMatrix(D_800AE688);
    gte_ldlv0((SV_80021174 *)a1);
    gte_rtps();
    gte_stsxy(&r.sx);
    gte_stflg(&r.flag);
    gte_stszotz(&r.otz);
    if (r.flag < 0) {
        return 0;
    }
    lim = (s16)a0;
    if (-lim < r.sx && r.sx <= lim && -(a0 >> 16) < r.sy && r.sy <= (a0 >> 16)) {
        return 1;
    }
    return 0;
}
