/* func_8017E608 — shared body (overlay slot 0x80128158, h_exact 66356b87). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017E608(void *a0)
{
    extern Mtx8_8017C910_8017E608 aD800AE620 __asm__("D_800AE620");
    extern void aFunc80016A5C(void *arg0, void *arg1) __asm__("func_80016A5C");
    Prim_8017C910_8017E608 prim;
    Mtx8_8017C910_8017E608 mtx;
    s32 p;

    p = (s32)a0;
    if (*(s32 *)(p + 0x2C) != 0) {
        prim.v[0].y = *(u16 *)(p + 0xA) - 0x20;
        prim.v[1].y = *(u16 *)(p + 0xA) + 0x20;
    } else {
        prim.v[0].y = *(u16 *)(p + 0xA) + 0x20;
        prim.v[1].y = *(u16 *)(p + 0xA) - 0x20;
    }
    prim.v[0].x = *(u16 *)(p + 0x6);
    prim.v[0].z = *(u16 *)(p + 0xE);
    prim.v[1].x = *(u16 *)(p + 0x6);
    prim.v[1].z = *(u16 *)(p + 0xE);
    prim.col[0].b = 0;
    prim.col[0].g = 0;
    prim.col[0].r = 0;
    switch (*(u32 *)(p + 0x30)) {
    case 0:
        prim.col[1].r = 0xFF;
        prim.col[1].b = 0;
        prim.col[1].g = 0;
        break;
    case 1:
        prim.col[1].g = 0xFF;
        prim.col[1].b = 0;
        prim.col[1].r = 0;
        break;
    case 2:
        prim.col[1].b = 0xFF;
        prim.col[1].g = 0;
        prim.col[1].r = 0;
        break;
    case 3:
        prim.col[1].b = 0xFF;
        prim.col[1].g = 0xFF;
        prim.col[1].r = 0xFF;
        break;
    }
    mtx = aD800AE620;
    prim.tag = 0x50000000;
    aFunc80016A5C(&prim, &mtx);
}
