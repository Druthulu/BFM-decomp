/* func_80175114 — shared body (overlay slot 0x80128158, h_exact 12d06a32). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80175184(s32 *a0);
void func_80175114(s32 *a0) {
    func_80147078(a0, 8);
    *(s16 *)((s32)a0 + 2) = 1;
    func_80175184(a0);
}
