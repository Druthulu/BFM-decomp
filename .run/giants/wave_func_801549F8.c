/* func_801549F8 @ 0x801549F8 (ov_SC01_077) — -O2 h_seq family exemplar.
 *
 * Counts how many entries in cmds[] fall into the switch "default" class,
 * iterating `count` (0xBC) entries where each entry's category (jump table of
 * 27 cases, jtbl_801D89A4) advances the index by 1 or 2.
 *
 * MATCHING NOTE (gcc-2.7.2 -O2, loop.c strength-reduction):
 *   A plain `switch (arr[i])` in a recognized do-while has arr invariant and i
 *   a biv, so gcc forms a DEST_ADDR giv (benefit 5) for `arr + i*4` that combines
 *   with the DEST_REG address giv (benefit 4) -> combined 9; 62*(9-2*biv_count[3])
 *   = 62*3 >= insn_count -> the access is strength-reduced to a WALKING POINTER
 *   (+addiu p,4/8), a 2-IV loop that never matches the target's single-index
 *   recompute (`sll v1,2; addu v0,v0,a0; lw`).  The zero-byte asm barrier below
 *   ties i (in==out, emits nothing) so i stays materialized across the back-edge:
 *   biv i is no longer eliminable and the address giv is no longer replaceable,
 *   so combine_givs leaves the DEST_ADDR anchor at benefit 5 (-> 5-6 = -1, "not
 *   worth while") and gcc RECOMPUTES the address each iteration = the target.
 *   (The do-while stays a recognized loop, so jtbl_801D89A4's base still hoists
 *   to $t0 and the -O2 register allocation matches — a `goto` loop would defeat
 *   SR too but also lose the hoist and shift every register.)  §34 zero-byte-asm.
 */
unsigned char func_801549F8(int param_1) {
    int c = 0;
    unsigned int i = 0;
    unsigned char n = *(unsigned char *)(param_1 + 0xbc);
    int *arr;

    if (n) {
        arr = *(int **)(param_1 + 0xb4);
        do {
            switch (arr[i]) {
            case 0: case 2: case 7: case 8: case 9: case 10:
            case 0xd: case 0x10: case 0x11: case 0x12: case 0x13:
            case 0x14: case 0x19: case 0x1a:
                i += 1;
                break;
            case 3: case 4: case 5: case 6: case 0xb: case 0xc:
            case 0xe: case 0xf: case 0x15: case 0x16:
                i += 2;
                break;
            default:
                i += 1;
                c += 1;
                break;
            }
            __asm__ __volatile__("" : "=r"(i) : "0"(i));
        } while (i != n);
    }
    return c;
}
