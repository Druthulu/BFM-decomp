/* func_8012BC60 — shared body (overlay slot 0x80128158, h_exact 34a25b32). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void Square0(s32 *a0, s32 *a1);
s32 func_8012BC60(struct Vec *a0, struct Vec *a1) {
    s32 d[3];
    d[0] = a0->unk2 - a1->unk2;
    d[1] = a0->unk6 - a1->unk6;
    d[2] = a0->unkA - a1->unkA;
    Square0(d, d);
    return d[0] + d[1] + d[2];
}
