---
ts: 2026-11-06T10:10:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wf1xaRJOxVlaEZg8Nvil
---
All fresh.

Now, before finalizing walls, let me reconsider if there's a known move for expand-void-return that could crack these. The moves catalog has:
- `keepalive | func_80184D28 | MATCH — keepalive replaced by return v0; (s32 fn returned nothing; flow kept v0 sets only via asm use)` — that was the opposite (a s32 function returning nothing).
- `keepalive,pin | func_800D2A24 | WALL expand-void-return`.
- Many WALL expand-void-return.

Could the clones be cracked by making the *function return the value through a call*? No.

Wait, one more idea: the TU's callers cast the function to `s32 (*)(s32,s32)` and use the result. What if the function body ends with a *recursive call* to itself via the cast and returns its value? No, target has no call.

Another idea: what if `rv` is stored into a *parameter* that the caller reads? No.

I'm confident.

But hold on — let me reconsider the possibility that the function definition's return type is not actually "outside the body" in the scorer's splice. The scorer replaces from the definition line to the end. If we provide a body starting with `s32 func_80182420(...)`, the TU's *earlier* declaration? Is there an earlier `extern` for func_80182420 before line 3252? Let me check. The callers declare it later. If there's no earlier declaration, then defining it s32 and later declaring `extern void` → conflict. We saw COMPILE-ERROR. So no.

Unless we could change the *callers* too — forbidden ("callers stay as they are").

OK, walls.

Now let me also double check the clone best v05's body is truly the same function semantics (u16 d changes semantics slightly, but it's a candidate body; for a wall it's just the best score). Fine.

Actually, wait. I want to reconsider the clone score 13 vs 15. The "best" should be a lever-free body. v05 (u16 d) is lever-free. But it changes the semantics (d as u16). That's a real-C move allowed by the catalog ("s16/u8 widths"). OK.

Hmm, but maybe a better lever-free body exists that keeps the value alive via a *real* use that the target ALSO has. Let me re-read the target for the clones once more:
```
lw v1,D_801E1BCC
slt v0,a1,a0
beqz v0,L
slt v0,v1,a1
beqz v0,L2
addiu v1,v1,1440
L2: addiu a1,a1,1440
L: slt v0,a0,v1
beqz v0,L3
slt v0,v1,a1
bnez v0,L4
subu a0,v1,a0
L3: j L5
li v0,-1
L4: slti v0,a0,16
bnez v0,L5
sll v0,a0,1
subu a0,a1,v1
slti v0,a0,16
bnez v0,L5
sll v0,a0,1
li v0,31
L5: jr ra
```
Wait, the target's first branch at index 12-14: `bnez v0,91c; subu a0,v1,a0` — the subu a0 = x - a0 is in the delay slot, then at 91c `slti v0,a0,16`. Then `bnez v0,93c; sll v0,a0,1` — so v0 = a0*2 (the result) and branch to return. Then `subu a0,a1,v1` (d = y - x), `slti v0,a0,16`, `bnez v0,93c; sll v0,a0,1`, `li v0,31`, `93c: jr ra`.

So the target computes the result into v0 on each path. That's the return value. Lever-free void → dead.

One more thought: could we make the value live by making the function *not void* through a `typedef`? No.

OK, walls for clones.

Now let me also think: the task says "Budget 20-30 min wall per item". I've done ~35 min total so far. Each item got a solid variant battery. Good.

Now let me finalize the artifacts.

1. Write win.c for each item = best lever-free body:
   - func_80182420: v05 (u16 d) — copy to win.c
   - func_8018A168: v05
   - func_80189E68: v05
   - func_8017D730: v02
2. Write notes.md per item.
3. Append results.tsv rows (4).
4. Append moves.md lines (4).
5. Write log phase-ends/current/logs/T11.cG27.md.

Wait — the constraint: "write only under .run/P40/T11/G27/ plus appends to .run/P40/T11/moves.md". The LOG path is phase-ends/current/logs/T11.cG27.md — allowed by the brief (LOG). The log is required.

Also "no git, no commit" — so I do NOT commit. The brief's standard coder instructions say commit, but this task explicitly says "no git, no commit". Follow the task brief.

Let me verify v05 is the best for the clones and copy. But wait: is v05's u16 d body "lever-free"? Yes. Let me double check v05's content for any asm/register. It's generated without. Good.

Actually, let me reconsider: should the "best" body be the one with the lowest score even if it's a weird u16? The wall evidence is about the mechanism (expand-void-return), not the score. I'll use v05 (13) as best.

Hmm, but the score 13 comes from u16 d which retains more instructions (23 vs 11) but mismatches on andi/sltiu. Is 13 < 15 meaningful? It's the lowest, so yes per the definition.

Actually, let me try a couple more variants to see if I can get below 13, e.g., `d` as u16 but with the comparisons adjusted, or `d` as `unsigned short` and `x`/`y` u16? v06 (x,y u16) was 31. What about only `d` u16 and `rv` u16? Let me quickly test 3-4 extra:
- d u16, rv u16
- d u16, x s32, y s32, but d init 0
- d u16 and the second d computation `d = y - x` cast

These are marginal. Let me do 4 quick ones to be thorough and maybe find lower.

Actually, the wall best isn't critical. Let me not over-invest. But the brief emphasizes the process; 13 is fine.

Hold on — I realize I should double-check whether v05 is really the *lowest* or whether the 11-ins variants (score 15) are "better" in some sense. The results row asks for `best` = "lowest score of a lever-free body". So 13.

Now, one concern: the generated variants include the `// !FAKE: do-while` in v12; the constraint says do{}while(0) only with that comment. v12 has it. Fine, but v12 isn't chosen.

Let me write the final artifacts.

First, let me copy the best bodies to win.c.

For the clones, v05 body has `u16 d;`. Let me verify v05 content.
