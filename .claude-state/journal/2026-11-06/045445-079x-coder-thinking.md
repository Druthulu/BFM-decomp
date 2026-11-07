---
ts: 2026-11-06T11:54:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_enoZtGR18AyGIhhMU53L
---
h1 still 13. So the pin isn't the cause.

Time check: item 2 has taken ~15 min. Let me consider the wall option for the launder too. p1 = 13 (barriers kept, launder gone). Not 0, so no PARTIAL there.

Hmm, but maybe I should attack the launder differently: what does the launder do? `__asm__ __volatile__("" : "=r"(pv));` — an asm with an output operand pv (no input). It forces pv to be defined (a new value) at that point, effectively "use" of pv's register. It prevents the compiler from merging pv with later values and forces pv to stay live.

Real C replacement: make pv's value actually used later, e.g. `pv` reused in the second store? But that changes semantics.

Wait — actually the launder's purpose might be to keep pv in $3 across the second store. Hmm.

Alternatively, maybe the real C is: the second tag update reads *p again? Like:
```
*(u32 *)p = (pv & 0xFF000000) | (*(u32 *)D_800AE7BC[D_800B9A02].a & m24);
ot = (u32 *)D_800AE7BC[D_800B9A02].a;
*ot = (*ot & 0xFF000000) | ((u32)p & m24);
```
With pv used only once, why does the target even have pv as a separate var? The launder forces it.

OK, what if the target's else-branch order is: the mask swap is caused by the launder's existence (an asm with an output operand creates a new pseudo). Removing it changes allocation.

Given the difficulty, maybe item 2 is a WALL too: best lever-free = 35 (v0), best partial = 13.

But wait — I should test whether removing barriers one at a time plus other real-C moves can get v0 down. v0 = 35 with 133 insns (6 fewer than target!). The 6 missing insns are the nops! The target has 6 nops in load-delay slots; mine fills them. That's `sched1-load-delay-fill` — a known wall tag.

Let me count: target 139, mine 133 → 6 nops missing. Indeed the diff showed target has `nop` after each lhu and mine fills them with the next group's work.

So the walls here: sched1 fills the load-delay slots that the target leaves as nop. That's precisely walls.txt `sched1-load-delay-fill` (G18 func_80180610). This is likely a WALL.

Given time constraints (item 2 ~20 min), let me do a few more quick probes to be honest about the 30-tries requirement, then record WALL with best=35? Hmm, but "best = lowest score of a lever-free body" — v0 = 35. p1/p2 are partial-lever bodies, not lever-free, so they don't count for `best` (but are useful evidence).

Wait, actually, re-reading: "result MATCH | PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers) | WALL (best = lowest score of a lever-free body)". For WALL, best = lowest lever-free score = 35.

I've scored for item 2: v0, p1, p2 (3) + 7 + 4 + 2 = 16 tries. The brief requires ≥30 scored tries for a WALL. So I need ~14 more scored lever-free candidates.

Let me generate a batch of ~16 lever-free variants (no barriers, no launder) with real-C moves:
- mask vars/inline (mFF/m24)
- ot handling (init at decl, otfirst, split temp)
- declaration order of xl/xr/yl/yr
- pointer reuse: p as u8* vs u32*
- order of the store pairs (0x10/0x08 etc.)
- idx computation placement
- pv/ot variants
- widths (s16 vs u16 for xl..)

Let me build a generator over the v0 base with ~20 variants. Then score. If nothing hits 0, record WALL.

Let me write gen5.py with a template of the lever-free body and knobs. I'll be efficient.

The v0 body (from orig minus barriers/launder) — let me construct it programmatically from orig.c lines minus the 3 lines. Then apply replacements.

Variants:
A. masks: {inline, vars m24+mFF, s32 vars}
B. else ot: {base, otfirst, otinit, otboth}
C. store pair order in the four corner groups: {base (hi,lo), swapped}
D. xl..yr decl: {s16, u16}
E. p type: u8* vs keep.

Let me pick 20 combos.

Actually, the main structural issue is the missing nops (delay slots filled). Real-C moves that stop the scheduler from filling delay slots: nothing obvious. The barrier was the fence. So lever-free is likely a WALL.

Still, let me generate 20 and score to satisfy the tries requirement and check for surprises.

Let me write it compactly.
