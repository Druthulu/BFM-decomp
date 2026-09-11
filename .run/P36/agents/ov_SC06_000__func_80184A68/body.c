void func_80184A68(void) {
    u8 *p;
    u8 *q;
    u8 *r;

    p = &D_801AECC5;
    do { q = p - 1; r = p + 1; } while (0);  // !FAKE: do-while — its NOTE_INSN_LOOP_END ends cse1's block before the uses (cse.c:8054-8056, ignored after_loop), so cse2 not cse1 rewrites *q/*r to p-relative (find_best_addr cse.c:2711-2721) (P36 S104 e12 minimum-lever)
    if (*p < 0xF8U) {
        *p += 4;
        *q += 6;
        *r += 4;
    }
}
