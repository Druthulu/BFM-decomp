/* func_80147324 — shared body (overlay slot 0x80128158, h_exact f4200521). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80147364(u16 param_1, u16 param_2);
extern void *D_8012707C;
void func_80147324(s32 arg0) {
    s32 temp_a0;
    temp_a0 = arg0 & 0xFFFF;
    if (temp_a0 == D_8012707C) {
        D_8012707C = 0;
        return;
    }
    func_80147364(temp_a0, 0);
}
