/* func_8012E688 — shared body (overlay slot 0x80128158, h_exact 9c43d3fc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_800AF648;
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);
void func_8012E688(s32 param_1, u16 param_2, u16 param_3)
{
    struct { short v[3]; short pad; short xy[2]; int sp1c; int flag; } f;
    register void *p __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung A headers1)
    u16 a = param_2;
    register u16 b __asm__("$17") = param_3;  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung A headers1)
    if (*(s32 *)(param_1 + 0x20) != 0) {
        f.v[0] = (short)*(s32 *)(*(s32 *)(param_1 + 0x20) + 0x48);
        f.v[1] = (short)*(s32 *)(*(s32 *)(param_1 + 0x20) + 0x4C);
        f.v[2] = (short)*(s32 *)(*(s32 *)(param_1 + 0x20) + 0x50);
        p = &D_800AF648;
        func_8004914C(p);
        func_800491AC(&D_800AF648);
        RotTransPers((s32)f.v, (s32)f.xy, &f.sp1c, &f.flag);
        if (f.flag < 0) {
            return;
        }
        if ((u16)(f.xy[0] + 199) >= 399) {
            return;
        }
        if ((u16)(f.xy[1] + 0xA9) >= 0x153) {
            return;
        }
    }
    func_8002D4C8(a, b);
}
