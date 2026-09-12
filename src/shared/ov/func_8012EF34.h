/* func_8012EF34 — shared body (overlay slot 0x80128158, h_exact 6fa7918e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012EFB8();  // K&R: 1 of 2 args (P37 unalias t4_ua1)
void func_8012EF34(s32 a0, s32 a1) {
    s32 sp10;
    register s32 v1 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B headers1)
    func_8012EFB8(a0);
    {
        register s32 *p __asm__("$3") = &sp10;  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B headers1)
        __asm__ __volatile__("swc2 $19, 0(%0)" : : "r"(p) : "memory");
    }
    v1 = sp10;
    *(s16 *)(a1 + 4) = v1;
}
