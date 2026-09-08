/* func_801701C8 — shared body (overlay slot 0x80128158, h_exact 5d39e0fd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);
extern void func_80171928(void *a0);
extern void *D_8011F738;
void func_801701C8(u8 * a0)
{
    s16 *p;
    s32 r;
    r = func_80012B04(((s16 **)a0)[8][9], *(s16 *)&D_8011F738, 4);
    if ((s16)r == 0) {
        func_80171928(a0);
    }
    p = ((s16 **)a0)[8];
    ((u16 *)p)[9] = (((u16 *)p)[9] + r) & 0xFFF;
}
