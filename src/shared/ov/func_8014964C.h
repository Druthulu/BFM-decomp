/* func_8014964C — shared body (overlay slot 0x80128158, h_exact fffcefd2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012EFB8(s32 a0);
void func_8014964C(s32 param_1, s32 param_2) {
    Vec3 in;
    Vec3 out;
    s32 mid[2];
    s32 p2;
    Vec3 *pin;
    s32 *m1;
    s32 *m2;
    s32 mtx;
    p2 = param_2;
    in.f0 = *(s16 *)(p2 + 2);
    in.f2 = *(s16 *)(p2 + 6);
    in.f4 = *(s16 *)(p2 + 0xA);
    pin = &in;
    mtx = *(s32 *)(param_1 + 0x20);
    __asm__ __volatile__("" : "=r"(mtx) : "0"(mtx));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B headers1)
    m1 = mid;
    __asm__ __volatile__("" : "=r"(m1) : "0"(m1));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B headers1)
    ((void (*)(s32, Vec3 *, s32 *))func_8012F14C)(mtx + 0x34, pin, m1);
    m2 = mid;
    ((void (*)(s32 *, Vec3 *))func_8012EFB8)(m2, &out);
    *(s16 *)(p2 + 2) = out.f0;
    *(s16 *)(p2 + 6) = out.f2;
    *(s16 *)(p2 + 0xA) = out.f4;
}
