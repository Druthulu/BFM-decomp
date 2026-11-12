/* guess_SetTexAnimAndReleaseGrab_2 — shared body (overlay slot 0x80128158, h_exact fba9368c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_SetTexAnim(int, int);
extern int func_8015E0D4(int);
/* guess_SetTexAnimAndReleaseGrab_2: starts texture animation 0x11 and lets go of the actor linked at +0x178 (moved, sent code 0x11, link cleared)
 * Confidence low, xref chain: guess_SetTexAnim(a0, 0x11); func_8015E0D4: +0x178 actor nudged, guess_PostActorEvent(actor, 0x11, .., pos, yaw), +0x178 = 0
 * Names ledger: config/names.tsv guess_SetTexAnimAndReleaseGrab_2 */
int guess_SetTexAnimAndReleaseGrab_2(int a0) {
    guess_SetTexAnim(a0, 0x11);
    return func_8015E0D4(a0);
}
