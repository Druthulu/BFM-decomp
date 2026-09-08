/* func_80163A94 — shared body (overlay slot 0x80128158, h_exact 205796ba). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80163A94(s32 param_1) {
    extern s32 D_800636C8;
    extern s32 D_800DE5A0;
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_8014659C(void);
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    extern void func_80146CA0(void *a0);
    extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
    extern void func_80146E90(s32 *a0, s32 a1);
    extern void func_80147324(s32 a0);
    extern void func_80149374(int, int);
    s32 iVar7;
    s32 iVar1;
    s32 iVar2;
    s32 iVar3;
    iVar7 = *(s32 *)(param_1 + 0x4c);
    *(u32 *)(iVar7 + 0x44) = *(u32 *)(iVar7 + 0x44) | 4;
    iVar1 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001C214(iVar1, (s32)&D_800DE5A0);
        *(s32 *)(iVar1 + 0x20) = (s32)&D_800636C8;
        *(s16 *)(iVar1 + 0x1c) = 0x1800;
        *(s16 *)(iVar1 + 0x1a) = 0x1800;
        *(s16 *)(iVar1 + 0x18) = 0x1800;
        *(u16 *)(iVar1 + 0x2c) = *(u16 *)(iVar1 + 0x2c) | 0x10;
        func_80149374(iVar7, param_1 + 4);
        iVar3 = *(s32 *)(param_1 + 0x20);
        iVar2 = *(s32 *)(iVar7 + 0x20);
        *(Blk16 *)(iVar3 + 0x34) = *(Blk16 *)(iVar2 + 0x34);
        *(Blk16 *)(iVar3 + 0x44) = *(Blk16 *)(iVar2 + 0x44);
        *(s16 *)(iVar1 + 0x10) = *(s16 *)(*(s32 *)(iVar7 + 0x20) + 0x10);
        *(s16 *)(iVar1 + 0x12) = *(s16 *)(*(s32 *)(iVar7 + 0x20) + 0x12);
        *(s16 *)(iVar1 + 0x14) = *(s16 *)(*(s32 *)(iVar7 + 0x20) + 0x14);
        *(s16 *)(param_1 + 0x60) = *(s16 *)(iVar7 + 0x100);
        *(s16 *)(param_1 + 0x62) = *(s16 *)(iVar7 + 0x102);
        *(s16 *)(param_1 + 0x64) = *(s16 *)(iVar7 + 0x104);
        func_80147324(0x448);
        func_80146E90((s32 *)param_1, 0x10);
        func_80146A6C(0xd, (void *)param_1, 0, 0, 0, 0, 0);
        func_80146DE8((s32 *)param_1, 0, 0, 0xffe00000);
        func_80146CA0((void *)param_1);
    }
    return;
}
