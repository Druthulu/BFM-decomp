/* func_80149954 — shared body (overlay slot 0x80128158, h_exact 7921cb4a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8012E5CC(s32 param_1, u16 param_2, u16 param_3);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80147364();
extern s32 func_800CCF28(s32 a0);
extern u16 *func_80146750(u16 *param_1);
extern u8 D_80126B5C;
extern void *D_8012707C;
extern s16 currentLocationId;
s32 func_80149954(s32 s0) {
    s32 sp10[2];
    s16 buf[10];
    if (*(s32 *)(s0 + 0x44) & 0x404) {
        return 0;
    }
    if ((*(u16 *)(s0 + 0xAA) & 0x90) == 0) {
        if (currentLocationId == 0x308D) {
            func_80015978((s32)&D_80126B5C, sp10);
            func_8012E5CC((s32)sp10, 0x4, 0x8E0);
            return 0;
        }
        func_8002D4C8(0x4, 0x8E0);
        return 0;
    }
    if (*(u16 *)(s0 + 0xAC) & 0x90) {
        if ((s32)D_8012707C == 0x8E0) {
            D_8012707C = 0;
        } else {
            func_80147364(0x8E0, 0);
        }
    }
    func_800CCF28(s0);
    *(s16 *)((s32)buf + 0x0) = 0x12;
    *(s32 *)((s32)buf + 0x8) = s0;
    *(s16 *)((s32)buf + 0x2) = 0;
    *(s16 *)((s32)buf + 0x4) = -0x1E;
    *(s16 *)((s32)buf + 0x6) = 0;
    *(s32 *)((s32)buf + 0xC) = 0;
    *(s32 *)((s32)buf + 0x10) = 0;
    func_80146750(buf);
    return 1;
}
