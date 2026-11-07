---
ts: 2026-11-06T04:48:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TAshbY2ZH1fTUUx4hoaT
---
So `prediction = mostly_true_jump`. For our branch, if prediction <= 0, it tries fallthrough first with `thread_if_true = 0`. Then `stop_search_p (trial, ! thread_if_true)` = `stop_search_p(trial, 1)` → labels stop the search. And in fill_slots_from_thread, `own_thread = own_fallthrough`.

Key insight: if the fall-through block starts with a CODE_LABEL that has other references, and thread_if_true=0 (prediction <= 0), the label stops the search → nop. But gcc deletes unused labels.

Alternative: make the first insn after the branch something `stop_search_p` catches. Asm is out. JUMP_INSN: the fall-through starting with an unconditional jump. In RTL, after `if (...) { body }` the body might begin with... hmm.

What about a BARRIER? Only after jumps.

Alternatively, make `own_fallthrough = 0`: `own_thread_p (NEXT_INSN (insn), NULL_RTX, 1)`. If the fall-through is not "owned" (e.g., the insn after the branch is a label that is a branch target from elsewhere), then the thread is not owned; then fill_slots_from_thread with own_thread=0: the loop condition `(! lose || own_thread)` and stop_search_p with labels_p=!thread_if_true=1. Since own_thread=0, the first conflict sets lose=1 and stops. But the li is not a conflict...

Hmm.

OK, maybe the right framing: the target's nop arises because of the asm, and reproducing it with real C is a wall (dbr-delay-fill). The brief allows PARTIAL and WALL. But we should try the moves.

Actually wait — maybe there's a much simpler lever: reorder the source so that the clamp branch isn't a conditional jump with a stealable fall-through. What if the clamp is written as a conditional expression or a min? That changes instructions.

Let me reconsider the whole function: maybe a different real-C spelling produces the same target instructions but a different reorg outcome. Target:

```
4d1c: andi v0,v0,0xff
4d20: sltiu v0,v0,129
4d24: bnez v0,4d48
4d28: nop
4d2c: li v0,128
4d30: lui at
4d34: sb v0,0(at)
4d38: j 4d48
4d3c: nop
```

Interesting: the target has `li v0,128` AFTER the nop. So the delay slot is nop and li is the first real insn of the body.

What if we write the body to store via a temp that's live at the branch target? Not possible.

What if we make the if-body start with a *store to memory* (may_trap_p)? `sb` is a store; may_trap_p for a store? In GCC, may_trap_p returns true for stores (memory references can trap) — actually `may_trap_p` on a `set (mem) (const)` returns 1 (store can trap). So if the first insn of the body were `sb`, it couldn't be moved → nop. But the body is li + lui + sb; li comes first. Could we force the address computation to be done *before* the branch (outside), so the body starts with sb? E.g.:

```
u8 *p = &D_80078EBF;   // address in a register
...
if (0x80 < D_80078EBF) {
    *p = 0x80;
}
```
Then the body would be `li v0,128; sb v0,0(at)` — the address (lui at) would be hoisted before the branch, and the first body insn is still li. Unless the value 0x80 is also precomputed... If both value and address are ready, the body is a single `sb v0,0(at)` — but the target has li inside. No.

Hmm, what if the value 0x80 is materialized before the branch and the body is just `sb`? Then the code differs (li moved before the branch). Not target.

OK here's another thought: `may_trap_p` isn't the only blocker; `insn_sets_resource_p (trial, &opposite_needed, 1)` — opposite_needed = live regs at the target = epilogue's live-ins. What's live at the epilogue? ra, sp. Hmm, but wait: mark_target_live_regs(opposite_thread) computes registers live at the start of the target block. At 4d48: lw ra, addiu sp, jr ra. Live-in: ra, sp. Plus v0? v0 is not used. So no.

BUT: what if we change the join so that the epilogue uses v0? Can't.

Alternative: flip the branch so the fall-through is the epilogue. E.g., write:
```
if (!(0x80 < D_80078EBF)) goto skip;
D_80078EBF = 0x80;
skip: ...
```
GCC would likely produce the same bnez.

Hmm, what about making the condition produce `beqz` instead of `bnez` (invert)? The target uses bnez v0 (v0 = sltiu result = "not > 0x80"). If we wrote `if (D_80078EBF <= 0x80) { } else { ... }`, codegen might emit beqz or bnez. The target uses bnez to skip.

Let me think about `prediction`: mostly_true_jump uses REG_BR_PROB if available; with -O2 without profile, it uses heuristics on the condition. If prediction > 0 (likely taken), it first tries the target thread (epilogue) — fill from target; probably fails (lw ra sets ra needed). Then `if (delay_list == 0 && own_fallthrough)` tries the fallthrough with thread_if_true=0. Same as before.

So either way, fallthrough is scanned with labels_p=1 (if thread_if_true=0) or... in the prediction>0 case the second call uses `0, 0` → thread_if_true=0 → labels_p=1.

So a label at the start of the fall-through would stop it. Can we get a CODE_LABEL at the start of the if-body with other uses? If a `goto` from another place targets it. E.g., a switch or an `if` that jumps there.

Idea: restructure the code so that the clamp block is shared (a label) — e.g.:

```
if (0x80 < D_80078EBF) goto clamp;
...
clamp: D_80078EBF = 0x80;
```

But gcc's jump optimization would see the fall-through and convert. Hmm, if the goto is the only path, it becomes fall-through and the label is deleted.

But what if there are two paths to the clamp? Then the target would have two jumps, not one. Not our shape.

Hmm OK. What about `stop_search_p` on a JUMP_INSN: if the fall-through's first insn is a JUMP_INSN (an unconditional jump), the search stops. Could the if-body start with an unconditional jump? Only if the body is itself a branch — not here.

Let me step back and consider that maybe the barrier isn't about reorg at all in the intended solution; maybe there's a body that produces the exact target including the nop through a different route, e.g., the `li v0,128` is not the first insn of the thread because an earlier insn (a copy) exists that reorg skips... 

Actually — here's a thought: `redundant_insn`. In fill_slots_from_thread, before the resource check, `if (prior_insn = redundant_insn (trial, insn, delay_list))` — if the trial insn is redundant with an insn before the branch, it's deleted and the scan continues (without filling). So if `li v0,128` were redundant with an earlier `li v0,128`... there is none. But if the body started with an insn that duplicates something before the branch, reorg deletes it and moves on. Hmm, dangerous.

What if the first insn of the body is a `move` that reorg's copy-propagation deletes... 

Let me try the empirical route now — I've spent a while. Let me create a batch of candidate bodies and score them with sc.sh (one line each). That's efficient.

Candidates:
a) do-while(0) around the clamp.
b) temp: add=0x80; store.
c) `if (D_80078EBF > 0x80)`.
d) `if (0x80 < D_80078EBF) { D_80078EBF = 0x80; }` with a preceding `r = 0;` dead reset (C0414).
e) reorder: put the clamp in a separate if with goto.
f) `D_80078EBF = D_80078EBF - D_80078EBF + 0x80;` — hmm, this creates uses.
g) `if (0x80 < D_80078EBF) { D_80078EBF = (u8)0x80; }`.
h) compute `add = 0x80 - 0;`
i) Use `while (0x80 < D_80078EBF) { D_80078EBF = 0x80; break; }` — hmm loop.

Let me write these quickly. Actually, a smarter move: since the target's delay slot is a nop, maybe we can get reorg to fill it with a *nop* by making the candidate insn annulled... no.

Wait wait. Let me reconsider. Look at the diff again: mine is 38 insns, target 39. The only difference is the nop. What if instead of preventing the fill, we ADD an insn somewhere that reorg can't move, making the count 39 and the delay slot... no, the diff compares insn by insn; the extra nop must be in the delay slot.

Alternatively: make the body's first insn `li v0,128` be preceded by an insn that stays (not moved) and is not a nop — that would be an extra insn, not matching.

Hmm, what about the `j 4d48`'s delay slot (4d3c nop)? Both have nop. Fine.

Let me look for a real-C construct that makes reorg skip the fall-through: `own_fallthrough = own_thread_p (NEXT_INSN (insn), NULL_RTX, 1)`. Let me read own_thread_p.
