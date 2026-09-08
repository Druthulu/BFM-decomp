/* func_8017385C — shared body (overlay slot 0x80128158, h_exact c612942e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80126B30;
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);
void func_8017385C(u8 *a0) {
    switch (D_80126B30) {
    case 0:
    default:
        *(u16 *)(a0 + 0xAC) |= 0x80;
        *(u16 *)(a0 + 0xAA) |= 0x80;
        break;
    case 1:
        *(u16 *)(a0 + 0xAC) |= 0x10;
        *(u16 *)(a0 + 0xAA) |= 0x10;
        break;
    }
    func_80171A1C(a0);
    func_80174650((s32)a0);
}
