/* func_8018512C — shared body (overlay slot 0x80128158, h_exact 7d4d544e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_801E873C;
extern s32 D_801E874C;
extern s32 D_801E8010;
extern u16 D_80126B66;
extern u16 D_800B99D8;
extern u8  D_8018B358[];
extern void func_80185F8C();
extern s32  func_8012DB84(void);
extern s32  func_80185C48(s32 a0, s32 a1);
extern void func_8013C9C4(s32);
extern void func_8018623C(u16 arg0, u16 arg1);
extern void func_80187354(s32 a0);
extern s32  func_80185D58(s32 a0);
void func_8018512C(s32 p) {
    s32 a0;
    {
        s32 q;
        register s32 q2 __asm__("$3");
        if (D_801E873C == 0) {
            q = *(s32 *)(p + 0x20);
            *(s16 *)(q + 0x12) = *(u16 *)(q + 0x12) + D_801E874C;
        } else {
            q2 = *(s32 *)(p + 0x20);
            *(s16 *)(q2 + 0x12) = *(u16 *)(q2 + 0x12) + 0x80;
        }
    }
    ((void (*)(s32))func_80185F8C)(p);
    a0 = func_80185D58(p);
    if (a0 != 0) {
        *(s16 *)(p + 0xDE) = a0;
    }
    {
        register s32 idx __asm__("$4");
        register s32 t __asm__("$2");
        s32 q;
        register s32 raw __asm__("$2");
        raw = D_800B99D8;
        idx = raw & 0xF;
        t = (idx >= 0x10) ? (0x1F - idx) : idx;
        idx = t << 2;
        q = *(s32 *)(p + 0x20);
        *(s16 *)(q + 0x14) = -0x420 - idx;
    }
    if (*(s16 *)(p + 0xE) < (s32)(s16)D_80126B66 + 0x80) {
        func_8012DB84();
        D_801E8010 = 1;
    }
    {
        s32 q;
        register s32 q2 __asm__("$3");
        if (D_801E873C == 0) {
            q = *(s32 *)(p + 0x20);
            *(s16 *)(q + 0x12) = *(u16 *)(q + 0x12) + D_801E874C;
        } else {
            q2 = *(s32 *)(p + 0x20);
            *(s16 *)(q2 + 0x12) = *(u16 *)(q2 + 0x12) + 0x80;
        }
    }
    if (func_80185C48(p, 1) != 0) {
        s32 q;
        ((void (*)(void *))func_8013C9C4)(D_8018B358);
        q = *(s32 *)(p + 0x20);
        *(s32 *)(p + 0x4C) = 0;
        *(s32 *)(p + 0x48) = 0;
        *(s32 *)(p + 0x44) = 0;
        *(s32 *)(p + 0x14) = 0;
        *(s16 *)(q + 0x14) = -0x400;
        func_80187354(p);
        func_8018623C((*(s16 *)(p + 0xDE) != 0x100) ? 0x4D7 : 0x4DE, 0);
        func_8018623C(0x4DF, 0x107F);
        *(s16 *)(p + 0x2) = *(u16 *)(p + 0x2) - 1;
    }
}
