/* func_8016D4DC — shared body (overlay slot 0x80128158, h_exact 70c20d8b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80126B58;
extern void func_8016C83C(s32 a0);
extern s32 VectorNormalSS(void *a0, void *a1);
extern short func_8016CF04();
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_800D22E4(s32 a0);
void func_8016D4DC(s32 a0) {
    s16 d[20];
    s32 a1 = *(s32 *)(a0 + 0x34);
    s32 dist;
    s32 idx;
    if (*(u16 *)a1 != 1) {
        *(s16 *)(a0 + 2) = 3;
        *(s32 *)(a0 + 0x34) = (s32)&D_80126B58;
        *(s32 *)(a0 + 0x1C) = 0x40;
        func_8016C83C(a0);
        return;
    }
    d[0] = *(u16 *)(a1 + 6) - *(u16 *)(a0 + 6);
    d[1] = *(u16 *)(a1 + 0xA) - *(u16 *)(a0 + 0xA);
    d[2] = *(u16 *)(a1 + 0xE) - *(u16 *)(a0 + 0xE);
    dist = VectorNormalSS(d, d);
    if (dist < 0x510) {
        func_8016CF04(a0, 2);
        *(s16 *)(a0 + 2) = 4;
        return;
    }
    if (dist < 0x1900) {
        idx = 6;
    } else if (dist < 0x6400) {
        idx = 5;
    } else {
        idx = 4;
    }
    func_8016C74C(a0, (s32)d, idx, 9, 0x400);
    func_800D22E4(a0);
    func_8016CF04(a0, 1);
}
