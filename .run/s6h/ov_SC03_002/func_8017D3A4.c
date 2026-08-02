extern int func_80178970(void);
extern s32 func_8012CBCC(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void (*D_80189030[])(void);

void func_8017D3A4(s32 a0) {
    s32 v0, v1;
    s32 stack[3];

    func_80178970();

    v0 = *(s32*)((s32)a0 + 0x1C);
    v1 = -1;
    v0 = v0 - 1;
    *(s32*)((s32)a0 + 0x1C) = v0;

    if (v0 != v1) {
        v0 = func_8012CBCC(a0);
        if ((v0 & 0x2000) == 0) {
            return;
        }
    }

    func_80146A6C(2, (void*)a0, 0, 0, 0, 0, 0);
    func_8012A828(a0, (void*)&D_80189030);

    v1 = *(s32*)((s32)a0 + 0x20);
    v0 = *(u16*)((s32)v1 + 0x12);
    v0 = v0 + 0xB00;
    *(u16*)((s32)v1 + 0x12) = v0;

    stack[0] = 0;
    stack[1] = 0;
    stack[2] = 0xFFF40000;

    func_8012B2CC(a0);
    func_8012B14C(a0, (s32)stack);

    *(u16*)((s32)a0 + 0xFE) = 1;
    *(s32*)((s32)a0 + 0x1C) = 0x40;
    *(u16*)((s32)a0 + 0x2) = 5;
}
