/* func_8014B034 — shared body (overlay slot 0x80128158, h_exact 4a864eaf). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014B084(void);
extern s16 D_80078E90;
void func_8014B034(s32 a0)
{
    register s16 *ptr = &D_80078E90;
    s16 v;
    v = ptr[1] + a0;
    ptr[1] = v;
    if (v >= 0x5A0) {
        ptr[1] = v - 0x5A0;
        func_8014B084();
    }
}
