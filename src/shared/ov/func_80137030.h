/* func_80137030 — shared body (overlay slot 0x80128158, h_exact 9b08c5e5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern short D_800B9A02;
extern u8 D_800A6518[];
extern void GsSortLine(void *a0, void *a1, s32 a2);
void func_80137030(s16 a0, s16 a1) {
    struct {
        u32 tag;
        s16 x0;
        s16 y0;
        s16 x1;
        s16 y1;
        u8 r;
        u8 g;
        u8 b;
    } line;
    s16 cx;
    s16 cy;
    s16 tx;
    s16 ty;
    tx = a0 - 3;
    ty = a1 - 3;
    cx = a0;
    cy = a1;
    line.tag = 0;
    line.r = 0;
    line.g = 0xFF;
    line.b = 0;
    line.x0 = tx;
    line.y0 = ty;
    line.x1 = cx;
    line.y1 = cy;
    GsSortLine(&line, &D_800A6518[(u16)D_800B9A02 * 20], 0);
    tx = a0 + 3;
    line.tag = 0;
    line.r = 0;
    line.g = 0xFF;
    line.b = 0;
    line.x0 = tx;
    line.y0 = ty;
    line.x1 = cx;
    line.y1 = cy;
    GsSortLine(&line, &D_800A6518[(u16)D_800B9A02 * 20], 0);
    ty = a1 + 3;
    line.tag = 0;
    line.r = 0;
    line.g = 0xFF;
    line.b = 0;
    line.x0 = cx;
    line.y0 = ty;
    line.x1 = cx;
    line.y1 = cy;
    GsSortLine(&line, &D_800A6518[(u16)D_800B9A02 * 20], 0);
}
