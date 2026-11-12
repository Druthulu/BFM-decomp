/* guess_PlaySound — shared body (overlay slot 0x80128158, h_exact 6d5164d1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80147364(u16 param_1, u16 param_2);
/* guess_PlaySound: requests sound id a0 through func_80147364(a0, 0)
 * Confidence medium, xref chain: func_80147364(a0, 0) -> main func_8002D4C8, whose flush keys SPU voices (SpuSetKey); in location 0x308D only when the player is on screen
 * Names ledger: config/names.tsv guess_PlaySound */
void guess_PlaySound(u16 arg0) {
    func_80147364(arg0, 0);
}
