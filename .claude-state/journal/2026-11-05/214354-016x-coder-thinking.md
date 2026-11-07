---
ts: 2026-11-06T04:43:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CZIPR8L3ERKaJ8dmSuPV
---
Target:
```
lbu v0,0(a0)
nop
subu v0,v0,a1
bgez v0
nop
move v0,zero
sb v0,0(a0)
lbu v0,1(a0)
nop
...
```

Each lbu has a nop after it (load delay slot). Mine: the loads get scheduled earlier so no nop and different regs.

So I need to prevent sched1 from hoisting the next lbu into the gap (between bgez/move and sb) — target keeps each group serial with nop after lbu.

In gcc 2.7.2, `sched1` = instruction scheduling before register allocation. The store `sb v0,0(a0)` after the if: sched1 hoists `lbu v0,1(a0)` above the sb since they don't conflict. To prevent, we need the second load to depend on something produced by the first store. In plain C, one way: use a pointer that is derived from a value stored? No.

Alternative: alias! If the compiler thinks the load may alias the store, it can't hoist. For that, the address expressions must be "may alias". With `p[0]` and `p[1]` where p is `u8 *`, addresses p+0 and p+1 are different constants; no alias. But if we use an unknown offset, e.g., a variable `s32 k = 0; ... p[k]` then `p[k+1]` — still different offsets, no alias.

What if the pointer type is a struct pointer and we write `*(u8*)((u8*)p + i)` with i variable? Still offset difference known.

What if we use two different pointers q and p that may alias: `u8 *p = a0; u8 *q = a0;` then `q[0]` store and `p[1]` load — gcc's alias analysis for two pointers of same type: since both derive from a0, it knows they alias at offset 0 vs 1? With -O2 and no -fno-strict-aliasing, gcc 2.7.2's alias analysis is weak. It might treat p[0] and p[1] as non-conflicting because constant offsets differ.

Actually wait: does sched1 even consider alias? In gcc 2.7.2, sched1's dependency analysis uses `true_dependence`/`anti_dependence` which for MEM refs calls alias analysis; two refs with different constant offsets from the same base are known disjoint.

Another approach: reorder the C so that the store comes before the next load in a way that... it already does.

What about making the store a `s16`/u32 store covering more? No, target is sb.

Alternatively, use `v0` variable declared as `u8`? Widths: `s32 v0` vs `u8 v0`. If v0 is u8, then `v0 = p[0] - a1;` truncates to u8 and the `if (v0 < 0)` would be always false (u8 unsigned) — changes codegen. If `s8 v0`? Then `p[0] - a1` truncation to s8 changes semantics. Target doesn't have truncation.

What if the if test uses `(s8)v0`? No.

Different tack: maybe prevent the *store* from being delayed rather than the load hoisted. In mine, stores are delayed: sb v1,0 happens after next load. If we make the store's value a memory dependence... hmm.

Another classic lever: make the three statements a do-while(0)? C0535 says do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item. But do-while(0) here — would that prevent sched1 from crossing? A do-while(0) creates a NOTE_INSN_LOOP_BEG/END? Actually do{}while(0) — gcc may still treat as loop for a while. C0535 says it splits cse1 EBB. Hmm, but the constraint says `do{}while(0)` only with `// !FAKE: do-while`. That's allowed as a move. But wait — is do-while(0) a "lever of another kind"? The list of levers: pin, launder, barrier, keepalive macro or asm. do-while is a real C move (per C0535). OK.

But actually here it's a straight-line schedule issue, not cse. Let's think about what the barrier does: barrier is `asm volatile("" ::: "memory")`. It stops the memory references from being reordered across it. So we need an equivalent in real C.

Real C construct that blocks memory reordering: a function call! A call to an opaque function clobbers memory, so loads/stores can't move across it. But that changes codegen (adds a call). Unless the call is to something that's a no-op and gets optimized... no, at -O2 calls aren't inlined without -finline-functions? gcc 2.7.2 -O2 does inline some static functions. Hmm.

What about a volatile local? volatile u8 *? That would be a different lever kind probably (volatile is a barrier-ish lever). Not allowed.

Alternative: rearrange the C so that the natural schedule matches. If we write the computation to reuse v0 as the same pseudo... The register allocation difference: mine has v1 for the subu result because v0 gets the next load. If we prevent hoisting by adding a real dependence between statements.

Idea: use the pointer p itself as the value carrier:
```
v0 = p[0] - a1;
if (v0 < 0) v0 = 0;
p[0] = v0;
```
Now write second as `v0 = p[1] - a1;` — no dependence.

What if we make p's value depend on the store: `p = a0; ... *p = v0; p = (u8*)((u32)p | 1)`? That's an identity-ish launder... `p|1` not identity for p[1]? Actually p[1] after p|1 would be p[2]. No.

What about making the second address depend on the stored byte value in a genuine way? Can't.

Alternative: process bytes with an array local? `u8 *p = a0; u8 t[3];` no.

Hmm, what about using the same variable for load and result via a cast chain: `v0 = *(s8*)p - a1;`? If we load as s8 instead of u8: lb (sign-extend) instead of lbu — different instruction. Target is lbu.

Let me reconsider: maybe the crack is to change the statement order / loop shape: e.g., three separate `if` with `else`? No.

Let's try the simplest candidates empirically:
1. Separate v0 per statement (v0,v1,v2 declared) — probably worse.
2. Use pointer increments.
3. do-while(0) around each statement.
4. Write as `p[0] = (v0 = p[0] - a1) < 0 ? 0 : v0;` — one statement, maybe combine.
5. Use `if (v0 < 0) { p[0] = 0; } else { p[0] = v0; }` — store per arm (moves show "store per arm" cracks barriers). That would give two sb sites and might serialize.
6. `p[0] = v0 < 0 ? 0 : v0;`

The moves list has many barrier MATCHes via "store per if-arm (no temp)". Let's try store per arm.

Candidate b: 
```
v0 = p[0] - a1;
if (v0 < 0) { p[0] = 0; } else { p[0] = v0; }
```
Let's test several variants quickly with sc.sh. Write them.

Also idea: unroll using explicit separate variables named to hint local-alloc? Register allocation isn't name-driven in gcc.

Another idea: make the value u8 and use `(v0 & 0xFF)`? no.

Let me generate candidates and score.
