/* guess_FreeSmallObject — shared body (overlay slot 0x80128158, h_exact 0f47073c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_ZeroMemory(void *a0, s32 a1);
/* $v0 at exit: leftover of void guess_ZeroMemory; no byte-neutral return: `return 0;` inserts `move v0,zero` at +0x48 (+1 insn), ov_SC03_099 objdump */
/* guess_FreeSmallObject: frees a 0x58-byte object: zeroes its +0x20 sub-object (0x84 bytes for type 1, else 0x38), then 0x58 bytes of the object
 * Confidence low, xref chain: guess_ZeroMemory(sub, 0x84 or 0x38 by the sub's type halfword), then guess_ZeroMemory(a0, 0x58); the guess_FreeActor pattern at 0x58 bytes
 * Names ledger: config/names.tsv guess_FreeSmallObject */
s32 guess_FreeSmallObject(u8 *a0) {
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
    guess_ZeroMemory(s0, 0x58);
}
