extern s32 D_800CDD2C;
extern s32 D_800CDD34;

extern void func_800CD674(s32, s32, s32);
extern void func_800116A0(void);

void func_800CD408(void) {
    s32 a1 = D_800CDD2C;
    s32 a2 = D_800CDD34;
    func_800CD674(0, a1, a2);

    a2 = D_800CDD34;
    a2 += 8;
    D_800CDD34 = a2;

    if (a2 < 0x80) {
        // skip
    } else {
        func_800116A0();
    }
}
