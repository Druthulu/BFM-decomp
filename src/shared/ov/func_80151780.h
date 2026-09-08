/* func_80151780 — shared body (overlay slot 0x80128158, h_exact 87ab762c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_8011DB1A;
extern s32 D_80127518;
extern s32 D_801151FC;
extern s32 func_801725CC(u8 *a0);
extern s32 func_80029D3C(void);
extern void func_80151878(void);
extern void func_80153B58(s32 *a0);
void func_80151780(s32 a0) {
    u8 idx;
    s32 *tbl;
    s32 fp;
    idx = *(u8 *)(a0 + 0xDD);
    tbl = *(s32 **)(a0 + 0x1F0);
    if (idx != 0 && idx < 0x21) {
        fp = tbl[idx - 1];
        if (fp != 0) {
            ((s32 (*)(s32))func_801725CC)(a0);
            {
                register s32 cur __asm__("$4");
                cur = D_8011DB1A;
                if (cur != 1000) {
                    D_8011DB1A = func_80029D3C();
                }
            }
            (*(void (**)(s32))((s32)tbl + (s32)(*(u8 *)(a0 + 0xDD)) * 4 - 4))(a0);
            D_801151FC = D_80127518;
        } else {
            ((void (*)(s32))func_80151878)(a0);
        }
    } else {
        (*(void (**)(s32))((s32)tbl + 8))(a0);
    }
    if ((*(u16 *)(a0 + 0xF0) & 0x200) != 0) {
        ((void (*)(s32))func_80153B58)(a0);
    }
    return;
}
