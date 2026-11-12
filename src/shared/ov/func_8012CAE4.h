/* guess_FreeActorDuringSpawn — shared body (overlay slot 0x80128158, h_exact 2820a65d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_ZeroMemory(void *a0, s32 a1);
extern u16 D_801274E4[];
/* guess_FreeActorDuringSpawn: frees an actor like guess_FreeActor and sets bit 0 of *D_801274E4, the flag the spawner tests after the init handler
 * Confidence medium, xref chain: *D_801274E4 |= 1, then the guess_FreeActor zeroing; func_8012C890 clears that bit before an actor's init handler and aborts the spawn if set
 * Names ledger: config/names.tsv guess_FreeActorDuringSpawn */
void guess_FreeActorDuringSpawn(void *a0) {
    u16 *d;
    void *p;
    s32 t;
    s32 a1;
    d = D_801274E4;
    *d |= 1;
    p = *(void **)((s32)a0 + 0x20);
    if (p != 0) {
        t = *(u16 *)p;
        if (t != 1) {
            if (t != 2) {
                goto done;
            }
            a1 = 0x38;
        } else {
            a1 = 0x84;
        }
        guess_ZeroMemory(p, a1);
    done:;
    }
    guess_ZeroMemory(a0, 0x10C);
}
