---
ts: 2026-11-06T06:28:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WMkEbYco9WoARJsduRZ3
---
Now it's crystal clear.

Target RTL:
- insn 43: `reg 90 = i << 2`
- insn 45: `reg 91 = reg 90 + reg 88` (reg 88 = &D_8018E894)
- insn 47: `reg/v 75 (u) = mem[reg 91]`

Mine (after loop.c):
- insn 43: `reg 90 = i << 2`
- insn 45: `reg 91 = reg 90 + reg 88`
- insn 47: `u = mem[reg 135]` ← replaced with the strength-reduced pointer reg 135.

And loop.c said: "Insn 45: giv reg 91 src reg 73 benefit 4 ... add (reg:SI 88)" and "Insn 47: dest address src reg 73 benefit 5 ... add (reg:SI 88)"; "giv at 45 combined with giv at 47"; "giv at 47 reduced to (reg:SI 135)".

In the target, loop.c's dump says only "Insn 43: giv reg 90 ... benefit 2 used 1 ..." and "giv of insn 43 not worth while, 0 vs 62". So in the target, loop.c did NOT consider insn 45/47 as givs at all!

Why? The difference: in the target, insn 47's MEM address is `(reg:SI 91)` — same as mine's pre-loop.c RTL. Both identical. So loop.c's *giv detection* differed. Hmm, but the RTL shown in the .loop dump is AFTER loop.c. In the target the giv wasn't reduced; in mine it was.

Look at the target's giv list: "Insn 43: giv reg 90 src reg 73 benefit 2 used 1 lifetime 1 replaceable mult 4 add 0". Note: "add 0" — no base. But insn 45 is `reg 91 = reg 90 + reg 88`, which is the actual address with base reg 88. In the target, insn 45 was NOT recorded as a giv.

In mine: "Insn 45: giv reg 91 src reg 73 benefit 4 used 1 lifetime 1 replaceable mult 4 add (reg:SI 88)" and "Insn 47: dest address src reg 73 benefit 5 ...".

So in the target, insn 45 (the plus) wasn't a giv. Why? Because reg 88 (the base) was... hmm. In loop.c, `record_giv` is called for insns in `find_mem_givs` (dest address) and in the main scan.

KEY: in the target, reg 88 is a HARD REGISTER? No... In the target, `&D_8018E894` — with the pins, maybe the address is a hard reg? Hmm, reg 88 in the target dump.

Let me look at what reg 88 is in the target: grep insn 40/41 in the target section.

Actually, the difference might be: in the target, insn 47's MEM is `(reg:SI 91)` and loop.c's find_mem_givs looks at the address `(plus (reg 90) (reg 88))`. Hmm, it should still find it.

Unless... in the target, insns 43/45/47 are in a different order or the block structure differs, e.g., loop.c's `find_mem_givs` requires the address to be computed inside the loop.

Wait — maybe the crucial difference: `used 1` vs the "lifetime". Hmm.

Let me look at the target's .loop dump around insns 40-47 BEFORE loop.c (the dump prints the RTL after optimization). Both show insn 45 as the plus.

Hmm, in the target's giv list I see only insn 43. So loop.c recorded givs at 43 only. In mine, at 43, 45, 47.

What's different? The `reg 88` base. In the target, maybe reg 88 is a *hard reg* or a pseudo that's already... Let me find insn 40/41 in the target dump: what sets reg 88?

Actually, in the target's dump, the "giv" at 43 is `reg 90 = i<<2` with "add 0" — meaning loop.c recorded it as a giv with no base. Then insn 45 (`reg 91 = reg 90 + reg 88`) — for loop.c to record it as a giv, reg 88 must be invariant (it is: &D_8018E894). Hmm, so why not?

AH WAIT. Maybe in the target, reg 88 is a HARD REGISTER because of the pin! `register s32 tmp __asm__("$2")` — no, that's reg $2.

Hmm, let me look at the target's insn that sets reg 88 and the surrounding RTL. Let me print the target's RTL from the start of the function to insn 50.

Hmm, this is a deep rabbit hole. Let me reconsider the time budget: item 2 has been ~20 min. I have w3 (score 5, pins kept) as a PARTIAL:pin candidate. Let me bank that first, then try a couple more ideas for the full MATCH.

Actually — hold on. A key realization: the pins block loop.c's giv reduction. If the mechanism is "reg 88 is a hard reg"... no. Let me test the simplest hypothesis: is it the *launder* that blocks it (w2 = launder kept, pins removed, 106 insns = target count)? Yes! w2 has 106 insns = no hoisting, with the launder kept and no pins.

So EITHER the launder OR the pins block the giv reduction. Both are asm-related. The launder is an `asm` insn; the pins are hard-reg vars.

Since the launder alone (w2) blocks it and gives 106 insns with score 34 (register differences), maybe the residual there is fixable! w2's problem is the pins removed → tmp/hh allocation differs.

Let me look at w2's residual (score 34). If the only issue is which register tmp/hh get, maybe real C can fix it.

Let me check w2's diff.
