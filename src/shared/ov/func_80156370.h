/* func_80156370 — shared body (overlay slot 0x80128158, h_exact f3bd412f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern S801563EC *func_801563EC(u16 idx);
extern s32 rand(void);
u16 func_80156370(u16 param_1) {
    u16 *puVar3;
    u16 uVar1;
    u16 uVar2;
    s32 iVar4;
    s32 iVar5;
    puVar3 = ((u16 * (*)(s32))func_801563EC)(param_1 & 0xFFFF);
    uVar1 = puVar3[0] & 0xfff;
    uVar2 = puVar3[1];
    iVar4 = rand();
    iVar5 = uVar2 + 1;
    return (u16)(uVar1 + iVar4 % iVar5);
}
