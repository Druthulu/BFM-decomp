/* guess_FreeSmallObjectAndParts — shared body (overlay slot 0x80128158, h_exact c20da3b0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_ZeroMemory(void *a0, s32 a1);
extern s32 guess_FreeSmallObject();  // K&R: ? of 1 args (P37 rung D t4_HD7)
/* guess_FreeSmallObjectAndParts: zeroes the 0x38-byte records at a0 +0x10, +0x14, +0x18 (when set) and frees a0 with guess_FreeSmallObject
 * Confidence medium, xref chain: guess_ZeroMemory(+0x10/+0x14/+0x18, 0x38) when non-zero, then guess_FreeSmallObject(a0)
 * Names ledger: config/names.tsv guess_FreeSmallObjectAndParts */
void guess_FreeSmallObjectAndParts(void *a0) {
    if (*(s32*)((s32)a0 + 0x10) != 0) {
        guess_ZeroMemory(*(void**)((s32)a0 + 0x10), 0x38);
    }
    if (*(s32*)((s32)a0 + 0x14) != 0) {
        guess_ZeroMemory(*(void**)((s32)a0 + 0x14), 0x38);
    }
    if (*(s32*)((s32)a0 + 0x18) != 0) {
        guess_ZeroMemory(*(void**)((s32)a0 + 0x18), 0x38);
    }
    ((void (*)(void *))guess_FreeSmallObject)(a0);
}
