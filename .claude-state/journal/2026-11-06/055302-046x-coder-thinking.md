---
ts: 2026-11-06T12:53:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VidPNtCn3m3nXJXdjj8q
---
v6/v7 compile errors — C89: declarations after statements (the `u32 c64` mid-block). Right, C89. Need to declare at the top of the block.

Let me fix: declare c64 in the declarations section of the inner block (where j,k,y,eight,pb,m24,mhi,vsum are), and assign it where needed.

Actually, the declaration position affects nothing for codegen except order; the *assignment* position matters.

Let me redo v6/v7 as:
v6: declare `u32 c64;` in decls, and `c64 = 0x64808080;` before the y store.
v7: `c64 = 0x64808080;` after the y store.

Also v10 (swap 0x78 and 0x64808080 stores) gives the same 2 — no change.

Let me also think about other levers:
- make `eight` be used... no.

Another idea: the target's join block begins with the sh. What if the block's *first* insn in source were something else, and the lui/ori hoist is limited by a dependence on the incoming edge? Hmm.

Idea: the branch into the join block. The join block is entered from the arm0 `j 62c` (with delay slot `addiu v0,v0,-2`) and from the else fall-through. In target, the sh is the first insn at 62c. In mine, also the sh at 141? No — mine has the lui/ori at 141-142 then sh at 143.

Interesting: in mine the block order is lui, ori, sh, ... So sched placed the lui/ori at the very head of the block.

What if I make the lui/ori depend on a value computed in the arms (e.g., y)? Then they couldn't be hoisted above the sh. E.g., if the constant build used a variable that is live from the arm... but that's a fake identity.

Hmm, what about this: the target's constant is built into v1, and v1 is *also* used as a temp in the arms? In the arm0 path, v0 = lhu, then `addiu v0,v0,-2`. v1 isn't used. In the join, v1 = 0x6480. At 166 `lw v1,0(s0)`.

What if I split the 0x4 store into two statements: `out[4] = 0x80; out[5] = 0x80; ...` no, that changes instructions.

What about writing the 0x4 store as two 16-bit stores? no.

New idea: maybe the sched hoist is limited by register pressure? No, sched1 (before reload) doesn't consider pressure... Actually sched1 does use REG_N_REFS? no.

Let me look at the ready-list tie-break more carefully, since the fix may be a source-order tweak. In sched.c's `schedule_block`, the loop picks `ready[0]`. The ready list is kept sorted by priority (and by `insn_unit`?). For equal priority, `priority` sorting is stable with the insertion order.

`make_ready_list`: walks from `tail` backward and adds insns whose successors are all scheduled. So the ready array order for equal priorities: the first added is the one nearest the end of the block.

When an insn is scheduled, its predecessors may become ready and are added. The `add_to_ready`/queue is sorted by priority; ties: `queue_insn`/`ready_add` — let me look at how ties are ordered (line 2370-2420).

Actually, maybe simpler: in mine, the sh is placed at 143 and lui/ori at 141-142. That means when the scheduler decided, it placed lui/ori *earlier* (i.e., they were scheduled later in the backward pass). Hmm, in backward scheduling, the insns placed at the *end* of the block are scheduled first. So in mine, the sh was scheduled before the lui/ori (sh placed later in the final order). In target, the sh was scheduled after (placed earlier).

So in mine the sh was *ready* before the lui/ori. The sh's readiness: it has no successors → ready from the start. Hmm, then it would be scheduled early in the backward pass = placed late. But it's placed at 143 which is early in the block. Confusing.

Let me stop the theory and be empirical, with a wider set of real-C variants. Options remaining:

A) Make y a u16/s16 variable computed differently.
B) Move the y store into the arms (CFG change) — try it; maybe the join block then starts with the lui/ori and the sh is in each arm; the target's single sh at the join would be wrong, but let's see the actual score.
C) Split the 0x4 store into a store of a *variable* assigned from a variable.
D) Reorder the whole tail.
E) Change `y` to be stored via `*(s16*)&out[0xA]`... same.
F) Use a do-while around the *constant store* only (v4 gave 6).
G) Use `do { } while(0)` around the y store AND put the constant store inside the same do-while (v2 gave 2).
H) Make the vsum stores move... no.

Let me reconsider the target: maybe the target's order is "source order" and the sched did NOT reorder at all in the join block. Then the target's join block starts with the sh. Mine's join block starts with lui/ori — the only difference.

So: can I prevent the sched from hoisting the lui/ori to the block head? A dependence on the block's entry would do it: if the constant build depended on a value only available after the sh (e.g. y), it couldn't be hoisted above. Is there a legitimate way to make the 0x64808080 store depend on y? No.

BUT: what about making the lui/ori depend on the *store address*? The address is out+0x4, computed from a1. The sh uses a1 too. No dependence.

What if the constant were stored to an address computed from the sh's address? e.g. `*(u32 *)((u8 *)out + 0x4)` vs the sh at out+0xA. Same base.

Hmm what if I change the 0x4 store to use a different base expression that requires a computation born after the sh? Like `out[1] = 0x64808080;` (out is s32*). Target: sw v1,-14(a1) where a1 = out+0x12, so -14 = out+4 = out[1]. Same.

What if the code writes `*(u32 *)((u8 *)out + 0x4) = 0x64808080;` but with `out` being a `s32 *`... same.

OK, different approach: what if we accept the hoist but make the *sh* also hoist above the lui/ori? If the sh were scheduled before (in final order) — target has sh at 141 and lui at 142. So we need the sh one slot earlier, i.e. the sched should place the sh before the lui/ori. That's exactly the target.

So we need the sh to win the tie. Ties in the ready list are broken by insertion order. Insertion happens when an insn becomes ready. The sh becomes ready at the start (no successors). The lui becomes ready when its successor (ori) is scheduled... wait no: readiness = all *successors* scheduled? For the lui, its successor is the ori (LOG_LINKS of ori contain lui). So the lui becomes ready when the ori is scheduled.

Hmm, but the ori becomes ready when the sw(-14) is scheduled. So the chain: sw scheduled → ori ready → ori scheduled → lui ready → lui scheduled.

Meanwhile the sh is ready from the start but is scheduled at some point.

In target the final order is sh, lui, ori (positions 141,142,143). Since backward: ori scheduled first (placed last at 143), then lui (142), then sh (141). So the sh was scheduled AFTER the lui — meaning the sh stayed ready longer than the lui. Why? Because the scheduler picks the highest priority; maybe the sh had a lower priority? All priority 1... but wait, `adjust_priority` and the delay-slot handling can boost priorities. Line 3898: "there must be a delay. Give INSN high enough priority that..." — that's for delay slots.

Hmm, in mine the order is lui, ori, sh (141,142,143). So the sh was scheduled FIRST (placed at 143 = latest), then ori, then lui. So the sh was picked before the ori. In target the ori was picked before the sh.

So: when both the sh and the ori are ready, target picks ori, mine picks sh. The ready list order: `make_ready_list` adds insns from the end backward. The sw(-14) is at the end of the block region... the sh is earlier in source. Both ready initially. If the ready list is ordered by descending uid (later first), the ori/sw come first... but the ori isn't ready initially.

OK here's the thing: after the sw(-14) is scheduled, the ori becomes ready and is added. The ready list is a priority queue; insertion at equal priority goes... `queue_insn` inserts after existing equal-priority insns? If it inserts at the *end* of the equal-priority run, then the sh (already there) stays ahead → mine's behavior (sh picked first). In target, the ori was picked first → the ori was inserted at the *front* of the equal-priority run? 

The difference between target and mine could be the ORDER of scheduling the sw(-14) vs the sh. Hmm.

Honestly, let me try the empirical set and see. Let me also try moving the y store's statement *later* in source (after the 0x400 store) — v9 gave 12, no.

Let me try: 
v12: the whole join block wrapped in `do { ... } while (0)` (v3 gave 21 — too many ins).
v13: y store inside a do-while + the constant store inside another do-while (v4 gave 6).

Hmm, v4 gave 6 — worse.

Let me look at what v4/v3 did — maybe informative. v4: two do-whiles → 203 ins, score 6. So the do-while around the y store alone does nothing (v1 = 2), but wrapping the constant store changes things.

Let me instead try: make the constant store's do-while contain both the 0x400 store and the 0x78 store... 

Actually, let me try a different real-C idea: use a *pointer* variable for the constant store's address that is initialized after the sh. Like:

```
u8 *p4;
...
p4 = (u8*)out + 0x4;
*(u32*)p4 = 0x64808080;
```
The address computation `addiu p4, a1, -14` would be born after the sh in source. If the lui/ori can't be hoisted above the `addiu` (no dependence), they still can. Hmm, but the address temp's live range starts at the addiu; local-alloc might assign it a register... The target has `sw v1,-14(a1)` — an immediate offset, no address temp. So a pointer temp would add an insn. Bad.

Let me think about "birth" more: the notes mention "sched1-birth-boost": "birthing-insn priority boost against a local-alloc constant". There's a concept where an insn that sets a register gets a priority boost (sched.c line ~3898?). Let me read around 3890.
