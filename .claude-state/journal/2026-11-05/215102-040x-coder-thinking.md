---
ts: 2026-11-06T04:51:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fTC7tHkYdLlpfa9cI7qz
---
The index says the fix for this exact residual is the zero-byte asm fence — which is a lever (barrier). The brief says lever-free is required; the barrier IS the row kind. So this is likely a genuine WALL for item 1 unless a real-C trick exists.

Given the moves catalog, `dbr-delay-fill` is an established WALL tag. But wait — before declaring a wall, I must try ≥ 30 scored tries per item and ≥ 20 min. Let me be efficient: I can generate many variants and score them in bulk with sc.sh. Each score takes ~1s? The batch of 10 took a few seconds. So 30+ tries is cheap. But I should spend the wall time too — the rule says a WALL needs ≥ 20 min AND ≥ 30 scored tries. So I'll keep exploring while doing other items in parallel? No — one item at a time, but I can do a big batch for item 1 now, then move on and come back if I have ideas.

Actually, a better strategy: since all 5 items are header barriers of the same "headers1" batch, and this one's residual is exactly the documented §34 asm-fence case, the others may have different residuals. Let me quickly baseline all 5 (remove barriers) to see the scores, then decide where to invest.

Let me first check the other 4 items' barriers and their lever-free scores. But careful with the 20-30 min budget per item. The budget is per item; I'll track time.

Item 1 started 21:42. It's now maybe 21:55. Let me continue with item 1 for a few more batches (30 tries), then decide.

Let me generate a larger batch of item-1 candidates with varied real-C moves:

More ideas:
- Use `if (D_80078EBF >= 0x81)`.
- Use `if (D_80078EBF & 0x80)`? no, wrong semantics.
- Move the clamp into a separate statement using a ternary: `D_80078EBF = (0x80 < D_80078EBF) ? 0x80 : D_80078EBF;` — different code (no branch likely).
- `if (0x80 < D_80078EBF) { D_80078EBF = 0x80; } else { }` — empty else.
- `if (0x80 < D_80078EBF) goto L; goto M; L: D_80078EBF = 0x80; M:;`
- Put the clamp store through a pointer variable.
- Reorder the two stores.
- Compute `add` differently.
- Use `s32 v = D_80078EBF; if (0x80 < v) ...` — this changes the value flow; might produce different code.
- Use `u8` temp: `u8 u = D_80078EBF + add; D_80078EBF = u; if (0x80 < u) D_80078EBF = 0x80;` — this could change the andi/sltiu sequence.

Hmm, the target's code: after `sb v0`, it does `andi v0,v0,0xff; sltiu v0,v0,129`. That's from the u8 comparison. If we use a temp `u8 u`, the code might be the same or different.

What about the *statement order*: the clamp check could be done before the store? No, semantics.

Let me think about a label more: in the RTL, the if-body might get a CODE_LABEL if the source has a label that is referenced by a `goto` from *the same* branch structure. Consider:

```
if (0x80 < D_80078EBF) {
  clamp:
    D_80078EBF = 0x80;
}
```
No reference → label deleted.

What if a `goto clamp` appears in a dead branch that gcc keeps? e.g. `if (0) goto clamp;` — optimized away.

What if the goto is in an unreachable-but-kept path? At -O2, dead code is removed.

Hmm, what about a `switch` with one case? no.

What about making the if-body a *loop body*: `do { D_80078EBF = 0x80; } while (0);` — tested (b1), no.

What about `while (0x80 < D_80078EBF) { D_80078EBF = 0x80; break; }`? Loop with a break — adds a jump.

OK here's another angle: what if the value `0x80` is stored via `add` which is a *u8* variable live at the epilogue? no.

Let me look at the actual RTL/cc1 dump to see the exact reason. There's tools/cc1_dumps_tu.sh for TU dumps. That could tell me the RTL around the branch (reorg runs after). Actually reorg doesn't dump RTL by default? With -dR? The pinned compiler flags may not allow. hdump.sh is for header pass dumps. Let me check what hdump.sh does.

Actually, a more productive approach: I know the exact mechanism. To stop the eager fill I need the first insn of the fall-through thread to be (a) asm/jump/label/sequence, (b) a store (may_trap) or something setting a live-in of the target.

Let me verify (b) empirically: does a store-first body get a nop? I can test by writing a body where the clamp is `*(u8*)&D_80078EBF = 0x80;` — still li first.

Alternatively, test whether may_trap_p blocks: write a body where the first insn after the branch is a load. E.g.:
```
if (0x80 < D_80078EBF) {
    add = D_80078EBF;   // a load? No, D_80078EBF was just loaded/added; gcc may reuse v0.
    D_80078EBF = 0x80;
}
```
If gcc re-loads the global (because the store clobbered it?), the first body insn could be `lbu`. But the target doesn't have that.

Since the target's instructions are fixed, the only freedom is in how the same instruction sequence is produced. The instruction sequence is:
```
andi v0,v0,0xff
sltiu v0,v0,129
bnez v0, L
nop
li v0,128
lui at
sb v0,0(at)
j L
nop
```
Any C that produces this exact sequence will have the same RTL shape (roughly), and the delay slot fill depends on the RTL insns' properties, which are the same. The ONLY way to differ is if the RTL has *extra* insns that are later deleted or that alter resource tracking — exactly what the asm does (an extra insn that stops the scan).

Could an extra C statement produce an RTL insn that is later deleted but affects reorg? Reorg runs after all other passes (it's the last). An insn deleted before reorg has no effect. An insn present at reorg would appear in the output (unless it's a nop...).

Unless the extra insn is a `NOTE` — notes don't stop the scan (stop_search_p returns 0 for NOTE).

What about a USE/CLOBBER insn? `mark_referenced_resources`/`mark_set_resources` skip USE/CLOBBER, and stop_search_p? GET_CODE USE is INSN with PATTERN USE — stop_search_p returns (SEQUENCE || ASM_INPUT || asm_noperands>=0) = false. So a USE doesn't stop it. But in fill_slots_from_thread, `if (GET_CODE (pat) == USE || GET_CODE (pat) == CLOBBER) continue;` — it skips them.

Hmm what about a `REG_LABEL` reference in an insn? `try_split` etc.

OK, one more idea: `eligible_for_delay`. The MIPS md may restrict which insns can go into a delay slot. In the target, `li` (an lui/ori pair, actually `li v0,128` = addiu v0,zero,128) — eligible. The asm blocks. Fine.

What if the clamp value is loaded as `li v1,128` vs `li v0,128`? Register choice is fixed by allocation.

I think item 1 is a WALL (dbr-delay-fill). But I need ≥30 tries and ≥20 min. Let me do a big batch of 25 more variants, many of which are plausible. If none crack it, record WALL with best score 5.

Actually wait. Let me reconsider one specific idea: **the dead-reset cse-breaker (C0414)**. If I insert `r = 0;` between the store and the clamp check, it creates a real 2nd set of r. That doesn't affect reorg. Scored b5 = 5 (same).

Another: **statement order** — put the clamp check as `if (D_80078EBF > 0x80)` (b3=5).

Hmm, what about making the clamp a *separate if* outside the inner if? No.

What about the `else` arm? The else at the outer if sets D_80078EBF = 0. The branch at 4cd0 (beqz) targets 4d40. Not our issue.

Let me now look at whether the target's nop could come from the branch being "annulled"... no.

Let me try a batch focused on shape changes that keep the instruction stream but alter insn order/labels:

c1: `if (0x80 < D_80078EBF) { D_80078EBF = 0x80; }` with `D_80078EBF` accessed via a pointer `p` declared at top: `u8 *p = &D_80078EBF;` then `*p = *p + add; if (0x80 < *p) *p = 0x80;` — likely different code (address in reg).
c2: clamp before store? no.
c3: `if (0x80 < (s32)D_80078EBF)`.
c4: `if (0x80 < (u32)D_80078EBF)`.
c5: `if ((s32)D_80078EBF > 0x80)`.
c6: `if (0x80 < D_80078EBF) D_80078EBF = 0x80;` (no braces).
c7: use `add = 0x80 - (D_80078EBF - D_80078EBF);` silly.
c8: `D_80078EBF = D_80078EBF > 0x80 ? 0x80 : D_80078EBF;`
c9: `if (D_80078EBF >= 0x81) { D_80078EBF = 0x80; }`
c10: `if (0x80 < D_80078EBF) { D_80078EBF = 0x80; r = 0; }` (dead reset after)
c11: `if (0x80 < D_80078EBF) { D_80078EBF = 0x80; add = 0; }`
c12: `if (0x80 < D_80078EBF) { D_80078EBF = 0x80; if (0) r = 1; }` (dead)
c13: `if (0x80 < D_80078EBF) { goto set; } goto done; set: D_80078EBF = 0x80; done:;`
c14: `if (0x80 < D_80078EBF) { D_80078EBF = 0x80; } if (0) { D_80078EBF = 0; }`
c15: `switch (0x80 < D_80078EBF) { case 1: D_80078EBF = 0x80; }`
c16: `if (0x80 < D_80078EBF) { do { D_80078EBF = 0x80; break; } while (1); }`
c17: `while (0x80 < D_80078EBF) { D_80078EBF = 0x80; break; }`
c18: `if (0x80 < D_80078EBF) { D_80078EBF = 0x80; } else { D_80078EBF = D_80078EBF; }` (identity else)
c19: clamp value via `add = 0x80; D_80078EBF = add;` and `add` used after the if? e.g. `return;`? can't.
c20: `if (0x80 < D_80078EBF) { D_80078EBF = 0x80; }` with `add` declared after? decl order change.

Let me also try: make the value 0x80 come from a u8 variable `u8 c = 0x80;` declared at function scope — then `D_80078EBF = c;` inside. If c is a register live across the branch, the store body might be `sb` only (address lui). Hmm.

And: `u8 c; c = 0x80;` right before the if — the li would be before the branch.

Let me generate c1-c20 and score. This gets us to 30 tries for item 1.

Note: some may fail to compile — that's fine.

Let me write gen2.py.
