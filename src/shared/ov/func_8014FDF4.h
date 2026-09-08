/* func_8014FDF4 — shared body (overlay slot 0x80128158, h_exact fa2e7415). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80150170(void *a0);
extern s32 func_8014FE60();
void func_8014FDF4(struct S8014FDF4 *a0) {
    if (a0->f6 != a0->f88 || a0->fA != a0->f8A || a0->fE != a0->f8C) {
        func_80150170(a0);
    } else {
        func_8014FE60(a0);
    }
}
