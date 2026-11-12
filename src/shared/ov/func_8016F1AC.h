/* guess_GetPlayerControlScript — shared body (overlay slot 0x80128158, h_exact 2ea02c87). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80126D50;
/* guess_GetPlayerControlScript: returns the code address held in the player's word +0x1F8 without its flag bits (0 when no script controls the player)
 * Confidence low, xref chain: D_80126D50 (guess_g_PlayerActor + 0x1F8) & 0x80FFFFFF; func_8016EE94/func_8016EFC8 store an address | 0x4000000 | flags there
 * Names ledger: config/names.tsv guess_GetPlayerControlScript */
s32 guess_GetPlayerControlScript(void) {
    return D_80126D50 & 0x80FFFFFF;
}
