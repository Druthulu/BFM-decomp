/* func_80180B20 — shared body (overlay slot 0x80128158, h_exact c32e6d39). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80180DB8();
extern void (*D_8018F58C[])(int);
extern void func_80162D28(s32*);
void func_80180B20(int param_1)
{
    func_80180DB8();
    D_8018F58C[*(unsigned short *)(param_1 + 2)](param_1);
    if (*(s32 *)(param_1 + 0x20) != 0) {
        ((void (*)(int))func_80162D28)(param_1);
    }
}
