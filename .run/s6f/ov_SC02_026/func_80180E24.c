extern s32 func_8012BD14(s32 a0);
extern void func_80143970(void *a0);
extern void func_8012E688(void *a0, s32 a1, s32 a2);

void func_80180E24(s32 a0) {
    s32 ret = func_8012BD14(a0);
    if (ret <= 0x64000) {
        typedef struct { s32 f0; s32 f1; } Struct;
        Struct *ptr = *(Struct **)(a0 + 0x20);
        *(s16 *)(a0 + 0x2) = 1;
        ptr->f1 = ptr->f1 & 0x7FFFFFFF;
        func_80143970((void *)a0);
        func_8012E688((void *)a0, 0xBA2, 0);
    }
}
