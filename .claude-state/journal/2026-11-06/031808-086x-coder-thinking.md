---
ts: 2026-11-06T10:18:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CHheGObYzhgpvSNz3X7J
---
rv = reg 74! refs 6, live 11. Priority 10909 (from the table). 

Allocation order: 75(x, 15000) 78(13333) 74(rv, 10909) 77(9333) 72(6153).

So x (r75) is allocated first: conflicts v0,a1 → takes v1.
Then r78 (13333, prefers a0): takes a0.
Then rv (r74, 10909): conflicts v0,sp → v0 is free! But it took v1? Wait, the final listing has rv in v1. Hmm, x is in v1 and rv is also in v1 — they must not conflict. Since x dies at 4410 and rv is born at 4400... they overlap at 4400-4410? On the path where rv is set at 4400 (li v1,-1), the code jumps to 4424; x is not used after 43f8 on that path. On the fallthrough path, x is used at 4410 while rv isn't set yet.

So x and rv don't overlap. Fine.

But why did rv take v1 instead of v0 (free)? Maybe because v0 is in rv's conflict set (r74 conflicts v0,sp). Yes! The table says r74 "conflicts v0,sp". So rv can't take v0.

Why does rv conflict with v0? Because the slt temps are in v0 where rv is live. Hmm.

If I could remove that conflict, rv would take v0 = target. 

What creates the conflict? rv (r74) is live in blocks where a local temp in v0 is live. Let me see: rv is live from its first set to the end. The first set is in block 8 or 9 (`if (a0 >= x) { rv = -1; }`). Blocks: 8 (insns 64-71), 9 (76-80), 10 (83-90), 11 (95), 12 (106-108).

The slt temps are in blocks 8/9/10. rv's live range: in block 8, `rv = -1` is at the end (goto done). So rv is live-out of block 8 → live at the block end. The slt temp in block 8 (`slt v0,a0,v1`) dies before.

Hmm. Maybe the conflict comes from block 10: `d = x - a0; if (d < 16) rv = d*2;` — the slti temp in v0 at the start of block 10, and rv live-out. If rv were v0, the slti temp (v0) and rv would overlap at the block boundary? The slti temp dies within the block, before rv's set. But global-alloc's conflict computation might be conservative across blocks: rv is live at block 10's start? On the path from block 8 (goto done), no. From block 9 (fallthrough), rv not yet live. So rv's live-in at block 10 is empty.

Hmm, but the table says conflicts v0. Let me look at the conflict computation: global.c marks conflicts between allocnos and hard regs used by *local-alloc'd* pseudos across the allocno's live range. It's computed per insn.

Anyway — the question: can a real-C change remove the v0 conflict? If rv didn't conflict with v0, it would take v0 (target). 

What if rv's first set moves later? E.g., restructure so rv is born after the slt temps. It already is.

Hmm, what if the conflict is due to the *delay slot* scheduling: `li v0,-1` in the delay slot of `j`. The slt temp at 43f0 (`slt v0,v1,a1`) is live at 43f4 (bnez), and rv's set at 4400 (delay of the j at 43fc). Between 43f4 and 4400, the slt temp dies at 43f4. So no overlap.

Hmm, maybe the conflict is with the slt temp in block 10 at 4414 (`slti v0,a0,16`) and rv's set at 4420 (`sll v0,a0,0x1`)? They don't overlap.

I'm not going to resolve this analytically. Let me try to steer rv by restructuring so that rv is born in a block with no v0 temp.

Actually, here's a cleaner idea: what if `rv` is declared as the FIRST variable and assigned in a way that... no.

Alternatively: what if we split rv into two variables (one for the -1 path, one for the d*2 path, one for 31)? Then each is live shorter, and the one that... no, they'd all need to be v0.

Hmm, what if rv is `s32` but the final `rv = 31;` and the branches all assign to a *single* variable... that's the current.

Let me try: make rv's live range shorter by assigning `rv` only at the end:
```
s32 rv;
if (a0 >= x) rv = -1;
else if (x >= y) rv = -1;
else { d = x - a0; if (d < 16) rv = d*2; else { d = y-x; if (d<16) rv = d*2; else rv = 31; } }
```
Same.

What about using `?:`:
```
rv = (a0 >= x) ? -1 : (x >= y) ? -1 : ((d = x - a0) < 16) ? d*2 : ...
```
Different codegen.

Honestly, the residual is a hard register assignment; real-C moves that don't change the instruction sequence are limited to decl order/init position, which I've tried (k0-k4).

Let me try one thing: `s32 rv;` declared but the first *assignment* being the one at the end... no.

OK. Let me now also reconsider: maybe I should test the `keepalive-only` for item 2 and 3 with some moves, but the effort/benefit is low.

DECISION: record all four as PARTIAL:keepalive,pin with win.c = orig (score 0), best = lever-free best, wall tag:
- items 1-3: expand-void-return
- item 4: greg-ref-count

Wait, but hold on. For item 4, is `greg-ref-count` the right tag? The wall description: "global-alloc ref-count priority gives a hot pseudo a different hard reg (G26)". Yes — i1's ref count (with the keepalive) changes the priority so f gets v1. Without the keepalive, f and giv swap. Actually, our residual (lever-free) is f vs giv, and the priority is ref-based. Yes, greg-ref-count fits.

Hmm, but actually, wait: for item 4, could the wall be `lreg-qty-priority`? The tag says "local-alloc qty priority (refs/live length) gives the hard reg to the other pseudo". Our case is global-alloc (the allocno order line). So greg-ref-count.

Now, let me reconsider whether to spend the remaining effort on items 1-3's keepalive-only steering. The result PARTIAL:keepalive would be better than PARTIAL:keepalive,pin. For item 1, we need rv in v0 (it's in v1 due to a v0 conflict). Let me try a couple of moves:

- Move the `rv = -1` assignments into a single shared block (fold with ||), which might change which block rv is born in and its conflict set.
- Reorder the d checks.

Let me generate 6 variants and score with keepalive kept. Quick.

Actually, the `||` fold: `if (a0 >= x || x >= y) { rv = -1; goto done; }` — the target has two separate tests (slt/beqz, slt/bnez). A || fold would generate the same two tests but with a shared target. Might match. Let me try.

Also `if (d < 16) rv = d * 2; else { d = y - x; ... }`.

Let me write gen1b.py.
