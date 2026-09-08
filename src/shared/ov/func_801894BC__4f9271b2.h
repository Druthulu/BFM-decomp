/* func_801894BC — shared body (overlay slot 0x80128158, h_exact 4f9271b2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int func_80178970(void);
extern void func_80188F28(int a0);
extern int func_80188FB4(int a0, void *a1);
extern void func_80188CB4(int a0);
extern char D_80191908[];
void func_801894BC(int param_1)
{
    ((void (*)(void))func_80178970)();
    func_80188F28(param_1);
    if (func_80188FB4(param_1, (void *)&D_80191908) != 0) {
        func_80188CB4(param_1);
    }
}
