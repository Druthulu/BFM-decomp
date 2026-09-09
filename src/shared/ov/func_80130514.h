/* func_80130514 — shared body (overlay slot 0x80128158, h_exact f6519009). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012CBF4(s32 a0);
extern void func_801319E0(int);
extern int func_80131D68(int, int);
extern int func_8012BEE8(int);
extern void func_80131CA8(int, int);
void func_80130514(int param_1)
{
    unsigned int uVar1;
    if ((*(unsigned int *)(param_1 + 0xb4) & 0x40) != 0) {
        uVar1 = ((int (*)(void))func_8012CBF4)();
        if (0xf < *(short *)(param_1 + 10)) {
            func_801319E0(param_1);
            return;
        }
        if (func_80131D68(param_1, uVar1) == 1) {
            return;
        }
        if (func_8012BEE8(param_1) != 0) {
            if ((uVar1 & 0x2000) != 0) {
                *(unsigned char *)(param_1 + 0xc1) = 0;
                *(unsigned short *)(param_1 + 0x5e) = 0;
                func_80131CA8(param_1, 0xe);
            }
        }
    }
    /* Scheduling barrier: blocks gcc-2.7.2 reorg from hoisting the join-block
       `move $a0,$s0` into the first branch's delay slot (target keeps a nop there). */
    __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B headers1)
    func_80131CA8(param_1, 0x13);
}
