---
ts: 2026-11-06T15:31:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4IxxaOQ80qGeQ907gzhh
---
a2's code:
```
5124: bne a2,v0,5130
5128: andi a1,a1,0xffff     <- our vol mask (moved into the delay slot)
512c: li a2,15
5130: sll a2,a2,0x8
5134: li a0,2715
5138: ori a1,a1,0x3000
513c: or a1,a1,a2
5140: jal
5144: andi a1,a1,0xffff     <- the final mask
```
Wait, mine has BOTH andis (5128 and 5144)! So the masks did NOT merge. Mine = 237 ins with an extra andi at 5128 and... but the target has 237 too. So mine is missing an instruction elsewhere: the target has `sll a2,a2,0x8` at 5128 AND at 5130 (two slls: the delay slot 5128 and 5130). Mine has `andi` at 5128, `li a2,15` at 512c, `sll a2,a2,0x8` at 5130 — so mine has ONE sll, the target has TWO.

Target:
```
5124: bne a2,v0,5134
5128: sll a2,a2,0x8       <- the "if (sx==0x10)" fall-through value (sx=... wait)
512c: li a2,15
5130: sll a2,a2,0x8
5134: li a0,2715
```
So the target has `sll a2,a2,0x8` at 5128 (delay slot) and at 5130 (fall-through). That's the `sx = sx << 8;` in-place shift: one in the delay slot (for the non-taken path) and one in the fall-through after `li a2,15`.

Mine: the delay slot is taken by our andi, so the `sll a2,a2,0x8` is only at 5130. But mine also has the andi at 5128. So mine = target + andi - sll = same count.

So the issue: our andi is scheduled into the bne delay slot, displacing the sll that reorg would steal there.

If the andi were placed elsewhere (not the delay slot), reorg would steal the sll into the delay slot and we'd match. The andi's position is determined by sched1/sched2.

Hmm, the andi at 5128 is `a1 = a1 & 0xFFFF` (vol mask). It's placed right after the bne (before li a2,15). The scheduler put it there.

What if the 2nd set is not a mask but something that schedules later? a1 (vol) is used at 5138 (ori). The andi computes a1 early. 

What if the 2nd set is `vol = vol | 0x3000;`? a1's ori got placed at 5128 (delay slot) — same problem.

Hmm, what if we give vol a 2nd set that produces a value in a *different* register (a new temp)? E.g. `vol = vol + 0x10000;` — 2 insns.

What about a 2nd set that's a *copy*: `{ s32 v2 = vol; vol = v2; }` — probably folded.

What if the 2nd set uses the *pan* computation to write vol? e.g., compute the pan into vol then... no, values differ.

Hmm. Let me think about what the launder does: `__asm__("" : "=r"(vol) : "0"(vol))` — a 0-byte insn with a set of vol. In the RTL, it's an insn that sched1 sees as a set of vol with priority 1. Since it's an asm, sched1 gives it priority 1 and it can't be moved much? Actually asm insns are scheduling barriers? No, they can be scheduled but have priority 1.

A plain-C 2nd set creates a real insn (andi/ori) that sched1 can move. That's the difference: the asm's set has a *dependency* but no real computation, and sched1 treats it as an opaque insn with pri 1.

Could we make the 2nd set an insn that sched1 gives priority 1 to? A call? no.

Hmm, what about a set of vol that is *dead* (deleted by flow before sched1)? Then it wouldn't kill the boost at sched1 time... wait, flow runs before sched1? Pass order: cse, combine, flow, ... sched1. The dead set would be deleted by flow before sched1, so no effect. That's why C0414's dead-reset works for cse but not for sched1.

So for sched1, the 2nd set must survive to sched1 (i.e., not be dead). Hence it costs an instruction unless it folds into an existing one.

The a2 andi survives (it's used). The scheduling is the issue.

Let me try to make the 2nd set fold into the *final* andi: if the 2nd set is `vol = vol & 0xFFFF` and the call's mask is removed, we get one andi. The target has the andi at the jal delay slot. If our mask is on vol (before the ori), it must be early. So the andi would be early — mismatch.

What if instead we make the *call arg* not have a final mask, and put the mask on vol? Then there's one andi (on vol) early. The target has the andi late. Different schedule.

Alternatively: keep the call's mask (late andi) and add a 2nd set that folds into the ori: `vol = vol | 0x3000;` then call `(vol | sx) & 0xFFFF`. a1 scored 8: the ori got hoisted to the delay slot (mine[218] ori a1,a1,0x3000 vs target sll). So the ori is early too.

Hmm, in the target, the ori is at 5138 (after the branch target). The launder's asm set apparently keeps the ori late.

What if the 2nd set is a set of vol to a *different* value that folds away? E.g., `vol = vol ^ 0x10000;` — bit 16 masked out → equivalent. It would emit a lui+xor (2 insns) — bad. But maybe gcc folds `x ^ 0x10000` into... no.

What about `vol = vol + 0x10000;`? 2 insns.

What about `vol = vol | 0x10000;`? 2 insns (lui+or).

Hmm, what about `vol = vol & 0xFFFF;` but placed so the andi schedules late? The andi on vol feeds the ori → must be before the ori. In the target, the ori is late (5138), so if our andi is right before the ori, it would be at ~5134. The target has `li a0,2715` at 5134 and `ori` at 5138. So an andi before the ori would add an insn.

Hmm.

What if the 2nd set is a set of a DIFFERENT variable that is *equivalent* to vol in the RTL? No.

OK, let me look at this from the score-2 state: a2 has the andi in the delay slot and the target has the sll. What if we prevent the andi from being scheduled into the delay slot by making it *depend* on something late? E.g., `vol = vol & 0xFFFF;` where the mask constant comes from... no.

What if we place the mask AFTER the pan computation but BEFORE the call? Then it's after the bne? No — the bne is at 5124, and the pan computation ends at 511c. The `if (sx == 0x10)` and `sx << 8` come at 5120-5130. If we put `vol = vol & 0xFFFF;` right before the call (after `sx = sx << 8;`), the andi would be at ~5134-5138 (after the branch), and the delay slot would keep the sll! Let me test that: place the mask just before the call.

But does the 2nd set still kill the birth boost? The birth boost affects the vol quotient's scheduling relative to the pan multiply. A 2nd set anywhere in the function (before the use) makes vol multi-set → sched1 won't boost its birth. So placing it later should still work! Let me test.

c1: insert `vol = vol & 0xFFFF;` just before the call (after `sx = sx << 8;`).
c2: insert `vol = vol | 0x3000;` just before the call and use `(vol | sx) & 0xFFFF`.

Let me test.
