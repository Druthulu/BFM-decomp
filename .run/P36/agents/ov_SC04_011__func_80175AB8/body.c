void func_80175AB8(param_1)
    s16 param_1;
{
   /* size 0x0C */
    extern S_AF634 D_800AF634[];
    extern S_AF634 D_800AF638[];

    extern u8  D_8011F7F0;
    extern u16 D_8011F7B4;
    extern u16 D_8011F7B6;
    extern s16 D_8011F7BC;
    extern s16 D_8011F7BE;
    extern s32 D_8011F804;
    extern u16 D_8011F80A;
    extern u16 D_8011F824;
    extern u8  D_8011F832;
    extern u8  D_8011F83A;
    extern u8 *D_80193B4C[];

    extern u32 *func_80176D94(void *param_1, u32 param_2, s16 param_3_);
    extern u32 *func_801770E0(void *param_1, u32 param_2, s16 param_3_);
    extern u32  func_801783D0(s32 a0, s32 a1);
    extern u32 *func_80177EA4(u32 *param_1, s32 param_2, u32 param_3, s32 param_4);
    extern u32 *func_80177B5C(u32 *a0, s32 a1, s32 a2, s32 a3, s32 a4);
    extern void func_80177940(u32 *p, u32 a_, u32 b_, u32 c_);
    extern u32 *func_80178298(u32 *param_1, u8 *param_2, short param_3, short param_4);
    extern s32 func_80024054(u8*, u8*);
    extern s32  func_8005A600(s32, s32, s32, s32, s32);

    u8 local[24];
    u8 *base;
    u8 *arr;
    u32 *slot;
    u32 *p;
    s16 q;
    s32 a2v;
    s32 t;
    s32 idx;
    s16 sv;

    p = (u32 *)(D_800AF638[param_1].g0 + D_800AF634[param_1].g0 * 4);
    base = &D_8011F7F0;
    arr = base - 0x48;
    slot = (u32 *)(param_1 * 4 + (s32)arr);
    *(volatile u32 *)&slot[6] = (u32)p;
    p = func_80176D94(p, (s16)(D_8011F7B4 - 0x71), (s16)(D_8011F7B6 + 0x51));
    p = func_801770E0(p, (s16)(D_8011F7B4 - 0x71), (s16)(D_8011F7B6 + 0x65));
    t = func_801783D0(D_8011F804, 0);
    p = func_80177EA4(p, t,
                      (s16)((*(u16 *)&D_8011F7BC) + 0x39), (s16)((*(u16 *)&D_8011F7BE) + 0x51));
    sv = (s16)func_801783D0((D_8011F824 < 1000) ? D_8011F824 : 0x3E7, 4);
    p = func_80177B5C(p, sv, D_8011F832,
                      (s16)(*(u16 *)(arr + 0x14) + 0x39),
                      (s16)(*(u16 *)(arr + 0x16) + 0x65));
    q = (s16)D_8011F80A / 15;
    a2v = (q & 3) * 15;
    t = func_801783D0(q >> 2, 8) + func_801783D0(a2v, 0);
    p = ((u32 * (*)(u32 *, s32, s32, s32))func_80177940)(
            p, (s16)t,
            (s16)(*(u16 *)(arr + 0x14) + 0x76),
            (s16)(*(u16 *)(arr + 0x16) + 0x65));
    idx = D_8011F83A & 0x7F;
    D_8011F83A = idx;
    func_80024054(*(u8 **)((u8 *)D_80193B4C + idx * 4), local);
    p = func_80178298(p, local,
                      (s16)(*(u16 *)(arr + 0x14) + 0x39),
                      (s16)(*(u16 *)(arr + 0x16) + 0x5B));
    func_8005A600((s32)p, 0, 0, 0x15, 0);
    *p = (((u32)p - 0x14) & 0xFFFFFF) | 0x2000000;
    slot[8] = (u32)p;
    p += 5;
    D_800AF634[param_1].g0 += ((s32)p - (s32)slot[6]) >> 2;
}
