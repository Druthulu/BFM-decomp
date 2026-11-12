/* guess_FreeObjectAndSubObject — shared body (overlay slot 0x80128158, h_exact 3baca933). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80162CCC();  // K&R: 0 of 1 args (P37 unalias t4_ua13)
/* guess_FreeObjectAndSubObject: zeroes object a0 (0x68 bytes) and its +0x20 sub-object (0x84 bytes when that one's first halfword is 1, else 0x38)
 * Confidence medium, code inference: func_80162CCC(a0): p = +0x20; p -> guess_ZeroMemory(p, *p == 1 ? 0x84 : 0x38); guess_ZeroMemory(a0, 0x68); spawn steps call it when allocation fails
 * Names ledger: config/names.tsv guess_FreeObjectAndSubObject */
void guess_FreeObjectAndSubObject(void) {
    func_80162CCC();
}
