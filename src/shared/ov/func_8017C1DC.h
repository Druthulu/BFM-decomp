/* func_8017C1DC — shared body (overlay slot 0x80128158, h_exact b126e240). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017C1DC(param_1)
int param_1;
{
    int addr;

    addr = *(int *)(param_1 + 0x20);
    if (*(unsigned int *)(param_1 + 0x1c) & 1) {
        *(unsigned int *)(addr + 4) = *(unsigned int *)(addr + 4) | 0x80000000;
    } else {
        *(unsigned int *)(addr + 4) = *(unsigned int *)(addr + 4) & 0x7fffffff;
    }
    if (func_80146E98(param_1) != 0) {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}
