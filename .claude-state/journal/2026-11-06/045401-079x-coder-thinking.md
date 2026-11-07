---
ts: 2026-11-06T11:54:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GezA2vSuyAT68jjsOkCR
---
The hash value `hash` for a MEM includes `hash += (unsigned) MEM;` but not in_struct. `hash_arg_in_struct` is just an output flag stored in `elt->in_struct`. The `lookup` function compares by hash and then `exp_equiv_p`. So in_struct doesn't affect the hash, only `in_struct` used in invalidation.

`lookup` → `hash` match → then iterates `first_same_value` and checks `exp_equiv_p`. Does exp_equiv_p compare MEM_IN_STRUCT_P? Let me check. `exp_equiv_p` is called with `for_eqv_p`... Let me grep MEM_IN_STRUCT_P in exp_equiv_p. Probably not compared.

So in_struct doesn't block forwarding. Confirmed by w9/w10.

OK, so how to make src_elt == 0? The store's src must not be recordable. Options:
- src is a MEM: then cse records the dest with the mem's value? "If we didn't put a REG_EQUAL value or a source into the hash table, there is no point in recording DEST" — src_elt for a MEM src would be the mem's table entry. If the mem value isn't in the table, src_elt = 0.

So if the store source is a memory load that cse didn't track, src_elt could be 0 and the store wouldn't be recorded!

E.g., `*(u8*)(arg0+6) = *(u8*)(arg0+7);` — but our store source is temp_v0.

Hmm, but what if I write the store as `*(u8*)(arg0+6) = (u8)(*(u8*)(arg0+6) - temp_a0);` (compound assignment)? The store's src is `(subreg:QI (minus (zero_extend (mem)) (reg)))`. The mem `(u8*)(arg0+6)` IS in the table (from the initial load at the start). So src_elt would be found (the minus expression?). cse tracks the minus result if it was assigned to a reg.

Hmm.

Actually, for a compound assignment `p[6] -= a;`, the RTL store src is `(plus:QI (mem:QI (arg0+6)) (subreg:QI (minus a)))` or similar. cse looks up this expression. The `(mem:QI)` entry exists (from the initial lbu? no — the initial load was at the very beginning: `lbu v0,6(s0)`). So the mem entry exists. Then the plus expression: cse might not have it in the table (it's new), so src_elt = 0 → store not recorded → the reload stays as lbu!

But the target's store value is v0 (the subtraction result), not a plus. Hmm, combine might transform `(plus (mem) (minus a))` into the same as `(minus (mem) a)` and produce the sb of v0. Let me just test!

Variant: replace
```
temp_v0 = *(u8 *)((u8 *)arg0 + 6) - temp_a0;
temp_v1 = -(temp_v0 & 0xFF);
*(u8 *)((u8 *)arg0 + 6) = (u8)temp_v0;
temp_v0 = *(u8 *)((u8 *)arg0 + 6);
```
with
```
temp_v0 = *(u8 *)((u8 *)arg0 + 6) - temp_a0;
temp_v1 = -(temp_v0 & 0xFF);
*(u8 *)((u8 *)arg0 + 6) = (u8)temp_v0;   // keep
```
Hmm, the compound assignment changes temp_v0's role.

Alternatively, write the store as:
```
*(u8 *)((u8 *)arg0 + 6) = (u8)(*(u8 *)((u8 *)arg0 + 6) - temp_a0);
```
but keep temp_v0 for temp_v1. That would be two reads. Hmm.

Actually, maybe the ORIGINAL source was:
```
temp_a0 = p[5];
temp_v0 = p[6] - temp_a0;
temp_v1 = -(temp_v0 & 0xFF);
p[6] = p[6] - temp_a0;    // compound-ish, recompute
temp_v0 = p[6];
```
No, that recomputes.

Let me think about the target's `sb v0,6(s0)`: the store value is v0, which is the subu result. If the source were a compound assignment, combine would need to CSE the subu. Possible.

Let me just try a variant where the store src is a MEM expression that cse can't record:
```
temp_v0 = *(u8 *)((u8 *)arg0 + 6) - temp_a0;
temp_v1 = -(temp_v0 & 0xFF);
*(u8 *)((u8 *)arg0 + 6) = (u8)(*(u8 *)((u8 *)arg0 + 6) - temp_a0);
temp_v0 = *(u8 *)((u8 *)arg0 + 6);
```
This recomputes p[6]-a but the compiler CSEs it to temp_v0. The store src is the subu result (a reg), which cse records → forwards. Hmm.

What if the store src is a value from a **different variable that isn't in the table**? Like a QImode temp set from temp_v0 via a cast — cse records regs.

Hmm, cse records ALL register values (that's its job). So src_elt == 0 is hard.

Wait, re-read: "If we didn't put a REG_EQUAL value or a source into the hash table, there is no point in recording DEST." — `sets[i].src_elt` is set only if the src expression is found in the table OR was inserted. cse inserts the src into the table as it goes (the src becomes an entry). For a REG src, it's inserted. For a complex src, cse looks it up; if found, src_elt; if not found, src_elt = 0 but the dest is still... hmm, actually cse inserts the src as a new entry too.

Let me look at where src_elt is set. Around line 6909: `sets[i].src_elt = ...`. Let me read.

This is getting deep. Let me try the empirical approach: test a batch of store-src variants and see which gives lbu.

Variants:
- store from a fresh u8 var loaded from a call? no.
- store `(u8)(temp_v0 & 0xFF)`.
- store `(u8)(temp_v0 - 0)`.
- store `(u8)(temp_v0 + 0)`.
- store via a pointer deref `*(u8*)(arg0+6) = *(u8*)((u8*)&temp_v0 + 0);` — reads temp_v0's byte from memory! That's a MEM src (the stack). Would add a stack slot. No.

Hmm.

Let me try: maybe use `(u8)temp_v0` where temp_v0 is declared **volatile**? lever.

OK, let me take stock. Item 2 started at 04:47; it's probably ~05:00 now. Let me check the time and then decide. If it's a WALL, I need 30 tries and 20 min. I've done ~10 tries. Let me continue with a batch.

Let me check the time.
