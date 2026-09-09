/* func_80161CD0 — shared body (overlay slot 0x80128158, h_exact 591d568e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void aF80161CD0(int param_1, unsigned int param_2) __asm__("func_80161CD0");
void aF80161CD0(int param_1, unsigned int param_2)
{

    extern unsigned short D_80181D60;
    if (param_2 < 8) {
        if (func_800CF8B4() != 0) {
            func_80147324((&D_80181D60)[param_2]);
        }
    }
}
