/* guess_ClearStoodOnActor — shared body (overlay slot 0x80128158, h_exact 0820809e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_ClearStoodOnActor: drops the object's link to the actor it stands on (+0x174): clears the link and that actor's byte +0x74 when the actor is live
 * Confidence low, xref chain: p = +0x174; p && *(u16 *)p != 0 -> +0x174 = 0, p[+0x74] = 0; func_8014CD80 does the same when p no longer carries the object
 * Names ledger: config/names.tsv guess_ClearStoodOnActor */
void guess_ClearStoodOnActor(void *a0) {
    s32 v1 = *(s32 *)((s32)a0 + 0x174);
    if (v1 != 0) {
        if (*(u16 *)(v1 + 0) != 0) {
            *(s32 *)((s32)a0 + 0x174) = 0;
            *(s8 *)(v1 + 0x74) = 0;
        }
    }
}
