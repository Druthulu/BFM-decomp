/* func_80187090 — shared body (overlay slot 0x80128158, h_exact 64eea305). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32  func_8012CBCC(s32 a0);                  /* host TU L3291 */
extern s32  func_8012BA10(s32 a0, s32 a1);          /* host TU L3071 */
extern void func_8012A828(s32 a0, void *a1);        /* host TU L2930/L3074 */
extern void func_8002D4C8(s32 a0, s32 a1);          /* host TU L52    */
extern s32  func_8012C658(s32 arg0, s32 arg1, s32 arg2); /* host TU L2524 */
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);  /* host TU L323   */
extern s32  func_8004787C(s32 a0);                  /* host TU L2198 */
extern s32  func_80047948(s32 a0);                  /* host TU L2197 */
extern u8 D_801E2170[];                             /* host TU L2938 */
extern u8 D_801E2910[];
extern u8 D_80190548[];
void func_80187090(s32 a0) {
    s32 t;
    u16 sp10[3];
    func_8012CBCC(a0);
    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012BA10(a0, 4);
        if (*(u16 *)(a0 + 0x72) & 0x4000) {
            *(u16 *)(a0 + 0x34) = 1;
            func_8012A828(a0, D_801E2910);
            func_8002D4C8(0xA82, 0);
        }
        break;
    case 1:
        if (*(s32 *)(a0 + 0x94) == 0x28 || *(s32 *)(a0 + 0x94) == 0x2A ||
            *(s32 *)(a0 + 0x94) == 0x2C || *(s32 *)(a0 + 0x94) == 0x2E) {
            if (*(s32 *)(a0 + 0x94) == 0x2E) {
                *(u16 *)(a0 + 0x34) = 2;
            }
            if (*(s32 *)(a0 + 0x94) == 0x28) {
                func_8002D4C8(0xA37, 0);
            }
            func_8012F14C(*(s32 *)(a0 + 0x20) + 0x34, (s32)D_80190548,
                          (s32)sp10);
            t = func_8012C658(0x265, 4, a0);
            if (t != 0) {
                *(u16 *)(*(s32 *)(t + 0x20) + 0x12) =
                    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
                *(s32 *)(t + 0x10) =
                    -(func_8004787C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) << 8);
                *(s32 *)(t + 0x18) =
                    -(func_80047948(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) << 8);
                *(u16 *)(t + 0x6) = sp10[0];
                *(u16 *)(t + 0xA) = sp10[1];
                *(u16 *)(t + 0xE) = sp10[2];
                *(u16 *)(*(s32 *)(t + 0x20) + 0x18) =
                    0x1000 - (((*(s32 *)(a0 + 0x94) - 0x28) << 12) >> 3);
                *(u16 *)(*(s32 *)(t + 0x20) + 0x1A) =
                    0x1000 - (((*(s32 *)(a0 + 0x94) - 0x28) << 12) >> 3);
                *(u16 *)(*(s32 *)(t + 0x20) + 0x1C) =
                    0x1000 - (((*(s32 *)(a0 + 0x94) - 0x28) << 12) >> 3);
            }
        }
        break;
    case 2:
        if (*(u16 *)(a0 + 0x72) & 0x4000) {
            *(u16 *)(a0 + 0xFC) = 0x1E;
            *(u16 *)(a0 + 0x2) = 9;
            func_8012A828(a0, D_801E2170);
            *(u16 *)(a0 + 0xAE) = 0x2900;
        }
        break;
    }
    func_8012C658(0x3DE, 0, a0);
}
