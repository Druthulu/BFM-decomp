/* func_8017DAC4 — shared body (overlay slot 0x80128158, h_exact 6a956abc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80017714(void *);
void func_8017DAC4(void *arg0)
{
    s32 a0 = (s32)arg0;
    Prim_8017DAC4 prim;
    Prim_8017DAC4 *q;
    u16 *p;
    u16 dx, dy;
    s32 i;
    q = &prim;
    p = *(u16 **)(a0 + 0x0);
    dx = *(u16 *)(a0 + 0x12);
    dy = *(u16 *)(a0 + 0x14);
    i = 0;
    prim.v[0].vz = 3;
    prim.f20 = prim.f24 = *(s32 *)(a0 + 0x4);
    prim.f28 = *(s32 *)(a0 + 0x8);
    prim.f2C = 0;
    prim.f30 = 0x50000000;
    do {
        q->v[0].vx = p[0] + dx;
        q->v[0].vy = p[1] + dy;
        q->v[1].vx = p[2] + dx;
        q->v[1].vy = p[3] + dy;
        q->v[2].vx = p[4] + dx;
        q->v[2].vy = p[5] + dy;
        q->v[3].vx = p[6] + dx;
        q->v[3].vy = p[7] + dy;
        func_80017714(q);
        p += 8;
        i++;
    } while (i < 3);
}
