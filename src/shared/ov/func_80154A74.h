/* guess_SetTexAnim — shared body (overlay slot 0x80128158, h_exact c8386d85). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154AB4(s32 a0, s32 a1);
/* guess_SetTexAnim: starts texture animation a1 from the object's table (+0xCC) unless it is already the current one (+0xD0)
 * Confidence medium, xref chain: if +0xD0 != (+0xCC)[a1]: func_80154AB4 sets +0xD0 and resets its counters; the +0xD0 script's frames MoveImage a VRAM rect to (0x200, 0x100)
 * Names ledger: config/names.tsv guess_SetTexAnim */
void guess_SetTexAnim(s32 a0, s32 a1) {
    if (*(s32 *)(a0 + 0xD0) != ((s32 *)*(s32 **)(a0 + 0xCC))[a1]) {
        func_80154AB4(a0, a1);
    }
}
