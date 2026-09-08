/* func_801884FC — shared body (overlay slot 0x80128158, h_exact bb479f68). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80188680(void *a0, s32 a1, s32 a2);
extern u16 D_80126B5E;
extern u16 D_80126B66;
s32 func_801884FC(void *a0) {
    s32 v1 = *(s16 *)((s32)a0 + 0xE);
    if (v1 >= 0x334 && v1 <= 0x496) {
        return 1;
    }
    if (v1 >= 0xF9 && v1 <= 0x1AD) {
        return 1;
    }
    if (func_80188680(a0, -5, 0xA61)) {
        return 2;
    }
    if (func_80188680(a0, 0x98, 0x8FF)) {
        return 2;
    }
    if (func_80188680(a0, -0x12, 0x2EB)) {
        return 2;
    }
    if (func_80188680(a0, 0xA5, 0x301)) {
        return 2;
    }
    if (func_80188680(a0, 0x6F, 0xCD)) {
        return 2;
    }
    if (func_80188680(a0, -0x2E, -0x17A)) {
        return 2;
    }
    if (func_80188680(a0, 0x69, -0x10CB)) {
        return 2;
    }
    if (func_80188680(a0, -0x9, -0x1215)) {
        return 2;
    }
    if (func_80188680(a0, 0x77, -0x135A)) {
        return 2;
    }
    if (func_80188680(a0, 0x74, -0x15FA)) {
        return 2;
    }
    if (func_80188680(a0, -0x4B, -0x1553)) {
        return 2;
    }
    if (func_80188680(a0, (*(s16 *)&D_80126B5E), (*(s16 *)&D_80126B66))) {
        return 2;
    }
    if (v1 >= -0xB54 && v1 <= -0xB45) {
        return 1;
    }
    return 0;
}
