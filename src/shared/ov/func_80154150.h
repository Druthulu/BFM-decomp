/* guess_SetAnim — shared body (overlay slot 0x80128158, h_exact 2ad8c33c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154190(u8 *a0, s32 a1);
/* guess_SetAnim: starts animation a1 from the object's table (+0xB0) unless it is already the current one (+0xB4)
 * Confidence medium, xref chain: if +0xB4 != (+0xB0)[a1]: func_80154190 sets +0xB4, resets its counters and steps it; the +0xB4 script sets the model's frame pointer
 * Names ledger: config/names.tsv guess_SetAnim */
void guess_SetAnim(s32 a0, s32 a1)
{
    if (*(s32 *)(a0 + 0xB4) != ((s32 *)*(s32 *)(a0 + 0xB0))[a1]) {
        func_80154190(a0, a1);
    }
}
