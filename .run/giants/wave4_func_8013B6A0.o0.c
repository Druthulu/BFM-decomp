struct S { int f0; short f4; short f6; short f8; short fa; int fc; char pad[12]; };
struct P { unsigned short a; unsigned short b; unsigned short c; };
extern struct S D_801A57C0[];

void func_8013B6A0(int param_1, struct P *param_2, int param_3) {
    D_801A57C0[param_1].f0 = 1;
    D_801A57C0[param_1].f4 = param_2->a;
    D_801A57C0[param_1].f6 = param_2->b;
    D_801A57C0[param_1].f8 = param_2->c;
    D_801A57C0[param_1].fc = param_3;
}
