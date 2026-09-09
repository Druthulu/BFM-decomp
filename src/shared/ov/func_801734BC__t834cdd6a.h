/* func_801734BC — shared body (overlay slot 0x80128158, h_text 834cdd6a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801734BC(s32 arg0, s32 _unused1) {
    extern void func_80173544(void);
    extern s16 D_80126B40;

    s16 temp;
    switch (((u32)arg0)) {
    case 0: temp = -0x4; break;
    case 1: temp = -0x8; break;
    case 2: temp = -0x12; break;
    case 3: temp = -0x18; break;
    case 4: temp = -0x1C; break;
    default: goto after;
    }
    D_80126B32 = temp;
after:
    D_80126B3E = 0;
    D_80126B40 = 0;
    func_80174684(&func_80173544);
}
