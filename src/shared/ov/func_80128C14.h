/* func_80128C14 — shared body (overlay slot 0x80128158, h_exact 96d28a20). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80010AE0(s32 a0);
extern s16 currentLocationId;
void func_80128C14(void) {
    s32 a0;
    switch (currentLocationId) {
    case 0x3023:
        a0 = 0x4E0;
        break;
    case 0x3081:
        a0 = 0x420;
        break;
    case 0x3067:
        a0 = 0x480;
        break;
    case 0x3093:
        a0 = 0xFFB;
        break;
    case 0x30A5:
        a0 = 0xFFB;
        break;
    default:
        a0 = 0x3E0;
        break;
    }
    func_80010AE0(a0);
}
