/* func_8016D64C — shared body (overlay slot 0x80128158, h_exact 77d41c29). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern short func_8016CBC0(void);
extern void func_80146C3C();
void func_8016D64C(int param_1)
{
    if (func_8016CBC0() == 0) {
        ((void (*)(int))func_80146C3C)(param_1);
    }
    return;
}
