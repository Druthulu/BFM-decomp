/* func_8017D8AC -- ov_SC06_015 (family of 5: also func_8017ED54/ov_SC06_014,
 * func_8017D9F0/ov_SC06_013, func_801830B4/ov_SC06_016, func_80181164/ov_SC06_030 -- all
 * byte-identical modulo per-overlay local static data addresses).
 *
 * Builds a 5-pointed symmetric star/cross set of screen coordinates around the projected
 * position of the object, then emits 4 Gouraud-shaded quads (POLY_G4, len=8, code=0x3A) whose
 * per-vertex colour/x/y are selected from that coordinate set via small per-overlay index
 * tables, and finally adds the sprite-header primitive itself to the OT.
 */

extern s32 D_80126950;
extern s16 D_800B9A02;
extern s32 D_800A651C;

extern void RotTransSV(void *a0, void *a1, void *a2);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

extern void *func_80010A08(s32 a0);
extern s32 GetTPage(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8005A600(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern s32 AddPrim(s32 a0, void *a1);

extern u8 D_800AF648;

extern s32 D_8018F81C;
extern s32 D_8018F824[];

extern u8 D_8018F830[];
extern u8 D_8018F831[];
extern u8 D_8018F832[];
extern u8 D_8018F833[];
extern u8 D_8018F840[];
extern u8 D_8018F841[];
extern u8 D_8018F842[];
extern u8 D_8018F843[];
extern u8 D_8018F850[];
extern u8 D_8018F851[];
extern u8 D_8018F852[];
extern u8 D_8018F853[];

/* §37/§124 SELF-axis: the TU declares `extern void func_8017D8AC(void);` (called with zero
   args at func_8017E51C) while the byte-true definition takes an s32. Define under a private
   C name bound to the real symbol. */
extern void aF8017D8AC(s32 param_1) __asm__("func_8017D8AC");
void aF8017D8AC(s32 param_1) {
    /* single raw local block; sp+0x18 .. sp+0x5B (verified via the outgoing-arg-area rounded
     * to 8 for func_8005A600's 5th argument, matching the sibling family's identical frame). */
    u8 buf[0x44];

    /* Loop-carried locals pinned to the exact callee-saved registers the target uses --
     * each is reused for TWO logical roles (early-phase / loop-phase), matching the target's
     * own register reuse across the two roles (§ "don't conclude unsteerable, try register
     * pins" -- these are loop/local values, never the incoming parameter, so S3 is respected). */
    register s32 vVec  __asm__("$17"); /* s1: RotTransSV/Pers vector ptr, then loop counter i */
    register s32 vFlag __asm__("$18"); /* s2: RotTransSV/Pers flag ptr,  then grid anchor     */
    register u8 *p0     __asm__("$16"); /* s0: D_800AF648 ptr, then prim-write pointer         */
    register u8 *cur    __asm__("$19"); /* s3: walking AddPrim arg (s4object+0xC, +=0x24)      */
    register void *s4o  __asm__("$20"); /* s4: func_80010A08(0x9C) result                       */
    register s32 *ctab  __asm__("$21"); /* s5: &D_8018F824 colour table                          */
    register s32 s6     __asm__("$22"); /* s6: OT-base + zcount, the AddPrim OT arg              */

    s32 zcount;
    s32 radius, inner;
    u16 cx, cy;
    s32 tpage;

    {
        register s32 *p __asm__("$2") =
            (s32 *)(*(s32 *)(param_1 + 0x20) + 0x34);
        __asm__ __volatile__(
            "lw $12, 0(%0)\n"
            "lw $13, 4(%0)\n"
            "ctc2 $12, $0\n"
            "ctc2 $13, $1\n"
            "lw $12, 8(%0)\n"
            "lw $13, 12(%0)\n"
            "lw $14, 16(%0)\n"
            "ctc2 $12, $2\n"
            "ctc2 $13, $3\n"
            "ctc2 $14, $4\n"
            "lw $12, 20(%0)\n"
            "lw $13, 24(%0)\n"
            "ctc2 $12, $5\n"
            "lw $14, 28(%0)\n"
            "ctc2 $13, $6\n"
            "ctc2 $14, $7\n"
            : : "r"(p) : "$12", "$13", "$14", "memory");
    }

    {
        /* §gcc-2.7.2-map/sched.md rule 7: a single-SET pseudo gets a "birthing boost" that
         * sinks it to just before its first consumer, regardless of source order. A 2nd SET
         * that survives CSE (a zero-byte re-tie) disables the boost so it schedules at its
         * natural (early) priority instead. */
        void *vecAddr = &D_8018F81C;
        void *arg1;
        __asm__ __volatile__("" : "=r"(vecAddr) : "0"(vecAddr));
        vVec = (s32)(buf + 0x10);
        arg1 = (void *)vVec;
        __asm__ __volatile__("" : "=r"(arg1) : "0"(arg1));
        vFlag = (s32)(buf + 0x38);
        RotTransSV(vecAddr, arg1, (void *)vFlag);
    }

    p0 = &D_800AF648;
    func_8004914C(p0);
    func_800491AC(p0);

    zcount = RotTransPers(vVec, (s32)(buf + 0x3C), (s32 *)(buf + 0x40), (s32 *)vFlag);
    if (zcount <= 0) {
        return;
    }
    if (*(s32 *)vFlag < 0) {
        return;
    }
    zcount = zcount << 2;

    radius = ((D_80126950 + 0x1F4) * 48) / zcount;

    cx = *(u16 *)(buf + 0x3C);
    cy = *(u16 *)(buf + 0x3E);

    {
        register s32 t1 __asm__("$9") =
            *(s32 *)((s8 *)&D_800A651C + (u16)D_800B9A02 * 0x14);
        s6 = t1 + zcount;
    }

    *(u16 *)(buf + 0x1C) = cx;
    *(u16 *)(buf + 0x2C) = cy;

    *(u16 *)(buf + 0x18) = cx - radius;

    inner = (radius * 179) >> 8;

    *(u16 *)(buf + 0x1A) = cx - inner;
    *(u16 *)(buf + 0x1E) = cx + inner;
    *(u16 *)(buf + 0x20) = cx + radius;
    *(u16 *)(buf + 0x28) = cy - radius;
    *(u16 *)(buf + 0x2A) = cy - inner;
    *(u16 *)(buf + 0x2E) = cy + inner;
    *(u16 *)(buf + 0x30) = cy + radius;

    s4o = func_80010A08(0x9C);
    if (s4o == 0) {
        return;
    }

    tpage = GetTPage(0, 1, 0, 0);
    func_8005A600((s32)s4o, 0, 0, (u16)tpage, 0);

    {
        register s32 t __asm__("$2") = (s32)((u8 *)s4o + 0xC);
        cur = (u8 *)t;
        ctab = D_8018F824;
        vFlag = (s32)buf;
        p0 = (u8 *)s4o + 0x2E;
        vVec = 0;

        *(s32 *)(buf + 0x04) = (s32)((u8 *)s4o + 0x30);
        *(s32 *)(buf + 0x08) = (s32)((u8 *)s4o + 0x54);
        *(s32 *)(buf + 0x00) = t;
        *(s32 *)(buf + 0x0C) = (s32)((u8 *)s4o + 0x78);
    }

    for (; vVec < 0x10;) {
        s32 color0, color1, color2, color3;
        u16 x0, x1, x2, x3;
        u16 y0, y1, y2, y3;

        color0 = ctab[D_8018F850[vVec]];
        *(s32 *)(p0 - 0x1E) = color0;
        color1 = ctab[D_8018F851[vVec]];
        *(s32 *)(p0 - 0x16) = color1;
        color2 = ctab[D_8018F852[vVec]];
        *(s32 *)(p0 - 0xE) = color2;
        color3 = ctab[D_8018F853[vVec]];
        *(u8 *)(p0 - 0x1F) = 8;
        *(u8 *)(p0 - 0x1B) = 0x3A;
        *(s32 *)(p0 - 0x6) = color3;

        x0 = *(u16 *)(vFlag + D_8018F830[vVec] * 2 + 0x18);
        *(u16 *)(p0 - 0x1A) = x0;
        x1 = *(u16 *)(vFlag + D_8018F831[vVec] * 2 + 0x18);
        *(u16 *)(p0 - 0x12) = x1;
        x2 = *(u16 *)(vFlag + D_8018F832[vVec] * 2 + 0x18);
        *(u16 *)(p0 - 0xA) = x2;
        x3 = *(u16 *)(vFlag + D_8018F833[vVec] * 2 + 0x18);
        *(u16 *)(p0 - 0x2) = x3;

        y0 = *(u16 *)(vFlag + D_8018F840[vVec] * 2 + 0x28);
        *(u16 *)(p0 - 0x18) = y0;
        y1 = *(u16 *)(vFlag + D_8018F841[vVec] * 2 + 0x28);
        *(u16 *)(p0 - 0x10) = y1;
        {
            s32 argA0;
            u8 *argA1;

            y2 = *(u16 *)(vFlag + D_8018F842[vVec] * 2 + 0x28);
            argA0 = s6;
            __asm__ __volatile__("" : "=r"(argA0) : "0"(argA0));
            *(u16 *)(p0 - 0x8) = y2;
            argA1 = cur;
            __asm__ __volatile__("" : "=r"(argA1) : "0"(argA1));
            {
                u8 idx3 = D_8018F843[vVec];
                cur += 0x24;
                y3 = *(u16 *)(vFlag + idx3 * 2 + 0x28);
                vVec += 4;
            }

            *(u16 *)(p0) = y3;

            AddPrim(argA0, argA1);
        }
        p0 += 0x24;
    }

    AddPrim(s6, s4o);
}
