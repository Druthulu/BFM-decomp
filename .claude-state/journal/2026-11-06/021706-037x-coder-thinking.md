---
ts: 2026-11-06T09:17:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1KjdCYa1X9ZrWRgDjOJ9
---
Interesting: the first branch (uVar2 != 1) code ends at insn 105 (`j 274c`) and 106 nop; then the else branch (uVar2==1) at 107. The keepalives for iVar7/t and fc are in the first branch.

Note: the function returns; bVar1 (t0) is dead after the &0x10 test, yet target keeps it live through... hmm, actually does it? In target, the &0x10 andi writes v0 because bVar1 is live to the keepalive point (line 47), which is *after* the &0x10 test (line 44). So yes.

So we need a real use of bVar1 between the &0x10 test and... Actually just after it: any real use of bVar1 later in the block (before the call) would do. There is none in the original semantics.

But wait — the source is a decompilation; the target binary is the ground truth. What if the original C had a use of bVar1 later that the current source doesn't? We're allowed to rewrite the C as long as it produces the same binary. So we could write code that reads bVar1 later but doesn't affect output — but that's an "identity launder"/dead use, which is what the keepalive was, and the brief forbids identity-statement launders and keepalive-like levers.

Hmm. So how can real C keep bVar1 live legitimately? Maybe by restructuring the bVar1 tests so that bVar1 is genuinely needed later: e.g., combine the &0x10 test into the later fc block? No, semantics.

Alternatively: make the &0x10 test not fold into t0 by other means. The fold happens in combine: `andi t0,t0,0x10` where t0 dies. What if the test's result is used in a way that needs a separate value, e.g. `if ((bVar1 & 0x10) != 0) *(s16*)(param_1+0xa) = -sVar5;` The andi result is used once by beqz. If the andi result were used twice, cse/combine couldn't use t0? Combine would still fold the AND into t0 if t0 dies and the AND has one use... Actually combine folds `(and reg 0x10)` into the branch's compare? In MIPS, `andi` then `beqz` — combine could merge into `andi v0,t0` and branch. The destination register choice: if t0 is dead after the andi, it may reuse t0.

What if bVar1 is used *before* the andi in a way that its value must survive... it does survive; the issue is only that it's dead after.

Another angle: change the *type* of bVar1 or how it's declared? It's `register u8 bVar1 __asm__("$8")`. If we make it `u8 bVar1` (no pin) — then the compiler might allocate differently. But the pin is not a row kind; still, we need t0 to hold bVar1. Actually maybe without the pin, bVar1 naturally lands in t0? The target uses t0 for bVar1 because $8 is caller-saved... hmm.

Let's look at the whole picture: which pseudos are in which regs in target. bVar1=t0($8). s8=iVar11. a2=param_1. a3=uVar6 (from f34+0x38? Actually a3 = uVar6? At insn 31 `addiu a3,v0,16` = uVar2b; and a0 = uVar6). t1 used for constants (153, etc.). v0/v1/a0/a1 scratch.

If we drop the $8 pin and declare `u8 bVar1`, then bVar1 might get t0 anyway via local-alloc (it's a short-lived byte). But then the andi fold would still use t0 if dead.

The real lever here: keep the pseudo alive. What real C could do that? Consider using bVar1 in the *condition of the call's arguments*: e.g. the call `func_8013AA24(iVar11, param_1)` — no.

Hmm, wait. Maybe reorder statements: put the `fc` block *before* the &0x10 test? Target order: &0x10 test (insns 69-73) then fc block (74-101). Source order: &0x10 test, then fc. If we moved the fc block before the &0x10 test, order changes.

What if the bVar1 test is spelled as part of the same expression as the store, e.g.:
`*(s16 *)(param_1 + 0xa) = (bVar1 & 0x10) ? -sVar5 : sVar5;`
Then the andi result feeds a select. The target codegen: `sh v1,10(a2); beqz v0, ...; negu v0,v1; sh v0,10(a2)`. That's exactly if/else. A ternary would produce the same. And the andi still folds to t0 if dead.

Could we make bVar1 used in the store to param_1+8 (the &0x60 test) *after* the &0x10 test by restructuring the boolean: `if ((bVar1 & 0x60) == 0 || (bVar1 & 0x80) != 0)` — this test is before. Hmm.

New idea: since we can reorder statements as long as the resulting insns match, maybe move the *bVar1 load* to a different point. No.

Alternative: keep bVar1 live by *combining* the &0x10 test into the later `fc` comparison? No.

Let me reconsider: maybe the real-C move is to make the &0x10 test use `sVar5`'s byte? No.

Wait — maybe I'm overcomplicating. Perhaps there is a different real-C spelling that produces the target's `andi v0,t0,0x10` even with t0 dead: e.g., if the AND is part of a larger expression that combine cannot fold into the hard reg. For instance `if ((u32)bVar1 & 0x10)` with a cast; or `if (bVar1 & 0x10u)`; or use `(bVar1 << 24) & 0x10000000`? Those change insns.

What about `if ((bVar1 & 0x10) != 0)` vs `if (bVar1 & 0x10)` — same.

What if the AND result is stored in a variable that is used later:
```
u32 m10 = bVar1 & 0x10;
if (m10) *(s16*)(param_1 + 0xa) = -sVar5;
```
m10 used once -> folded.

Hmm. Let me look at how combine picks the dest. In combine, when combining `(and (reg t0) 0x10)` into `(if_then_else (eq (and ...) 0))`, the result register is the pseudo's. In GCC 2.7.2, `combine` calls `subst` which may create a new register unless `undobuf`/`reg_dead`. Actually the andi was already generated in the .rtl from the C expression; the dest pseudo is a new pseudo (v0 normally). The question is why without the keepalive it becomes t0: local-alloc/global-alloc coalesces? No, the insn sequence shows andi t0,t0,0x10 then beqz t0 — the dest pseudo was *tied* to the source. This is combine's doing: combine sees `(set (reg:SI 82) (and:SI (reg:SI 8) (const 16)))` where reg 82 is a fresh pseudo, and reg 8 dies; it changes the dest to reg 8 (a "split"/"tie"?). Actually in combine, `subst` with `undobuf` and `i1` ... There's a known optimization: `combine` merges `(set (reg A) (op (reg B) ...))` where A dies? Hmm.

Whatever the pass, the fix needs a live B after.

OK here's another thought: maybe the bVar1 pseudo *is* live in target beyond the andi not because of a later real use but because of the keepalive asm creating a USE at line 47. We need to replace with real C that keeps it live. Since semantics don't use bVar1 later, the only way is to restructure so that a *real* use moves after the &0x10 test. Is there any bVar1 use that could be moved after? The &0x60/&0x80 test applies to the +8 store, which must precede +0xa (target order). BUT the bVar1 load and tests: what if we compute the &0x60/&0x80 *condition* into a variable early, then apply it (store) after the &0x10 test? No—order.

Alternatively, move the &0x10 test *later*: the &0x10 test negates param_1+0xa. What if we move that negation to after the fc block? Target order has it before fc (69-73 before 74). No.

Hmm, what if we can make bVar1 live by using it in the *division* for the second sVar5? E.g., `(uVar2b & 0xffff)` — no.

Let me reconsider the problem: maybe we don't need bVar1 live after the andi; maybe we need t0's pseudo to not be dead so local-alloc doesn't reuse. Another route: change the AND to a different form that yields `andi v0,t0,0x10` naturally, e.g. test a *copy* of bVar1 stored in a variable used later? 

Hold on — look at target insn 44: `andi v0,t0,0x8` for the &8 test. That one is before, and t0 is live after (used at 49), so it goes to v0. Good. So for &0x10 at 69, the target's t0 must be live after 69. The keepalive at source line 47 is *after* the &0x10 test (line 44) — yes. So t0 live through 69..? Actually the asm use is right after line 44, before fc. So the live range extends a couple insns.

Real C alternative: could we move the bVar1 *load* (`bVar1 = *(u8*)(iVar11+0x22)`) to after the &0x10 test? No—it's needed before.

Could we move the *&0x60/&0x80 test* to after the &0x10 test while preserving insn order? No.

Hmm, what if we split bVar1 into two variables? E.g., `u8 bVar1 = ...; u8 bVar1b = bVar1;` and use bVar1b for the &0x10 test? Then bVar1's last use is the copy; the &0x10 test uses bVar1b, which dies at the andi -> andi writes bVar1b's reg. Not helpful unless bVar1b is pinned.

What if the &0x10 test uses a value that's genuinely live later: `u8 x = bVar1 & 0x10; ... if (x) ...;` still one use.

OK, alternative: use the pinned bVar1 in a way that forces a *copy* into a new pseudo at the test, and the new pseudo is live later? No.

Let me look at this from a different angle: maybe there's another real-C spelling of the whole region that yields the same insns with t0 live naturally. For example, hoisting the &0x10 test's result into a variable used in *both* the +0xa negation and something later... 

Wait, actually: `zr` is pinned $0 and used as `iVar7 = fc + zr;`. That's a launder-ish pin? zr pin is a register pin ($0) — not a row kind (pin is not in kinds? kinds=keepalive only). Hmm, but pins may stay.

Let me look at what happens with the pin removed: maybe the keepalive becomes unnecessary if the pin is dropped and bVar1 gets a different reg? Let's test: drop the $8 pin AND the keepalive; see score.
