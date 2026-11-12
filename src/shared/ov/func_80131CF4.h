/* guess_LookupIdValue — shared body (overlay slot 0x80128158, h_exact 9d2db9ce). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_LookupIdValue: returns the value paired with id a1 in a table of {id, value} word pairs; id 0 ends it, id 0xD continues at its value
 * Confidence high, code inference: walks 8-byte {id, value} pairs from a0: 0 ends (returns 0), 0xD links to the pair list at value, a matching id returns value
 * Names ledger: config/names.tsv guess_LookupIdValue */
s32 guess_LookupIdValue(s32 *a0, s32 a1)
{
    if (a0 == 0) {
        return 0;
    }
    while (a0[0] != 0) {
        if (a0[0] == 0xD) {
            a0 = (s32 *)a0[1];
        } else if (a0[0] == a1) {
            return a0[1];
        } else {
            a0 = (s32 *)((u8 *)a0 + 8);
        }
    }
    return 0;
}
