/* func_80148824 — shared body (overlay slot 0x80128158, h_exact 1767f7bc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80047D3C(s32 a0);
s32 func_80148824(void *arg0)
{
    register u32 t __asm__("$2");
    register s32 hi __asm__("$3");
    register s32 lo __asm__("$2");
    register s32 chi __asm__("$5");
    register s32 clo __asm__("$4");
    t = *(u16 *)((u8 *)arg0 + 0xAE);
    hi = (t >> 8) - 0x80;
    chi = hi;
    __asm__ __volatile__("" : : "r"(chi));
    lo = (t & 0xFF) - 0x80;
    clo = lo;
    if (hi == 0) {
        if (lo < 0) {
            return (-clo) & 0xFF;
        }
        return clo & 0xFF;
    } else if (lo == 0) {
        if (hi < 0) {
            return (-chi) & 0xFF;
        }
        return chi & 0xFF;
    }
    hi = hi * hi;
    chi = lo * lo;
    return func_80047D3C(hi + chi) & 0xFF;
}
