/* func_80166054 — shared body (overlay slot 0x80128158, h_exact a4984404). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80166054(s32 param_1) {
    extern void func_80149374(s32 a0, s32 a1);
    extern s32 func_8004787C(s32 a0);
    extern s32 func_80047948(s32 a0);
    extern void func_800D1FC8(s32 a0, s32 a1);
    extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
    extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
    extern void func_801661CC(s32 a0);
    extern void func_80146C3C(u8 *a0);
    extern u8 D_800D387C[];
    extern u8 D_800D3888[];
    s32 obj;
    s16 s0;
    s16 s1;
    s32 r0;
    s32 r1;
    s32 v1;
    s32 iVar2;
    s32 iVar3;
    s32 v0;
    s32 r2;
    s32 a0;
    obj = *(s32 *)(param_1 + 0x34);
    func_80149374(obj, param_1 + 4);
    v1 = *(s32 *)(param_1 + 0x2c);
    if (v1 != 0) {
        s1 = 8;
        if (v1 != 3) {
            s0 = *(u16 *)(*(s32 *)(obj + 0x20) + 0x12);
        } else {
            u32 fld = *(u32 *)(param_1 + 0x30);
            s0 = fld & 0xfff;
            s1 = (fld >> 12) & 0xf;
        }
        iVar2 = func_8004787C(s0);
        r0 = iVar2 << s1;
        r1 = -r0;
        iVar3 = func_80047948(s0);
        a0 = iVar3 << s1;
        r2 = -a0;
        if (*(s32 *)(param_1 + 0x2c) == 2) {
            r1 = r0;
            r2 = a0;
        }
        *(s32 *)(param_1 + 0x10) = r1;
        *(s32 *)(param_1 + 0x18) = r2;
    }
    *(s32 *)(param_1 + 0x14) = 0xffff0000;
    func_800D1FC8(param_1, 6);
    v0 = func_800D21C4(param_1, D_800D387C, 0x9c);
    if (v0 != 0) {
        s32 uVar1;
        *(s32 *)(param_1 + 0x20) = v0;
        *(u32 *)(v0 + 4) = *(u32 *)(v0 + 4) | 0x50000040;
        if (*(s32 *)(param_1 + 0x2c) != 3) {
            *(u16 *)(v0 + 0x18) = 0x2000;
        } else {
            *(u16 *)(v0 + 0x18) = *(u16 *)(param_1 + 0x32);
        }
        *(u16 *)(v0 + 0x1a) = *(u16 *)(v0 + 0x18);
        func_80128EA8(v0, param_1 + 0x24, (s32)D_800D3888);
        func_801661CC(param_1);
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}
