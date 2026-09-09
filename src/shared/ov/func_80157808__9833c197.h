/* func_80157808 — shared body (overlay slot 0x80128158, h_exact 9833c197). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80157808(void *param_1)
{
    D_80181584[*(unsigned short *)((char *)param_1 + 2)]();
    D_8018E848 = D_8018E848 - 1;
    if (D_8018E848 == -1) {
        func_801599A4(param_1);
        func_80159B3C(param_1);
    }
}
