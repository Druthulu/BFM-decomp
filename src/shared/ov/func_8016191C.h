/* func_8016191C — shared body (overlay slot 0x80128158, h_exact 64d215db). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8016151C(void *a0);
extern void func_8014C010(int a0, int a1);
int func_8016191C(int param_1, unsigned int param_2)
{
    if (param_2 & 1) {
        func_8014C010(param_1, 1);
        return 1;
    }
    if (param_2 & 0x4000) {
        func_8014C010(param_1, 1);
        return 2;
    }
    if (param_2 & 0x2000) {
        func_8014C010(param_1, 1);
        return 4;
    }
    return 0;
}
