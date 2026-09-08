/* func_80184A08 — shared body (overlay slot 0x80128158, h_exact 5f634e86). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_801E8754;
extern void func_80036D58();
extern void func_8018623C(u16 arg0, u16 arg1);
extern void func_80185E00(void);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_8018EDDC[];
extern s32 D_801E8820;
extern void func_80181934(void);
extern void func_8018621C(void);
extern s32 D_801B9230;
extern void func_8018483C();
void func_80184A08(s32 p) {
    s16 t;
    D_801E8754 -= 1;
    if (D_801E8754 == -1) {
        func_80036D58(2);
    }
    t = *(u16 *)(p + 0xDE) - 1;
    *(s16 *)(p + 0xDE) = t;
    if (t == 0) {
        func_8018623C(0x4E1, 0);
    }
    t = *(u16 *)(p + 0xDC) - 1;
    *(s16 *)(p + 0xDC) = t;
    if (t == 0) {
        func_80185E00();
        func_8012A828(p, &(*(s32 *)D_8018EDDC));
        D_801E8820 = 0x3E8;
        func_80181934();
        *(s16 *)(*(s32 *)(p + 0x20) + 0x14) = -0x400;
        ((void (*)(void *))func_8018621C)(&D_801B9230);
        *(s16 *)(p + 0xA) = -0x3F4;
        *(s16 *)(p + 0x6) = 0;
        *(s16 *)(p + 0xE) = 0x3C98;
        *(s16 *)(p + 0x2) = *(u16 *)(p + 0x2) + 1;
    } else {
        func_8018483C(p);
    }
}
