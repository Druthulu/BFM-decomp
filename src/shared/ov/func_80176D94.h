/* func_80176D94 — shared body (overlay slot 0x80128158, h_exact 9a53081e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void *func_80177784(void *a0, s32 a1, s32 a2, s32 a3);
extern u32 func_801783D0(s32 a0, s32 a1);
extern void *func_801777BC();
extern u16 D_8011F82C;
extern u16 D_8011F82A;
u32 *func_80176D94(void *param_1, u32 param_2, s16 param_3_)
{
    s32 c3 = 3;     /* $s5 */
    s32 cad = 0xad;  /* $s4 */
    s32 cff = 0xff;  /* $s3 */
    s32 iVar6 = (s16)param_3_;               /* -> $s1 */
    u32 uVar5 = iVar6 << 16;                 /* -> $s0 */
    void *uVar2;
    void *u4, *u5;                           /* fresh single-set save vars (S2 boost) */
    u32 *puVar3;
    s16 sVar1;
    u32 uVar4;
    u32 dl;                                  /* multi-set D-load var (2 sets, no boost) */
    s32 t;
    uVar2 = ((void * (*)(void *, s32, s32))func_80177784)(param_1, uVar5 | (u16)param_2, 0x6b565040);
    uVar2 = ((void * (*)(void *, s32, s32))func_80177784)(uVar2, uVar5 | ((param_2 + 8) & 0xffff), 0x6b565808);
    uVar2 = ((void * (*)(void *, s32, s32))func_80177784)(uVar2, uVar5 | ((param_2 + 0x10) & 0xffff), 0x6b564060);
    u4 = ((void * (*)(void *, s32, s32))func_80177784)(uVar2, uVar5 | ((param_2 + 0x30) & 0xffff), 0x6b563858);
    sVar1 = (s16)func_801783D0(D_8011F82C, 4);
    u5 = func_801777BC(u4, sVar1, (s32)((param_2 + 0x18) << 16) >> 16, iVar6, c3, cad, cff);
    sVar1 = (s16)func_801783D0(D_8011F82A, 4);
    puVar3 = (u32 *)func_801777BC(u5, sVar1, (s32)((param_2 + 0x38) << 16) >> 16, iVar6, c3, cad, cff);
    dl = ((struct { u16 h; } *)&D_8011F82C)->h;
    { u32 v0m = ((u32)(puVar3 - 5) & 0xffffff) | 0x3000000;
      register u32 c6000 __asm__("$6") = 0x6000dcff;  // !FAKE: pin $6 — NEEDED DIFFERS (P36 rung B headers1)
      puVar3[1] = c6000;
      *puVar3 = v0m; }
    uVar4 = ((iVar6 + 10) << 16) | ((param_2 + 1) & 0xffff);
    puVar3[2] = uVar4;
    puVar3[3] = ((s32)(dl * 0x50e6) >> 16) | 0x20000;
    dl = ((struct { u16 h; } *)&D_8011F82A)->h;
    puVar3[5] = ((u32)puVar3 & 0xffffff) | 0x3000000;
    puVar3[10] = ((u32)(puVar3 + 5) & 0xffffff) | 0x3000000;
    puVar3[6] = 0x600000ff;
    puVar3[7] = uVar4;
    puVar3[0xb] = 0x60000000;
    puVar3[0xc] = ((iVar6 + 9) << 16) | (param_2 & 0xffff);
    t = (s32)(dl * 0x50e6) >> 16;
    puVar3[8] = t | 0x20000;
    puVar3[0xd] = (t + 2) | 0x40000;
    return puVar3 + 0xf;
}
