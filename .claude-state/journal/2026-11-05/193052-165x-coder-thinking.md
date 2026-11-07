---
ts: 2026-11-06T02:30:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wlWnEqK6ddGbP4QlV2q4
---
No eligible_for_delay in MIPS → default is `#define eligible_for_delay(...) 1`? Actually reorg.c has:
```
#ifndef ELIGIBLE_FOR_DELAY
#define eligible_for_delay(insn, ...) 1
```
Probably.

Let me look at this from a totally different angle: what real-C change could make the branch's *target* thread fill the slot instead (or make the fall-through fill fail)? 

What if the addiu's destination is live at the epilogue because the function returns a value? It's void. But wait — maybe the real game function returns s32 and the TU declares it void? The signature must stay as-is per the constraints ("no signature or decl change outside the body (callers stay as they are)"). So void.

Hmm, what if the epilogue uses v0 because `jr ra` is preceded by something? No.

Let me look at the target's epilogue: b3c: lw ra; lw s0; addiu sp; jr ra; nop. Yes.

OK, what about the possibility that the target's nop is the *delay slot of the j at a58/a6c*? No, those have nops too, and mine matches them.

The missing nop is specifically after bnez at a7c. Let me check: in mine, is the addiu in the delay slot? Yes.

What if I make the addiu's result be used by a *branch* on the taken path? E.g., if the code after the epilogue... no.

What if the `state` variable is read after the branch on the taken path? no.

Hmm, let me try making the fall-through thread not owned by adding a label that's referenced by a forward branch from inside the same if body, e.g.:

```
if (unk98 == 0) {
    if (0) goto L;
    unk34 = state + 1;
L:
    ...
}
```
The `if (0)` folds. 

What about a label that's referenced by a real branch: e.g., `if (state == 0xFFFF) goto L;` — that adds a branch. ✗

What about a `switch (state)` where case 0's body is shared? no.

Let me try the do-while variants more systematically, since they're cheap: wrap (a) the addiu+sh in do-while, (b) the entire if body, (c) the addiu alone, (d) the calls, (e) the whole case.

Also try reordering the statements inside the if: target order is store, call1, call2. What if the store is written as `unk34 += 1` with a reload (b1 → 8).

Another idea: make the addiu's source a0 be *reloaded* after the branch, i.e., use `((Unk*)s0)->unk34 = ((Unk*)s0)->unk34 + 1;` (b1) — the compiler emitted 74 ins still with the addiu in the slot (it kept the cached a0? b1 scored 8, same). Hmm.

What about making the first insn after the branch a *load*: `t = *(s16*)(s0+0x98);`? no.

Let me try: `((Unk*)s0)->unk34 = state + 1;` but compute state+1 via a function call? no.

Let me look at whether the target's nop could be due to the addiu being in a *different basic block* (after a label that jump2 deleted but reorg still sees? no, reorg is after jump2).

Hmm, wait: reorg runs after jump2. If jump2 deleted a label at the addiu, reorg wouldn't see it. So own_fallthrough would be true. Unless the label survived jump2 (referenced).

What if the original C had a `switch` with a `case 0:` and the addiu is the target of the switch's jump table? No, case 0 is reached via the dispatch; the addiu is inside the case.

OK, let me consider (a) again: v0 live at the epilogue. What if the target's `func_80183ACC` is called in a context where the caller uses v0? Liveness is per-function; no.

Hmm, wait: maybe `mark_target_live_regs` marks v0 live at the epilogue because of the *return value* convention: the function is void, but gcc's epilogue might have a USE of v0? Let me check the RTL: the .jump2 dump of the orig would show if v0 is used in the epilogue block. Let me dump orig's dbr/rtl and look at the epilogue label block. Actually, the epilogue is generated in final, not RTL; at reorg time the return label's block is empty (the label is at the end). So mark_target_live_regs(epilogue) = live at the end = the return registers? For a void function, nothing.

Hmm, so why did the target not fill?

Let me look at the actual target's delay slot after bnez: nop. And mine fills with the addiu. Let me check whether the target's `bnez` target (b3c) is the SAME as mine's (b38 due to shift) — yes, the epilogue.

Could the difference be the *prediction*? If the target's branch was predicted NOT taken (prediction < 0), reorg would try the fall-through first — same fill. If prediction == 0, same.

Hmm.

Maybe the difference is that in the target, the fall-through thread was NOT owned because of a label at the addiu that was referenced by a branch from *inside the same thread* — e.g., a backward branch. What if the original C's case 0 body had a loop or a goto?

I think this is a WALL. But let me try a few more cheap variants before recording:
- do-while around the addiu+sh (store inside a loop)
- do-while around the whole if body
- do-while around the addiu only
- goto to a label after the addiu from a `if (0)` (folded, no)
- restructure case 0 as an if/else with the body in the else
- `state + 1` computed as `state - -1`? no
- `((Unk*)s0)->unk34 = state + 1;` where state is `s16` instead of u16? The load `lh` vs `lhu` changes.
- Make the addiu a `li`+`addu`? no.

Let me try these 6 and then record a WALL if none.
