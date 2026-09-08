/* func_80178608 — shared body (overlay slot 0x80128158, h_exact 1015df76). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80016714(void *a0, s32 a1);
extern void func_8013E4B4(void);
extern u8 D_801202A0[];
extern u16 D_801270C0;
extern s16 D_801270C4;
extern s32 D_801274D8;
extern s16 D_801270C2;
extern u8 D_801270C6;
extern u8 D_801270C7;
extern s32 D_801274DC;
extern s32 D_801274E0;
void func_80178608(void) {
    u16 *p = &D_801270C0;
    func_80016714(D_801202A0, 0x6480);
    *p = 1;
    D_801270C4 = 1;
    D_801274D8 = 0x240000;
    D_801270C2 = 0;
    D_801270C6 = 0;
    D_801270C7 = 0;
    D_801274DC = 0x271000;
    D_801274E0 = 0x400000;
    func_80016714((u8 *)p + 8, 0x400);
    func_8013E4B4();
}
