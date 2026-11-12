/* guess_ClearObjectAndSubObject — shared body (overlay slot 0x80128158, h_exact 14311349). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_ClearObjectAndSubObject: zeroes a0's +0x20 sub-object (0x84 bytes when its u16 +0 is 1, else 0x38) and then 0x68 bytes of a0
 * Confidence medium, xref chain: guess_ZeroMemory(+0x20, *p == 1 ? 0x84 : 0x38); guess_ZeroMemory(a0, 0x68); guess_FreeObjectAndSubObject wraps it
 * Names ledger: config/names.tsv guess_ClearObjectAndSubObject */
void guess_ClearObjectAndSubObject(a0)
    u8 *a0;
{
    u8 *s0 = a0;
    u16 *p = *(u16 **)(s0 + 0x20);
    if (p != 0) {
        s32 a1;
        if (*p == 1) {
            a1 = 0x84;
        } else {
            a1 = 0x38;
        }
        guess_ZeroMemory(p, a1);
    }
    guess_ZeroMemory(s0, 0x68);
}
