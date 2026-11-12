/* guess_PlayActorSound — shared body (overlay slot 0x80128158, h_exact a82785b8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_LookupIdValue();  // K&R: 1 of 2 args (P37 unalias t4_ua6)
extern void guess_RequestSound(s32 a0, s32 a1);
/* guess_PlayActorSound: looks key a1 up in actor a0's id table (+0xBC) and requests that sound; returns the id or 0
 * Confidence medium, xref chain: id = guess_LookupIdValue(+0xBC, a1) & 0xFFFF; id != 0 -> guess_RequestSound(id, 0); callers pass keys 0x30/0x31 by player distance
 * Names ledger: config/names.tsv guess_PlayActorSound */
s32 guess_PlayActorSound(void *a0) {
    s32 s0 = guess_LookupIdValue(*(s32 *)((u8 *)a0 + 0xBC)) & 0xFFFF;
    if (s0 != 0) {
        guess_RequestSound(s0, 0);
        return s0;
    }
    return 0;
}
