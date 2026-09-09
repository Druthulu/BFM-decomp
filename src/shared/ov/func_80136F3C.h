/* func_80136F3C — shared body (overlay slot 0x80128158, h_exact d6334f65). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern short D_800B9A02;
extern u8 D_800A6518[];
extern void GsSortLine(void *a0, void *a1, s32 a2);
void func_80136F3C(s32 a0, s32 a1)
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
    register s16 x1    __asm__("$16");               /* $s0 */  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B headers1)
    register s16 x0    __asm__("$17");               /* $s1 */  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B headers1)
    u8 *base = D_800A6518;  /* $s3 */
    register s16 white __asm__("$20");               /* $s4 */  // !FAKE: pin $20 — NEEDED DIFFERS (P36 rung B headers1)
    s16 y0;
    s16 y1;
    y0 = a1 - 3;
    x1 = a0 + 3;
    __asm__("" : "=r"(x1) : "0"(x1));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B headers1)
    y1 = a1 + 3;
    white = 0xFF;
    x0 = a0 - 3;
    line.tag = 0;
    line.r = white;
    line.g = 0;
    line.b = 0;
    line.x0 = x0;
    line.y0 = y0;
    line.x1 = x1;
    line.y1 = y1;
    GsSortLine(&line, &base[(u16)D_800B9A02 * 20], 0);
    line.tag = 0;
    line.r = white;
    line.g = 0;
    line.b = 0;
    line.x0 = x1;
    line.y0 = y0;
    line.x1 = x0;
    line.y1 = y1;
    GsSortLine(&line, &base[(u16)D_800B9A02 * 20], 0);
}
