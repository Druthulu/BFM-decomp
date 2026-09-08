/* func_8013A250 — shared body (overlay slot 0x80128158, h_exact e163cc8f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80139A8C(s32 a0);
extern void func_80139B18(s32 a0);
extern void func_80138B88(s32 a0);
void func_8013A250(struct S8013A250 *a0) {
    if (a0->unkC != 0) {
        a0->unkC = a0->unkC - 1;
        func_80139A8C((s32)a0);
        if ((a0->unk8 & 0x80020) == 0) {
            func_80139B18((s32)a0);
            return;
        }
    }
    func_80138B88((s32)a0);
}
