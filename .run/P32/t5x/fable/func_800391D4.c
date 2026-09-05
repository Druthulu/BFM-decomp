/* func_800391D4 (main / src/800_c.c, 75 ins) -- MATCH in match_one AND rtu_match (real TU), Fable T5x 2026-09-05.
 * Levers, all measured (see .run/P32/t5x/reports/func_800391D4.md):
 *  - `register s32 i __asm__("$7")`: a hard reg is not a biv (loop.c:3572), so D_80073140[i] is never a giv ->
 *    the target's per-iteration sll/lui/addu/lw stays (S79).
 *  - `extern s32 D_80073140[][1]` + `[i][0]`: load-bearing spelling of the table access (S79; the TU now carries it).
 *  - `a1v = arg1;` BEFORE `off = 0;`: the s16 parameter's sign-extend becomes preheader SOURCE code emitted before
 *    off's init. Left implicit, the extend is an in-loop invariant that move_movables splices in front of
 *    NOTE_INSN_LOOP_BEG, i.e. AFTER `off = 0` (loop.c:1652/1708) -- the S79 closeness-3 residual.
 *  - NINE `__asm__("")` pads: insn_count knife-edge. move_movables hoists the D_800C6DD0 address iff
 *    threshold(58) * savings(1) * lifetime(1) >= insn_count (loop.c:1631). The target does NOT hoist it, so the
 *    loop must count >= 59 real insns; moving the extend out of the body cost 2, so 7 pads -> 9.
 */
void func_800391D4(s32 arg0, s16 arg1, s16 arg2) {
    extern u8 D_800C6DD0[];
    extern u8 D_800C6DD4[];
    extern s32 D_80073140[][1];
    extern s32 D_800C7D20;
    extern s32 D_800A2B98;
    extern u8 *D_800762B0;
    extern u8 D_800762B4[];

    u8 *base;
    u8 *entry;
    register s32 i __asm__("$7");
    s32 off;
    s32 mask;
    s32 a1v;

    i = 0;
    base = arg0 + arg2 * 0x1A;
    a1v = arg1;
    off = 0;
    do {
        __asm__("");
        __asm__("");
        __asm__("");
        __asm__("");
        __asm__("");
        __asm__("");
        __asm__("");
        __asm__("");
        __asm__("");
        if (*(base + i + 0x23) != 0 && *(s16 *)&D_800C6DD4[off] == a1v) {
            entry = &D_800C6DD0[(s16)i * 0x60];
            if (entry[0x5A] != 0) {
                s32 off2;
                u8 *base2;
                off2 = *(s16 *)(entry + 6) * 0x1A;
                base2 = *(s32 *)(entry + 0x50);
                *(base2 + off2 + (s16)i + 0x23) = 0;
                entry[0x5A] = 0;
            }
            mask = D_80073140[i][0];
            D_800C7D20 &= ~mask;
            D_800A2B98 |= mask;
            D_800762B0[i] = 2;
            D_800762B4[i] = 0;
        }
        i++;
        off += 0x60;
    } while (i < 0x10);
}
