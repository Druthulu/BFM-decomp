/* func_80181934 — shared body (overlay slot 0x80128158, h_exact 0bff6629). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80126948[];
extern u16 D_80126B5E;
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_80126978;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_8012697A;
extern s16 D_801274E8;
extern void func_8012A094(s32 a0);
extern void func_8012A018(s32 a, s32 b);
extern void func_80129CF8(void);
extern void func_80181D2C(u8*);
extern s16 D_800B9AB8[];
extern s16 D_800B9ABA[];
void func_80181934(void)
{
    u16 v1;
    v1 = D_80126B5E;
    D_80126954 = 0x64;
    D_8012695C = 0x190;
    D_80126968 = 0x155;
    D_8012696A = 0x800;
    D_80126978 = -0x80;
    D_8012696C = 0;
    D_80126976 = 0;
    D_8012697A = 0x400;
    D_801274E8 = v1;
    func_8012A094((s32)D_80126948);
    func_8012A018((s32)func_80181D2C, 2);
    func_80129CF8();
    *(u16*)&D_800B9AB8[0] = 0xFFB0;
    D_800B9ABA[0] = (s16)0x74;
}
