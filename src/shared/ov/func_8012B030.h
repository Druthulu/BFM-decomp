/* guess_SnapActorToGround — shared body (overlay slot 0x80128158, h_exact 2654ea19). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80134510(s32 arg);
/* guess_SnapActorToGround: drops object a0 onto the surface under it: on a hit stores the probed x/y/z and clears the fraction halves
 * Confidence medium, xref chain: local = +6/+A/+E; if func_80134510(local): position = local, fraction halves +4/+8/+C = 0, return 1
 * Names ledger: config/names.tsv guess_SnapActorToGround */
s32 guess_SnapActorToGround(u8 *a0) {
    u16 local[3];
    local[0] = *(u16 *)(a0 + 0x6);
    local[1] = *(u16 *)(a0 + 0xA);
    local[2] = *(u16 *)(a0 + 0xE);
    if (func_80134510((s32)local) == 0) {
        return 0;
    }
    *(u16 *)(a0 + 0x6) = local[0];
    *(u16 *)(a0 + 0xA) = local[1];
    *(u16 *)(a0 + 0xE) = local[2];
    *(u16 *)(a0 + 0xC) = 0;
    *(u16 *)(a0 + 0x8) = 0;
    *(u16 *)(a0 + 0x4) = 0;
    return 1;
}
