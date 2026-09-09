/* func_8012E364 — shared body (overlay slot 0x80128158, h_exact 6d96fc6c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8012E364(s32 arg0_)
{

    extern s16 D_80126CE0;
    extern s32 D_8018E690;
    extern s32 D_8018E694;
    register s32 arg0 __asm__("$6");
    register s32 prev __asm__("$5");
    register u16 flags __asm__("$2");
    s32 a;
    s32 diff;
    s32 v;
    register s32 d __asm__("$2");
    s32 spd;
    s32 e1;
    s32 e2;

    arg0 = arg0_;
    *(s16 *)(arg0 + 0x5C) = 0;
    a = D_80126CE0;
    if (a == 0) {
        D_8018E690 = 0x1000;
        D_8018E694 = 0x1000;
    }
    a = ((0x90 - a) << 12) / 0x90;
    *(s32 *)(arg0 + 0x1C) += 1;
    spd = 0x1000;

    diff = D_8018E690 - a;
    if (diff > 0) {
        D_8018E690 -= diff >> 2;
    } else if (diff < 0) {
        D_8018E690 += (-diff) / 4;
    }

    prev = D_8018E694;
    e1 = *(s32 *)(arg0 + 0x20);
    v = D_8018E690 - prev + spd;
    D_8018E694 = spd;
    flags = *(u16 *)(e1 + 0x2C);
    D_8018E690 = v;
    *(u16 *)(e1 + 0x2C) = flags | 0x10;

    e2 = *(s32 *)(arg0 + 0x20);
    d = __builtin_abs(v);
    *(s16 *)(e2 + 0x1C) = d;
    *(s16 *)(e2 + 0x18) = d;
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = 0x1000;
}
