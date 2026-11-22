/* func_8012BC60 — shared body (overlay slot 0x80128158, h_exact 34a25b32). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void Square0(s32 *a0, s32 *a1);
s32 func_8012BC60(VECTOR *a0, VECTOR *a1) {   /* T20.c16: actor +4 16.16 positions, integer parts (was struct Vec *) */
    s32 d[3];
    d[0] = HIH(a0->vx) - HIH(a1->vx);
    d[1] = HIH(a0->vy) - HIH(a1->vy);
    d[2] = HIH(a0->vz) - HIH(a1->vz);
    Square0(d, d);
    return d[0] + d[1] + d[2];
}
