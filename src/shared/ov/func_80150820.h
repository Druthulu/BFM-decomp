/* func_80150820 — shared body (overlay slot 0x80128158, h_exact e4d59092). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014BD24(s32 a0, s32 a1);
extern void func_8014ACE8(void *a0, s32 a1, s32 a2);
void func_80150820(s32 a0, s32 a1) {
    if (a1 != 0) {
        func_8014BD24(a0, a1);
        func_8014ACE8((void *)a0, 4, a1);
    }
}
