/* func_801535F4 — shared body (overlay slot 0x80128158, h_exact 9333ce9e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014ED28();
extern void func_80146D90(s32 a0);
extern void func_8014CC28(s32 a0);
extern void func_8014FA04(s32 a0);
s32 func_801535F4(void *arg0) {
    s32 var_s1;
    u32 flags;
    register u32 fcopy __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B headers1)
    s32 ret;
    var_s1 = 0;
    if (((s32 (*)(void))func_8014ED28)() != 0) {
        func_80146D90((s32)arg0);
    }
    if ((*(s32 *)((u8 *)arg0 + 0x34) > 0) &&
        (((s32 (*)(s32))func_8014CC28)((s32)arg0) != 0)) {
        var_s1 = 1;
    }
    flags = ((s32 (*)(s32))func_8014FA04)((s32)arg0);
    fcopy = flags;
    if (flags & 0x4000) {
        ret = 2;
    } else if (flags & 0x2000) {
        ret = 1;
    } else {
        ret = 4;
        if ((fcopy & 0x8000) == 0) {
            ret = var_s1;
        }
    }
    __asm__ __volatile__("" : : "r"(flags));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B headers1)
    return ret;
}
