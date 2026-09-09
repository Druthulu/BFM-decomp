/* func_8017C294 — shared body (overlay slot 0x80128158, h_exact 720317ef). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017C294(void *a0, void *a1, s32 a2)
{
    SVEC_BEBC corner[4];
    SVEC_BEBC view[4];
    SVEC_BEBC hit[4];
    SVEC_BEBC org;
    SVEC_BEBC eye;
    s16 *rect = (s16 *)a0;
    s32 i;
    s32 x0, y0, x1, y1;
    s16 m;
    s32 d;
    s32 z;
    s16 u, v;
    s32 mnx, mnz, mxx, mxz;

    x0 = rect[0];
    y0 = rect[1];
    x1 = x0 + rect[2];
    y1 = y0 + rect[3];
    m = (rect[2] < rect[3]) ? rect[3] : rect[2];
    d = (s16)(m / 20);
    z = func_800491EC();

    corner[0].vx = x0; corner[0].vy = y0; corner[0].vz = z;
    corner[1].vx = x1; corner[1].vy = y0; corner[1].vz = z;
    corner[2].vx = x0; corner[2].vy = y1; corner[2].vz = z;
    corner[3].vx = x1; corner[3].vy = y1; corner[3].vz = z;

    org.vx = 0;
    org.vy = 0;
    org.vz = 0;
    func_8017C66C((u16 *)&org, &eye);

    for (i = 0; i < 4; i++) {
        func_8017C66C((u16 *)&corner[i], &view[i]);
        if (func_8017C710((short *)&eye, (short *)&view[i], (short *)&hit[i], a2)) {
            func_8017C908((s32)&hit[i], (s32)&corner[i]);
            corner[i].vx = (corner[i].vx < x0 - d) ? (x0 - d)
                : ((corner[i].vx > x1 + d) ? (x1 + d) : corner[i].vx);
            corner[i].vy = (corner[i].vy < y0 - d) ? (y0 - d)
                : ((corner[i].vy > y1 + d) ? (y1 + d) : corner[i].vy);
            func_8017C66C((u16 *)&corner[i], &view[i]);
            func_8017C710((short *)&eye, (short *)&view[i], (short *)&hit[i], a2);
        }
    }

    v = (hit[2].vx > hit[3].vx) ? hit[3].vx : hit[2].vx;
    u = (hit[0].vx > hit[1].vx) ? hit[1].vx : hit[0].vx;
    if (u > v) u = v;
    mnx = u;
    if (eye.vx < mnx) mnx = eye.vx;

    v = (hit[2].vz > hit[3].vz) ? hit[3].vz : hit[2].vz;
    u = (hit[0].vz > hit[1].vz) ? hit[1].vz : hit[0].vz;
    if (u > v) u = v;
    mnz = u;
    if (eye.vz < mnz) mnz = eye.vz;

    v = (hit[2].vx < hit[3].vx) ? hit[3].vx : hit[2].vx;
    u = (hit[0].vx < hit[1].vx) ? hit[1].vx : hit[0].vx;
    if (u < v) u = v;
    mxx = u;
    if (mxx < eye.vx) mxx = eye.vx;

    v = (hit[2].vz < hit[3].vz) ? hit[3].vz : hit[2].vz;
    u = (hit[0].vz < hit[1].vz) ? hit[1].vz : hit[0].vz;
    if (u < v) u = v;
    mxz = u;
    if (mxz < eye.vz) mxz = eye.vz;

    ((s16 *)a1)[0] = mnx;
    ((s16 *)a1)[1] = mnz;
    ((s16 *)a1)[2] = mxx - mnx;
    ((s16 *)a1)[3] = mxz - mnz;
}
