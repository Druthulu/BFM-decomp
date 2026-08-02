extern void func_8012CBCC(s32 a0);
extern void func_8012E688(void*, s32, s32);

void func_80180BFC(s32 a0) {
    if (((s32 (*)(s32))func_8012CBCC)(a0) & 0x2000) {
        s16 v = *(s16 *)(a0 + 0x70);
        if (v != 0) {
            *(s16 *)(a0 + 0x2) = 2;
            ((void (*)(void*, s32, s32))func_8012E688)((void *)a0, 0xBA2, 0);
        } else {
            void *p = *(void **)(a0 + 0x20);
            *(s16 *)(a0 + 0x2) = 3;
            *(s32 *)(p + 0x4) |= 0x80000000;
            *(s32 *)(a0 + 0x1C) = 0x1E;
        }
    }
}
