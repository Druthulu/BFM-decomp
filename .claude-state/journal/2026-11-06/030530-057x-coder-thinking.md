---
ts: 2026-11-06T10:05:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tMS5MOQdtOJgPFvEcLbc
---
Now for func_800CD314 lever-free:
- order: 72 74 76 77 73
- 74 conflicts: 72 74 2 4 29 → conflicts with hard regs v0 (2), a0 (4), sp (29). No v1! 
- 74 has no preferences.
- 73 conflicts 72 73 76 77 2 29, prefers 4 (a0).

So r74 (t) conflicts v0, a0, sp. It can't take v0 because v0 is live during r74's life (occupied by another allocno: r75! r75 is not in the order line because... wait r75 is missing from "5 regs to allocate: 72 74 76 77 73". r75 = tb. Why isn't it in the global order? Because r75 is BLOCK-LOCAL (local-alloc handled it) — it's in the lreg dispositions "Register 75 in 2" (v0). Yes! r75 (tb) is local to block 2 and got v0 by local-alloc.

So tb (r75) is a block-local qty assigned v0 by local-alloc BEFORE global-alloc runs. Then global-alloc sees v0 as live/occupied during t's range (because r75 is in v0 and overlaps t), so t (r74) conflicts v0 and gets v1.

In the ORIG (matching) body, tb was pinned to v1, so r75 didn't exist as a local qty; t (r74) got v0 with preference.

So the crux: lever-free, local-alloc assigns tb → v0, and global-alloc then can't give t v0.

To fix: make tb NOT block-local (so it's a global allocno and global-alloc orders it after t), OR make local-alloc assign tb a different reg.

Why is tb block-local but t global? Because t is used in multiple blocks? t is used only in block 2 too... Hmm. The difference: t is "dies in 2 places" (2 defs) while tb has 1 def. Local-alloc handles pseudos local to one block. Both are in block 2 only. So why is t global?

Maybe t is live across the block boundary: t's value at insn 83 (t=unk50) is used by `addiu v0,t,-8` and then `sh v0,10(s0)` at the END of the block? Let me check: the block ends at the call func_80147324(0x8E2)? No.

Actually block 2 might be `if ((cnt & 7) == 0)` body. t = unk50; s0->unkA = t-8; then func_80147324(0x8E2). t dies there. Hmm.

Let me look at the lreg "Register 74 used 4 times across 8 insns in block 2; dies in 2 places" — it says "in block 2" so it's block-local?! But then why is it in the global order line? 

Confusing. Let me look at the -dl output semantics: the .lreg file has "Register 74 used 4 times across 8 insns in block 2; dies in 2 places; GR_REGS or none." — these lines are from global-alloc's `find_reg`? Actually they appear in the .lreg dump BEFORE the RTL, under "Register N used...". Hmm.

Wait, actually in the .lreg dump, the lines "Register 72 used 16 times across 43 insns; crosses 2 calls" etc. are printed by local-alloc? No — those are global-alloc's allocno scan output, which prints to the .lreg file? That doesn't make sense.

Let me just look at the .lreg file's structure: after ";; Function func_800CD314" there are "Register N used..." lines then "Basic block" lines then dispositions then RTL. The "Register N used..." lines are global-alloc's debug (printed during global-alloc to rtl_dump_file = the -dl file? no).

Regardless, the alloc_table parses them as pseudos with refs/live/block. For r74 it says "in block 2" — but alloc_table's regex captured group 4 = block. For r74: "used 4 times across 8 insns in block 2; dies in 2 places" → block=2.

Hmm, if block is 2 and it's in the global order line, maybe "block 2" means the allocno lives only in block 2 but is still a global allocno (local-alloc couldn't take it because it "dies in 2 places"?). Actually local-alloc only handles pseudos that die exactly once per block? A pseudo with multiple sets in a block may be excluded.

So t (2 defs) → global; tb (1 def) → local (v0).

Goal: make tb global too, so global-alloc orders both by priority (t first → v0, tb → v1). How to make tb global? Give tb 2 defs! E.g., initialize tb at declaration: `s32 tb = ...`? That's a def. Or use tb twice.

Simplest real-C move: make tb have two assignments, e.g.:
```
tb = s0->unk54;
s0->unkE = tb;
```
only 1 def. Add a second def that's not dead-code-eliminated. E.g.:
```
tb = 0;           // def 1
tb = s0->unk54;   // def 2
s0->unkE = tb;
```
The first `tb = 0` would be dead and eliminated. Unless used: hmm.

Alternative: make t block-local (1 def) and tb global. If t has 1 def, local-alloc gives t v0 (first), then global tb gets v1. But t needs 2 defs (unk4C and unk50). Could split t into two variables t and t2 (each 1 def) → both block-local. Then local-alloc assigns in priority order: t (unk4C) v0, t2 (unk50) ?, tb (unk54) v1? Let's see: three block-local qtys: t (52-54, 2 refs, life 2, pri 1), t2 (55-59, life 4, 2 refs, pri 0.5), tb (53-58, 2 refs, life 5, pri 0.4). Order by pri desc: t (v0), t2 (v1? free at 55? v0 dead at 54, v1 free) — hmm t2 born at 55, v0 free → t2 gets v0. tb born at 53: at 53, t live (52-54) in v0, so tb → v1. Then t2 at 55: v0 free → v0. Result: t=v0, tb=v1, t2=v0. That matches target (unk4C v0, unk54 v1, unk50 v0)!

But earlier v1.c used a separate `u` (block-scoped) and got score 7 with reordering: lw v1,76; lw a1,84; ... because the declaration `{ s32 u = ...; }` inside the block caused sched1 to reorder. Hmm, v1.c's issue was the loads grouped (lw v1,76; lw a1,84) and stores later. But that was a scheduling artifact.

Wait, v1.c's diff: mine 52 lw v1,76; 53 lw a1,84; 54 -- ; ... 58 sh v1,6; 59 sh a1,14. So sched1 moved both loads up. Target has 52 lw v0,76; 53 lw v1,84; 54 sh v0,6. So target's first store is at 54, mine's at 58.

Why would splitting u change the schedule? In nopin (t reused), the first store (sh t,6) is at 54 right after the tb load. In v1, the store moved later. Possibly because with separate u, the RTL dependencies changed.

Hmm. Maybe instead keep t as one variable (2 defs → global) and make tb global too by giving it 2 defs. 

How to give tb 2 defs naturally? `tb = s0->unk54; s0->unkE = tb;` — one def. What if I write it as:
```
tb = ((Unkstruct_800CD314 *)s0)->unk54;
((Unkstruct_800CD314 *)s0)->unkE = tb;
```
same.

Alternative: make tb a variable used in a way that requires 2 defs, e.g., reuse tb later for something. Hmm.

Or: change t to be block-local by making its second def a different pseudo, and keep the first t with 2 refs. Actually t currently has 2 defs. If I use a nested temp for unk50 (`s32 u = ...` inside a `{}`), t becomes 1 def → local. Then t local (v0), u local (?), tb local (?). This is v1.c which had scheduling issues.

Maybe the scheduling issue in v1 was due to `{ s32 u = ...; ... }` block scoping. Let me try declaring `u` at function scope instead and see if scheduling returns.

Actually, the scheduling difference: in nopin, t is used at both 54 and 59; sched1 keeps the store at 54 because... hmm.

Let me try variants:
- v4: declare `s32 u;` at top, then `u = s0->unk50; s0->unkA = u - 8;` (no block scope).
- v5: keep t for unk4C, use t for unk50 too but insert something.

Let me just try v4.
