extern void func_8012B370(int a0);
extern void func_8012C218(void *a0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

void func_801834E0(s32 a0)
{
    s32 t;
    register s32 *a1 asm("$5");
    u32 v0;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;

    if (t != 0) {
        a1 = *(s32 **)(a0 + 0x20);
        v0 = *(u32 *)(a1 + 0x1);
        v0 ^= 0x80000000;
        *(u32 *)(a1 + 0x1) = v0;
        ((void (*)(void))func_8012B370)();

        t = *(s32 *)(a0 + 0x1C);
        if ((t & 0x3) != 0) {
            s32 s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    func_8012C218((void *)a0);
}
