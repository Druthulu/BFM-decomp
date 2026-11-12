/* guess_StartTriangleAction — shared body (overlay slot 0x80128158, h_exact 0e5161ea). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8015DE24(s32 *a0);
extern void func_80157510(s32 *a0);
/* guess_StartTriangleAction: enters the state the standing step takes on Triangle: state 0xF when +0x178 is set, else state 6 with +0x1AA = 1
 * Confidence low, xref chain: +0x178 ? func_8015DE24 (state 0xF) : (+0x1AA = 1, func_80157510 (state 6)); called after guess_IsTrianglePressed
 * Names ledger: config/names.tsv guess_StartTriangleAction */
void guess_StartTriangleAction(s32 *a0) {
    if (*(s32 *)((s32)a0 + 0x178) != 0) {
        func_8015DE24(a0);
    } else {
        *(s8 *)((s32)a0 + 0x1AA) = 1;
        func_80157510(a0);
    }
}
