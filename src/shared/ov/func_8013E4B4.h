/* func_8013E4B4 — shared body (overlay slot 0x80128158, h_exact 8d40ae9b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012C750(s32 a0);
extern u8 *D_801274C8;
extern void *D_801274CC;
void func_8013E4B4(void) {
    u8 *s0;
    Ent *p;
    s32 i;
    s0 = D_801274C8;
    if (s0 != 0) {
        if (*(u16 *)(s0 + 6) != 0) {
            do {
                func_8012C750(s0);
                s0 += 0x14;
            } while (*(u16 *)(s0 + 6) != 0);
        }
    }
    s0 = (u8 *)D_801274CC;
    if (s0 != 0) {
        p = (Ent *)(s0 + 6);
        for (i = 0; p[i].guard != 0; i++) {
            p[i].field &= 0x7FFF;
        }
    }
}
