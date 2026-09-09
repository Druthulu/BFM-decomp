/* func_80165580 — shared body (overlay slot 0x80128158, h_exact 7088316d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80165580(s32 _arg0)
{
    if (D_80078EC5 & 0x80) {
        ((void (*)(void))func_80165B28)();
    } else {
        D_80181EDC[D_80078EC1 & 0x7F]();
    }
}
