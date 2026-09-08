/* func_8013E588 — shared body (overlay slot 0x80128158, h_exact 6f79cf5a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_800D0EC4(void);
extern void func_80141874(void);
extern u8 D_800B9A15;
extern unsigned char D_800B9A13;
extern u16 D_80115110;
extern unsigned short D_80115112;
extern void *D_8011DB24;
void func_8013E588(void * _arg0)
{
    if (func_800D0EC4() == 0) {
        D_800B9A15 = 1;
        D_800B9A13 = 2;
        D_80115110 = 1;
        D_80115112 = 0;
        D_8011DB24 = func_80141874;
    }
}
