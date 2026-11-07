---
ts: 2026-11-06T14:42:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TEfFcdEs2qSehA5aPerY
---
In the post-reorg RTL, the a1 la is insn 94, placed AFTER the OR chain (insns 72,75,77). So the la is late in the post-reorg RTL. But in the .cse2 (pre-sched) it was insn 47 (early). So sched1 or sched2 moved it.

The sched dumps showed the launch order with 47 second, but that must be my misreading. The post-reorg RTL has it at insn 94 (late). So the scheduler DID sink it.

OK, so it's a scheduler sink (sched1 or sched2). The keepalive asm pins it. Real C can't.

Actually, wait — the insn NUMBER 94 vs 47 is the ORIGINAL insn number (the RTL keeps the original insn uids, just reordered in the linked list). The list order is determined by the NEXT/PREV pointers. So insn 94 (originally the a1 la at uid 94?) Hmm, in .cse2 the a1 la was insn 47. But in .dbr it's insn 94. That means the insn was renumbered? No, uids don't change. So maybe insn 47 in .cse2 was a DIFFERENT a1 la (the D_8019DC18 one) and insn 94 is the D_8019DC34 one.

Let me re-check: in .cse2, insn 47 = `(set (reg:SI 5 a1) ...)`. Which symbol? Let me check the .cse2 dump for insn 47's symbol. Earlier I saw insn 47 = `(set (reg:SI 5 a1)`. In the .rtl dump, insn 47 might be D_8019DC18 (the first la). Let me verify: the .rtl grep showed insn 47 `(set (reg:SI 5 a1)`. Let me check its symbol.

Ah, I bet insn 47 is the D_8019DC18 la (before the func_8012B1B4 call), and the D_8019DC34 la is insn 94! Let me verify. In the .dbr dump, insn 47 = `(set (reg:SI 5 a1) (symbol_ref D_8019DC18))`. Yes! So insn 47 is the D_8019DC18 la, NOT the D_8019DC34 one.

So my earlier mapping was wrong. The a1 = D_8019DC34 la is insn 94 (or 96 in orig). Let me redo the analysis:

In .cse2 (c1): insn 47 = D_8019DC18 la (call arg). The D_8019DC34 la is later. Let me find it in .cse2. It's probably insn 94 (as in .dbr). And in orig (with keepalive), the D_8019DC34 la is insn 96 (2 later due to the asm).

So in the sched dumps, the relevant insn is 94 (c1) / 96 (orig). Let me check the sched dump for insn 94/96.

In c1's sched block 3, the insns list included 94 (ref_count 1). And in orig's, 96 (ref_count 1). Let me look at their launch positions.

From c1's sched2 block 3: "ready list at T-4: 86 89 94 96 98, now 98 96 89 86 94" and "T-5: ... 94 ... 77". The launch order T-20..T-1: 45,47,49,52,58,61,64,67,70,72,75,77,94,96,98,86,89,100,104,105. So insn 94 (a1 la) is launched at T-8 (13th). Late-ish.

In orig's sched2: launch order T-21..T-1: 45,47,49,52,55,57,60,63,66,69,72,74,77,79,88,91,96,98,100,102,106,107. So insn 96 (a1 la) is at T-6 (17th). Also late-ish.

Hmm, both late in sched2. But the target .s has the la early (2nd). So sched2 doesn't put it early in either. So the .s order doesn't match sched2's T-order interpretation.

I give up on mapping the dumps. The empirical fact: target has the la early, c1 has it late, and the keepalive pins it.

Let me record the WALL. The pass: likely sched1 (the keepalive's data dependency pins the la). Let me use the tag `sched1-asm-barrier-order` or a new descriptive tag. Let me check walls.txt for existing tags to pick the closest. The tags: sched1-birth-order, sched1-load-order, sched1-load-delay-fill, sched2-store-hoist. 

I'll use `sched1-birth-order` since the mechanism is sched1 ordering an insn's birth. Actually, the la's "birth" (placement) is pinned by the asm. `sched1-birth-order` is described as "sched1 orders two independent insn births opposite to source; reorder moves the other". Not quite, but close.

Hmm, let me use a new tag `sched1-la-sink`: "the la's only consumer is the later call; without the keepalive's empty asm (its early consumer) sched sinks the la to the call". That's precise.

Let me record the WALL:
- dir: func_80183130__ov_SC04_004_jr_8017AE2C
- file: src/ov_SC04_004/ov_SC04_004_jr_8017AE2C.c
- func: func_80183130
- kinds: keepalive
- result: WALL
- best: 4
- tries: 32
- wall: sched1-la-sink
- evidence: "keepalive's empty asm is a1's only early consumer; without it sched sinks the &D_8019DC34 la from insn 22 to 31 (51=51 ins, ORDER); 15 stmt/decl reorders all 4"

Let me count evidence chars: ~150. Need ≤140. Shorten: "keepalive's empty asm is a1's only early consumer; without it sched sinks the &D_8019DC34 la to the call (22->31, 51=51, ORDER); 15 reorders all 4" — ~145. Trim more: "empty asm is a1's only early consumer; without it sched sinks the &D_8019DC34 la to the call (pos 22->31, 51=51, ORDER); 15 reorders all 4" — ~135. Good.

Let me write the notes and results row, and append to moves.md.

Let me also clean up the dumps (_d4, _dc1) to free disk.

Let me first verify the final win.c for this item is c1 (the lever-free body). Actually, the item's "win.c" should be the lever-free body. Since it's a WALL, there's no win.c with score 0. The brief says "each MATCH/PARTIAL has its win.c scoring 0". For WALL, no win.c needed. But the DONE WHEN says "every item has exactly one results.tsv row". So I just need the row.

Wait, but I created a win.c earlier (the baseline orig copy, score 0 with keepalive). That's misleading. Let me remove it or leave it? The brief says "each MATCH/PARTIAL has its win.c scoring 0". For a WALL, win.c isn't required. Let me remove the baseline win.c (it contains the keepalive, which is not lever-free). Actually, let me leave the best lever-free body as win.c? The brief for WALL: "best = lowest score of a lever-free body". Let me set win.c = c1 (the best lever-free body, score 4) so the record is clear. Let me copy c1 to win.c.

Hmm, but then win.c scores 4, not 0. That's fine for a WALL (the brief only requires win.c score 0 for MATCH/PARTIAL). Let me put the best lever-free body as win.c for the record.

Let me do that and record.

Actually, let me double check the time budget: the brief says 20-30 min per item, past 30 min stop and record a wall. I'm well past 30 min on this item. Let me record the wall now and move on.

Let me write the results row and notes.
