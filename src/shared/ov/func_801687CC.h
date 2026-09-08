/* func_801687CC — shared body (overlay slot 0x80128158, h_exact 28712a68). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80168828(void);
extern void func_80146C3C();
void func_801687CC(s32 param_1)
{
    if (*(int *)(param_1 + 0x1c) < 3) {
        func_80168828();
        *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
    } else {
        ((void (*)(int))func_80146C3C)(param_1);
    }
}
