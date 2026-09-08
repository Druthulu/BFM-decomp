/* func_80133298 — shared body (overlay slot 0x80128158, h_exact dd5916cc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012F0BC(s32 *a0, s32 *a1, s32 *a2);
extern void func_8012B2CC(s32 a0);
extern void func_8013339C(s16 *a0, s16 *a1);
extern void func_8012F1A4(s32 *a0, s32 a1, s32 *a2);
void func_80133298(s32 *a0)
{
    extern u8 D_80126B5C; /* canonical decl (engine_core.h DEFINE_func_8012BD14) */
    extern s32 D_80126B5C_w __asm__("D_80126B5C"); /* same symbol, s32 view */
    extern s32 D_80126B60;
    extern s32 D_80126B64;
    s32 in[3];
    s32 out[3];
    s32 tmp[3];
    Blk32L_80133298 m;
    in[0] = D_80126B5C_w;
    in[1] = D_80126B60;
    in[2] = D_80126B64;
    func_8012F0BC((s32 *)(a0[8] + 0x34), in, tmp);
    func_8012B2CC((s32)a0);
    m = *(Blk32L_80133298 *)(a0[8] + 0x34);
    func_8013339C((s16 *)&m, (s16 *)(a0[8] + 0x18));
    func_8012F1A4((s32 *)&m, (s32)tmp, out);
    D_80126B5C_w = out[0];
    D_80126B60 = out[1];
    D_80126B64 = out[2];
}
