/* func_80180D38 — shared body (overlay slot 0x80128158, h_exact 505c2aa4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();   /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2541) */
extern void func_80172710(void);
extern s16 D_801E7010;
extern s16 D_801E7012;
s32 func_80180D38(void *a0)
{
    void *p;
    u16 st;
    if (func_8012BD14(*(s32 *)((s32)a0 + 0x64)) > 0x4000) {
        __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B headers2)
        return 0;
    }
    p = *(void **)((s32)a0 + 0x64);
    st = *(u16 *)((s32)p + 0x2);
    switch (st) {
    case 3:
        *(s16 *)((s32)p + 0x2) = 8;
        break;
    case 2:
        if (*(u16 *)((s32)p + 0x34) != 1) {
            return 0;
        }
        goto hit;
    case 4:
        if (*(u16 *)((s32)p + 0x34) != 0) {
            return 0;
        }
    hit:
        D_801E7010 = st;
        D_801E7012 = *(u16 *)((s32)p + 0x34);
        *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) = 10;
        break;
    default:
        return 0;
    }
    func_80178BF8();
    return (s32)func_80172710;
}
