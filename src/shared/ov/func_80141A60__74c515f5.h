/* func_80141A60 — shared body (overlay slot 0x80128158, h_exact 74c515f5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80141A60(void)
{

    extern u8  D_8011514D;
    extern u8  D_8011515C;
    extern u16 D_80115116;
    s32 iVar1;
    s32 pad[2];
    (void)&pad;   /* §36#3 frame-pad induction: force frame 0x20 (vs 0x18) */

    D_801151D0 = ((s32 *)D_801151C8)[(*(u16 *)&D_800B9A02)];
    func_8013F350();
    if ((*(u16 *)&D_8011511A) >= 4) {
        func_8013FAF8((*(u16 *)&D_8011511A), (*(u16 *)&D_8011511A) + 1);
    }
    func_8013FAF8(2, 3);
    iVar1 = func_8014032C(2, (s16)((*(u8 *)&D_8011514C) + D_8011514D * D_8011515C));
    if (iVar1 != 0 && iVar1 != D_80115130) {
        D_80115130 = iVar1;
        func_80139954();
        func_801376E8(iVar1, (int)&D_8017FE40);
    }
    func_80137B80();
    iVar1 = func_800D0EC4();
    if (iVar1 != 0) {
        D_80115116 = 0xfff8;
        D_80115112 = D_80115112 + 1;
    }
}
