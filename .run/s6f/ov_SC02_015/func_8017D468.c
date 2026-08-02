extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern u8 D_80126948[];
extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017D500(void *a0);

void func_8017D468(void) {
    D_80126954 = 0x12C;
    D_8012695C = 0x384;
    D_80126968 = 0x155;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017D500, 0);
    func_8012A094((s32)D_80126948);
    func_8017D500(D_80126948);
}
