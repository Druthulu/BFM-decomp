/* func_80163C2C — shared body (overlay slot 0x80128158, h_exact ac5193f0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80163C2C(s32 param_1) {
    extern void func_80164530(s32 arg0);
    extern void func_80013F3C(s32 a0);
    extern void func_800126C4(s32 a0, s32 a1);
    extern void func_800123F0(s32 a0, s32 a1);
    extern void func_80012558(s32 a0, s32 a1);
    extern void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg4);
    extern void func_80162FC0(s32 *a0);
    extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
    extern void func_80146E90(s32 *a0, s32 a1);
    extern void func_80147364(u16 param_1, u16 param_2);
    extern void func_80146CA0(void *a0);
    extern u16 func_80156370(u16 param_1);
    extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
    extern s32 func_801632F0(void);
    extern s32 func_801632E0(void);
    extern void func_80015978(s32 a0, s32 *a1);
    extern void func_80015954(s32 a0, s32 a1);
    extern void func_80146AB4(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6);
    extern s32 func_80163764(s32 a0);
    extern void (*D_8011DB10)(s32);
    u8 dead[0x20];
    Buf32 buf;
    u8 dead2[8];
    s32 iVar3;
    s32 iVar4;
    s32 obj;
    u16 tmp;
    s32 flags;
    iVar4 = *(s32 *)(param_1 + 0x4c);
    iVar3 = *(s32 *)(param_1 + 0x20);
    ((void (*)(void))func_80164530)();
    *(u16 *)(iVar3 + 0x14) = (*(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) + 0x71) & 0xfff;
    ((void (*)(void *))func_80013F3C)(&buf);
    ((void (*)(void *, s32))func_800126C4)(&buf, *(s16 *)(param_1 + 0x60));
    ((void (*)(void *, s32))func_800123F0)(&buf, *(s16 *)(param_1 + 0x64));
    ((void (*)(void *, s32))func_80012558)(&buf, *(s16 *)(param_1 + 0x62));
    ((void (*)(void *, s32))func_80012558)(&buf, *(s16 *)(iVar3 + 0x12));
    ((void (*)(void *, s32))func_800126C4)(&buf, *(s16 *)(iVar3 + 0x10));
    ((void (*)(void *, s32))func_800123F0)(&buf, *(s16 *)(iVar3 + 0x14));
    ((void (*)(s32, s32, s32, s32, void *))func_80163194)(param_1, 0, 0, 0x18000, &buf);
    ((void (*)(s32))func_80162FC0)(param_1);
    *(Blk16 *)(iVar3 + 0x34) = buf.lo;
    *(Blk16 *)(iVar3 + 0x44) = buf.hi;
    if (*(s32 *)(param_1 + 0x2c) >= 0) {
        ((void (*)(s32, s32, s32, s32))func_80146DE8)(param_1, 0, 0, 0xc0000);
        ((void (*)(s32, s32))func_80146E90)(param_1, 0x20);
        ((void (*)(s32, s32))func_80147364)(4, 0x448);
        ((void (*)(s32))func_80146CA0)(param_1);
        ((void (*)(s32))func_80146CA0)(param_1);
        return;
    }
    func_801634D8(param_1, 0xd, (u16)((s32 (*)(s32))func_80156370)(0xd), 1, 0);
    flags = ((s32 (*)(s32))func_801632F0)(param_1);
    if ((flags & 1) != 0) {
        obj = ((s32 (*)(s32))func_801632E0)(param_1);
        *(s32 *)(iVar4 + 0x184) = obj;
        *(u32 *)(iVar4 + 0x44) = *(u32 *)(iVar4 + 0x44) | 0x20;
        tmp = *(u16 *)(obj + 0x36);
        *(u16 *)(iVar4 + 0x18a) = 0;
        *(u16 *)(iVar4 + 0x188) = 0;
        *(u16 *)(iVar4 + 0x194) = tmp;
        ((void (*)(s32, s32, s32, s32))func_80146DE8)(param_1, 0, 0, 0xc0000);
        if (D_8011DB10 == 0) {
            ((void (*)(s32, s32))func_80015978)(param_1 + 4, param_1 + 0x58);
        } else {
            (*D_8011DB10)(param_1 + 0x58);
            func_80015954(param_1 + 0x58, param_1 + 4);
        }
        *(u16 *)(param_1 + 0x66) = 0;
        ((void (*)(s32, s32))func_80147364)(4, 0x448);
        ((void (*)(s32, s32, s32, s32, s32, s32, s32))func_80146AB4)(0x30, param_1, 0, 0, 0, 0, *(s32 *)(iVar4 + 0x184));
    } else {
        if ((flags & 6) == 0) goto ret;
        ((void (*)(s32, s32, s32, s32))func_80146DE8)(param_1, 0, 0, 0xc0000);
        ((void (*)(s32, s32))func_80146E90)(param_1, 0x20);
        ((void (*)(s32, s32))func_80147364)(4, 0x448);
        ((void (*)(s32))func_80146CA0)(param_1);
    }
    ((void (*)(s32))func_80146CA0)(param_1);
ret:
    func_80163764(param_1);
}
