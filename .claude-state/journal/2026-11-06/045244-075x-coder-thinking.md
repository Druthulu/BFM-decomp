---
ts: 2026-11-06T11:52:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sYjQBasweAAb3cwoIDRH
---
Line 1715: in `invalidate_memory`, `|| (nonscalar && p->in_struct)`. So a store that is "nonscalar" invalidates in_struct entries. And line 1951: hash includes MEM_IN_STRUCT_P.

But for the forwarding lookup, the load's mem is hashed with MEM_IN_STRUCT_P included (line 1951 sets hash_arg_in_struct, which affects the hash). So a store to `(mem/s:QI addr)` (scalar) and a load from `(mem/s:QI addr)` with in_struct true would have DIFFERENT hashes → no match → no forwarding!

So if I make the STORE through a struct field (MEM_IN_STRUCT_P true) and the LOAD through a plain pointer (false), or vice versa, the hash differs and cse won't forward! Let me test.

Actually wait, `MEM_IN_STRUCT_P` is set by the front-end for memory refs that are part of a struct. For `((struct B*)arg0)->f6`, the mem is in_struct. For `*(u8*)((u8*)arg0+6)`, not in_struct.

So: store via struct field, load via plain pointer → different hash → no forward. Let me test!

But careful: the mem for the struct field would be `(mem:QI (plus (reg) (const 6)))` with in_struct=1, and the plain load `(mem:QI (plus (reg) (const 6)))` with in_struct=0. The assembly would be the same sb/lbu. 

Let me write w9: store via `((struct B *)arg0)->f6`, load via plain `*(u8 *)`.

I tried the bit-field for both store and load (w7) — both were in_struct, so same hash → forwarded.

Now let me try store in_struct, load scalar. And the reverse.

Let me test both.
