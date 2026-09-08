/* func_80171D78 — shared body (overlay slot 0x80128158, h_exact 0d330bd8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8017248C(s32 a0, s32 a1);
extern s32 ratan2(s32 a0, s32 a1);
extern void func_80171EC8(s32 a0);
extern void func_80146D90(s32 a0);
s32 func_80171D78(s32 a0, s32 a1)
{
    s32 ret;
    s32 ang;
    s32 p;
    ret = func_8017248C(a0, a1);
    if (ret != 0) {
        func_80146D90(a0);
        return ret;
    }
    ang = ratan2(*(s16 *)(a1 + 0) - *(s16 *)(a0 + 6),
                 *(s16 *)(a1 + 4) - *(s16 *)(a0 + 0xE));
    ang = (ang + 0x800) & 0xFFF;
    p = *(s32 *)(a0 + 0x20);
    *(s16 *)(p + 0x12) = ang;
    func_80171EC8(a0);
    return 0;
}
