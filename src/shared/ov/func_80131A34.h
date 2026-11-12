/* guess_StartActorSequenceById — shared body (overlay slot 0x80128158, h_exact d5151bad). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_StartActorSequence(s32 a0, void *a1);
/* guess_StartActorSequenceById: looks id a1 up in the object's id table (+0xBC) and, when found, starts that sequence; ids 8, 0xB, 0x20 set bit 2 of +0xC4
 * Confidence medium, xref chain: p = guess_LookupIdValue(+0xBC, a1); if p: set or clear bit 2 of +0xC4 by id, guess_StartActorSequence(a0, p), return 1
 * Names ledger: config/names.tsv guess_StartActorSequenceById */
s32 guess_StartActorSequenceById(s32 a0, s32 a1)
{
    extern s32 guess_LookupIdValue();  // K&R: 1 of 2 args (P37 unalias t4_ua6)
    void *p;
    p = (void *)((int (*)(int, int))guess_LookupIdValue)(*(s32 *)(a0 + 0xBC), a1);
    if (p != 0) {
        if (a1 == 0xB || a1 == 8 || a1 == 0x20) {
            *(s32 *)(a0 + 0xC4) |= 4;
        } else {
            *(s32 *)(a0 + 0xC4) &= -5;
        }
        guess_StartActorSequence(a0, p);
        return 1;
    }
    return 0;
}
