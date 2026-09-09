/* func_80157D20 — shared body (overlay slot 0x80128158, h_exact d073e622). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80157D20(void)
{

    extern u16 D_80180E00[];
    register void *a0v __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B headers2)
    register s32 a1v __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B headers2)
    void *param_1 = a0v;
    s32 param_2 = a1v;

    ((void (*)(void))func_80156648)();
    ((void (*)(void *, s32))func_80147078)(param_1, D_80180E00[param_2]);
    ((void (*)(void *))func_80157D74)(param_1);
}
