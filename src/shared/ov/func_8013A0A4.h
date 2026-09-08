/* func_8013A0A4 — shared body (overlay slot 0x80128158, h_exact baf65af9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80139A8C(s32 a0);
extern void func_80139B18(s32 a0);
void func_8013A0A4(struct S8013A0A4 *a0) {
    if (a0->field_1E != 0) {
        a0->field_1E = a0->field_1E + 5;
    } else {
        a0->field_1E = 4;
    }
    if (a0->field_1E >= 0xC) {
        a0->field_16 = (a0->field_16 + 1) % (a0->field_2E + 1);
        a0->field_1E = 0;
        if (a0->field_8 & 0x100) {
            a0->field_4 = 6;
        } else {
            a0->field_4 = 2;
        }
    }
    func_80139A8C((s32)a0);
    func_80139B18((s32)a0);
}
