/* func_801726D0 — shared body (overlay slot 0x80128158, h_exact 27e107b4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80172760(s32 a0);
extern s32 func_80174650(s32);
extern void (*D_80127088)(void);
extern s32 D_801270BC;
extern s16 D_80126B0C;
void func_801726D0(void * _arg0)
{
    D_80127088 = func_80172760;
    D_801270BC = 0;
    D_80126B0C = 0;
    ((void (*)(void))func_80174650)();
}
