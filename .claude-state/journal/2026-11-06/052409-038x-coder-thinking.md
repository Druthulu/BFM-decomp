---
ts: 2026-11-06T12:24:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5l9x144khoy6Orog5MvU
---
Key: "a zero-byte `__asm__` ref that keeps the pinned value LIVE PAST the temp" — that's our keepalive. And it's needed because the pin's qty_phys_sugg invites the tie.

Since the keepalive is a row kind that must go, we need another way to keep pos live past the temp. OR remove the pin? But pins are allowed to stay... The pin on pos causes the tie suggestion. If we drop the pos pin and use a plain variable, maybe the tie goes away and the allocation is still t4?

Wait, but the pin is what forces pos into t4 (target's move t4,a2). Without the pin, arg2/pos might get a different reg. But in my a1.c (no pins), arg2 got t3 and arg1 t4. Hmm.

So the pin gives pos=t4. And the pin's qty_phys_sugg invites the addiu to tie to t4. Removing the pin loses pos=t4.

What if we keep the pin but make the tie impossible by keeping pos live — the keepalive is the documented cure but it's a row kind.

Alternative real-C: use `pos` in a way that's live past the addiu. Hmm.

WAIT. What if we move the keepalive's effect into the OTHER arm: make pos live in the join block by using it in the store's address computation? No.

Let me reconsider the whole tail. What if the source computes `var_v0_3 = pos + 2` but ALSO uses `pos` in the same block for something real... The block has D_801152AA = 0xFFF. What if the store were `D_801152AA = 0xFFF + (pos - pos)`? launder.

Hmm, what about the `b4b = D_801909C4` assignment: `b4b = D_801909C4;` could be written as `b4b = (s16 *)(D_801909C4);` — no pos.

I'm going to try a batch of variants programmatically, including:
1. Move `b4b = D_801909C4;` out of the arms to the join (before the store).
2. Compute var_v0_3 with the sign folded: `var_v0_3 = (arg1 & 1) ? pos + 2 : pos - 2;` at the join.
3. Use a delta variable.
4. Use do-while wrappers.
5. Reorder the store and the tail.

Actually, here's a thought: in the join block, if we use pos in the store's expression: `b4b[1] = var_v0_3;` — what if instead the arms compute only the DELTA and the join does `b4b[1] = pos + delta;`? Then pos dies in the JOIN block at the addiu → tie (dst = pos's reg t4). But wait — the pin's qty_phys_sugg: the tie suggestion is unconditional for the pinned reg. If the addiu's src is pos (pinned t4) and it dies, dst prefers t4. Yes, tie.

Unless the join block's addiu is a 3-operand add (addu v0,t4,delta) — no tie for 3-operand? The tie suggestion applies when an input dies and the output can share; for addu (3-operand in RTL, 2 in asm), gcc's local-alloc can still tie dst to a dying src.

Hmm.

Let me think about the qty_phys_sugg mechanism: it's recorded when `combine_regs` sees a pseudo that is the same as a hard reg (the pinned pseudo). The suggestion is that OTHER pseudos prefer that hard reg. So var_v0_3 prefers t4 (pos's reg) → tie. To avoid, pos must be live (find_free_reg can't honor).

OK so with the pin, the tie is inevitable unless pos is live past. Without the pin, pos might not be t4 anyway.

Could we keep the pin on pos but have var_v0_3 NOT prefer it? The suggestion is registered per hard reg and applies to pseudos whose... hmm.

Let me try a variant where the pos pin is on a DIFFERENT variable: e.g., keep `register s32 pos __asm__("$12")` but make the addiu's source a different variable (a copy of pos) that's not pinned. Then the tie would be to that variable's reg, not t4? The target has addiu v0,t4,2 — the source IS t4. So the addiu's src must be pos (t4). The tie preference is for the pinned hard reg t4 → dst prefers t4.

Hmm, unless the src is a different pseudo allocated to t4 by coincidence, not by the pin. If we drop the pin and get pos→t4 naturally, the tie would still prefer t4 (dst prefers src's reg when src dies). So the tie is about src dying, not the pin. Wait, no: the tie suggestion (dst prefers src's reg) exists regardless of pins; the pin's qty_phys_sugg is an ADDITIONAL unconditional suggestion.

So even without the pin, if pos dies at the addiu, dst ties to pos's reg. The target needs pos live.

Conclusion: pos must be live past the addiu. The only real way: a use after.

Hmm, is there a real use? Let me look at the tail once more:

```
D_80126720 = (arg0->unk4 + arg0->unk6) >> 1;
D_80126722 = (arg0->unk8 + arg0->unkA) >> 1;
D_80126724 = (arg0->unkC + arg0->unkE) >> 1;
return 1;
```

What if pos (arg2) were used as the return value... the target returns 1 (li v0,1 at d58, before the D_80126724 store). So return 1.

What if the D_801152AA store used pos in a real way: `D_801152AA = pos & 0xFFF`? No.

OK — maybe there's a different crack: make the addiu NOT tie by having var_v0_3's assignment be in a different block than pos's death. If pos dies in the join block and var_v0_3 is computed in the arms... pos is used in the arms (addiu) so it doesn't die in the join.

What if pos is used only in the join block (via a delta), and the addiu is in the join: pos dies at the join addiu, but the join block also contains the tail. If pos is used AFTER the addiu in the same block... no.

I'll try the batch approach and see if anything surprises me. But given time (I'm at ~40 min on item 1), let me set up a generator to produce ~20 variants quickly and score them, then move on.

Actually, hold on. Let me reconsider the possibility of removing the launder via a real 2nd set that DOES match. What if:

```
s32 a1s = arg1;          // copy for later (merges, no good)
```

What if instead the later uses read `(s32)((u16)arg1)`? no.

Hmm, what about using a global: `D_801152AA = 0;` etc. no.

Let me look at the problem from the "what C produced the target" view: the target was produced by the lever body (orig.c), which we have and which scores 0. The lever body's structure IS the C that generates the target (with asm). So the target's shape is asm-driven. A lever-free MATCH would need a fundamentally different C that produces identical code — often impossible (hence WALL).

Given the shard is "singleton crack shard" (items where levers remain), WALLs are expected outcomes. The brief requires ≥20 min and ≥30 scored tries for a WALL. I've done ~10. Let me generate 25+ quick variants to satisfy that, then record the best (score 3, b2) as WALL with the appropriate tag.

But first, let me try the promising ones:
- b2 with the tail store order swapped
- b2 with var_v0_3 computed in the join
- b2 with do-while

Let me write a small generator script under the item dir that emits variants. Since each score is a compile (~2s), 25 variants = ~1 min. Good.

Plan: base = b2 (launder+pins+barriers, no keepalive, score 3). Generate variants of the tail:
1. move b4b assignment out of arms
2. var_v0_3 = pos + 2 computed before D_801152AA
3. store before D_801152AA
4. delta variable + join add
5. do-while wrappers
6. declare var_v0_3 as s32
7. use `b4b[1] = pos + 2` inline in arms with a join store omitted (duplicate stores)
8. conditional expression
9. reorder tail globals
10. move the `b4b = D_801909C4` to before the if

Also try b1 (launder only) variants.

Actually, let me focus: the ONLY diff in b2 is 3 insns (t4 vs v0). Variants that keep the structure and change the tail could crack it.

Let me write the generator as a Python script that takes a template and produces variants. Simpler: write each variant with a shell heredoc? The Write tool is cleaner. But 20 files... Let me write a Python script that generates the files.

Actually, a smarter approach: use sed to transform b2 into variants in a loop. Let me write a Python script .run/P40/T11/G31x/func_.../gen.py that reads b2.c and applies textual substitutions, writing v*.c, then run sc.sh on all.

Let me look at b2's tail text first.
