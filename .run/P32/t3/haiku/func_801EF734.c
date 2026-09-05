extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_80187344(s32);
extern s32 func_80029178(s32);
extern void func_80178CBC(s32, s32);
extern short D_801F0900;
extern short D_801F0A6C;
extern short D_801F0A9C;
extern short D_801F0934;

void func_801EF734(void *a0) {
    s32 s0 = (s32)a0;
    s32 v0;

    *(u16 *)((s32)a0 + 2) = 0x5;
    func_8012E8E0((s32)a0, (s32)&D_801F0900);
    func_8012E88C((s32)a0);
    func_80187344((s32)a0);

    v0 = func_80029178(0xDF);
    if ((v0 & 0xFF) != 0) {
        *(short *)((s32)a0 + 0x34) = 0;
        func_80178CBC(s0, (s32)&D_801F0A6C);
        return;
    }
    v0 = func_80029178(0xE0);
    if ((v0 & 0xFF) != 0) {
        *(short *)((s32)a0 + 0x34) = 1;
        func_80178CBC(s0, (s32)&D_801F0A9C);
    } else {
        *(short *)((s32)a0 + 0x34) = 2;
        func_80178CBC(s0, (s32)&D_801F0934);
    }
}
