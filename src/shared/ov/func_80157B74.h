/* func_80157B74 — shared body (overlay slot 0x80128158, h_exact c3e70a00). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern s32 func_80161208();
void func_80157B74(int param_1)
{
    if (*(unsigned short *)(param_1 + 0xB8) == 0x8000) {
        ((void (*)(void))func_801599A4)();
        ((void (*)(int))func_80159B3C)(param_1);
    } else {
        ((void (*)(int))func_80161208)(param_1);
    }
}
