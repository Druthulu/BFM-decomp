/* func_80142EC0 — shared body (overlay slot 0x80128158, h_exact 41e70b0a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80142EC0(s32 param_1) {

    extern s32 D_8018089C[];
    s32 d = param_1;
    s32 obj;
    s32 ret;
    s16 sVar2;

    do { ret = ((s32 (*)(void))func_8012C1B8)(); } while (0);
    obj = ret;
    *(s32 *)(d + 0x20) = ret;
    if (ret == 0) {
        ((void (*)(s32))func_8012CAE4)(d);
    } else {
        func_8001CA1C(obj, 0);
        sVar2 = (s16)((*(u16 *)(d + 0x70) & 0xf) * 0x600 + 0xc00);
        *(s16 *)(obj + 0x1a) = sVar2;
        *(s16 *)(obj + 0x18) = sVar2;
        *(s16 *)(d + 0xfc) = 0;
        ((void (*)(s32, s32))func_8012A828)(d, D_8018089C[*(u16 *)(d + 0x70) & 0xf]);
        ((void (*)(s32))func_80142B2C)(d);
    }
}
