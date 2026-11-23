/* func_8014FDF4 — shared body (overlay slot 0x80128158, h_exact fa2e7415). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80150170(void *a0);
extern s32 func_8014FE60(void *e);
void func_8014FDF4(Unkstruct_80126B58 *a0) {
    if (a0->unk4.i.hi.s != a0->unk88.s || a0->unk8.i.hi.s != a0->unk8A.s || a0->unkC.i.hi.s != a0->unk8C.s) {
        func_80150170(a0);
    } else {
        func_8014FE60(a0);
    }
}
