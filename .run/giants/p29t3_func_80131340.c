// @class: plumbing
// @stuck: none — MATCH (424/424). Verified TWICE: match_one 424/424 standalone AND 424/424
//   relocation-masked through the REAL src/ov_SC01_077/ov_SC01_077_jr_8012ACE0.c at the
//   func_80131340 slot (L1635) with every DEFINE_ macro expanded (cpp -> cc1 -> maspsx
//   --expand-div -> as, exit 0, zero `conflicting types`).
//
// ---------------------------------------------------------------------------------------
// THE TWO LEVERS THAT CRACKED IT (both byte-proven; do not "clean up"):
//
// (1) `case 0: case 1:` SHARE one block. jtbl_801D8144 (read from the sibling overlay data,
//     asm/ov_SC03_099/data/tail2.data.s @801BCE68) is
//       [0]=0x80131440 [1]=0x80131440 [2]=0x80131634 [3]=0x8013174C [4]=0x801318F4
//     — two entries point at the SAME block. That is the ONLY reason the shared block
//     re-tests `*(u8*)(a0+0xC2) == 0` to gate its vector-init half (gcc-2.7.2 has no VRP,
//     so the switch value is not propagated into the case body).
//
// (2) CROSS-JUMP POLARITY (§5a, the 4-instruction shortfall). The `lh 0x76` / E00-vs-C78
//     if-else appears TWICE (case 3's tail @801318DC and case 4 @80131944). Both arms must
//     be written `if (x <= 0) E00(a0,6); else C78(a0);` — the SAME polarity in BOTH sites.
//     Writing case 3 as the "natural" `if (x > 0) C78 else E00` compiles 4 ins SHORT: gcc
//     merges case 3's ENTIRE tail into case 4's (`j` straight to the shared `lh`).
//     Why (ground-truthed against tools/reference/gcc-2.7.2/jump.c):
//       - jump.c:1969 `find_cross_jump(insn, target, 2, ...)` pairs each `j Lend` with every
//         OTHER jump to Lend (the jump_chain) and merges BACKWARD while
//         `rtx_renumbered_equal_p` holds. The forward walk hits the LOWER address first, so
//         case 3 is always e1 (deleted/redirected) and case 4 is e2 (kept) — hence the
//         surviving .L80131954/.L80131964 bodies physically live in case 4.
//       - With the matching polarity, case 3's FIRST `j` is the E00 body -> it merges into
//         .L80131954, leaving `bgtz -> Lelse; j .L80131954; Lelse:`. Lelse now sits directly
//         after the `j`, so jump.c's conditional-jump-around-an-unconditional-jump transform
//         fires and INVERTS it to `blez -> .L80131954`; the C78 body then merges into
//         .L80131964, giving exactly `blez .L80131954 / j .L80131964`. The two sites are now
//         textually different (blez+j vs bgtz+fallthru), so find_cross_jump stops at the
//         branch and both `lh` blocks survive. That asymmetric-looking output is EMITTED BY
//         symmetric source — the inversion is what creates the asymmetry.
//       - With the opposite polarity in case 3, the C78 body merges FIRST, the inversion
//         fires the other way, and case 3 becomes byte-identical to case 4 -> fully merged.
//     NOTE: the §5a volatile-asm barrier is the WRONG tool here — it would also un-merge the
//     .L80131954/.L80131964 call bodies (+8 ins). The fix is polarity, not a barrier.
//
// OTHER BYTE-PROVEN KEYS:
//   - Two SEPARATE locals for the two func_80131CF4 results. Reusing one `temp` lets gcc
//     coalesce it into $a1 for the second call and emits an extra `move a1,v0` up at the
//     FIRST call site (+1 ins, whole-function cascade).
//   - The /3 store block: `*(s32*)(a0+0x14) = (-D_801D94AC)/3;` must come FIRST (before the
//     0x1C/0xC2 stores). Written after them, gcc will not hoist the D_801D94AC load above
//     `sw zero,0x1C($s0)` and the mult-latency slots fill differently (9 ins reordered).
//   - sp10/18/20/28 are four 8-byte, 2-byte-aligned vectors. `sp28 = sp20` is a DEAD
//     aggregate copy that gcc-2.7.2 KEEPS (no aggregate DSE) — it is load-bearing, not dead
//     code. align(2) < 4 is what makes the copies lwl/lwr + swl/swr (cf. the TU's own `M8`
//     align-1 idiom at L1614, used by func_801312D0 directly above this slot).
//   - Every vector field read is `lhu` -> the fields are u16. Contrast `lh 0xA($s0)`,
//     `lh 0x76($s0)`, `lh 0x12($v0)`, which are genuinely signed (s16 casts).
//   - `func_801319E0(a0)` gets a NOP delay slot, not `addu $a0,$s0,$zero`: cse-2.7.2 deletes
//     the redundant arg copy because $a0 still holds the param at the first call. Declaring
//     it 0-arg to "explain" the nop would be wrong (canonical is 1-arg) — just call it.
//   - `*(s32*)(a0+0x10) = *(s32*)(a0+0x10) * 15 / 16;` -> (x<<4)-x then the bgez/+0xF/sra-4
//     signed-div-by-16 fixup. `>>4` would drop the fixup.
//   - func_80131D68 is 2-arg here — (a0, D_801D94A8); a1 is reloaded from the global before
//     all 5 of its call sites (the value is NOT cached in a callee reg: gcc-2.7.2's cse is
//     extended-basic-block-local, so each join point reloads).
//
// DECL RECONCILE (§17a-1) — the TU declares these at FILE scope BEFORE this slot (L1635),
// so they are HARD `conflicting types` if redeclared differently. Sigs below are byte-copies
// of the canonical set; where the canonical return is `void` but the asm USES $v0, the read
// is done with a call-site cast (the codebase's own idiom, engine_core.h L17026) — which is
// codegen-neutral:
//   - func_8012CBF4 / func_8012CBA4 / func_8012CC64: canonical `void`, $v0 used -> cast.
//   - func_80131E00: canonical takes `struct S80131E00 *` -> declared K&R no-proto here
//     (compatible with the prototyped decl at L1250; params are promotion-safe: ptr + s32),
//     matching the TU's own precedent `extern void func_80131CA8();` at L1189.
//   - func_8012B23C / func_8012CC64 / func_8012CEB0 / func_8012DBD0 / func_8012CBF4 are
//     DEFINE_-instantiated ABOVE this slot — the decls here are exact-identical
//     redeclarations (legal C), not new sigs.
//   - func_80131CF4 is declared 2-arg `(int,int)`, mirroring func_801312D0's already-matched
//     block-scope decl at L1619 (the engine_core canonical 1-arg form is the stale one).

extern void func_801319E0(s32 a0);
extern s32 func_8012DBD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8012CC64(s32 a0, s32 a1);
extern int func_80131D68(int, int);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8012CBA4(s32 a0);
extern void func_8012CBF4(s32 a0);
extern void func_80131E00();
extern void func_80131C78(s32 a0);
extern void func_80131CA8(int a0, int a1);

extern s32 D_801D94A8;
extern s32 D_801D94AC;

void func_80131340(s32 a0)
{
    /* 8-byte, align-2 vector: align < 4 is what makes the assignments unaligned
     * (lwl/lwr + swl/swr) block moves. Block-scope so the body stays self-contained
     * for the dedup_propagate lift (§28-#1) and cannot collide with the TU's `M8`. */
    struct V8 {
        u16 vx, vy, vz, pad;
    };
    extern struct V8 D_80186FD4;
    /* BLOCK-scope, mirroring the already-matched func_801312D0's decl at TU L1619: the
     * later DEFINE_func_80131AC8() (TU L1964, AFTER this slot) redeclares func_80131CF4
     * with the stale 1-arg engine_core canonical. A file-scope `extern int
     * func_80131CF4(int,int);` here is a HARD `conflicting types` against it (cc1 rc=33,
     * measured); block-scope goes out of scope before that macro and compiles clean. */
    extern int func_80131CF4(int, int);

    struct V8 sp10;
    struct V8 sp18;
    struct V8 sp20;
    struct V8 sp28;
    s32 temp;
    s32 var_a1;

    if (*(s16 *)(a0 + 0xA) >= 0x10) {
        func_801319E0(a0);
        return;
    }

    temp = func_80131CF4(*(s32 *)(a0 + 0xBC), 0x2E);
    if (temp != 0) {
        sp10.vz = 0;
        sp10.vx = 0;
        sp10.vy = temp;
    } else {
        sp10 = D_80186FD4;
    }

    if (*(s32 *)(a0 + 0x10) != 0 || *(s32 *)(a0 + 0x18) != 0) {
        var_a1 = func_80131CF4(*(s32 *)(a0 + 0xBC), 0x19);
        if (var_a1 == 0) {
            var_a1 = 0x50;
        }
        func_8012DBD0(a0, var_a1,
                      *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800, 0x1D);
    }

    switch (*(u8 *)(a0 + 0xC2)) {
    case 0:
    case 1:
        if (*(s32 *)(a0 + 0xC4) & 4) {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0x100;
        }
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x3D) {
            func_80131E00(a0, 0xD);
            return;
        }
        if (*(u8 *)(a0 + 0xC2) == 0) {
            *(u8 *)(a0 + 0xC2) = 1;
            sp18.vx = *(u16 *)(a0 + 0x3A);
            sp18.vy = *(u16 *)(a0 + 0x3E);
            sp18.vz = *(u16 *)(a0 + 0x42);
            sp20 = sp18;
            sp20.vx += sp10.vx;
            sp20.vy += sp10.vy;
            sp20.vz += sp10.vz;
            sp28 = sp20; /* load-bearing dead aggregate copy — gcc-2.7.2 has no aggregate DSE */
            func_8012CEB0((s32)&sp18, (s32)&sp20, 1);
            sp20.vx -= sp10.vx;
            sp20.vy -= sp10.vy;
            sp20.vz -= sp10.vz;
            *(u16 *)(a0 + 0x3A) = sp20.vx;
            *(u16 *)(a0 + 0x3E) = sp20.vy;
            *(u16 *)(a0 + 0x42) = sp20.vz;
            *(u16 *)(a0 + 0x6) = sp20.vx;
            *(u16 *)(a0 + 0xA) = sp20.vy;
            *(u16 *)(a0 + 0xE) = sp20.vz;
        }
        D_801D94A8 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&sp10);
        if (D_801D94A8 & 0x8000) {
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        if (D_801D94A8 & 0x4000) {
            func_8012B23C(a0);
            *(u8 *)(a0 + 0xC2) = 4;
        } else if (D_801D94A8 & 0x2000) {
            if (func_80131D68(a0, D_801D94A8) == 1) {
                return;
            }
            *(u8 *)(a0 + 0xC2) = 2;
            func_80143B6C(a0, 1);
            *(s32 *)(a0 + 0x14) = 0xFFF30000;
            *(s32 *)(a0 + 0x1C) = 0;
        } else if (D_801D94A8 & 0x8000) {
            *(u8 *)(a0 + 0xC2) = 2;
            *(s32 *)(a0 + 0x1C) = 0;
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        break;

    case 2:
        if (*(s32 *)(a0 + 0xC4) & 4) {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0x100;
        }
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x3D) {
            func_80131E00(a0, 0xD);
            return;
        }
        D_801D94AC = *(s32 *)(a0 + 0x14);
        D_801D94A8 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&sp10);
        if (D_801D94A8 & 0x8000) {
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        if (D_801D94A8 & 0x4000) {
            func_8012B23C(a0);
            *(u8 *)(a0 + 0xC2) = 4;
        } else if (D_801D94A8 & 0x2000) {
            if (func_80131D68(a0, D_801D94A8) == 1) {
                return;
            }
            func_80143B6C(a0, 1);
            /* MUST precede the 0x1C/0xC2 stores — see the header note on the /3 block. */
            *(s32 *)(a0 + 0x14) = (-D_801D94AC) / 3;
            *(s32 *)(a0 + 0x1C) = 0;
            *(u8 *)(a0 + 0xC2) = 3;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
        } else if (D_801D94A8 & 0x8000) {
            *(u8 *)(a0 + 0xC2) = 3;
            *(s32 *)(a0 + 0x1C) = 0;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        break;

    case 3:
        *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x10) * 15 / 16;
        *(s32 *)(a0 + 0x18) = *(s32 *)(a0 + 0x18) * 15 / 16;
        if (*(u8 *)(a0 + 0xC3) & 1) {
            D_801D94A8 = ((s32 (*)(s32))func_8012CBA4)(a0);
            if (D_801D94A8 & 0x8000) {
                *(s32 *)(a0 + 0x18) = 0;
                *(s32 *)(a0 + 0x10) = 0;
            }
            if (func_80131D68(a0, D_801D94A8) == 1) {
                return;
            }
            if (!(D_801D94A8 & 0x6000)) {
                func_80131E00(a0, 0xD);
                return;
            }
        } else {
            D_801D94A8 = ((s32 (*)(s32))func_8012CBF4)(a0);
            if (D_801D94A8 & 0x8000) {
                *(s32 *)(a0 + 0x18) = 0;
                *(s32 *)(a0 + 0x10) = 0;
            }
            if (D_801D94A8 & 0x4000) {
                func_8012B23C(a0);
                *(u8 *)(a0 + 0xC2) = 4;
                break;
            } else if (D_801D94A8 & 0x2000) {
                if (func_80131D68(a0, D_801D94A8) == 1) {
                    return;
                }
                *(u8 *)(a0 + 0xC3) |= 1;
            } else if (D_801D94A8 & 0x8000) {
                *(s32 *)(a0 + 0x18) = 0;
                *(s32 *)(a0 + 0x10) = 0;
            }
        }
        if ((*(s32 *)(a0 + 0x1C) & 3) == 3) {
            func_80143B6C(a0, 1);
        }
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) < 0x11) {
            break;
        }
        if (!(D_801D94A8 & 0x6000)) {
            func_80131E00(a0, 0xD);
            return;
        }
        /* polarity MUST match case 4's — see the cross-jump note in the header. */
        if (*(s16 *)(a0 + 0x76) <= 0) {
            func_80131E00(a0, 6);
        } else {
            func_80131C78(a0);
        }
        break;

    case 4:
        D_801D94A8 = ((s32 (*)(s32))func_8012CBA4)(a0);
        if (D_801D94A8 & 0x8000) {
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        if (D_801D94A8 & 0x2000) {
            if (func_80131D68(a0, D_801D94A8) == 1) {
                return;
            }
            if (*(s16 *)(a0 + 0x76) <= 0) {
                func_80131E00(a0, 6);
            } else {
                func_80131C78(a0);
            }
        } else {
            if ((*(s32 *)(a0 + 0x1C) & 3) == 3) {
                func_80143B6C(a0, 1);
            }
            *(s32 *)(a0 + 0x1C) += 1;
            if (*(s32 *)(a0 + 0x1C) >= 0x3D) {
                func_80131E00(a0, 0xD);
                return;
            }
        }
        break;
    }

    func_80131CA8(a0, 0x2F);
}
