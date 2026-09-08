/* func_801831A8 — shared body (overlay slot 0x80128158, h_exact 2e98bb22). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_8018ED88;
extern void func_8013C9C4(s32);
void func_801831A8(void * arg0) {
    if ((*(s32 *)((char *)arg0 + 0x204) & 0xF) == 0) {
        func_8013C9C4((s32)&D_8018ED88);
    }
}
