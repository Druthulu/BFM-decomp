/* func_8012DFD4 — shared body (overlay slot 0x80128158, h_exact ffa5782a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012E014(s32 arg0);
extern void func_8012E138();
void func_8012DFD4(u8 *a0) {
    if (a0[0x74]) {
        ((void (*)(void))func_8012E014)();
    } else {
        func_8012E138();
    }
}
