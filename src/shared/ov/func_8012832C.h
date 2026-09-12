/* func_8012832C — shared body (overlay slot 0x80128158, h_exact 0c4914b6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 currentLocationId;
extern s32 func_80029504(void);
extern s32 func_800CF854(s32);
extern s32 func_801289F0(void);
extern s32 func_801288E8(s32);
extern s32 func_80128940(s32);
extern s32 func_80029178(s32);
extern s32 func_801288B0(void);
extern void func_80011C10(void);
void func_8012832C(void) {
    s32 a0 = func_80029504();
    s32 v0;
    switch (currentLocationId) {
    case 0x300E:
        if (func_800CF854(a0) == 0) {
            v0 = func_80128998();
        } else {
            v0 = func_801289F0();
        }
        break;
    case 0x30A0:
        if (a0 < 0x640) {
            v0 = func_801288E8(a0);
        } else {
            v0 = func_80128940(a0);
        }
        break;
    case 0x3014:
        if (a0 == 0x4B0 && (func_80029178(0x138) & 0xFF) == 0) {
            v0 = func_801288B0();
        } else {
            v0 = 1;
        }
        break;
    default:
        func_80011C10();
        return;
    }
    if (v0 != 0) {
        func_80011C10();
    }
}
