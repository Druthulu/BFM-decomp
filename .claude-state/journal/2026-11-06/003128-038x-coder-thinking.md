---
ts: 2026-11-06T07:31:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_56aIGWN7GRfH3TMu8GQq
---
Similar wall. So item1 is likely a WALL: the pin's hard reg $4 reserves a0; lever-free temps take a0. Best lever-free 14.

But wait — the pin is under "other causes" and may stay. Can I keep the pin AND make it effective via real C? The keepalive is what made it effective. Without the asm, the pin is inert. Unless I keep the pin's assignment live through real use. But any real use of keep_a0 would consume it — e.g., `s1 = (s32)keep_a0;`? That's a copy that might be optimized/coalesced. Hmm, that's essentially an identity launder.

Actually, maybe I can keep the pin effective by using `keep_a0` in place of arg0/s0 for a real access. For example:
```
keep_a0 = arg0;
s1 = ((Unkstruct*)keep_a0)->unk34;
```
Then keep_a0 ($4) is used for the load, so it's live until then; but not across the copies. And the if-block uses s0. Not enough.

What if the if-block's decrement uses `keep_a0`:
```
if ((((Unkstruct*)keep_a0)->unk1C -= 1) == -1)
```
Then keep_a0 is live from its def at top across the copies and the call → a0 crosses a call → but a0 is caller-saved; a register-asm var bound to $4 crossing a call is fine (it's a fixed hard reg, the compiler will save/restore? Actually a register variable pinned to $4 crossing a call is unsafe but GCC allows; the call clobbers $4). Hmm, target doesn't save a0. And it would use $4 across the call, but func_800CAF84 might clobber a0 → semantically wrong. Also the target uses s0 for the decrement.

OK, item1 looks like a WALL. But before declaring, let me spend some tries on other real-C moves that might shift a0. The brief requires ≥30 scored tries and ≥20 min for a WALL. We've done ~9 tries. Let me keep going a bit, but efficiently.

Other ideas to reserve a0 in the first block: a pseudo that is live across the copies and allocated to a0 by local-alloc. Since local-alloc assigns caller-saved regs in a block, a local temp defined BEFORE the copies and used AFTER them (but not crossing a call) would be allocated a caller-saved reg, likely a0 (first free). Then the copy temps would take a1-a3! What local value is defined before the copies and used after them, before the call? 

In the target: is there such a value? `v0` (the pointer) is defined before and used through the copies; it's in $2. `s1` defined before, used after the call → callee. `s0` callee.

But what if in the original C, `s1` was NOT used after the call, and instead the if-block recomputed it? No, target uses s1.

What if `v0` were allocated to a0? It's used across the copies; if it got a0, then the copy temps would take v1,a1,a2,a3? But target has v0 = $2. So no.

Wait — maybe `v0` in the target is $2 because local-alloc assigned it $2 as the first quantity (birth earliest). Then the copy temps take v1, a0... no.

Hmm, what if there's a value defined before the copies and used only in the if-block's call setup — `id`? If `id = 0x4B` were moved BEFORE the copies, id would be live across the call → callee-saved. Not a0.

What if `0x8000` is materialized early (before the copies) as a local? It's a constant, not a pseudo.

Let me look at what the `li v0,0x8000` is: the 6th argument (a5=0x8000). It's materialized in the if-block. The `sw v0,20(sp)` stores it.

OK, another thought: maybe the target's first block is NOT one block with the if; maybe `func_800CAF84()` call creates a block boundary? In GCC 2.7, `block_alloc` splits at `CODE_LABEL` and jumps; calls don't split. But `regs_live_at` is computed per block.

I'm fairly convinced this is a hard wall. But let me check whether the a0 reservation could come from the *pin* being kept legitimately: the pin is allowed to stay. The keepalive is the listed kind. What if instead of the asm keepalive, we use the pin variable in a REAL store that the target also has? E.g., target has `sw v0,28(s0)` etc. no.

Actually — wait. Let me re-read the constraint: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added". And "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind."

Hmm the parenthetical "no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm" is a definition of the category, but the row kind is keepalive. I think keeping the pin is allowed. But the pin alone is inert.

Given the evidence (all variants 14, engine search best 14, known wall tag), I'll mark WALL. But let me do more tries to meet the ≥30 tries requirement. Let me try more variants: temp naming, pointer reuse, widths, statement order.

Ideas:
- Name the four loaded values with s32/u32 locals.
- Use `v0 += 0x34` then copy from v0.
- Copy via `Struct16 *` pointers.
- Change s0 to void*.
- Compute `s1` differently.
- Use `*(Struct16*)(s0+0x38) = *(Struct16*)(v0+0x34);` with a named `Struct16 *src`.
- Add `s32 pad;` decl (unused decls are removed).
- Change the if to use `--` prefix.
- Change `id` to a macro.
- Split the if condition.

But none will reserve a0 unless a pseudo occupies it. The only pseudo that could occupy a0 in the first block is one defined before and used after the copies (or across). Let me deliberately introduce such a pseudo with real C that doesn't change instructions: e.g., name the source address computation `s32 a = v0 + 0x34;` used by both copies? Then `a` is live across both copies → allocated a caller-saved reg (maybe a0), and the copy temps shift to a1-a3! But that adds an `addiu` instruction (a = v0+0x34) unless the compiler folds it into the load offsets. If `a = v0 + 0x34` and used as `*(s32*)(a)` and `*(s32*)(a+0x10)`, the compiler may compute `a` in a register (addiu) → extra instruction, score worse. But maybe it folds into offsets and keeps the pseudo. Let's try: 

```
s32 base = v0 + 0x34;
*(Struct16 *)(s0 + 0x38) = *(Struct16 *)base;
*(Struct16 *)(s0 + 0x48) = *(Struct16 *)(base + 0x10);
```
This would keep `base` live across the copies → local-alloc might put it in a0, and the loads could use base as the pointer with offsets (no extra insn if the compiler uses base+0 and base+0x10). Target uses v0 with offsets 0x34..0x50 directly. If base is in a register, the loads would be `lw v1,0(base)` etc. — different bytes. Unless base is coalesced with v0 (same register) → then a0 not reserved. Hmm.

What if we name the SOURCE pointer `s32 *p = (s32 *)(v0 + 0x34);` and the destination `s32 *q = (s32 *)(s0 + 0x38);`? These add addiu instructions unless folded. Target has no addiu for them.

Alternative real-C that creates a live pseudo with no extra instruction: a variable that is a copy of an existing value, e.g. `s32 s1b = s1;` used in the if-block instead of s1. That would coalesce (same value, copy propagation) → same.

A value defined before the copies and used after the call must be callee-saved. Not a0.

A value defined before the copies and used between the copies and the call? The call is immediately after the copies. Nothing there.

So no natural a0 reservation. WALL it is. Let me record and move on, but first do the required ≥30 tries. I have 9. Let me run a broader batch of ~25 generated variants to be honest about the try count. That's cheap (each ~1-2s → ~40s). Let me generate a bunch of plausible real-C permutations.

Actually, the requirement: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". I should genuinely try 30+ distinct bodies. Let me produce ~25 more variants via a generator with combinations, score them, and record. Time check: started 00:20. It's maybe 00:30 now. Need 20 min min → until ~00:45. Let me continue exploring genuinely.

Let me think about the li order too: even if a0 were fixed, the li order would remain (score 2). So both must be fixed. The li order could be fixed by source order: put `id = 0x4B;` before... it already is. Hmm, sched1 birth order: li a0,75 (id def) vs li v0,0x8000 (constant for arg). Actually in the target, li a0,75 comes first. Maybe if `id` is used as an argument EARLIER in the call's arg evaluation? Source order of args: id, s1, 0,0,0,0x8000,0. The 0x8000 is the 6th. Target emits li a0,75 then li v0,0x8000 — matches source order. Mine emits v0 first, then a0. That's sched1 reordering by priority: li a0,75 (id) has a use later in `move a1,s1`? No. Why would sched1 sink li a0,75? Because a0 is... the id value's birth priority. Hmm. If a0 were reserved (live), the id's li would have different scheduling.

Anyway.

Let me try variants with a named source pointer and other tricks, plus combinations. Generate ~25.
