/* func_80154A74 — shared body (overlay slot 0x80128158, h_exact c8386d85). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154AB4(s32 a0, s32 a1);
void func_80154A74(s32 a0, s32 a1) {
    if (*(s32 *)(a0 + 0xD0) != ((s32 *)*(s32 **)(a0 + 0xCC))[a1]) {
        func_80154AB4(a0, a1);
    }
}
