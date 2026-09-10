/* func_801416D4 — shared body (overlay slot 0x80128158, h_exact 7589d537). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_8011514C;
extern u8 D_8011514D;
extern u8 D_8011515C;
extern s32 func_800D11F0(s32 a0);
extern s32 func_800D1658(s32 a0);
extern void func_80141C0C(s32);
s32 func_801416D4(s16 param_1) {
    u8 cVar2;
    s32 iVar1;
    s32 two;
    two = 2;
    iVar1 = 0;
    cVar2 = *(u8 *)&D_8011514C + D_8011514D * D_8011515C;
    if (param_1 == 1) goto c1;
    if (param_1 < 2) {
        if (param_1 == 0) goto c0;
        goto ret;
    }
    if (param_1 == two) goto c2;
    goto ret;
c0:
    iVar1 = func_800D11F0(cVar2 & 0xFF);
    goto ret;
c1:
    iVar1 = func_800D1658(cVar2 & 0xFF);
    goto ret;
c2:
    func_80141C0C(6);
    iVar1 = 1;
ret:
    return (iVar1 << 0x10) >> 0x10;
}
