/* func_80187300 — shared body (overlay slot 0x80128158, h_exact 0080a712). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012CBCC(s32 a0);
extern s32 func_8012BA10(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern u16 D_80126B96;
extern u8 D_801E2170[];
extern u8 D_801E2B50[];
extern u8 D_80190550[];
extern u8 D_80190558[];
extern u8 D_80190560[];
extern u8 D_80190568[];
void func_80187300(s32 a0) {
    s32 state;
    s32 pad[2];
    func_8012CBCC(a0);
    state = *(u16 *)(a0 + 0x34);
    switch (state) {
    case 0:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012BA10(a0, 4);
        if (*(u16 *)(a0 + 0x72) & 0x4000) {
            *(u16 *)(a0 + 0x34) = 1;
            func_8012A828(a0, D_801E2B50);
        }
        break;
    case 1:
        if (*(s32 *)(a0 + 0x94) == 0xF) {
            func_8002D4C8(0xA89, 0);
            *(u16 *)(a0 + 0x34) = 2;
            if (func_8012D5E4(a0, (s32)D_80190550, (s32)D_80190558, 0x18) == 1) {
                D_80126B96 = 4;
            }
            if (func_8012D5E4(a0, (s32)D_80190550, (s32)D_80190560, 0x18) == 1) {
                D_80126B96 = 4;
            }
            if (func_8012D5E4(a0, (s32)D_80190550, (s32)D_80190568, 0x18) == 1) {
                D_80126B96 = 4;
            }
        }
        break;
    case 2:
        if (*(u16 *)(a0 + 0x72) & 0x4000) {
            func_8012A828(a0, D_801E2170);
            *(u16 *)(a0 + 0x2) = 0xA;
            *(u16 *)(a0 + 0xFC) = 4;
            *(s16 *)(a0 + 0xAE) = -1;
        }
        break;
    }
    func_8012C658(0x3DE, 0, a0);
}
