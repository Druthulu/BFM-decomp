/* func_801867F8 — shared body (overlay slot 0x80128158, h_exact e9c8174e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C218(void *a0);
extern s32 func_8012CBCC(s32 a0);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801907C8[];
extern s16 D_801907D0;
extern s16 D_801907D2;
extern s16 D_801907D4;
extern s16 D_801907D8;
extern s16 D_801907DA;
extern s16 D_801907DC;
extern s16 D_801907E0;
extern s16 D_801907E2;
extern s16 D_801907E4;
void func_801867F8(s32 a0) {
    extern u16 D_80126B96;
    u16 *q;
    s32 r;
    s32 t;
    s16 sp10[3];
    if (*(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) < 0x4001) {
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) + 0x100;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) + 0x100;
    }
    r = (s32)D_801907C8;
    sp10[0] = (D_801907D0 * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
    sp10[1] = (D_801907D2 * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
    sp10[2] = (D_801907D4 * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
    if (func_8012D5E4(a0, r, (s32)sp10, 0x30) != 0) {
        q = &D_80126B96;
        *q |= 0x4200;
    }
    sp10[0] = (D_801907D8 * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
    sp10[1] = (D_801907DA * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
    sp10[2] = (D_801907DC * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
    if (func_8012D5E4(a0, r, (s32)sp10, 0x30) != 0) {
        q = &D_80126B96;
        *q |= 0x4200;
    }
    sp10[0] = (D_801907E0 * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
    sp10[1] = (D_801907E2 * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
    sp10[2] = (D_801907E4 * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
    if (func_8012D5E4(a0, r, (s32)sp10, 0x30) != 0) {
        q = &D_80126B96;
        *q |= 0x4200;
    }
    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;
    if (t > 0) {
        if (func_8012CBCC(a0) == 0) {
            return;
        }
    }
    func_8012C218((void *)a0);
}
