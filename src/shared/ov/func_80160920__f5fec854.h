/* func_80160920 — shared body (overlay slot 0x80128158, h_exact f5fec854). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80160920(unsigned short *param_1)
{
    if ((((int (*)(void))guess_GetPadHeld)() & 8) == 0) {
        ((code *)D_80181160)[*param_1](param_1);
        ((void (*)(unsigned short *))func_80160A74)(param_1);
    } else {
        if (((int (*)(unsigned short *))func_80161208)(param_1) == 0 && param_1[0x5c] == 0x8000) {
            ((void (*)(unsigned short *, int))guess_SetAnim)(param_1, 0x25);
            ((void (*)(unsigned short *))guess_NextStep)(param_1);
        }
    }
    return;
}
