extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_80184CB8(s32*, s32);
extern short D_80191074;

void func_8017EAAC(void * arg0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_80191074);
    }
}
