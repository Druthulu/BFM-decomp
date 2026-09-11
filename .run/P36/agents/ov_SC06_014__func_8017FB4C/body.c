void func_8017FB4C(void *a0)
{
    void *s2 = *(void **)((s32)a0 + 0x20);
    void *p;
    s32 rot;
    s32 flag;
    s32 angle;
    s32 a;
    s32 b;

    func_8017FD74(a0);
    p = (void *)D_801A14A8;
    if (p != 0) {
        rot = *(u16 *)((s32)s2 + 0x12) + 0x800;
        p = *(void **)((s32)p + 0x20);
        flag = *(u16 *)((s32)p + 0x12) & 0x400;
        angle = rot & 0xFFF;
        if (flag) {
            a = func_80012A60(angle, 0x400);
            b = func_80012A60(angle, 0xC00);
            if ((s16)a <= (s16)b) {
                *(u16 *)((s32)s2 + 0x12) = 0x400;
            } else {
                *(u16 *)((s32)s2 + 0x12) = 0xC00;
            }
        } else {
            a = func_80012A60(angle, 0);
            b = func_80012A60(angle, 0x800);
            if ((s16)a <= (s16)b) {
                *(u16 *)((s32)s2 + 0x12) = 0;
            } else {
                *(u16 *)((s32)s2 + 0x12) = 0x800;
            }
        }
    }
    func_80171990((u8 *)a0);
}
