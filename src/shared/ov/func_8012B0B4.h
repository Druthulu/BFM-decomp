/* func_8012B0B4 — shared body (overlay slot 0x80128158, h_exact fcda221c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int func_80047948(int a0);
extern int func_8004787C(int a0);
void func_8012B0B4(unsigned int *param_1, int param_2, int param_3)
{
    int iVar1, iVar2;
    int prod;          /* mflo dest = $a3 (both products) */
    unsigned int *p;    /* store addr copied into $v0 */
    int sh1;            /* shares $v0 with p (non-overlapping) */
    register int sh2 __asm__("$3");            /* 2nd-product shift -> $v1 */  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B headers1)
    unsigned int uVar3, result;
    uVar3 = (param_2 - 0x400U) & 0xfff;
    iVar1 = func_80047948(uVar3);
    result &= 0xFFFF0000;
    prod = iVar1 * param_3;
    sh1 = prod >> 0xc;
    result |= sh1 & 0xFFFF;
    iVar2 = func_8004787C(uVar3);
    prod = iVar2 * -param_3;
    result &= 0xFFFF;
    /* Force the param_1->$v0 copy AND let the scheduler hoist it into the
       mult->mflo delay slot (a plain `p = param_1` gets coalesced away). */
    __asm__ ("addu %0,%1,$zero" : "=r"(p) : "r"(param_1));  // !FAKE: instruction addu — NEEDED DIFFERS (P36 rung B headers1)
    sh2 = prod >> 0xc;
    result |= sh2 << 0x10;
    *p = result;
}
