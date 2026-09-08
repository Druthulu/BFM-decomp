/* func_80181820 — shared body (overlay slot 0x80128158, h_exact 07c2791e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_80126976;
extern s16 D_8012696C;
extern s16 D_80126978;
extern s16 D_8012697A;
extern u8 D_80126948[];
extern void func_8012A018(s32 a, s32 b);
extern void func_80181D2C(u8*);
extern void func_8012A094(s32 a0);
void func_80181820(void) {
    u8 *ptr;
    D_80126954 = 0x12C;
    D_8012695C = 0x3E8;
    D_80126968 = 0x80;
    D_8012696A = 0x200;
    D_80126976 = 0x50;
    D_8012696C = 0;
    D_80126978 = -0xC8;
    D_8012697A = 0;
    func_8012A018((s32)func_80181D2C, 0);
    ptr = D_80126948;
    ((void (*)(void *))func_80181D2C)(ptr);
    func_8012A094((s32)ptr);
}
