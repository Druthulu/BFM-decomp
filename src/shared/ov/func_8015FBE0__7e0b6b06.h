/* func_8015FBE0 — shared body (overlay slot 0x80128158, h_exact 7e0b6b06). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015FBE0(s32 *param_1)
{

    extern u8 D_800B9A17;
    if (param_1[0x61] < 0) {
        ((void (**)(s32 *))D_80181160)[*(u16 *)param_1](param_1);
        ((void (*)(s32 *, s16))func_80147078)(param_1, 0);
        ((void (*)(s32 *))func_80159B70)(param_1);
    } else {
        D_80078EC1 = 0;
        ((void (*)(s32 *, s32))func_80154150)(param_1, 0x20);
        ((void (*)(s32 *, s32))func_80154A74)(param_1, 0x18);
        ((void (*)(s32, s32 *, s32, s32, s32, s32, s32))func_80146A6C)(0x16, param_1, 0, 0, 0, 0, 0);
        func_80147324(0x44F);
        ((void (*)(s32 *))func_801553A8)(param_1);
        ((void (*)(s32 *))func_801553C0)(param_1);
        D_801270C0 = 2;
        D_800B9A17 = 0;
        ((void (*)(s32 *))func_80146CA0)(param_1);
    }
}
