/* func_8013A4C4 — shared body (overlay slot 0x80128158, h_exact 2db7165d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8013A530();
void func_8013A4C4(struct S8013A4C4 *a0) {
    struct Inner8013A4C4 *a1 = a0->unk4;
    a0->unkE = 0;
    a1->unk28 -= 0x400;
    a1->unk2A -= 0x400;
    if (a1->unk28 < 0x401) {
        a1->unk2A = 0;
        a1->unk28 = 0;
        a0->unk0 = 4;
        a0->unk2 = 0;
        a0->unk4 = 0;
    } else {
        func_8013A530();
    }
}
