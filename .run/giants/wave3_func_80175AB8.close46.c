extern s32 D_800AF634[];
extern s32 D_800AF638[];
extern u16 D_8011F7B4;
extern u16 D_8011F7B6;
extern s32 D_8011F804;
extern u16 D_8011F7BC;
extern u16 D_8011F7BE;
extern u16 D_8011F824;
extern u8  D_8011F832;
extern u16 D_8011F80A;
extern u8  D_8011F83A;
extern u32 D_8018A23C;
extern u8  D_8011F7F0;

extern u32 *func_80176D94(void *param_1, u32 param_2, s16 param_3_);
extern u32 *func_801770E0(void *param_1, u32 param_2, s16 param_3_);
extern u32  func_801783D0(s32 a0, s32 a1);
extern u32 *func_80177EA4(u32 *param_1, s32 param_2, s32 param_3, s32 param_4);
extern u32 *func_80177B5C(u32 *param_1, s32 param_2, s32 param_3, s32 param_4, s32 param_5);
extern u32 *func_80177940(u32 *param_1, s32 param_2, s32 param_3, s32 param_4);
extern u32 *func_80178298(u32 *param_1, u8 *param_2, s16 param_3, s16 param_4);
extern s32  func_8005A600(s32, s32, s32, s32, s32);
extern void func_80024054(void *a0, void *a1);

void func_80175AB8(short param_1) {
    s32 off = param_1 * 12;
    u8 *b = &D_8011F7F0;
    s32 *s4;
    s32 iVar9;
    u32 *h;
    s32 iVar5;
    u16 uVar7;
    u32 uVar6;
    u8 auStack_30[24];

    iVar9 = *(s32 *)((u8 *)D_800AF638 + off) + *(s32 *)((u8 *)D_800AF634 + off) * 4;
    __asm__ __volatile__("" : "=r"(b) : "0"(b));
    s4 = (s32 *)(b - 0x48) + param_1;
    s4[6] = iVar9;
    h = func_801770E0(func_80176D94(iVar9, (s16)(D_8011F7B4 - 0x71), (s16)(D_8011F7B6 + 0x51)),
                      (s16)(D_8011F7B4 - 0x71), (s16)(D_8011F7B6 + 0x65));
    h = func_80177EA4(h, func_801783D0(D_8011F804, 0),
                      (s16)(D_8011F7BC + 0x39), (s16)(D_8011F7BE + 0x51));
    uVar7 = 999;
    if (D_8011F824 < 1000) {
        uVar7 = D_8011F824;
    }
    h = func_80177B5C(h, (s16)func_801783D0(uVar7, 4), D_8011F832,
                      (s16)(*(u16 *)(b - 0x34) + 0x39), (s16)(*(u16 *)(b - 0x32) + 0x65));
    iVar5 = (s16)D_8011F80A / 15;
    h = func_80177940(h,
                      (s16)(func_801783D0(iVar5 * 0x10000 >> 0x12, 8) +
                            func_801783D0((iVar5 & 3) * 0xf, 0)),
                      (s16)(*(u16 *)(b - 0x34) + 0x76), (s16)(*(u16 *)(b - 0x32) + 0x65));
    uVar6 = D_8011F83A;
    D_8011F83A = uVar6 & 0x7f;
    func_80024054((&D_8018A23C)[uVar6 & 0x7f], auStack_30);
    h = func_80178298(h, auStack_30,
                      (s16)(*(u16 *)(b - 0x34) + 0x39), (s16)(*(u16 *)(b - 0x32) + 0x5b));
    func_8005A600((s32)h, 0, 0, 0x15, 0);
    *h = ((u32)(h - 5) & 0xffffff) | 0x2000000;
    *(u32 **)(s4 + 8) = h;
    h += 5;
    *(s32 *)((u8 *)D_800AF634 + off) += ((s32)h - s4[6]) >> 2;
}
