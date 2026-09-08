/* func_80139FBC — shared body (overlay slot 0x80128158, h_exact 9267af04). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80139FBC(struct obj *a0) {
    if (a0->unk8 & 0x800) {
        a0->unk8 &= ~0x800;
        a0->unk4 = 2;
    }
}
