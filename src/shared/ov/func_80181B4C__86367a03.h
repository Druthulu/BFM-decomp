/* func_80181B4C — shared body (overlay slot 0x80128158, h_exact 86367a03). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_80126978;
extern u16 D_80126B5E;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_8012697A;
extern s32 D_801269E4;
extern u8 D_801269E8;
extern s16 D_801274E8;
extern u8 D_80126948[];
extern void func_80181D2C(u8*);
extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32);
extern void func_80129CF8(void);
void func_80181B4C(void)
{
    u16 v1;
    D_80126954 = 0x12C;
    D_8012695C = 0x190;
    D_80126968 = 0x80;
    D_8012696A = 0x800;
    D_80126978 = -0x80;
    v1 = D_80126B5E;
    D_8012696C = 0;
    D_80126976 = 0;
    D_8012697A = -0xC8;
    D_801269E4 = 0;
    D_801269E8 = 0;
    D_801274E8 = v1;
    func_8012A018((s32)func_80181D2C, 0x2);
    D_80126968 = 0x120;
    func_8012A094(D_80126948);
    func_80129CF8();
}
