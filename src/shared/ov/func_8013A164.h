/* func_8013A164 — shared body (overlay slot 0x80128158, h_exact ccd63ab9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_8012752C;
void func_8013A164(struct S8013A164 *a0) {
    s32 flags;
    if (a0->field_40 == 0 || a0->field_18 == 0 || *a0->field_40 == 2) {
        flags = a0->field_08 | 0x1000;
        a0->field_08 = flags;
        if (flags & 0x10000) {
            if (D_8012752C != 0) {
                if (flags & 0x40000) {
                    a0->field_04 = 2;
                } else {
                    a0->field_04 = 0x10;
                }
            } else {
                a0->field_04 = 2;
            }
        } else {
            a0->field_04 = 2;
        }
    }
}
