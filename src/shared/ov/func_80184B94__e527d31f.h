/* func_80184B94 — shared body (overlay slot 0x80128158, h_exact e527d31f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012B744(void *a0, void *a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s32 func_8012BE98(s32 a0, u16 *a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 D_8018EF88[];
void func_80184B94(s32 s0) {
    u16 *s1 = *(u16 **)(s0 + 0xCC);
    s32 v1;
    s32 state;
    s32 msg;
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) = (u16)func_8012B744((void *)(s0 + 4), s1);
    func_8012B178(s0, 0xFFFA0000);
    func_8012AD80(s0);
    if (func_8012BE98(s0, s1) < 0x41) {
        s32 idx = *(u16 *)(s0 + 0x70);
        s32 tmp1;
        s32 tmp2;
        s32 base;
        *(u16 *)(s0 + 6) = s1[0];
        idx &= 0xF;
        tmp1 = s1[1];
        *(u16 *)(s0 + 0xA) = tmp1;
        tmp2 = s1[2];
        *(u16 *)(s0 + 2) = 1;
        *(u16 *)(s0 + 0xE) = tmp2;
        base = *(s32 *)(s0 + 0x64);
        *(s32 *)(base + 0xE0) |= D_8018EF88[idx];
    }
    if (!(*(s32 *)(s0 + 0xE0) & 0x20000000)) {
        if (!(*(u16 *)(s0 + 0x70) & 1)) {
            state = *(s32 *)(s0 + 0x94);
            if (state == 9) {
                func_8002D4C8(0x77E, 0);
                state = *(s32 *)(s0 + 0x94);
            }
            if (state != 0xF) {
                return;
            }
            msg = 0x77D;
        } else {
            state = *(s32 *)(s0 + 0x94);
            if (state == 0xF) {
                func_8002D4C8(0x781, 0);
                state = *(s32 *)(s0 + 0x94);
            }
            if (state != 0x1B) {
                return;
            }
            msg = 0x780;
        }
        func_8002D4C8(msg, 0);
    }
}
