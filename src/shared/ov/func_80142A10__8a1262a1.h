/* func_80142A10 — shared body (overlay slot 0x80128158, h_exact 8a1262a1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80142A10(int param_1)
{

    extern void (*D_801801C0[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_801801C0[*(u16 *)(param_1 + 2)]();
        if (*(s16 *)(param_1 + 0xFC) != 0) {
            ((void (*)(int))func_80142A80)(param_1);
        }
    }
}
