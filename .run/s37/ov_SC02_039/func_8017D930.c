extern s32 func_8017DBD0(u32 a0v);
extern s16 func_8017DB14(u32 a0);

void func_8017D930(void *a0, void *a1) {
    u16 *r = (u16 *)a0;
    s16 *m = (s16 *)a1;
    s16 cx;
    s16 sx;
    s16 cy;
    s16 sy;
    s16 cz;
    s16 sz;
    s32 sxsy;
    s32 cxcz;
    s32 cxsz;

    cx = func_8017DBD0(r[0] & 0xFFF);
    sx = func_8017DB14(r[0] & 0xFFF);
    cy = func_8017DBD0(r[1] & 0xFFF);
    sy = func_8017DB14(r[1] & 0xFFF);
    cz = func_8017DBD0(r[2] & 0xFFF);
    sz = func_8017DB14(r[2] & 0xFFF);

    cxsz = (cx * sz) >> 15;
    cxcz = (cx * cz) >> 15;
    sxsy = (sx * sy) >> 15;

    m[0] = (cz * cy) >> 15;
    m[1] = ((sxsy * cz) >> 15) - cxsz;
    m[2] = ((cxcz * sy) >> 15) + ((sx * sz) >> 15);
    m[3] = (sz * cy) >> 15;
    m[4] = ((sxsy * sz) >> 15) + cxcz;
    m[5] = ((cxsz * sy) >> 15) - ((sx * cz) >> 15);
    m[6] = -sy;
    m[7] = (cy * sx) >> 15;
    m[8] = (cy * cx) >> 15;
}
