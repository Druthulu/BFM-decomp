/* func_8017DCC0 — shared body (overlay slot 0x80128158, h_text d9f46ebc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017DCC0(u8 *a0) {
    s32 v;
    if (*(u16 *)(a0 + 0xB8) & 0x8000) {
        switch ((s16)(*(u16 *)&D_80126B3A - 2)) {
        case 0: v = 0; break;
        case 1: v = 1; break;
        case 2: v = 2; break;
        case 3: v = 3; break;
        case 4: v = 4; break;
        }
        D_80126B3C = v;
        func_8017C624(a0, -0x60, v);
        func_80171A1C(a0);
    }
}
