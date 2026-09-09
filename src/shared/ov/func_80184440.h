/* func_80184440 — shared body (overlay slot 0x80128158, h_exact 2c4a16e5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_801EAC64;
extern s32 D_801EAC68;
void func_80184440(void) {
    __asm__ __volatile__(  // !FAKE: asm-body .set — DEFERRED T7 (P36 rung A headers2)
        ".set noreorder\n"
        "addiu $sp, $sp, -8\n"
        "sw $fp, 0($sp)\n"
        "addu $fp, $sp, $zero\n"
        "li $v0, 1\n"
        "lui $at, %%hi(D_801EAC64)\n"
        "sw $v0, %%lo(D_801EAC64)($at)\n"
        "lui $at, %%hi(D_801EAC68)\n"
        "sw $zero, %%lo(D_801EAC68)($at)\n"
        "addu $sp, $fp, $zero\n"
        "lw $fp, 0($sp)\n"
        "addiu $sp, $sp, 8\n"
        : : : "memory");
}
