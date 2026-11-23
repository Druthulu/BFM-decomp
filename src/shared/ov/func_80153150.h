/* func_80153150 — shared body (overlay slot 0x80128158, h_exact 87f4ab69). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149020(s32 *a0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void guess_NextStep(void *a0);
void func_80153150(Unkstruct_80126B58 *a0) {
    s16 nv;
    func_80149020((s32 *)a0);
    nv = (s16)(a0->unk64.u - 0x100);
    a0->unk64.u = nv;
    a0->unk62.s = nv;
    a0->unk60.s = nv;
    if (nv <= 0) {
        a0->unkDE.u = 0x10;
        func_801470B4((s32)a0);
        func_8015369C((s32)a0);
        guess_NextStep(a0);
    }
}
