---
ts: 2026-11-06T20:24:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_t6is5MmJgmgNlVQSCpSq
---
Now it's clear:

ORIG (pinned, launder): 
- insn 97: a0 = s0
- insn 100: a1 = -524288
- insn 102: a1 = asm (the launder, a separate insn between the constant and the call!)
- insn 105: v0 = 7 (hi)
- then the call sequence: call; delay slot = the sh store.

NOLAU:
- insn 95? (a0 = s0 presumably)
- insn 101: v0 = 7
- insn 103: sh (store)
- call sequence with the delay slot = `a1 = -524288` (moved into the delay slot).

So the difference: in orig, the constant `a1=-524288` is a separate insn BEFORE the call, and the launder insn 102 sits between. In nolau, the constant is in the call's delay slot.

Who decides? The .dbr dump is post-reload reorg: in nolau, the sequence has the constant in the delay slot of the call (as a SEQUENCE). This placement was done by reorg? Or by sched2 before reorg? The .dbr dump is *after* reorg (dbr=dbr_schedule dump). In orig, the call's delay slot has the store, and the constant is before.

In nolau, the call's delay slot has the constant, and the store is before the call.

So reorg fills the delay slot with the insn that ends up immediately before the call: in orig, the store (insn 107) is right before the call in RTL order? Actually in orig the RTL order is: 100 (const a1), 102 (asm), 105 (v0=7), then call seq [call, sh]. Hmm, the call sequence is a SEQUENCE where the sh is the delay slot. So in orig, the sh is in the delay slot, and the const+asm+li are before.

In nolau: 101 (v0=7), 103 (sh), then call seq [call, const]. So the const is in the delay slot and the sh is before.

So the order of insns 100/102/105 vs the store differs. In orig, the const is before the li and the store. In nolau, the const moved after the store (into the delay slot).

This is sched2 (post-reload scheduler) ordering: sched2 decides the order of the const vs the store, then reorg fills the delay slot with the last insn before the call.

In orig, the asm insn 102 (a real RTL insn, zero-width) sits between the const and the li, pinning the const at its position (sched2 doesn't move the const past the asm because the asm has REG_DEP?). Actually the asm insn creates a scheduling barrier of sorts (asm has unknown side effects, so sched2 won't move insns across it? The const 100 is before the asm 102, and the li 105 after).

Hmm, the notes say the re-tie "stops the constant from being rematerialised down at the call" — but from the RTL, the constant insn 100 is at its source position and the asm 102 follows. Without the asm, sched2 moves the const down into the delay slot.

So we need a real-C reason for sched2 to keep the const before the store. sched2 orders by priorities and dependencies. The store `sh v0,2(s0)` depends on the li v0,7. The const a1 has no dependency on the store. sched2's priority: the const (a1) has... hmm.

What if we make the constant *depend* on something that's computed after the store? No.

Alternative: change the source order so the const is defined earlier, e.g., before `move a0,s0`? The `q` pin (`register s32 q __asm__("$4") = s0;`) makes a0=s0 at the arm top. In target: `move a0,s0` (21b8), `lui a1` (21bc), `li v0,7` (21c0), `jal`, `sh` (delay).

What if we move `r = 0xFFF80000;` BEFORE `q`'s declaration? E.g.:
```
s32 r = 0xFFF80000;
register s32 q __asm__("$4") = s0;
((Unk*)s0)->unk2 = 7;
func_8012B178(q, r);
```
The C decl `register s32 q ... = s0;` emits `move a0,s0` at that point. Order in RTL: r const, move a0, li, sh, call. sched2 might then place the const before the move — target has move a0 first, then lui. Hmm.

Actually, maybe a simpler fix: sched2 moved the const into the delay slot because it was the "last" insn. If we make the const's scheduling priority higher or add a dependency, it stays.

Alternatively — maybe use the C0414 dead-reset trick: give r a second set that is real but eliminated later? The asm insn 102 is *between* the const and the call. What if we add a real C operation on r that combine folds away but which sits between? E.g., `r = 0xFFF80000; r += 0;` folds.

What if we use the other arm's constant? no.

Hmm, what about using `r` in a comparison that's folded: `if (r) ...` no.

Let me think about sched2's behavior: it schedules the block after the call (the tail block: move a0, li v0 7, sh, call). Wait, is the const part of the same basic block? The arm block: from the bnez target to the call. sched2 reorders within the block by priority. The const has a REG_EQUAL note and low priority? The store and the li have a dependency.

In orig, the asm insn 102 is in the block between them. sched2 doesn't move the const past the asm because asm insns are scheduling barriers? Let me check sched2/sched.c: asm insns have `INSN_PRIORITY`? Actually sched2 (`sched2`/`schedule_block`) uses `maybe_never`? For asm, `sched_analyze_insn` treats `asm_noperands >= 0` specially: it adds dependencies for all live regs? Let me check sched.c for ASM_INPUT.

Alternatively: the launder asm *clobbers* a1 (the output), creating a dependency: the call's a1 use depends on insn 102 (which depends on 100). So the chain 100 -> 102 -> call. Without it, the const 100 is free and sched2 sinks it into the delay slot (or reorg picks it).

Hmm, in orig the store (105->107) also depends. The call's delay slot gets the last insn in the schedule; reorg fills with the store (107) since it's last.

If we give the const a dependency on the store... e.g., make the constant computation use the stored value? `r = 0xFFF80000 + (v & 0)` — identity.

What if the store's value is used in the constant? Semantics: unk2 = 7, and the arg is 0xFFF80000. We could write `((Unk*)s0)->unk2 = 7; r = 0xFFF80000;` — the const after the store. Then sched2 sees: li, sh, const, call. The const is last → in the delay slot (same as nolau). No.

What if we compute the constant *from* the store's value in a value-preserving way? e.g., `s32 seven = 7; ((Unk*)s0)->unk2 = seven; r = 0xFFF80000 | (seven & 0);` — identity.

Hmm, but here's a real one: `r = 0xFFF80000; ... ((Unk*)s0)->unk2 = 7;` and the call uses r. The dependency we need is const -> store. Not natural.

What about using the *pinned* q in the constant? `r = (s32)((u32)q & 0xFFF80000)`? Not equivalent.

Let me look at how sched2's reorg decides. Actually the key question: does the target's `lui a1,0xfff8` position come from sched2 keeping it before the li/store? In orig, the RTL order before the call is: const, asm, li, [call, sh]. So sched2 placed li after the asm; the asm blocked reordering. Actually sched2 doesn't reorder across asm? Let me check sched.c's handling of ASM_INPUT: `sched_analyze_insn` for asm with operands adds dependencies on all registers used and sets `reg_pending_barrier`? Let me look.

Let me grep sched.c for asm handling.
