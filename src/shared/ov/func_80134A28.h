/* guess_Vec3sDotAdd_2 — shared body (overlay slot 0x80128158, h_exact ffd70f58). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_Vec3sDotAdd_2: returns the dot product of two s16 vectors plus a2
 * Confidence high, code inference: returns a0->x * a1->x + a0->y * a1->y + a0->z * a1->z + a2 over two Vec3s; body identical at all 3 addresses
 * Names ledger: config/names.tsv guess_Vec3sDotAdd_2 */
s32 guess_Vec3sDotAdd_2(s32 a0, s32 a1, s32 a2) {
    return *(s16*)(a0 + 0x0) * *(s16*)(a1 + 0x0)
         + *(s16*)(a0 + 0x2) * *(s16*)(a1 + 0x2)
         + *(s16*)(a0 + 0x4) * *(s16*)(a1 + 0x4)
         + a2;
}
