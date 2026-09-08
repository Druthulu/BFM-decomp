/* func_80165718 — shared body (overlay slot 0x80128158, h_exact edc0f248). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80165A20(s32 a0);
extern u8 D_80078EC1;
void func_80165718(s32 a0) {
    switch (D_80078EC1) {
    case 3:
    case 0xC:
    case 0x18:
        func_80165A20(a0);
        break;
    }
}
