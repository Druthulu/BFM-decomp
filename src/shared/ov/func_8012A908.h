/* func_8012A908 — shared body (overlay slot 0x80128158, h_exact 0eb9b74e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 guess_g_ObjectTable[]; // Names ledger: config/names.tsv guess_g_ObjectTable
extern u16 D_801270C0;
extern void func_8012A988(u8 *a0);
void func_8012A908(void) {
    u8 *p = guess_g_ObjectTable;
    s32 i;
    for (i = 0; i < 0x60; i++) {
        if (((s16)D_801270C0 == 1) || (*(u16 *)(p + 0x72) & 0x1000)) {
            func_8012A988(p);
        }
        p += 0x10C;
    }
}
