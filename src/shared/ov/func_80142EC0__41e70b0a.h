/* func_80142EC0 — shared body (overlay slot 0x80128158, h_exact 41e70b0a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80142EC0(s32 param_1) {

    extern s32 D_8018089C[];
    register s32 d   __asm__("$16") = param_1;   /* $s0 */  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B headers2)
    register s32 obj __asm__("$17");             /* $s1 */  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B headers2)
    s32 ret;
    s16 sVar2;

    ret = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(d + 0x20) = ret;
    obj = ret;
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
