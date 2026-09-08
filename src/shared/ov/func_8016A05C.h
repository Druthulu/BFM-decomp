/* func_8016A05C — shared body (overlay slot 0x80128158, h_exact a1c05555). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078EC0;
void func_8016A05C(void *a0) {
    s32 v0;
    if (D_80078EC0 & 0x7F) {
        v0 = *(u16 *)((s32)a0 + 2) + 1;
    } else {
        v0 = 2;
    }
    *(s16 *)((s32)a0 + 2) = v0;
}
