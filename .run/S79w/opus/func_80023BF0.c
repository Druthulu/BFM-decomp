/* func_80023BF0 (main, src/800.c, 281 ins) -- NEAR 18, length EXACT (281/281).
 * S79w opus.  Came in at 90 (the S77w draft), left at 18.  Real-TU (rtu_match,
 * src/800.c) agrees: 18 mismatched, so the residual is NOT a TU/plumbing artifact.
 *
 * ============================================================================
 * THE WHOLE RESIDUAL WAS ONE REGISTER PERMUTATION, AND IT IS NOW SOLVED.
 * ============================================================================
 * Every "scheduling" difference in the 90-draft (the hoisted `lhu c`, the third
 * `lbu` moving, the preheader constant order) was a CONSEQUENCE of a register
 * grant, never a cause: sched1 runs BEFORE local/global alloc, sched2 runs AFTER
 * with hard regs, so a value that lands in a still-busy register cannot be
 * hoisted.  (Second confirmation of cookbook §78's law.)
 *
 * THE INSTRUMENT (do this FIRST on any whole-function permutation, it is 5 min):
 *   cc1 -dg writes <input>.greg (conflict matrix + "N regs to allocate:" in
 *   global.c priority order + "Register dispositions").  Then, because the
 *   shipped tools/bin/gcc-2.7.2-psx/cc1 is i386-static WITH a symbol table,
 *   gdb gives the EXACT allocno_n_refs / allocno_live_length that drive
 *   allocno_compare -- no debug info needed, read the args off $esp:
 *     break find_reg          -> dump allocno_order[i], allocno_reg,
 *                                allocno_n_refs, allocno_live_length (Nx1 loop)
 *     break *find_free_reg    -> qty=*(int*)($esp+12) born=+24 dead=+28
 *     break *post_mark_life   -> reg=*(int*)($esp+4) birth=+16 death=+20
 *   (scripts left in .run/S79w/opus/{pri,la2}.gdb, driver probe.sh + roles.py
 *   which prints a role->register map for MY object next to the target's.)
 *   pri = floor_log2(refs)*refs/live_length*10000 (global.c:594); grants are
 *   plain ascending-regno first-fit (mips.h has no REG_ALLOC_ORDER).
 *
 * THE FOUR LEVERS THAT TOOK 90 -> 18, each byte-measured one at a time:
 *
 *  1. §194-A FENCE IN **BOTH** ARMS (90->114 on its own -- a LOCAL REGRESSION
 *     THAT IS REQUIRED).  The S77 draft fenced only the sprite arm because the
 *     poly-arm fence measured 92->116.  Measured cause: the fence stops sched1
 *     hoisting `lhu c` to the top of the block, which shortens c1's
 *     live_length 24 -> 16 and lifts its allocno priority 10000 -> 15000, i.e.
 *     from BELOW giv1 (13333) to ABOVE it.  That is the ONLY way to get the
 *     target's `c1 == arg0 == $a2` / `giv1 == $a3` / `x == $t0` triple.
 *     A lever that regresses closeness can still be the one the target needs:
 *     judge it on the ALLOCATION, not on the score.
 *  2. `code`'s FULL PREFERENCE FOR $a0 (114->99->40).  In the target $a0 holds
 *     `code`, but code's priority (2647) is nowhere near giv2's (21250):
 *     priority can NEVER win it.  The mechanism is global.c:952-953 --
 *     find_reg's pass 0 does `used |= regs_someone_prefers[allocno]`, the union
 *     of the FULL PREFERENCES of LOWER-priority conflicting allocnos.  So one
 *     preference on the low-priority `code` pushes giv2, giv1 AND x off $a0 and
 *     then code claims it.  set_preference (global.c:1535) unwraps a non-copy
 *     SET one level (`src = XEXP (src, 0)`), so `(set code (ashift tA 16))`
 *     gives code a preference for tA's hard reg.  Hence:
 *       (a) split the 0x74/0x76 base into its own variable, so code no longer
 *           HARD-conflicts with $a0/$v1 (its preference used to be pruned), and
 *       (b) write the colour word as COMPOUND accumulation
 *             code = b26 << 16;  code |= (b25<<8)|base;  code |= b24;
 *           so the first insn's temp tA is what code prefers.
 *  3. `register u32 base __asm__("$3")` -- THE PIN THAT UNBLOCKED (2) (99->40).
 *     tA is a block-LOCAL qty; local-alloc gives it $v1 by first-fit because
 *     nothing local occupies $v1 over its 2-insn range, and then code's
 *     preference for $v1 is pruned (code conflicts with $v1).  In the target
 *     $v1 holds `base` for exactly that window -- but base is a GLOBAL allocno,
 *     invisible to local-alloc, so no C spelling can make local-alloc see it.
 *     Pinning base to $3 makes it a HARD reg, which regs_live_at DOES see
 *     (local-alloc.c:1416), so tA is pushed to $a0 and code inherits $a0.
 *     Zero bytes, and it is the target's own register.
 *  4. THIRTEEN ZERO-BYTE FENCES AFTER `pkt = D_800A5E60;` (40->28).  Pure
 *     live-length arithmetic (§47 slider, scaled up).  Two priority pairs were
 *     inverted by a hair and both needed the SAME +13 insns of live range on
 *     the function-scope variables that are live at that point:
 *        tpage 12/148=811 vs 0x180010 3/40=750   -> tpage must drop below 750
 *        otab   8/215=372 vs 0x3870   3/84=357   -> otab must drop below 357
 *     +13 gives 12/161=745 and 8/228=350; +12 leaves tpage exactly TIED (750)
 *     and a tie goes to the lower allocno number, i.e. still wrong.  The fence
 *     must sit AFTER `pkt = D_800A5E60;`: before it, pkt does not get the +13
 *     and x/pkt invert.  N=4/8/10/12/13/16 measured 40/38/35/35/28/28.
 *
 *  5. TWO MORE PINS, same mechanism as (3), for two decisions that are likewise
 *     unreachable by priority (28->22->18):
 *       `register u32 m24 __asm__("$11")` = 0xFFFFFF, assigned INSIDE the loop
 *       guard.  otptr (7 refs/35) always outranks the mask (5/34) by 4000 vs
 *       2941, in both loops, and no C-reachable ref/length change can invert
 *       that (uses and hoist positions are both structural) -- so the target's
 *       `mask $t3 / otptr $t4` needs the register named.  Placement matters:
 *       at the top of the arm it costs 4 more (32); inside `if (c != 0xFFFF)`
 *       it is 22.
 *       `register u32 e1 __asm__("$4")` = 0xE1000015 in the epilogue (22->18):
 *       same class, and it also fixes the epilogue schedule, because with the
 *       constant in $a0 the &otab[idx] chain must wait for it to die.
 *
 * ============================================================================
 * WHAT IS LEFT (18), AND WHY I STOPPED
 * ============================================================================
 * EVERY remaining diff is INSTRUCTION ORDER inside two blocks; every register,
 * immediate and opcode is already the target's:
 *   * 10 diffs: the two loop preheaders emit `lui/ori $t3` (the 0xFFFFFF pin)
 *     BEFORE `sll $v0,$v0,2 / addu $t4,$v0,$s2`; the target emits it after.
 *     Root cause, measured: sched2 ties on INSN_PRIORITY (both chains are
 *     length-1) and breaks the tie by LUID, and loop.c's move_movables inserts
 *     every hoisted movable IMMEDIATELY BEFORE loop_start -- i.e. AFTER any
 *     source statement in the preheader.  A pinned constant is a source
 *     statement, so its LUID is always lower than the hoisted group's and it is
 *     always scheduled first.  The pin and the target's order are therefore
 *     MUTUALLY EXCLUSIVE from C: you can have `otptr == $t4` (pin) or the
 *     hoist order (no pin), not both.  Without the pin the same 10 instructions
 *     are in the right order with the two registers swapped (closeness 28).
 *   * 4 diffs (x2 arms is included above) / 4 diffs in the epilogue: `lui
 *     $a2,0xFF000000` is emitted before the &otab[idx] chain instead of after;
 *     same sched2 LUID tie, driven by which operand of the OT-link `|` is
 *     evaluated first.  The target's hoist order (otptr, 0xFFFFFF, 0xFF000000)
 *     says its source evaluates `otab[idx] & 0xFFFFFF` BEFORE
 *     `*(u32*)pkt & 0xFF000000`; writing it that way (z1) reorders the hoists
 *     but costs 6 elsewhere (24).
 *
 * MEASURED INERT / WORSE (do not re-run):
 *   arm-local `code` (99); `code` holding the base with compound accumulation
 *   (105/113); `cb`/`hi`/`mid` temps for the colour bytes, arm-local or not
 *   (99, identical object -- cc1 normalises them all); an explicit `ot` pointer
 *   for &otab[idx], function-scope OR arm-local OR pinned to $12 (276 @ 284
 *   ins: it becomes a 4-death global allocno and buys a 4th callee-saved reg,
 *   cookbook §78's `otp` trap in reverse); `u8 *otab` with an explicit byte
 *   offset (34); zero-byte 2/3/4-asm DECOY qtys around the b26 load, six
 *   placements (98-192: the decoy never lands in $v1 over tA's 2-insn window,
 *   because its own qty priority is <= tA's); fences inside the loop body
 *   (37/35 -- and provably useless for the otptr/mask pair: adding n to both
 *   lengths moves 14/(35+n) vs 10/(34+n) the WRONG way for all n>0);
 *   swapping either OT-link `|` operand order (38/38 from 28, 24 from 18);
 *   moving `D_800A5E60 = pkt+0x40` to the end (18, byte-identical);
 *   pinning the epilogue 0xFF000000 to $a2 (18, byte-identical);
 *   pinning the loop 0xFF000000 to $t5 (276 @ 283 ins).
 *
 * STRUCTURE (inherited from S69/S76/S77, all still byte-verified -- keep it):
 *   the dispatch is a balance_case_nodes median tree, source case order
 *   0x1850, 0x1858, 0x3870, 0x3871, 0x3872, default; 0x1850/0x1858 SHARE one
 *   body whose head is stolen into the beq delay slot (§164-36b); the emit
 *   block appears ONCE; packet fields are written PKT-RELATIVE so loop.c emits
 *   ONE combined giv; the OT link takes NO temp; `c` is declared INSIDE each
 *   arm; `tpage` is built through the `tp` temp, never in place; and an
 *   intermediate the target computes in a SCRATCH register is a NESTED
 *   EXPRESSION, not a second assignment to the same variable (S77's lever 1).
 */
#include "common.h"

extern u8 D_800AF630[];
extern u8 D_800A6610[];
extern u16 D_800B9A02;
extern u8 *D_800A5E60;

typedef struct { s16 vx, vy, vz, pad; } Vec23BF0;

#define SetRot23(m) __asm__ volatile ( \
    "lw $12, 0(%0);"  "lw $13, 4(%0);"  "ctc2 $12, $0;"  "ctc2 $13, $1;" \
    "lw $12, 8(%0);"  "lw $13, 12(%0);" "lw $14, 16(%0);" \
    "ctc2 $12, $2;"   "ctc2 $13, $3;"   "ctc2 $14, $4" \
    : : "r"(m) : "$12", "$13", "$14")
#define SetTrans23(m) __asm__ volatile ( \
    "lw $12, 20(%0);" "lw $13, 24(%0);" "ctc2 $12, $5;" \
    "lw $14, 28(%0);" "ctc2 $13, $6;"   "ctc2 $14, $7" \
    : : "r"(m) : "$12", "$13", "$14")

void func_80023BF0(s32 arg0)
{
    Vec23BF0 v;
    u32 xy;
    u32 sxy2;
    u32 mac0;
    s32 z;
    u32 flags;
    u16 *prims;
    u16 b9;
    u16 idx;
    s32 x;
    s32 y;
    u32 *otab;
    u8 *pkt;
    u32 code;
    s32 tpage;
    s32 tp;
    u8 *mat;
    register u32 m24 __asm__("$11");
    register u32 e1 __asm__("$4");
    register u32 base __asm__("$3");

    mat = D_800AF630;
    prims = *(u16 **)(arg0 + 0x20);
    b9 = D_800B9A02;
    flags = *(u32 *)(arg0 + 4);
    otab = (u32 *)(b9 * 0x4000 + D_800A6610);

    if (flags & 0x4000000) {
        u8 *m = mat + 0x18;
        SetRot23(m);
        SetTrans23(m);
        v.vx = *(u16 *)(arg0 + 8) + *(u16 *)(arg0 + 0x2E);
        v.vy = *(u16 *)(arg0 + 0xA) + *(u16 *)(arg0 + 0x30);
        v.vz = *(u16 *)(arg0 + 0xC) + *(u16 *)(arg0 + 0x32);
        __asm__ volatile("lwc2 $0, 0(%0);lwc2 $1, 4(%0)" : : "r"(&v));
        __asm__ volatile("nop;nop;rtps");
        __asm__ volatile("swc2 $14, 0(%0)" : : "r"(&xy) : "memory");
        __asm__ volatile("swc2 $8, 0(%0)" : : "r"(&sxy2) : "memory");
        __asm__ volatile("cfc2 $12, $31;nop;sw $12, 0(%0)" : : "r"(&mac0) : "$12", "memory");
        __asm__ volatile("mfc2 $12, $19;nop;sra $12, $12, 2;sw $12, 0(%0)" : : "r"(&z) : "$12", "memory");
        if (z <= 0) {
            return;
        }
        idx = z + 1;
        {
            u32 t = xy;
            x = *(u16 *)(arg0 + 0xE) + t;
            y = t >> 16;
        }
    } else {
        x = *(u16 *)(arg0 + 0xE) + (*(u16 *)(arg0 + 8) + *(u16 *)(arg0 + 0x2E));
        idx = *(u16 *)(arg0 + 0x2C);
        y = *(u16 *)(arg0 + 0xA) + *(u16 *)(arg0 + 0x30);
    }

    tp = (*(u8 *)(arg0 + 0x27) + 0x100) << 6;
    if (*(u8 *)(arg0 + 0x27) < 0xE0) {
        tpage = tp | 0x16;
    } else {
        tpage = tp | 0x10;
    }
    pkt = D_800A5E60;
        __asm__ __volatile__("");
        __asm__ __volatile__("");
        __asm__ __volatile__("");
        __asm__ __volatile__("");
        __asm__ __volatile__("");
        __asm__ __volatile__("");
        __asm__ __volatile__("");
        __asm__ __volatile__("");
        __asm__ __volatile__("");
        __asm__ __volatile__("");
        __asm__ __volatile__("");
        __asm__ __volatile__("");
        __asm__ __volatile__("");

    if (!(flags & 0x400000)) {
        u16 c;
        base = 0x74000000;
        if (flags & 0x40000000) {
            base = 0x76000000;
        }
        code = *(u8 *)(arg0 + 0x26) << 16;
        code = code | ((*(u8 *)(arg0 + 0x25) << 8) | base);
        code = code | *(u8 *)(arg0 + 0x24);
        __asm__ __volatile__("");
        c = *prims;
        if (c != 0xFFFF) {
            m24 = 0xFFFFFF;
            do {
                switch (c) {
                case 0x1850:
                case 0x1858:
                    *(u16 *)(pkt + 8) = x + 4;
                    *(u16 *)(pkt + 0xA) = y - 7;
                    break;
                case 0x3870:
                    x += 7;
                    prims++;
                    continue;
                case 0x3871:
                    x += 4;
                    prims++;
                    continue;
                case 0x3872:
                    x += 2;
                    prims++;
                    continue;
                default:
                    *(u16 *)(pkt + 8) = x;
                    x += 7;
                    *(u16 *)(pkt + 0xA) = y;
                    break;
                }
                *(u32 *)pkt = 0x3000000;
                *(u32 *)(pkt + 4) = code;
                *(u16 *)(pkt + 0xC) = *prims++;
                *(u16 *)(pkt + 0xE) = tpage;
                *(u32 *)pkt = (*(u32 *)pkt & 0xFF000000) | (otab[idx] & m24);
                otab[idx] = (otab[idx] & 0xFF000000) | ((u32)pkt & m24);
                pkt += 0x10;
            } while ((c = *prims) != 0xFFFF);
        }
    } else {
        u16 c;
        base = 0x64000000;
        if (flags & 0x40000000) {
            base = 0x66000000;
        }
        code = *(u8 *)(arg0 + 0x26) << 16;
        code = code | ((*(u8 *)(arg0 + 0x25) << 8) | base);
        code = code | *(u8 *)(arg0 + 0x24);
        __asm__ __volatile__("");
        c = *prims;
        if (c != 0xFFFF) {
            m24 = 0xFFFFFF;
            do {
                if (c == 0x3870) {
                    x += 0x10;
                    prims++;
                } else {
                    *(u16 *)(pkt + 8) = x;
                    x += 0x10;
                    *(u16 *)(pkt + 0xA) = y;
                    *(u32 *)pkt = 0x4000000;
                    *(u32 *)(pkt + 4) = code;
                    *(u16 *)(pkt + 0xC) = *prims++;
                    *(u16 *)(pkt + 0xE) = tpage;
                    *(u32 *)(pkt + 0x10) = 0x180010;
                    *(u32 *)pkt = (*(u32 *)pkt & 0xFF000000) | (otab[idx] & m24);
                    otab[idx] = (otab[idx] & 0xFF000000) | ((u32)pkt & m24);
                    pkt += 0x14;
                }
            } while ((c = *prims) != 0xFFFF);
        }
    }

    pkt[3] = 1;
    e1 = 0xE1000015;
    *(u32 *)(pkt + 4) = ((flags >> 23) & 0x60) | e1;
    *(u32 *)pkt = (*(u32 *)pkt & 0xFF000000) | (otab[idx] & 0xFFFFFF);
    D_800A5E60 = pkt + 0x40;
    otab[idx] = (otab[idx] & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
}
