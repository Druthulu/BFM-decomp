/* guess_ShowEneLabelAndValue — shared body (overlay slot 0x80128158, h_exact f456cbc9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_ShowEneLabelAndValue: posts the string "ENE" at screen (0x80, 0x88) and the u16 *a0 as 8 decimal digits at (0xA8, 0x88) to text slots 2 and 3, which are drawn every frame
 * Confidence medium, string: func_8001534C(2, "ENE", 0x80, 0x88) fills a type-1 (string) slot, func_800153CC(3, *a0, 0xA8, 0x88, 0x40) a type-2 (number, 0x40 = decimal) slot; func_80015498 draws both kinds
 * Names ledger: config/names.tsv guess_ShowEneLabelAndValue */
void guess_ShowEneLabelAndValue(u16 *arg0) {
    func_8001534C(2, &D_8018E370, 0x80, 0x88, 0, 0);
    func_800153CC(3, *arg0, 0xA8, 0x88, 0x40, 0);
}
