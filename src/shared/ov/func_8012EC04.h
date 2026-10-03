/* func_8012EC04 — shared body (overlay slot 0x80128158, h_exact 32bb75a9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80049CAC(s32 a0, s32 a1);
void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3)
{
    struct { s16 h[8]; } buf;
    s32 iVar4;
    s32 M;
    s32 c;
    u32 v;   /* $s1 */
    iVar4 = *(s32 *)(param_1 + 0x20);
    v = *(u32 *)(iVar4 + 0x20);
    if (v == 0) {
        *(Blk16 *)(param_3)             = *(Blk16 *)(iVar4 + 0x34);
        *(Blk16 *)((s32)param_3 + 0x10) = *(Blk16 *)(iVar4 + 0x44);
    } else if ((v & 0x1000000) != 0) {
        s32 p;
        s32 w;
        p = (s32)(v & 0xfeffffff);
        p = p + param_2 * 8;
        buf.h[0] = *(s16 *)(p + 6);
        w = *(s32 *)p;
        buf.h[1] = (s16)(*(u8 *)(p + 1) | ((w & 0xf) << 8));
        buf.h[2] = (s16)(((w >> 0x10) & 0xff) | ((w & 0xf0) << 4));
        func_80049CAC((s32)&buf, (s32)param_3);
        param_3[5] = *(s8 *)(p + 3);
        param_3[6] = *(s8 *)(p + 4);
        param_3[7] = *(s8 *)(p + 5);
    } else {
        s32 q;
        v = v + param_2 * 0xc;
        q = (s32)v;
        buf.h[0] = *(s16 *)(q + 6);
        buf.h[1] = *(s16 *)(q + 8);
        buf.h[2] = *(s16 *)(q + 0xa);
        func_80049CAC((s32)&buf, (s32)param_3);
        param_3[5] = *(s16 *)(q + 0);
        param_3[6] = *(s16 *)(q + 2);
        param_3[7] = *(s16 *)(q + 4);
    }
    /* --- GTE tail --- */
    /* gte_SetRotMatrix(M) */
    M = *(s32 *)(param_1 + 0x20) + 0x34;
    gte_SetRotMatrix(M);
    /* column 0: param_3 in place */
    gte_ldclmv((s32)param_3); gte_rtir();
    gte_stclmv((s32)param_3);
    /* column 1: param_3 + 2 */
    c = (s32)param_3 + 2;
    gte_ldclmv(c); gte_rtir();
    gte_stclmv(c);
    /* column 2: param_3 + 4 */
    c = (s32)param_3 + 4;
    gte_ldclmv(c); gte_rtir();
    gte_stclmv(c);
    /* gte_SetTransMatrix(M) — M reloaded */
    M = *(s32 *)(param_1 + 0x20) + 0x34;
    gte_SetTransMatrix(M);
    /* gte_ldlv0(param_3->t) ; gte_rt() ; gte_stlvnl(param_3->t) */
    c = (s32)param_3 + 0x14;
    gte_ldlv0(c); gte_rtv0tr();
    gte_stlvnl(c);
}
