extern u8 D_800AF630[];
extern void func_8001C044(void);
extern void func_80015310(void);
extern void func_8002D858(void);
extern u8 D_800D93FC[];
extern void func_800183E0(s32 a0);
extern s16 D_800EC894;
extern s32 func_800D1E18(void);
extern s32 D_800EC8B0;
extern void func_800118AC(void);

void func_800D0174(void) {
    register u8 *base = D_800AF630;

    *(base + 0xA3E1) = 1;
    func_8001C044();
    func_80015310();
    func_8002D858();
    func_800183E0((s32)&D_800D93FC[0]);
    D_800EC894 = 0;
    D_800EC8B0 = func_800D1E18();
    func_800118AC();
}
