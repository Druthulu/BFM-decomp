/* func_8013E370 — shared body (overlay slot 0x80128158, h_exact adcb98f1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void *D_801274CC;
extern s32 func_8013E410(void);
extern s32 func_8013E448(s32 a0);
extern void func_8012C724(s32 a0, s32 a1);
void func_8013E370(void) {
    u8 *s0;
    u8 *s2;
    s32 r;
    s0 = (u8 *)D_801274CC;
    if (s0 == 0) return;
    if (*(u16 *)(s0 + 6) == 0) return;
    s2 = s0 + 6;
    do {
        if ((*(u16 *)(s2 + 4) & 0x8000) == 0) {
            r = func_8013E410();
            if (r == 0) return;
            if (func_8013E448((s32)s0) != 0) {
                func_8012C724((s32)s0, r);
            }
        }
        s2 += 0x14;
        s0 += 0x14;
    } while (*(u16 *)s2 != 0);
}
