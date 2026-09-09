/* func_80137178 — shared body (overlay slot 0x80128158, h_exact f5d8c9a9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern short D_800B9A02;
extern u8 D_800A6518[];
extern void GsSortLine(void *a0, void *a1, s32 a2);
void func_80137178(s32 a0, s32 a1)
{
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
    s16 x0;             /* $s3 */
    s16 white;             /* $s1 */
    u8 *base = D_800A6518; /* $s2 */
    s16 x1;
    s16 y0;
    s16 y1;
    x0 = a0 - 3;
    y0 = a1 - 3;
    x1 = a0 + 3;
    y1 = a1 - 3;
    white = 0xFF;
    line.tag = 0;
    line.r = 0;
    line.g = 0;
    line.b = white;
    line.x0 = x0;
    line.y0 = y0;
    line.x1 = x1;
    line.y1 = y1;
    GsSortLine(&line, &base[(u16)D_800B9A02 * 20], 0);
    y0 = a1 + 3;
    line.tag = 0;
    line.r = 0;
    line.g = 0;
    line.b = white;
    line.x0 = x0;
    line.y0 = y0;
    line.x1 = x1;
    line.y1 = y1;
    GsSortLine(&line, &base[(u16)D_800B9A02 * 20], 0);
    y1 = a1 + 3;
    line.tag = 0;
    line.r = 0;
    line.g = 0;
    line.b = white;
    line.x0 = x0;
    line.y0 = y0;
    line.x1 = x1;
    line.y1 = y1;
    GsSortLine(&line, &base[(u16)D_800B9A02 * 20], 0);
}
