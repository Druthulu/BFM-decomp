void func_8017F024(s32 a0) {
    s32 *p;

    /* The table's handlers take the actor (func_8017EE3C(s32 a0) is entry 1): passing it keeps a second set of $a0
     * in the RTL (cse deletes the copy — $a0 still holds the parameter), so the later argument copy is not a
     * "birthing" insn for sched1 (sched.c:2469-2545) and stays at the top of the block, where it keeps the mask
     * constant out of $a0 (P36 S104 e26). */
    ((void (*)(s32))D_8018AFBC[*(u16 *)(a0 + 2)])(a0);
    if (*(u16 *)a0 != 0) {
        p = *(s32 **)(a0 + 0x20);
        p[1] |= 0x80000000;
        func_8012B2CC(a0);
    }
}
