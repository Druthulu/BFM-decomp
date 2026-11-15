/* func_8016B6BC — shared body (overlay slot 0x80128158, h_exact c6b4f7b5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8016B6BC(s32 param_1, s32 param_2, s32 param_3, s32 param_4) {

    extern int D_80181C88;
    int iVar1;
    M8_8016B6BC *q;
    Src_80016B60 prim;
    Src_80016B60 *p = &prim;
    DVec_8016B6BC off;
    unsigned int v;
    unsigned int c;

    q = (M8_8016B6BC *)*(int *)((int)&D_80181C88 + ((param_4 << 0x10) >> 0xe));
    p->flags = 0x50000000;
    c = (unsigned int)param_2;
    v = 0x20;
    if (c < 0x20) {
        v = c;
    }
    if (*(int *)(param_1 + 0x2c) == 0) {
        c = c | (v << 0x10 | v << 8);
    } else {
        c = c << 8 | v << 0x10 | v;
    }
    p->rgb0 = c;
    iVar1 = (int)(short)param_3;
    p->rgb1 = 0;
    p->rgb2 = 0;
    func_80013CFC(iVar1, (int)q++, &p->v[0]);
    func_80013CFC(iVar1, (int)q++, &p->v[1]);
    func_80013CFC(iVar1, (int)q, &p->v[2]);
    guess_CopyVec3HighHalves(param_1 + 4, (s32 *)&off);
    p->v[0].vx += off.x;
    p->v[0].vy += off.y;
    p->v[1].vx += off.x;
    p->v[1].vy += off.y;
    p->v[2].vx += off.x;
    p->v[2].vy += off.y;
    p->v[0].vz = 3;
    func_8001739C(p);
}
