extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017D22C(void *a0);
extern u8 D_80126948[];
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

void func_8017D194(void) {
    D_80126954 = 0x190;
    D_8012695C = 0x4B0;
    D_80126968 = 0x2AA;
    D_8012696A = 0xA00;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017D22C, 1);
    func_8012A094((s32)D_80126948);
    func_8017D22C(D_80126948);
}
