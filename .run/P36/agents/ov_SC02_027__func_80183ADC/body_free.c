void func_80183ADC(s32 a0)
{
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern s32 func_80029178(s32);
    extern void func_80183344(s32 a0);
    extern void func_801832D8(s32 a0);

    extern s32 D_801AD2B8;
    extern s32 D_801AB718;
    extern s32 D_801AB728;

    s32 v0;
    s32 temp;

    if ((*(s32 *)((s32)a0 + 0x20) = v0 = ((s32 (*)(void))func_8012C1B8)()) == 0) {
        func_8012CAE4(a0);
        return;
    }

    /* §67: pin v0 against hoisting past the store */
    func_8001C214(v0, (s32)&D_801AD2B8);

    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = 0x1000;
    temp = *(s32 *)((s32)a0 + 0x20);
    *(s16 *)(temp + 0x1C) = 0xA00;
    *(s16 *)(temp + 0x18) = 0xA00;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;

    *(s32 *)((s32)a0 + 0x58) = (s32)&D_801AB718 | 0x20000000;
    *(u16 *)((s32)a0 + 0x5C) = 0xCC00;
    *(u8 *)((s32)a0 + 0x75) = 0;

    if ((func_80029178(((u16 *)&D_801AB728)[*(s16 *)((s32)a0 + 0x70)]) & 0xFF) != 0) {
        func_80183344(a0);
        return;
    }

    *(u16 *)((s32)a0 + 0xFE) = 0;
    func_801832D8(a0);
}
