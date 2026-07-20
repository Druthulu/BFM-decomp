/* func_80179B74 @ 0x80179b74 (ov_SC01_077, jr_80178D40 block) — 111 ins.
 * Ring-buffer command writer: pushes the command word *param_1 (+ 0..4 operand
 * halfwords, selected by a jtbl_801D8F9C switch) into the u16 ring D_801DA310[512]
 * at write index D_801DA714 (masked & 0x1ff), write-through after every store.
 *
 * STATUS: NEAR (best draft = 110/111 ins, 82 masked-mismatch via match_one.py).
 *   The initial block is byte-exact EXCEPT the pointer register, and the whole
 *   control flow / switch layout (jtbl range [0,0x22], shared tails .L80179CE4 /
 *   .L80179D08, case-0x13 goto) matches. Frame is exact (0x80 dead-reservation via
 *   `s32 pad[30]` + address-take — the §6 "reserved local sets frame size" idiom;
 *   the target has ZERO stack usage yet a 0x80 frame).
 *
 * TWO un-steerable gcc-2.7.2 residuals (resisted 20 C-lever + register-pin variants,
 * match_one.py only — permuter out of task scope):
 *   R1  param-copy register: target does `addu $a1,$a0,$zero` (ptr->a1, value reuses
 *       freed a0); gcc puts our ptr in a2 (it moves param_1 out of a0 to free a0 for
 *       the $4-pinned value, and picks a2 not a1). Pinning p->$5 breaks the prologue
 *       (maspsx emits p+2 before the frame). This cascades through every ptr use.
 *   R2  shared-tail SOFTWARE-PIPELINING: target threads the ring index through v0
 *       (current) / v1 (next, precomputed) rotating across the .L80179CE4/.L80179D08
 *       merge — gcc modulo-schedules the naive `store[i]; i=(i+1)&0x1ff; writeback`.
 *       naive-C (index in memory) RELOADS D_801DA714 at the merge; a threaded local
 *       `int i` pins to ONE reg (no rotation) and inflates the ptr allocation.
 *       Neither reproduces the v0/v1 rotation. This is the last ~3-instruction gap.
 *
 * Register pins ($4=value a0, $2=index v0) are steering aids (got 99->82 mismatch),
 * NOT semantics: the true source is the plain naive write-through below (see the
 * `.run/drafts_wave3/scratch/v20.c` variant, which gets the ptr register RIGHT but
 * reloads the tail => 92 ins). A permuter run on THIS 110-ins base (regalloc+schedule
 * only) is the recommended finish path.
 */
extern u16 D_801DA310[0x200];
extern s16 D_801DA714;

void func_80179B74(s16 *param_1) {
    s32 pad[30];
    register u16 cmd asm("$4");
    s16 *p;
    register int i asm("$2");
    (void)&pad;

    p = param_1;
    cmd = *p;
    i = D_801DA714;
    D_801DA310[i] = cmd;
    D_801DA714 = (i + 1) & 0x1ff;
    p = p + 1;
    switch ((short)cmd) {
    case 1: case 5:
        i = D_801DA714; cmd = *p; D_801DA310[i] = cmd; D_801DA714 = (i = (i + 1) & 0x1ff); p = p + 1;
        break;
    case 0x13:
        i = D_801DA714; cmd = *p; D_801DA310[i] = cmd; D_801DA714 = (i = (i + 1) & 0x1ff);
        goto LAB_D08;
    case 2: case 3: case 4: case 6: case 0x12: case 0x14: case 0x1f:
        i = D_801DA714; cmd = *p; D_801DA310[i] = cmd; D_801DA714 = (i + 1) & 0x1ff;
        return;
    case 0: case 0x22: default:
        return;
    case 0x17: case 0x1c: case 0x1d: case 0x20:
        i = D_801DA714; cmd = *p; D_801DA310[i] = cmd; D_801DA714 = (i = (i + 1) & 0x1ff); p = p + 1;
        cmd = *p; D_801DA310[i] = cmd; D_801DA714 = (i = (i + 1) & 0x1ff); p = p + 1;
        break;
    }
    cmd = *p; D_801DA310[i] = cmd; D_801DA714 = (i = (i + 1) & 0x1ff);
LAB_D08:
    cmd = p[1]; D_801DA310[i] = cmd; D_801DA714 = (i + 1) & 0x1ff;
    return;
}
