/* func_80151ECC — shared body (overlay slot 0x80128158, h_exact bc1cdab4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149020(s32 *a0);
extern void guess_NextStep(void *a0);
extern s32 func_80172630(u8 *a0);
void func_80151ECC(Unkstruct_80126B58 *a0) {
    func_80149020((s32 *)a0);
    a0->unk64.s = a0->unk64.s + (a0->unkDE.u << 6);
    a0->unkDE.u = a0->unkDE.u + 5;
    if (a0->unk64.s >= 0x1556) {
        a0->unkDE.u = 0x10;
        guess_NextStep(a0);
    }
    func_80172630((u8 *)a0);
}
