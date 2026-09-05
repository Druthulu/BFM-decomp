extern s32 func_801789AC(s32 a0);
extern void func_80178CBC(s32 a0, s32 a1);
extern s32 func_80178970(s32 *a0);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80029514(s32 a0);
extern void func_80178D18(u8 *a0);
extern void func_801EF560(void *a0);
extern s32 D_801F0C34;
extern s32 D_801F0D24;

void func_801EF49C(void *a0) {
    s32 v1;

    v1 = *(u16 *)((s32)a0 + 0x34);

    if (v1 != 0) {
        if (v1 == 1) {
            goto L801EF51C;
        }
        return;
    }

    v1 = func_801789AC((s32)a0);
    if (v1 == 0) {
        return;
    }
    if (v1 == 1) {
        func_80178CBC((s32)a0, (s32)&D_801F0C34);
        *(s16 *)((s32)a0 + 0x34) = 1;
    } else {
        func_80178CBC((s32)a0, (s32)&D_801F0D24);
    }
    return;

L801EF51C:
    if (func_80178970((s32 *)a0)) {
        func_80029124(0xEC, 1);
        func_80029514(0x6E);
        func_80178D18((u8 *)a0);
        func_801EF560(a0);
    }
}
