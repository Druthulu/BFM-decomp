extern void (*D_801AFA04[])(void *);
extern s32 func_8012D624(void *a0, s32 a1, s32 a2);
extern void func_8012C218(void *a0);
extern void func_8012B370(void *a0);

void func_80184250(void *a0) {
    u16 temp;
    s32 a1;

    D_801AFA04[*(u16 *)((s32)a0 + 0x2)](a0);

    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        *(u16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) - 0x40;
        temp = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18);
        a1 = (s32)(temp << 16) >> 24;
        if (func_8012D624(a0, a1, 0x14) == 1) {
            func_8012C218(a0);
        } else {
            *(u16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) + 0x40;
            func_8012B370(a0);
        }
    }
}
