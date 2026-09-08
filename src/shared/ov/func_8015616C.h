/* func_8015616C — shared body (overlay slot 0x80128158, h_exact 9fff1f2f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern S801563EC *func_801563EC(u16 idx);
extern s32 func_80029B4C(s32 a0, s32 a1);
extern s32 func_80029BC8(s32 a0, s32 a1);
extern s32 func_80029C44(s32 a0, s32 a1);
extern s32 func_80029178(s32 arg);
extern s32 func_8015640C(s32 a0, s32 a1);
extern s32 rand(void);
extern u16 D_8012693A;
extern u16 D_801152B8;
u32 func_8015616C(s32 param_1, u16 param_2) {
    u16 *p;
    u16 uVar1, uVar2, uVar3, uVar4, uVar5, uVar7;
    u32 base;
    u32 uVar12;
    s16 sVar11;
    p = ((u16 * (*)(s32))func_801563EC)(param_2 & 0xFFFF);
    uVar1 = p[0];
    uVar2 = p[1];
    uVar3 = p[2];
    uVar4 = p[3];
    uVar5 = p[4];
    uVar7 = p[5];
    base = uVar1 & 0xFFF;
    if (uVar1 & 0x4000) {
        uVar12 = func_80029B4C(base, (s32)(s16)uVar2)
               + func_80029BC8((s32)(s16)uVar3, (s32)(s16)uVar4);
    } else if (uVar1 & 0x2000) {
        uVar12 = func_80029C44(base, (s32)(s16)uVar2);
    } else {
        uVar12 = base + rand() % (uVar2 + 1);
    }
    D_8012693A = uVar5;
    if ((u8)func_80029178(0x81)) {
        D_8012693A = D_8012693A << 1;
    }
    sVar11 = 0;
    if (uVar7 != 0) {
        if ((u8)func_80029178(0x1A)) {
            sVar11 = 5;
        } else if ((u8)func_80029178(0x19)) {
            sVar11 = 4;
        } else if ((u8)func_80029178(0x18)) {
            sVar11 = 3;
        } else if ((u8)func_80029178(0x17)) {
            sVar11 = 2;
        } else if ((u8)func_80029178(0x16)) {
            sVar11 = 1;
        }
    }
    D_801152B8 = uVar7 + sVar11;
    if (uVar1 & 0x8000) {
        uVar12 = func_8015640C(param_1, uVar12 & 0xFFFF);
    }
    return uVar12 & 0xFFFF;
}
