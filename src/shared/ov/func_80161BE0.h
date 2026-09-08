/* func_80161BE0 — shared body (overlay slot 0x80128158, h_exact 2e065293). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int func_801497A8(void);
extern void func_801599A4(void *a0);
extern void func_80149864(void);
int func_80161BE0(void *param_1)
{
    if (func_801497A8() == 0) {
        return 0;
    }
    func_801599A4(param_1);
    ((void (*)(void *))func_80149864)(param_1);
    return 1;
}
