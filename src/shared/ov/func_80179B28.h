/* func_80179B28 — shared body (overlay slot 0x80128158, h_exact 72ad1764). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80139914(s32 a0);
void func_80179B28(s32 a0) {
    s32 v1;
    if (a0 == 0) return;
    if (*(s32 *)a0 == 0) return;
    v1 = *(s16 *)(a0 + 4);
    if (v1 == 0) return;
    if (v1 == 0xE) return;
    func_80139914(a0);
}
