/* func_80153E00 — shared body (overlay slot 0x80128158, h_exact d8de78ab). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078E78[];
extern s32 D_80127518;
extern s16 currentLocationId;
extern s16 D_8011DB0C;
extern u16 D_8011F748;
extern s16 D_8011DB1A;
extern void func_80149020(s32 *a0);
extern u16 func_80148800(s32 *a0);
extern s32 func_8014891C(s32 a0);
extern s32 func_80148980(u8 *a0);
extern s32 func_801489E8(s32 a0);
extern s32 func_80148A48(s32 a0);
extern void func_80153C18(void);
extern void func_8015410C(void);
extern void func_80159B3C(void *a0);
extern void func_80165718(s32 a0);
extern void func_8014BC44(s32 a0, s32 a1);
extern void func_8014ACE8(void *a0, s32 a1, s32 a2);
extern void func_8014B310(void);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_80153E00(s32 param_1) {
    s32 b;
    u32 uVar3;
    register u32 s2 __asm__("$18");  // !FAKE: pin $18 — NEEDED DIFFERS (P36 rung B headers1)
    u8 *s3;
    u32 t;
    s32 iVar4;
    s32 db0c;
    func_80149020((s32 *)param_1);
    s3 = D_80078E78;
    b = *(u8 *)(param_1 + 0xA9);
    if (b == 0x53) goto LAB_E74;
    if (b < 0x54) {
        if (b == 0x41) goto LAB_E64;
        t = (u16)uVar3;
        goto LAB_EC8;
    }
    if (b == 0x73) goto LAB_E74;
    t = (u16)uVar3;
    goto LAB_EC8;
LAB_E64:
    uVar3 = func_80148800((s32 *)param_1) & 0xf000;
    goto LAB_EC4;
LAB_E74:
    iVar4 = func_8014891C(param_1);
    s2 = (u32)(iVar4 != 0) << 0xc;
    uVar3 = s2;
    iVar4 = func_80148980((u8 *)param_1);
    if (iVar4 != 0) {
        uVar3 = s2 | 0x4000;
    }
    iVar4 = func_801489E8(param_1);
    if (iVar4 != 0) {
        uVar3 = uVar3 | 0x8000;
    }
    iVar4 = func_80148A48(param_1);
    if (iVar4 != 0) {
        uVar3 = uVar3 | 0x2000;
    }
LAB_EC4:
    t = (u16)uVar3;
LAB_EC8:
    uVar3 = t >> 0xc;
    if ((((u16)uVar3 != 0) && (((u16)uVar3 & *(u8 *)(param_1 + 0xdf)) == 0)) &&
        (iVar4 = *(u8 *)(param_1 + 0xde) - 1, *(u8 *)(param_1 + 0xde) = (u8)iVar4, (u8)iVar4 == 0)) {
        ((void (*)(s32))func_80153C18)(param_1);
    }
    *(u8 *)(param_1 + 0xdf) = (u8)uVar3;
    if (D_80127518 == 0) {
        if (currentLocationId != 0x3075) {
            *(u16 *)(param_1 + 0x88) = *(u16 *)(param_1 + 0x244);
            *(u16 *)(param_1 + 0x8a) = *(u16 *)(param_1 + 0x246);
            *(u16 *)(param_1 + 0x8c) = *(u16 *)(param_1 + 0x248);
        }
        ((void (*)(s32))func_8015410C)(param_1);
        func_80159B3C((void *)param_1);
        func_80165718(param_1);
        return;
    }
    db0c = *(u16 *)&D_8011DB0C;
    if (db0c == 1) goto LAB_FA8;
    if (db0c < 2) goto LAB_AC;
    if (db0c == 2) goto LAB_FD4;
    if (db0c != 3) goto LAB_AC;
    ((void (*)(s32))func_8014B310)(param_1);
LAB_FA8:
    func_8014BC44(param_1, (s32)D_8011DB1A);
    func_8014ACE8((void *)param_1, 1, (s32)D_8011DB1A);
    goto LAB_9C;
LAB_FD4:
    func_8014BC44(param_1, (s32)D_8011DB1A);
    func_8014ACE8((void *)param_1, 1, (s32)D_8011DB1A);
    ((void (*)(s32))func_8014B310)(param_1);
    func_80146994(0x42, param_1, 0, 0);
    func_80146A6C(0x42, (void *)param_1, 0x20, 0, 0, 1, 0);
    func_80146A6C(0x42, (void *)param_1, 0, 0, 0x20, 1, 0);
    func_80146A6C(0x42, (void *)param_1, -0x20, 0, 0, 1, 0);
    func_80146A6C(0x42, (void *)param_1, 0, 0, -0x20, 1, 0);
LAB_9C:
    D_8011DB0C = 0;
    D_8011F748 = 0;
LAB_AC:
    if (D_8011F748 != 0) {
        ((void (*)(s32))func_8015410C)(param_1);
        func_80159B3C((void *)param_1);
        func_8014BC44(param_1, *(u16 *)(s3 + 0x3C));
        D_8011DB0C = 0;
        D_8011F748 = 0;
    }
}
