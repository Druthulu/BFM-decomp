/* func_80187DB8 — shared body (overlay slot 0x80128158, h_exact 2dfcb449). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80187F30(void*, s32);
extern s32 func_80143BDC(u16*);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern u16 D_80126B66;
void func_80187DB8(s32 param_1) {
    u16 sp10[3];
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + 0x100;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + 0x40;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) + 0x58;
    if (((s32 (*)(s32, s32))func_80187F30)(param_1, 1) != 0) {
        s32 t0, t1, t2, t3;
        sp10[0] = *(u16 *)(param_1 + 0x6);
        sp10[1] = *(u16 *)(param_1 + 0xA);
        sp10[2] = *(u16 *)(param_1 + 0xE);
        ((void (*)(u16 *))func_80143BDC)(sp10);
        t0 = *(s32 *)(param_1 + 0xE0);
        t1 = *(s32 *)(param_1 + 0xE4);
        t2 = *(s32 *)(param_1 + 0xE8);
        t3 = *(s32 *)(param_1 + 0xDC);
        *(s32 *)(param_1 + 0x4C) = 0;
        *(s32 *)(param_1 + 0x44) = 0;
        *(s32 *)(param_1 + 0x10) = t0;
        *(s32 *)(param_1 + 0x14) = t1;
        *(s32 *)(param_1 + 0x18) = t2;
        *(s32 *)(param_1 + 0x48) = t3;
    }
    if (func_8012BEE8(param_1) == 1 ||
        (s32)(s16)D_80126B66 - 0x200 < *(s16 *)(param_1 + 0x6)) {
        func_8012C218((void *)param_1);
    }
}
