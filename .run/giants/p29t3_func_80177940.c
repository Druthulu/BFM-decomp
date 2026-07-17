// @class: schedule
// @stuck: 5/101 — sched1 emits the $s1(c)/$s2(a) param copies in the wrong order (4 ins, idx 5/6/7/10: equal-priority birthing_insn_p ties broken by INSN_LUID, not steerable from source order); + idx 51 `andi $a2,$v0,0xf` where target has `addu $a2,$v0,$zero` (need a cse-opaque reg-copy that combine still folds to a bare move).

extern s32 func_80029504(void);

/* GPU packet chain: 5 x 0x14-byte SPRT_8-shaped primitives (tag len 3, code 0x74),
 * each node's tag back-links to the previous node.  1 head + a 4-iteration nibble walk. */
void func_80177940(u32 *p, u32 a_, u32 b_, u32 c_)
{
    /* $s0/$s1/$s2 hold b/c/a across the call (cookbook §17 register pins). */
    register u32 a __asm__("$18");
    register u32 b __asm__("$16");
    register u32 c __asm__("$17");
    /* $v0 pin keeps the whole `v` chain in-place on one hard reg, which makes each
     * step NON-birthing (loop.c/sched.c `birthing_insn_p`, cookbook §30) so sched1
     * leaves the chain at the top of the prologue instead of sinking it to its use. */
    register u32 v __asm__("$2");
    u32 *q;
    u32 *r;
    u32 flag;
    u32 n;
    u32 nn;
    u32 t;
    u32 cl;
    u32 cs;
    u32 col;
    s16 i;

    b = b_; c = c_; a = a_;

    /* v = ((u32)(ret - 10) < 0x4b0) ? 0xb4 : 0, written as in-place updates on one
     * variable so no step births a fresh pseudo (see the $v0 pin note above). */
    v = (u32)func_80029504();
    v = v - 10;
    v = (v < 0x4b0);
    v = -v;
    v = v & 0xb4;

    cs = c << 16;
    p[0] = ((u32)(p - 5) & 0xffffff) | 0x3000000;
    p[2] = cs | ((b + 0xf) & 0xffff);
    p[1] = 0x74808080;
    p[3] = (((v << 6) | 0x4016) << 16) | 0x3850;
    p += 5;

    q = p;
    /* Zero-code barrier: makes the loop's `v` opaque to cse2, so the hoisted clut
     * chain below is NOT merged with the prologue's identical one (the target keeps
     * both -- cse2 runs after loop.c and would otherwise fold them into one). */
    __asm__("" : "=r"(v) : "0"(v));
    /* Computed here (not in the loop) so it lands in the preheader AHEAD of the
     * flag/i inits, matching the target's RTL order. */
    cl = ((v << 6) | 0x4016) << 16;
    flag = 0x1000000;
    for (i = 0; i < 4; i++) {
        nn = (a << 16) >> 28;
        /* `& 0xf` is a no-op on a 4-bit value; it exists to keep `n` a SEPARATE
         * pseudo from `nn` (a plain `n = nn` is value-propagated by cse and the
         * copy disappears; the target keeps `addu $a2,$v0,$zero`). */
        n = nn & 0xf;
        if (nn != 0 || i == 3 || i == 1) {
            flag = 0;
        }
        q[0] = ((u32)(q - 5) & 0xffffff) | 0x3000000;
        q[2] = cs | (b & 0xffff) | flag;
        /* `col` is set twice in the loop (the second is dead) so n_times_set != 1 and
         * loop.c will not treat 0x74808080 as a movable -- the target materialises it
         * INSIDE the loop (lui duplicated into the bne delay slot). */
        col = 0x74808080;
        q[1] = col;
        t = (n * 8 + 8) | 0x4000;
        q[3] = cl | t;
        q += 5;
        b += 8;
        a <<= 4;
        col = 0;
    }
    p = q;
    r = p;
    /* Barrier forces the `addu $v0,$s3,$zero` copy the target has (r would otherwise
     * be value-propagated onto p and share $s3). */
    __asm__("" : "=r"(r) : "0"(r));
    *(u16 *)(r - 8) += 6;
    *(u16 *)(r - 3) += 6;
}
