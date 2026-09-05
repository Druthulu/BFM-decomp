extern s32 func_80178970(s32 *a0);
extern void func_80029514(s32 a0);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80178D18(u8 *a0);
extern void func_80162120(void);
extern s32 func_8018151C(s32);

void func_801CBB80(u8 * a0)
{
    if (func_80178970((s32 *)a0)) {
        func_80029514(0x78);
        func_80029124(0xED, 1);
        func_80178D18((u8 *)a0);
        func_80162120();
        func_8018151C((s32)a0);
    }
}
