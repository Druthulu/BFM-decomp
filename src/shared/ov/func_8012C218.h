/* guess_FreeActor — shared body (overlay slot 0x80128158, h_exact ce41e186). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_ZeroMemory(void *a0, s32 a1);
/* guess_FreeActor: frees a 0x10C-byte actor: zeroes its +0x20 sub-object (0x38 bytes for type 2, 0x84 for type 1), then the actor itself
 * Confidence medium, xref chain: guess_ZeroMemory(sub, 0x38 or 0x84 by the sub's type halfword), then guess_ZeroMemory(a0, 0x10C); guess_SpawnActor reuses slots whose +0 is 0
 * Names ledger: config/names.tsv guess_FreeActor */
void guess_FreeActor(void *a0) {
    u16 *p = ((u16 **)a0)[8];   /* 0x20/4 */
    if (p) {
        s32 a1;
        switch (*p) {
        case 2:  a1 = 0x38; break;
        case 1:  a1 = 0x84; break;
        default: goto skip;
        }
        guess_ZeroMemory(p, a1);
    }
skip:
    guess_ZeroMemory(a0, 0x10C);
}
