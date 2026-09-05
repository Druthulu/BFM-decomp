extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_80187344(s32);
extern s32 func_80029178(s32);
extern void func_80178CBC(s32, s32);
extern short D_801F0900;
extern short D_801F0E10;
extern short D_801F0DD0;

void func_801EF624(void *a0) {
    register s32 s0 __asm__("$16") = (s32)a0;
    *(s16 *)(s0 + 0x2) = 0x1A;
    func_8012E8E0(s0, (s32)&D_801F0900);
    func_8012E88C(s0);
    func_80187344(s0);
    if ((func_80029178(0xEF) & 0xFF) != 0) {
        func_80178CBC(s0, (s32)&D_801F0E10);
        *(s16 *)(s0 + 0x34) = 1;
    } else {
        func_80178CBC(s0, (s32)&D_801F0DD0);
        *(s16 *)(s0 + 0x34) = 0;
    }
}
