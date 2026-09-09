/* func_801550FC — shared body (overlay slot 0x80128158, h_exact 1a1b2a6c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801550FC(s32 arg0)
{
    if (arg0 & 0x40000000) {
        MoveImage(&D_801810A4[arg0 & 0xFF], 0x200, 0x100);
    } else {
        ((void (*)(void))func_800183E0)();
    }
}
