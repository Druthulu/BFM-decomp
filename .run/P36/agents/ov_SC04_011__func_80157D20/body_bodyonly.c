void func_80157D20(void)
{

    extern u16 D_80192768[];
    void *a0v;
    u16 a1v;
    void *param_1 = a0v;
    s32 param_2 = a1v;

    ((void (*)(void))func_80156648)();
    ((void (*)(void *, s32))func_80147078)(param_1, D_80192768[param_2]);
    ((void (*)(void *))func_80157D74)(param_1);
}
