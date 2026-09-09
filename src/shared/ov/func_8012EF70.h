/* func_8012EF70 — shared body (overlay slot 0x80128158, h_exact 59d11e9c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012EFB8(s32 a0);
void func_8012EF70(s32 a0, s32 a1) {
    s32 sp10;
    register s32 v1 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B headers1)
    func_8012EFB8(a0);
    {
        register s32 *p __asm__("$3") = &sp10;  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B headers1)
        __asm__ __volatile__(
            "mfc2 $12, $19\n"
            "nop\n"
            "sra $12, $12, 2\n"
            "sw $12, 0(%0)\n"
            : : "r"(p) : "memory", "$12");
    }
    v1 = sp10;
    *(s16 *)(a1 + 4) = v1;
}
