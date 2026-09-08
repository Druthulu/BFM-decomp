/* func_80185D10 — shared body (overlay slot 0x80128158, h_exact 501b2845). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8012F2E8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012CB64(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
s32 func_80185D10(void *a0) {
    s16 out[3];
    s16 in[3];
    in[0] = D_80126B5E;
    in[1] = D_80126B62;
    in[2] = D_80126B66;
    func_8012F2E8((s32)a0, (s32)in, (s32)out);
    return func_8012CB64((s32)out, -0x80, 0x80, -0x60, 0);
}
