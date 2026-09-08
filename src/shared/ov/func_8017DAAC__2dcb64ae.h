/* func_8017DAAC — shared body (overlay slot 0x80128158, h_exact 2dcb64ae). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8017DB50(void);
extern u8 D_800B9A15;
extern unsigned char D_800B9A13;
extern u16 D_80115110;
extern u16 D_80115112;
extern s16 D_80115126;
extern s16 D_801CD878;
extern void *D_8011DB24;
s32 func_8017DAAC(s32 a0, s32 a1)
{
    void *func_ptr;
    D_800B9A15 = 1;
    D_800B9A13 = 4;
    D_80115110 = 3;
    func_ptr = func_8017DB50;
    D_80115112 = 0;
    D_80115126 = (s16)a0;
    D_801CD878 = (s16)a1;
    D_8011DB24 = func_ptr;
    return (s32)func_ptr;
}
