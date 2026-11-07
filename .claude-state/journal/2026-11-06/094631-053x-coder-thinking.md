---
ts: 2026-11-06T16:46:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2QtbpL4fKr2cbjVV4CLs
---
Score 6, a pure register swap: mine has h in v0 and t in v1; target has h in v1 ($3) and t in v0.

Target:
- t = s0 << 1 → v0
- h = lh → v1
- h << 4 → v1
- h<<4 + s2 → v1
- t + that → v0
- lhu 0(v0) → a1

Mine:
- t → v1
- h → v0
- h<<4 → v0
- +s2 → v0
- t(v1) + v0 → v1
- lhu 0(v1)

So I need to swap t and h's registers: h=$3, t=$2.

This is a local-alloc qty priority/order issue. Both t and h are block-local, single-block, defined and used once or twice.

Let me think about local-alloc allocation:
- t: defined by sll, used in the addu. 2 refs.
- h: defined by lh, used in sll. 2 refs.
Priorities depend on life lengths and ref counts. Currently t gets v1, h gets v0? Wait, mine: t=v1, h=v0. Target: t=v0, h=v1.

Hmm, interesting. Why does t get v1 in mine? The allocation order: t's qty... Let me think about the tie loop:
- The sll `v1 = s0 << 1` (t) — output t, input s0 (dies? s0 is used later at `s0 = s0 + 1`, so not dead).
- The lh `v0 = lh(...)` (h) — output h.
- `sll v0,v0,4` — h = h << 4 (in-place, tied).
- `addu v0,v0,s2` — h = h + s2 (in-place).
- `addu v1,v1,v0` — t = t + h (tied in-place, h dies).
- `lhu a1,0(v1)` — uses t.

In the target: t=v0, h=v1. In mine: t=v1, h=v0. Just a swap.

How to influence? The allocation order/priority. Both are defined early in the block. t's def comes first (source order), h's second. qty numbers: t < h. If priorities tie, the lower qty number wins → t gets the first free reg (v0). But mine gave t=v1 and h=v0. So priorities differ.

Let me compute:
- t: def at insn 2 (sll), last use at insn 6 (addu). n_refs = 2. life = 6-2 = 4.
- h: def at insn 3 (lh), last use at insn 5 (addu) — wait, h is used in the sll (h<<4) at insn 4 and the addu at 5. n_refs = 3? (def + 2 uses). Hmm.

Priorities: pri = floor_log2(nrefs)*nrefs*size/(death-birth)*10000.
- t: floor_log2(2)=1, 1*2*4/4 = 2 → 20000.
- h: floor_log2(3)=1, 1*3*4/(5-3=2) = 6 → 60000.

So h has higher priority → allocated first → gets v0 (first free). Then t → v1. That's MINE. Target wants h=v1.

So I need to flip the priority: make t higher than h, or make h's priority lower.

Target has h=$3 (v1), t=$2 (v0). So t allocated first.

Ways:
- Make h's live range longer (lower priority): pri = nrefs/(life). Longer life → lower pri.
- Make t's live range shorter or refs more.

But I can't change the code's semantics; I can change the C spelling:
- Statement order: if I move `h = ...` before `t = s0 << 1`, then h's qty number < t's; but priority still dominates.
- Change h's type: if h is `s16` instead of `int`, the qty size might change? HImode qty size is 1 vs SImode 4? qty_size is in words: HImode = 1? Actually qty_size = mode size in words? Let me check: `qty_size[q]` is the size in words (GET_MODE_SIZE / UNITS_PER_WORD), min 1? If h is HImode, qty_size = 1? That would LOWER h's priority (size factor 1 vs 4). Then t (SImode, size 4) would beat h!

But wait: if h is s16, then `h << 4` requires sign extension (sll/sra) — extra insns. Unless h is u16 and the shift... the target has `lh` (sign-extended load) then `sll v1,v1,0x4`. If h were s16, gcc would use `lh` then `sll` — but h is used as `(h << 4)`, so it needs sign extension of the 16-bit value: `lh` already sign-extends to 32 bits, so h in a register is a full 32-bit sign-extended value. gcc models HImode values in registers with the upper bits... for `h << 4` where h is s16, gcc must sign-extend to SImode: `sll/sra` after the lh? Actually `lh` loads sign-extended, so gcc knows the value is sign-extended if the load pattern says so (sign_extend:SI (mem:HI)). The RTL for `*(s16*)` is `(sign_extend:SI (mem:HI ...))` — an SImode value! So h as s16 in C assigned from a s16 load: the tree type is s16 (short), and `h << 4` promotes to int; gcc would need to sign-extend h (the short) — but it knows h came from a sign-extending load, so combine can fold the extension into the load → `lh`. So the RTL might be identical.

Hmm, but the qty for h would be HImode with size 1, lowering priority. Worth testing!

Alternatively, make t's priority higher: t's life is short. If I reorder the statements so t's def is later (closer to its use), t's priority rises. E.g., move `t = s0 << 1;` after the h load and h<<4? But that changes the instruction order in the target (the target has t's sll at 2734 before the lh at 2738). If the source order changes, the RTL order changes and sched1 might reorder back? Risky.

Alternatively, reorder: `h = ...; a = s0<<9; t = s0<<1;`? The target order is: sll a0,s0,9; sll v0,s0,1; lh v1. So t's def is before h's. Keep that.

So: change h's type to s16 (or u16) to lower its qty priority. Let me test:
- `s16 h;` (assignment from *(s16*) is exact).
- `u16 h;` (assignment from s16 → conversion; gcc would zero-extend? h = *(s16*) then h<<4: h is u16, the load is sign-extended s16, assigned to u16 → truncation, then <<4 promotes to int → zero-extend h. That would add insns.)

So `s16 h` is the natural one. Let me test both s16 and int with different decl orders.

Also: `s32 h` (int) is current.

Other ideas:
- Change t's type to make it higher priority? t = s0 << 1 is SImode.
- Change s0's type? s0 is the counter; target s0=$16.

- Statement order: move `s0 = s0 + 1;` before the h load? The target has the lh at 2738 then addiu s0 at 273c. So the order is: lh, addiu s0. Hmm, the C has `h = *(s16*)(...); s0 = s0 + 1;`. Keep.

- What about making h's use appear later (longer life)? h's life is 3 insns (lh, sll, addu). If I add another use of h later, life extends, priority drops. But that changes code.

Let me try s16 h first.

Also, another thought: the target's h=$3 and t=$2. local-alloc's first free reg order: which reg does it pick first for the highest-priority qty? Apparently v0 ($2). So h (highest pri) gets $2 in mine. To get t first, t must outrank h.

With h as s16 (HImode), qty_size = 1? Let me check qty_size semantics: in local-alloc, `qty_size[q] = (GET_MODE_SIZE (GET_MODE (reg)) + UNITS_PER_WORD - 1) / UNITS_PER_WORD`? Something like that. For HImode: (2+3)/4 = 1. For SImode: 1. Hmm, both 1! So no difference. Let me check the code.

Let me grep qty_size assignment in local-alloc.c.
