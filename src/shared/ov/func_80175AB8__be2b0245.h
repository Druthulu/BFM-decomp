/* func_80175AB8 — shared body (overlay slot 0x80128158, h_exact be2b0245). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
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
    extern u8 *D_801821E4[];

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
    register u32 *a0v __asm__("$4");
    u32 uv;
    s32 k;
    s16 q;
    s32 r1;
    s32 a2v;
    register s32 sum __asm__("$5");
    s32 r2;
    s32 idx;
    s16 sv;

    p = (u32 *)(D_800AF638[param_1].g0 + D_800AF634[param_1].g0 * 4);
    __asm__("" : "=r"(base) : "0"(&D_8011F7F0));               /* L1 */
    arr = base - 0x48;
    slot = (u32 *)(param_1 * 4 + (s32)arr);
    *(volatile u32 *)&slot[6] = (u32)p;                        /* L2 */
    p = func_80176D94(p, (s16)(D_8011F7B4 - 0x71), (s16)(D_8011F7B6 + 0x51));
    p = func_801770E0(p, (s16)(D_8011F7B4 - 0x71), (s16)(D_8011F7B6 + 0x65));
    p = func_80177EA4(p, func_801783D0(D_8011F804, 0),
                      (s16)((*(u16 *)&D_8011F7BC) + 0x39), (s16)((*(u16 *)&D_8011F7BE) + 0x51));
    uv = D_8011F824;
    k = 0x3E7;
    if (uv < 1000) {
        k = uv;
    }
    sv = (s16)func_801783D0(k, 4);
    p = func_80177B5C(p, sv, D_8011F832,
                      (s16)(*(u16 *)(base - 0x34) + 0x39),
                      (s16)(*(u16 *)(base - 0x32) + 0x65));
    q = (s16)D_8011F80A / 15;
    a2v = (q & 3) * 15;
    r1 = func_801783D0((s32)(q << 16) >> 18, 8);
    r2 = func_801783D0(a2v, 0);
    a0v = p;                                                   /* L4 */
    sum = r1 + r2;                                             /* L3 */
    p = ((u32 * (*)(u32 *, s32, s32, s32))func_80177940)(
            a0v, (s16)sum,
            (s16)(*(u16 *)(base - 0x34) + 0x76),
            (s16)(*(u16 *)(base - 0x32) + 0x65));
    idx = D_8011F83A & 0x7F;
    D_8011F83A = idx;
    __asm__ __volatile__("" ::: "memory");
    ((void (*)(s32, u8 *))func_80024054)(((s32 *)D_801821E4)[idx], local);
    p = func_80178298(p, local,
                      (s16)(*(u16 *)(base - 0x34) + 0x39),
                      (s16)(*(u16 *)(base - 0x32) + 0x5B));
    func_8005A600((s32)p, 0, 0, 0x15, 0);
    *p = (((u32)p - 0x14) & 0xFFFFFF) | 0x2000000;
    slot[8] = (u32)p;
    p += 5;
    D_800AF634[param_1].g0 += ((s32)p - (s32)slot[6]) >> 2;
}
