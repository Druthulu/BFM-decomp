/* func_8016F764 — shared body (overlay slot 0x80128158, h_exact b883cd28). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80171928(void *a0);
void func_8016F764(void *a0) {
    s32 v0 = *(s32 *)((u8 *)a0 + 0x200) - 1;
    *(s32 *)((u8 *)a0 + 0x200) = v0;
    if (v0 == -1) {
        func_80171928(a0);
    }
}
