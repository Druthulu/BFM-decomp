---
ts: 2026-10-22T21:56:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_trZNN02u16yqkrLCismU
---
q2 and q4 have the same real diff: the -0x60 group hoisted, plus the second lh chain missing an `addu at,at,v0`.

Wait — the missing addu at line 60 in mine. The second table read (the Blk8 copy) at 3730ish: `lh v1,524(s0)` then the chain. In mine there's no `addu at,at,v0`? That means the Blk8 copy's address computation differs... Hmm, but then the score would be much worse.

Hmm, the diff at 60: mine lacks `addu at,at,v0`. Since the -0x60 group shifted everything by 4, the line-based diff after the insert/delete may be misaligned. The "60d60" is likely an artifact of the shift (the diff compares line by line after the earlier hunks; if the total line count is equal but content shifted...).

Actually the diff shows: lines 26-30 replaced by 1 line (nop) → mine has 5 lines where target has 1; then lines 33-37 in target are added (5 lines) → net 0. Then "60d60" deletes an addu. So mine has an extra addu somewhere at 60 — probably a shift artifact: after the two hunks the streams realign, so 60d60 is real.

Hmm, mine has an EXTRA `addu at,at,v0` at 60 and target doesn't. And mine's total ins = 79 = target. But we deleted 5 and added 5 → equal counts, then deleting an extra addu makes mine 78? But it says 79 both...

I'm overanalyzing the diff mechanics. Let me directly look at mine's second table chain.

Actually, the key: the score is 4 for these, and 15 for the plain one. The scoring function is what matters, and 0 is the goal.

Given time (16:02, item 4 at 14 min), let me try more do-while placements to see if any hits 0. Specifically the -0x60 group placement is the issue; do-while didn't move it.

Hmm, but why did the score drop from 15 to 4 while the instruction diff is the same? Maybe the score weights the `beq` displacement (target +0x128 vs mine +0x124) — a branch offset difference counts. In p1/q2/q4, the branch offset is 37a4 vs 37a8 → 4 bytes off, because... the -0x60 group placement.

Hmm no, in the plain win.c the branch offset was also different? Let me check: plain win had "beq v1,v0,37a4 | 37a8"? The dt diff for plain showed "14 beq v1,v0,37a4 | 37a8" — yes same.

So why 15 vs 4? Different scoring of the other hunks. Whatever.

Let me now think about the real fix for the delay slot once more, with a new idea: what if the -0x60 group is placed *after* the index chain by making the index chain shorter/earlier? 

Alternative: what if I split the table read so that the -0x60 stores come between the read and the index computation? E.g.:

```
v1 = D_801944F4[idx].f6;   /* load */
...stores...
```
The load's result v1 is used by the index chain (sll v0,v1). So the chain must follow the load.

Idea: compute the index chain FIRST from a different variable, e.g.:
```
s32 idx = ((Unkstruct*)a0)->unk20C;
s32 off = idx * 5 * 4;    /* the sll/addu/sll chain */
v1 = *(u16 *)((u8*)D_801944F4 + off + 6);
```
This splits the chain from the load — the chain would be computed from the unk20C load (not from v1). Then the delay slot of `lh v1,524(s0)`... hmm, the chain still depends on the same load.

Hmm, wait: currently the chain is `v1 = ...; sll v0,v1,2; addu v0,v0,v1; sll v0,v0,2`. The load's result is used immediately by sll. So the delay slot can't take the sll.

If instead I compute `idx` from the load and the multiply chain from idx, it's the same dependency.

OK, what if the delay slot gets filled by an insn that's harmless in the target? The target has a nop. So no.

Time: 16:03. Let me try a couple of "wild" ideas quickly:
r1: put the -0x60 group between `func_8017E664();` and the table read.
r2: put the table read BEFORE `func_8017E664();`.
r3: move the -0x60 group before `func_8017E664();`.

These change the block structure (a call splits blocks!). If the stores are before the call, they're in a different block → no hoisting into the lh delay slot. But the target has them after the call... and after the lh. Hmm, but moving them before the call changes the asm order (stores before the jal).

Hmm no.

r4: What if the table read `v1 = ...` is moved after the stores in source? Then the stores are before the load → can't fill its delay slot. But the target's asm order is: lh, nop, chain, lhu, stores. So the load must come first.

Hmm, BUT: what if the stores come first in source and the compiler reorders them after the load? Unlikely.

r5: What if I read the table TWICE, once into v1 (for the index) and... no.

Let me try r4 and a couple of others, then decide. Actually, let me reconsider the whole thing: maybe the answer is a *different* table-read spelling that yields an extra insn so the delay slot gets the nop. The target has 79 ins and mine 78 in the plain version — one missing insn (the nop). With the do-while, mine has 79 (the do-while adds a note/insn? no, 79 ins in the object means a real nop appeared somewhere).

Hmm! p1/q2/q4 have 79 ins — the same count as the target. Where did the extra insn come from? Maybe a real `nop` appeared in the second chain (the missing addu → a nop instead?). 

Let me look at mine's second chain for q2 (lines 55-65).

Actually, let me look at the whole q2 disassembly to see the state.
