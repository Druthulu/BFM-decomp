extern int func_80178970(void);
extern void func_80178D18(void);

void func_8017D5C4(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 7;
    }
}
