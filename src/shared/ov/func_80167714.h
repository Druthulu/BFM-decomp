/* func_80167714 — shared body (overlay slot 0x80128158, h_exact a7f0e3d6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80146C3C();
extern void func_80147324(s32 arg0);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 rand(void);
void func_80167714(s32 param_1) {
    s32 *psVar7;
    s32 iVar2;
    s32 src;
    u32 uVar4;
    psVar7 = *(s32 **)(param_1 + 0x34);
    if (*(u16 *)psVar7 != 1) {
        goto LAB_80167894;
    }
    if (*(s16 *)(param_1 + 0x12) > *(s16 *)(param_1 + 0x10)) {
        iVar2 = *(s32 *)(param_1 + 0x1c);
        if (iVar2 < 1) goto LAB_801677b0;
        *(u16 *)(param_1 + 0x10) = rand() & 0x30;
        iVar2 = -0x20;
    } else {
        iVar2 = *(s32 *)(param_1 + 0x1c);
        if (-1 < iVar2) goto LAB_801677b0;
        *(u16 *)(param_1 + 0x10) = (rand() & 0x30) + 0x40;
        iVar2 = 0x20;
    }
    *(s32 *)(param_1 + 0x1c) = iVar2;
LAB_801677b0:
    *(s16 *)(param_1 + 0x12) = *(u16 *)(param_1 + 0x12) + *(s32 *)(param_1 + 0x1c);
    if ((*(u32 *)(param_1 + 0x2c) & 8) != 0) {
        *(s32 *)(param_1 + 0x30) = *(s32 *)(param_1 + 0x30) + 0x80;
    } else {
        *(s32 *)(param_1 + 0x30) = *(s32 *)(param_1 + 0x30) - 0x40;
    }
    uVar4 = *(u32 *)(param_1 + 0x2c);
    *(u32 *)(param_1 + 0x2c) = uVar4 + 1;
    if ((uVar4 & 0xf) == 0) {
        func_80147324(0x44e);
    }
    src = *(s32 *)((s32)psVar7 + 0x20);
    *(Blk16 *)(param_1 + 0x38) = *(Blk16 *)(src + 0x34);
    *(Blk16 *)(param_1 + 0x48) = *(Blk16 *)(src + 0x44);
    func_801670E4(param_1, 0, 0, 0);
    if ((*(u32 *)(*(s32 *)(*(s32 *)(param_1 + 0x34) + 0x4c) + 0x44) & 0x20) == 0) {
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) - 1;
    }
    return;
LAB_80167894:
    ((void (*)(s32))func_80146C3C)(param_1);
}
