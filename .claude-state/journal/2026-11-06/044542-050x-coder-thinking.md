---
ts: 2026-11-06T11:45:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_U1r9e0OJ3HVgZA1GZ5tJ
---
Line 261 and 268 are relevant:
- `barrier | func_8014B944 | MATCH: do-while on the a1-free ifs (keeps load after store AND a1 refs 7 so base->s0/a1->s1) + union-member read of EA6 forces the cse reload; 141/141 (G21)` — "union-member read forces the cse reload"!
- `barrier | func_8014FE60 | MATCH: the a[2]/b[2] comparison reads through a struct member (in-struct MEM) so cse does not forward the load into the scalar stores; the stores re-load like the target`
- `barrier | func_80175820 | MATCH — struct-member u16 load sq->v for D_800B9A02 (in_struct): the nonscalar ptr[2] store invalidates it, cse re-loads`

So the trick to force a cse reload is to read through a **struct member** (MEM_IN_STRUCT) or a **union member**. Because cse's hashing distinguishes in_struct memory (hash_arg_in_struct), so a scalar read and an in-struct read of the same address are NOT equated. Let me check: cse.c hashes MEM with MEM_IN_STRUCT_P separately (hash_arg_in_struct). And exp_equiv_p for MEM — let me check if it compares MEM_IN_STRUCT_P.

Let me look at exp_equiv_p's MEM case and the hashing.

Line 1943/1951/1971 in hash_rtx: if MEM_VOLATILE_P skip; if MEM_IN_STRUCT_P set hash_arg_in_struct=1.

So a MEM with MEM_IN_STRUCT_P set is hashed differently. If the first load is scalar (no in_struct) and the reload is in_struct (struct member), they hash differently → cse won't equate → reload survives!

So: make the ELSE reload read through a struct member. E.g., define a struct type with a field at 0xD0, and read `((S*)a1)->f0d0`. The first read stays a plain pointer deref. 

Similarly, the comment in the original says "Re-declaring D_801151D0 as a one-field struct..." for the other function. Here, for the reload, use a struct member read.

But I need the struct type. The TU might already have a struct with fields at 0xD0. Let me check what types exist. `Unkstruct_800B5CB8` has fields unk70, unk1C, etc. Let me check if it has 0xD0/0xCE/0xCC/0xDC. The function uses `Unkstruct_80126948` for a2. Let me look for a struct type covering these offsets. Let me grep the TU for a struct with 0xD0.

Actually, I can define a local struct inside the function? C allows `struct { ... }` but not a tag usable... Actually I can do `((struct { char pad[0xD0]; s16 f; } *)a1)->f`. That's an anonymous struct type defined in the cast. Valid C. The field access yields MEM_IN_STRUCT_P.

But wait — does a cast to an anonymous struct pointer and field access produce MEM_IN_STRUCT? Yes, component ref.

Let me try: in the else, replace `d0 = *(s16 *)(a1 + 0xD0);` with `d0 = ((struct { u8 p[0xD0]; s16 v; } *)a1)->v;`. Hmm, but the struct size/offset: p[0xD0] then v at 0xD0. Good.

But there's a subtlety: MEM_IN_STRUCT_P is set for the field. The load would be `lh a0,208(a1)`. And cse hashes it as in_struct, distinct from the scalar load at the top. 

But also the top load: source `if (*(s16 *)(a1 + 0xD0) < 0x28)`. That's a scalar MEM (no in_struct). Good. So they differ.

Wait, but the first load is used twice: in the compare and in `v0 = *(s16*)(a1+0xD0)+8`. Those two are both scalar → cse folds to one. Good.

Now for (a) a1 coalescing and (b) cpy coalescing. Let me tackle (b) with the HImode trick: `cpy` as s16. But v_cpy16 didn't help (score 18). Why? Maybe because `cpy = d0` where d0 is s32 and cpy is s16 — the assignment truncates (s16), which is a mode change; gcc would emit a sign-extend, not a plain copy. And the target's cpy is s32 (`addiu v0,v1,2` where v1 = d0). Hmm.

Actually the target insn 16 `move v1,a0` is `cpy = d0` (both s32). To keep this copy, I need cpy as a separate s32 pseudo. The HImode trick works for s16 values because the HImode copy `t = v` (both s16) escapes cse. But here d0 is s16 (loaded as s16) and cpy is s32. If I make cpy s16, then `cpy = d0` is s16=s16 (HImode copy, escapes cse) and `v0 = cpy + 2` sign-extends cpy. But the target does `addiu v0,v1,2` where v1 = d0 (already s32-extended). Hmm.

Let me just test the struct-member reload first (that's the documented trick) and see the score. Then handle the copies.

Actually, for (a) and (b), maybe the struct trick and a do-while can help, but the copies are the hard part. Let me look at func_8014B944's win if available. Let me check if its shard dir exists under .run/P40/T11. Let me find it.

Actually, let me just try the struct reload and a few copy variants and score.

Let me also reconsider (a): the target `move a1,a0`. What if a1 is a `u8 *` and the accesses use it — v_a1ptr scored 18 (no change). So pointer type doesn't prevent coalescing.

What if a1 is read through a struct in the top load too? No.

Hmm, let me look at func_8014B944's win for the "a1 refs 7 so base->s0/a1->s1" — that's about making a1 have more refs so it gets a different register. Interesting: "do-while on the a1-free ifs (keeps load after store AND a1 refs 7 so base->s0/a1->s1)". So they increased a1's ref count via a do-while to change register allocation. But that's a different structure.

For our case, a1 is a copy of a0v. The issue is coalescing, not ref count. Actually, "a1 refs 7 so base->s0/a1->s1" suggests a1 is a separate variable that needs refs to win a register. In our target, a1 IS a separate variable (copy of a0). Maybe if a1 has more refs, local-alloc won't coalesce? No, coalescing is separate from ref count.

Wait — actually, maybe the `+ zr` doesn't prevent coalescing; maybe it does something else. Let me re-read the comment: "The entry `addu $a1,$a0,$zero` is the RC-12 `+ zr` opaque copy (§249 point 3) with BOTH ends pinned (the §249 addendum: an unopposed destination-only pin lets copy-preference drag the source onto the same register)." So the pins on both a0v (the parameter $a0?) and a1 ($a1) force the copy to stay. Hmm, "BOTH ends pinned" — the source a0v is $a0 (argument) and the destination a1 is $a1? But the source `a0v` isn't pinned in the source. Wait, `register s32 zr __asm__("$0")` is the zr pin. `a1 = a0v + zr`. The "+ zr" is `(plus a0v (reg 0))`, which is an opaque copy because (reg 0) isn't a normal register. So a1 = a0v + 0 is a genuine add → forces a copy. The "both ends pinned" refers to the zr pin and... hmm, the destination a1 is a normal pseudo.

OK regardless: `+ zr` creates an opaque `addiu a1,a0,0`? But the target shows `move a1,a0` (which is `addu a1,a0,zero` or `or a1,a0,zero`). An `addiu a1,a0,0` would assemble to `addiu a1,a0,0`, not `move`. So the target's `move a1,a0` is a plain register copy, meaning the opaque copy resolved to a plain move. So `a1 = a0v + zr` where zr is reg 0 → the add folds to a copy → `move a1,a0`. And it's opaque enough to not be coalesced.

So real C to get `move a1,a0` without coalescing: need an opaque copy. Hmm.

Let me look at the HImode trick more concretely: for s16 values, `t = v` where both are HImode escapes cse. Why? Because cse treats HImode copies differently? Or because the value is sign-extended? Actually moves.md says "the HImode copy t = v escapes cse equivalence class". 

For a pointer, maybe I can route through an HImode intermediate that doesn't lose data? The pointer is 32-bit; HImode is 16-bit. Can't.

What about DImode? `long long` copy? Overkill.

Let me look at the actual G07 WALL for func_80181E64 and its MATCH to understand the exact mechanism. Let me read the moves line 203 fully: "pin | func_80181E64 | MATCH — s16 v and the store reads v: the HImode copy t = v escapes cse, so the target's opaque move s8,v0 survives (G07; supersedes the WALL line above)". So the value v was s16, and the copy t=v (both s16) survived. For our pointer (SImode), an HImode copy is impossible.

Hmm. So (a) might be a genuine wall for SImode.

But wait — maybe there's another way: the target's `move a1,a0` could be reproduced if a1 is used as a HImode value somewhere, forcing a mode... no.

Let me reconsider: maybe a1 doesn't need to be a copy. What if I use a0v directly but rename via a cast that changes the mode? Like `(u8*)a0v` — same SImode.

Alternatively, what if the function is re-derived so the parameter is loaded from the stack or something? No.

Let me look at func_800D0D7C (WALL cse-opaque-copy) and func_8003DF8C — did they get cracked? func_8003DF8C MATCH (u16 i/j). func_800D0D7C — only WALL. So SImode-ish opaque copies remained walls.

Let me focus: the reload (c) is crackable with a struct member. Let me test that. If the score drops a lot, maybe the copies become the only residual and I can decide WALL vs more effort.

Let me test:
- v_struct_reload: else d0 read via anonymous struct member.
- v_struct_reload + cpy variants.

Let me also try: maybe making `d0` read through the struct AND the top read scalar fixes the reload; and maybe the copies then... no, copies are separate.

Let me test the struct reload.

Also, I realize: for (b) cpy = d0, maybe if d0 is read via a struct member (in_struct) and cpy = d0, then cpy is a copy of an in_struct load. Would that keep the copy? Possibly the in_struct attribute propagates? Unlikely.

Let me just test v_struct_reload and see the diff. Write gen2.py.

Struct cast: `((struct { u8 p[0xD0]; s16 v; } *)a1)->v`. Let me use that.

Actually, gcc 2.7.2 might not like an anonymous struct in a cast? It should. Let me try.

Let me write gen2.py with:
- v_sr: struct reload
- v_sr_cpy16: + cpy s16
- v_sr_reloadorder: + store reorder
Let me test.
