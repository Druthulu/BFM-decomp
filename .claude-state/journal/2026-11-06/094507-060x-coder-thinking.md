---
ts: 2026-11-06T16:45:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gyayGT0APMnawhWJFplN
---
Mine (unpinned):
- temp (source v0) → $v1
- source v1 → $a0
- source a0r → $a1?
- pointer a1 → $a2

Target:
- temp v0 → $v0
- v1 → $v1
- a0r → $a0
- a1 (pointer) → $a1

So the unpinned allocation rotates: v0←$v1, v1←$a0, a0r←$a1, a1←$a2? Wait mine's `sh a0,48(a2)`: the store `CAST_WIDTH(u16,a1,0x30)=v1` stores v1's value. Hmm, mine stores `a0` to `48(a2)`. So source v1→$a0, source a1→$a2. And source a0r→$a1 (`move a1,v1` where v1 is source v0? confusing).

Target: v1→$v1, a1→$a1, a0r→$a0.
Mine: v0→$v1, v1→$a0, a0r→$a1, a1→$a2.

So local-alloc handed $v0 to... something else? Let me check which pseudo got $v0 in mine. In the diff, `sll v0,a0,0x10` — v0 is used. Mine[13] `sll v0,v1,0x10` vs target `sll v0,v0,0x10`. So mine's $v0 holds the *source v0?* no...

Let me think in terms of the source variables:
- The first block: `v0 = p->unk70; v0 = v0*2; at = D_8019C7D4 + v0; v0 = *(u16*)at; v1 = a1->unk30; v1 = v1 + v0; a1->unk30 = v1; if ((s32)(v0<<16) < 0) ...`

Target:
```
3354 lh v0,112(s0)     ; v0 = unk70
3358 lw a1,32(s0)      ; a1 = s0->unk20
335c sll v0,v0,1
3360 lui at
3364 addu at,at,v0
3368 lhu v0,0(at)      ; v0 = D_8019C7D4[v0]
336c lhu v1,48(a1)     ; v1 = a1->unk30
3374 addu v1,v1,v0
3378 sll v0,v0,0x10     ; test value
337c bgez v0,...
3380 sh v1,48(a1)
```
Mine:
```
13 sll v0,v1,0x10      ; test
15 sh a0,48(a2)        ; store
16 lh v1,112(s0)
17 sll v0,a0,0x10
18 sll v1,v1,1
20 addu at,at,v1
21 lh v1,0(at)
22 sra a0,v0,0x10
23 move a1,v1
24 addiu v1,v1,-48
25 slt v0,v1,a0
```
So mine: source v0→$v1, source v1→$a0, source a1→$a2, source a0r→$a1.

Which pseudo got $v0 in mine? `sll v0,v1,0x10` uses v0 as a dest for the test value — that's source v0's copy? In target `sll v0,v0,0x10` (source v0). In mine, `sll v0,v1,0x10` where v1 is source v0. So mine's $v0 is a *different* pseudo used for the shifted test value (a temporary created by the `(s32)(v0 << 16)` expression). In target, that temp IS v0 (reused).

So the difference: the `(v0 << 16)` result gets its own pseudo in mine (allocated $v0), whereas in target it's folded into v0 itself.

Hmm, the target's `sll v0,v0,0x10` reuses v0. Mine has `sll v0,v1,0x10` — a separate pseudo in $v0. That's the crux: cse/combine didn't reuse.

How to make it reuse? The expression `(s32)(v0 << 16)` — v0 is an s32 local holding a u16 load (zero-extended). `v0 << 16` could be a new pseudo. In target, the same register is used because the temp dies immediately and local-alloc ties it to the dying v0? Hmm, `sll v0,v0` is the same dest and src → local-alloc's copy preference (tie).

In mine, v0 is in $v1 and the shift temp is in $v0 — so local-alloc did NOT tie them. Why? Because of allocation order/conflicts.

Real-C moves: 
- Write the test as `(s32)v0 < 0`? No, the target does `sll v0,v0,0x10; bgez v0`. The source is `if ((s32)(v0 << 16) < 0)`. Equivalent: `if ((s16)v0 < 0)` — that might emit `sll` too. Actually `(s16)v0 < 0` would emit `sll v0,v0,0x10` then bgez? Or `sll` + `sra`? Hmm.
- Maybe use a `s16` local for the loaded value: `s16 v0 = *(u16*)at;`? But the source v0 is s32.

Let me try variants:
- m01: pin removed, `v0` declared s16? Changes semantics elsewhere (v0 used as an index too).
- m02: change `if ((s32)(v0 << 16) < 0)` to `if ((s16)v0 < 0)`.
- m03: introduce the shift into a variable: `at = v0 << 16; if ((s32)at < 0)`? reuses `at` (which is free after the load).
- m04: reorder declarations.
- m05: use `v0` directly as the pointer? 
- m06: make `a1` a pointer type instead of s32 (`Unkstruct_800B5CB8 *a1 = ...`)? C0241: prefer s32 to void* for parameters.
- m07: remove the `s0` copy and use `arg0` directly (C0241: parameter itself is a dial). But the pin removal is the only requirement; using arg0 directly may change regalloc. Let's try: replace `s32 s0 = (s32)arg0;` with `s32 s0 = (s32)arg0;`? Hmm, `arg0` is void*, s0 is s32. If we use `(s32)arg0` inline everywhere, the parameter stays in $a0 and gets copied to $s0 by the prologue anyway.

Actually the target's prologue: `sw s0,32(sp); move s0,a0` — the parameter is copied to $s0. So `s0 = (s32)arg0` is right.

The key difference is the $v0/$v1 rotation. Let me think about local-alloc priority. In the target, v0 (temp, many refs across the function) gets $v0 and v1 gets $v1. In mine, the shift temp got $v0 and the source v0 got $v1.

If the shift temp is eliminated (reuse v0), the allocator might give v0 $v0. Let me try m02/m03.

Actually, the pin forces $2 and the allocator then assigns others around it. Lever-free, we need the same assignment naturally.

Let me try a batch of source variants (all with the pin removed) and score.

Variants:
m01: `if ((s16)v0 < 0)` instead of `if ((s32)(v0 << 16) < 0)`
m02: `v0 <<= 16; if (v0 < 0) { v0 = ...; }` — but v0 is reused after.
m03: `if (v0 & 0x8000)` (the u16 load's bit 15) — emits `andi`? target has `sll`+bgez. Different bytes.
m04: `if ((u16)v0 & 0x8000)` — andi.
m05: declare `s32 v0;` after `s32 s0` (order).
m06: merge v0/v1? no.
m07: make `at` s16? no.

The target's test: `sll v0,v0,0x10; bgez v0`. So the source's `(s32)(v0 << 16) < 0` compiles to sll+bgez. `(s16)v0 < 0` might compile to `sll v0,v0,0x10; bgez v0` too (the s16 compare is done by shifting). Let me test.

Also, maybe the real issue is that in mine the shift result is a separate pseudo that grabs $v0 *before* v0. If I write the test to reuse v0 (e.g., `v0 = v0 << 16; if (v0 < 0)`) then v0 is set twice (reg_n_sets 2) — but that's fine, no sched issue here? Actually sched1 birthing boost could apply. Hmm, but the target's `sll v0,v0` is a self-set.

Let me just test a batch.
