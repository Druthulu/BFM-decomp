/* func_8016F0E4 — shared body (overlay slot 0x80128158, h_exact 72d01994). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8017196C(s32 *a0, s8 a1);   /* == DEFINE_func_8017196C's own signature */
extern void func_80147060(u8 *a0);
extern void func_801511A8(u8 *a0);
extern void func_80148634(void *a0);
void aF8016F0E4(u8 *p) __asm__("func_8016F0E4");
void aF8016F0E4(u8 *p) {
    extern s16 D_80078EB4;                       /* fleet-canonical spelling; see the &-cast below */
    extern u8 D_800B9A17;
    *(s32 *)(p + 0x1F8) = 0;
    *(s32 *)(p + 0x1FC) = 0;
    func_8017196C((s32 *)p, 0);
    func_80147060(p);
    func_801511A8(p);
    if (*(u16 *)&D_80078EB4 != 0) {
        D_800B9A17 = 1;
    }
    func_80148634(p);
}
