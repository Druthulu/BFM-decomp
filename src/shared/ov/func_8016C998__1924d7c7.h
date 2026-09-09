/* func_8016C998 — shared body (overlay slot 0x80128158, h_exact 1924d7c7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8016C998(s32 param_1)
{

    extern s16 D_80126CE0;
    u16 *psVar7;
    s32 r;
    short i;
    extern Slot_998 D_8018EE98[];

    psVar7 = *(u16 **)(param_1 + 0x34);
    if (*psVar7 != 1) {
        *(s16 *)(param_1 + 2) = 6;
    }
    func_8016CBC0();
    if (*(s16 *)(param_1 + 0x28) != *(s16 *)(*(s32 *)(param_1 + 0x30) + 0x36)) {
        return;
    }
    if ((D_80126B9C & 0x20) == 0) {
        return;
    }
    if ((*(s32 *)(param_1 + 0x1c) == 0) ||
        (*(s16 *)(param_1 + 0x12) < D_80126CE0)) {
        *(s16 *)(param_1 + 0x12) = D_80126CE0;
        i = 0;
        do {
            if (D_8018EE98[i].f0 == 0) {
                goto found;
            }
            i++;
        } while (i < 8);
    found:
        if (i >= 8) {
            return;
        }
        r = func_80146A6C(0x30, psVar7, 0, 0, 0, 0x8000, *(s32 *)(param_1 + 0x30));
        if (r == 0) {
            return;
        }
        D_8018EE98[i].f0 = 1;
        *(Blk32_998 *)(r + 0x38) = *(Blk32_998 *)(param_1 + 0x38);
        *(s16 *)(r + 0x2a) = i;
        *(s16 *)(r + 6) = *(s16 *)(param_1 + 6);
        *(s16 *)(r + 0xa) = *(s16 *)(param_1 + 0xa);
        *(s16 *)(r + 0xe) = *(s16 *)(param_1 + 0xe);
        *(s32 *)(param_1 + 0x1c) = 0x10;
    } else {
        *(s32 *)(param_1 + 0x1c) = *(s32 *)(param_1 + 0x1c) - 1;
    }
}
