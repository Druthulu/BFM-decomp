/* func_80159BE4 — shared body (overlay slot 0x80128158, h_exact 1cf147fb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80159BE4(s32 arg0)
{
    int v;

    ((void (*)(int, void *))guess_SetMoveVector)(arg0, &D_80181878);
    if ((*(unsigned int *)(arg0 + 0x44) & 0x200) != 0) {
        guess_SetAnim(arg0, 5);
        guess_SetTexAnim(arg0, 0x1C);
    } else {
        guess_SetAnim(arg0, 4);
        guess_SetTexAnim(arg0, 0x11);
    }
    *(int *)(arg0 + 0x234) = 0;
    *(int *)(arg0 + 0x238) = 0;
    func_801553C0(arg0);
    ((void (*)(int))func_801553A8)(arg0);
    ((void (*)(int))func_80172590)(arg0);
    ((void (*)(int))guess_NextStep)(arg0);
}
