---
ts: 2026-11-06T11:45:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_coQI61Tpkeu9PJffYffv
---
None improved much. v_vol = 10 (34 vs 33 ins) — volatile forced the reload but added insns (lhu+sll/sra as the comment warned). v_reload = 18 (32 ins) — reordering the stores didn't force the reload (still folded), but the store order changed slightly (32 ins).

The core issue remains: a1 and cpy coalesce, and the reload folds. This is the classic opaque-copy WALL.

Let me look at the v_vol disassembly to see if the reload works and what extra insns. And let me think harder about (a) and (b).

Actually, let me reconsider the register-pair mismatches. The diff said "a0->a1 x3, a1->v0 x1". So mine uses a0 where target uses a1 (3 times) — that's the a1 coalescing. And a1->v0 x1 — that's the cpy/load allocation.

For (a): Can I force a1 into $a1 specifically? The target's `move a1,a0` — a1 is in $a1. gcc chose $a1 for the copy. If a1 doesn't coalesce with a0v, gcc's local-alloc would assign a register. To force non-coalescing, I need the copy to be "needed" — e.g., a1 is used while a0v is still live. 

Idea: use a0v in a way after a1 is created. What if the parameter is read twice? E.g., the function does something with a0v after a1... but the target doesn't. However, I could make a0v's value used in the result somehow? No.

Alternative idea: make a1 a HImode-influenced pointer. What if a1 = (s32)(u16)(...) — truncates.

Hmm. Actually — maybe the copy can be forced by making the two values have different modes: a0v is s32 (SImode). If a1 is a `u8 *` (PSImode? On MIPS, pointers are SImode in gcc 2.7.2). So same mode.

What about `long long`? No.

Let me look at how gcc decides to coalesce `a1 = a0v`. In expand, a copy between pseudos of the same mode → register copy, which local-alloc may coalesce. To prevent coalescing, the source must be used after the copy, OR the copy must cross a call, OR there's a mode change.

Since the target keeps the copy, maybe the original source had something that kept a0v live. But the matched source used `a0v + zr` (opaque). So real C needs another way.

Idea: use a0v in the function body naturally. What if the first load is `*(s16 *)(a0v + 0xD0)` (using a0v) and subsequent uses use a1? Then a0v is live at the first load, a1 = a0v copy... but then a0v and a1 overlap. Hmm, that might force a1 separate! Let me think: 
```
a1 = a0v;
v0 = *(s16 *)(a0v + 0xD0);   // uses a0v after a1 defined
```
Then a0v is live after a1 = a0v (the load uses a0v), so a1 can't coalesce with a0v (different values? no, same value). Actually coalescing is allowed even if both are live if they hold the same value? No — coalescing merges two pseudos into one register only if their live ranges don't conflict. If a0v is live after a1=a0v, and a1 is also live, they conflict → no coalesce. 

But this changes the code: the first load would use a0v instead of a1. In the target, the first load uses a1 (`lh v0,208(a1)`). Hmm, so if I use a0v for the first load, it'd be `lh v0,208(a0)` — different from target's `lh v0,208(a1)`. Unless the copy `move a1,a0` then the load uses a1. 

Wait, what if I force a1 separate by using a0v in a harmless way that doesn't affect codegen? Like a comparison that's always true and folded? No, folded away.

Hmm. What if the parameter is used to initialize a2 as well? `a2 = D_80126948` — no relation.

Let me reconsider: maybe I don't need a1 separate. What if I restructure so that the function uses a0v directly (no a1 copy), and the target's `move a1,a0` + `(a1)` accesses are all `(a0)`? Then mine would be 32 ins (one fewer) and all accesses use a0. That's what nopin does (score 18). The target specifically has a1. So to match, I need the copy.

This is exactly the "cse-opaque-copy" wall. Let me check the G07 WALLs: func_80181E64, func_800D0D7C, func_8003DF8C. The latter two/three were later MATCHed with HImode tricks. Let me look at func_80181E64's MATCH: "s16 v and the store reads v: the HImode copy t = v escapes cse, so the target's opaque move s8,v0 survives". So an s16 copy of an s16 value. Here a1 is a pointer.

But maybe I can split the pointer into HImode halves? No.

Let me think about the target more: `move a1,a0` where a0 = a0v (s32 arg). If I could make a1 a different mode... 

What if a1 is declared as a `struct` pointer and the accesses go through a struct? The mode is still SImode.

Hmm, what about making a1 `unsigned` vs a0v `signed`? Both SImode. No.

OK, let me look at the actual register allocation. The target: a0v in $a0 (argument), a1 in $a1. gcc assigned a1 to $a1. If a1 coalesces with a0v, it's in $a0. To get it into $a1 without a0v being live, gcc would still coalesce (copy propagation). Unless the copy is "opaque".

Let me check: does the `+ zr` opaque copy force a1 to $a1 specifically, or just prevent coalescing? The target has `move a1,a0` so a1 is in $a1. If the copy weren't coalesced, local-alloc would pick a register — likely $a1 (next free). So preventing coalescing is enough.

Real C to prevent coalescing: the classic is a mode mismatch. Let me try making a1 a pointer and a0v... hmm.

Wait — what if I introduce a temporary `s32 t = a0v;` and then `a1 = t;`? Two copies. gcc might coalesce both. No.

What if the copy crosses a function call? The function has no calls (leaf). Can't.

Let me look at whether there's a way via `register` without asm: `register u8 *a1;`? The brief says "no `register` vars". So no.

Hmm. What about a `union` copy: 
```
union { s32 i; u8 *p; } u;
u.i = a0v;
a1 = u.p;
```
That's a memory store/load (union in memory) or might be optimized. Probably adds insns.

What about a bitfield extraction that yields the same value? No.

Let me check the moves.md G07 WALL details and any subsequent crack for func_800D0D7C. Let me grep.

Actually, let me reconsider the time. I've spent maybe 30+ min total. Item 2 has had ~10 scored tries. The brief requires a WALL to have ≥20 min and ≥30 scored tries. So I must try at least 30 bodies before declaring WALL. Let me generate a larger batch of variants and score them.

But before brute force, let me understand the levers better. Let me look at v_vol's disassembly (score 10) — maybe with tweaks it can reach 0? v_vol: 34 vs 33 ins. The volatile reload added an extra insn (lhu+sll+sra per comment). Let me see.

Let me dump v_vol. Actually, let me reconsider: the target's reload `lh a0,208(a1)` is a single insn. v_vol produces lhu+sll+sra (3 insns) for a volatile s16? That's odd. Let me check.

Let me get v_vol's diff/disassembly. Use --keep.

Actually, let me first check whether a `volatile s16*` read gives lhu+sll/sra. The comment says yes. So volatile is a dead end for the reload.

For the reload, another idea: use a `struct` member access for the second load vs pointer for the first, hoping cse treats them differently. Or make the first load `u16` and the second `s16` (different modes → cse won't equate; but the target first load is `lh` (s16), so changing to u16 would make it `lhu` — wrong).

Hmm wait, the target first load IS `lh v0,208(a1)` (s16). And d0 reload is `lh a0,208(a1)` (s16). Same.

What if the first access is via `*(s16*)(a1 + 0xD0)` and the second via a struct field `((S*)a1)->f` where f is at 0xD0? get_inner_reference vs expand_expr pointer deref — both produce MEM with same address/mode. cse equates. Unless the struct field has MEM_IN_STRUCT_P set and the pointer deref doesn't → different MEM attrs → cse's `exp_equiv_p` might still consider them different? cse compares memory with `rtx_equal_p` on the address and checks MEM flags? In gcc, cse's `exp_equiv_p` for MEM compares the address and the mode and MEM_VOLATILE_P, but not MEM_IN_STRUCT_P. Hmm, actually it might. Let me check cse.c.

This is getting deep. Let me take a step back and consider the budget. I have 4 items; 2 cracked. Items 2 and 4 remain. Let me time-box item 2.

Let me check the current time.
