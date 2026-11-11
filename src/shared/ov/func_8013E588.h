/* func_8013E588 — shared body (overlay slot 0x80128158, h_exact 6f79cf5a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_800D0EC4(void);
extern void func_80141874(void);
extern u8 D_800B9A15;
extern unsigned char guess_g_ActiveMenu;
extern u16 guess_g_OpenMenuId;
extern unsigned short guess_g_MenuStep;
extern void *D_8011DB24;
void func_8013E588(void * _arg0)
{
    if (func_800D0EC4() == 0) {
        D_800B9A15 = 1;
        guess_g_ActiveMenu = 2;
        guess_g_OpenMenuId = 1;
        guess_g_MenuStep = 0;
        D_8011DB24 = func_80141874;
    }
}
