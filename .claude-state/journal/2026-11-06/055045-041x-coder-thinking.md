---
ts: 2026-11-06T12:50:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PQFxYBFq1NneqsAwtzQ3
---
The difference: target has

```
140 lhu v0,0(v0)     (D_801C11CE)
141 nop              (load delay)
142 addiu v0,v0,1
143 sh v0,-8(a1)     (y store)
144 lui v1,0x6480
145 ori v1,v1,0x8080
146 lui v0,0x400
147 sw v0,0(s0)
...
```

Mine:
```
140 lhu
141 nop
142 addiu
143 lui v1,0x6480
144 ori
145 sh v0,-8(a1)     <- y store moved down past the lui/ori
146 lui v0,0x400
...
```

So in the target, the y store (`*(s16*)((u8*)out+0xA) = y`) comes before the `lui/ori` constant build of 0x64808080. In mine, sched sinks the y store below the lui/ori.

The barrier in orig was exactly for this: "keeps the y store ahead of the 0x64808080 pair".

So I need a real-C way to keep the y store before the 0x64808080 pair. The pair is the constant for `*(u32*)((u8*)out + 0x4) = 0x64808080;` (lui+ori into v1). The y store is `*(s16*)((u8*)out + 0xA) = y;`.

Why does sched sink the sh? Priority: the lui/ori are on the critical path to the sw at 0x4, so sched (backward) places them earlier (they're needed by the sw). Hmm.

Real-C options:
1. Make the y store's value computation later? y = D_801C11CE + 1 — that's computed at 140-142 already.
2. Make the constant build depend on the store: e.g., write the 0x64808080 store using a variable that is computed from... no.
3. Reorder source: move the y store AFTER the 0x4 store? No, target order is sh then lui/ori then sw.
4. Change the order of statements so that the sw to out+4 comes earlier/later?

In target: sh (y store) at 143, then lui/ori (const), then sw 0x400 to 0(s0)?? Wait: `sw v0,0(s0)` — s0 is a different pointer (out?). Let me map: a1 = out (after out += 5?), s0 = something else.

Actually the sequence: sb -5(a1) (out+0xD = 0x38), lhu D_801C11CE, addiu, sh -8(a1) (out+0xA = y), lui/ori 0x64808080 into v1, lui 0x400, sw 0(s0) (0x04000000 to *out), li 120, sb -6(a1) (out+0xC = 0x78), li 0x4056, sw v1,-14(a1) (out+0x4 = 0x64808080), sh -4(a1) (out+0xE = 0x4056)...

So the sh y store must stay above the lui/ori pair. The lui/ori pair builds the constant for the sw at -14(a1).

In mine, sched placed sh after the lui/ori but before the sw — i.e., it delayed the sh to fill a slot.

Hmm: why would sched delay the sh? Backward scheduling: it processes from the end. The sw -14(a1) is placed at 149 in both. The lui/ori feed it. In mine the sh went at 145 (after ori, before lui v0,0x400). In target the sh is at 143, before the lui/ori.

What forces the sh above the lui/ori? In orig the barrier. Lever-free: what real-C dependency could order the sh before the lui/ori?

Idea: make the sh's address computation or value depend on something the lui/ori also... no, dependencies force order in one direction only.

Idea: make the lui/ori pair be born later in source order — it already is (the 0x4 store is after the y store in source). The scheduler moved the lui/ori up. To prevent that, the lui/ori's producer must have a dependency on the sh.

Idea: reuse a register. E.g. if the constant 0x64808080 were built into the same register that y used (v0)? In target: y is in v0 (lhu v0; addiu v0; sh v0). Then lui v1,0x6480; ori v1. So the constant goes to v1, not v0. If instead the constant were built in v0, there'd be a WAR/anti-dependence on the sh → the lui couldn't move above the sh! That's a real-C move: make the constant build use the same pseudo as y (v0).

How? The constant 0x64808080 is a literal in `*(u32 *)((u8 *)out + 0x4) = 0x64808080;`. Its register is chosen by local-alloc/global-alloc. If I introduce a temp for it: `s32 c64 = 0x64808080;` and use it, then that temp could get v0. But it needs to not conflict with y's live range. If the temp is declared/assigned after the y store, local-alloc might give it v0 since y dies at the sh. Actually that's exactly the classic: local-alloc reuses a dead register. But then the lui/ori would still be movable above the sh? No! If the constant temp is allocated to v0 and v0 holds y until the sh, then the lui/ori (which set v0) must come after the sh (a WAR/anti dependence on y). Yes!

But careful: does that change the target? Target builds into v1, and y is in v0. If I force the constant into v0, the target would have v1... no. Hmm. The target has `lui v1,0x6480` — so the constant is in v1. So the constant temp is NOT v0 in target. So the anti-dependence theory doesn't hold for the target; the target has a different reason.

Hmm, so what in the target keeps the sh above the lui? The barrier in the source. Right.

Let me think about the actual scheduler priorities. Maybe the sh can be kept above by making it part of a different scheduling region? The whole loop body is one BB.

Alternatively, maybe a do-while(0) around the y store + the constant build? C0535 says do{}while(0) splits cse1 EBB; for sched it apparently can affect the block. In item 1, do-while around the store worked. Let's try do-while variants here:

w1: do { *(s16*)((u8*)out + 0xA) = y; } while (0);
w2: do { *(s16*)... = y; *(u32*)out = 0x04000000; ... } while (0) — grouping.
w3: do { ... } while(0) around the whole tail group starting at the y store.

Actually in the moves list: "func_8017D7B4 MATCH: ... + do-while(0) on the D_801269EA=0 store keeps sh zero before E8" — similar shape (do-while on a store keeps a sh before something).

Let me try do-while around the y store first.

Also there might be an alternative: swap the two statements `*(s16*)((u8*)out + 0xA) = y;` and the `*(u32*)out = 0x04000000;`? No, target order is y store then 0x400 store... wait target: sh at 143, lui/ori at 144-145, then sw 0x400 at 147. Source order: y store, then *(u32*)out = 0x04000000, then sb 0x78, then sw 0x4, then sh 0xE.

Hmm the target's actual order at 142-150:
142 lui v1,0x6480
143 ori v1,v1,0x8080
144 lui v0,0x400
145 sw v0,0(s0)
146 li v0,120
147 sb v0,-6(a1)
148 li v0,16470
149 sw v1,-14(a1)
150 sh v0,-4(a1)

Interesting: the `sw v0,0(s0)` at 145 is `*(u32*)out = 0x04000000`? out is s0? Hmm, a1 = out+? Let's see: sb -5(a1) = out+0xD... if a1 = out+0x12 then -5 = 0xD, -8 = 0xA, -14 = 0x4, -4 = 0xE, -6 = 0xC, -2 = 0x10, 0 = 0x12. So a1 = out + 0x12 (the giv base!). And s0 = out (the real base) for the 0(s0) store.

OK. So the schedule: sw 0x400 to 0(s0) at 145, which is the source's `*(u32 *)out = 0x04000000;` (third statement). And sw v1,-14(a1) at 149 is the 0x4 store.

Anyway. The key: sh y at 143 must precede lui v1,0x6480 at 142? No — 142 is before 143. Let me re-read:

Target:
141 nop
142 lui v1,0x6480
143 sh v0,-8(a1)
144 ori v1,v1,0x8080
145 lui v0,0x400
146 sw v0,0(s0)
147 li v0,120
148 sb v0,-6(a1)
149 li v0,16470
150 sw v1,-14(a1)
151 sh v0,-4(a1)

Hmm wait, the dump earlier showed target:
```
139      624:	00000000 	nop
140      628:	24420001 	addiu	v0,v0,1
141      62c:	a4a2fff8 	sh	v0,-8(a1)
142      630:	3c036480 	lui	v1,0x6480
143      634:	34638080 	ori	v1,v1,0x8080
144      638:	3c020400 	lui	v0,0x400
145      63c:	ae020000 	sw	v0,0(s0)
```
and mine:
```
139 nop
140 addiu v0,v0,1
141 lui v1,0x6480
142 ori v1,v1,0x8080
143 sh v0,-8(a1)
144 lui v0,0x400
145 sw v0,0(s0)
```

So target: addiu, sh, lui, ori, lui, sw.
Mine: addiu, lui, ori, sh, lui, sw.

So the sh is delayed past the lui/ori pair. Both have the sh before the sw.

The barrier in source is right after the y store, i.e. between sh and the 0x400/0x78/0x4 statements. So the barrier stops the lui/ori from moving *above* the sh.

Lever-free: need something that keeps lui/ori below the sh.

Idea: the lui/ori (constant 0x64808080) is generated for the store `*(u32*)((u8*)out + 0x4) = 0x64808080;`. If the constant were instead built from a variable computed after the y store... e.g. `s32 m = 0x64808080;` placed after the y store. Then the constant's birth is after the sh in source; but sched can still hoist a constant build (li/lui) upward if it's independent. Sched hoists to fill gaps. The only thing stopping hoisting is a dependence.

What if the constant is derived from y? e.g. no.

What if I move the sh *later* in source but rely on... no, target has sh before.

Hmm. What if the sh were part of a block move (struct)? The y store is a 2-byte store. `*(s16*)` — no template.

What if the two adjacent stores sh(0xA) and the 0x4 store become one 8-byte block move? They're at offsets 0xA and 0x4, and other stores in between (0x0, 0xC, 0xE). Not contiguous.

Let me look at what the barrier actually does in sched: the asm insn is a real insn in the block; sched must place it, and everything after it (in source) must be scheduled after it, everything before before it. So it splits the block into two regions at the asm. Both the lui/ori and sh are in different regions.

Plain C: is there a real insn that acts as a scheduling barrier? A *call* would, but that changes semantics. 

Alternative: use the loop structure — put the y store in a `do{}while(0)` and the constant in another? Let me test empirically: try do-while around the y store, and also around the whole tail block.

Let me also consider: maybe reordering source statements helps. E.g., if I move the `*(u32*)out = 0x04000000;` statement before the y store... no, changes target.

Let me just try a batch of candidates:
a) do { sh y } while(0)
b) do { sh y; } while(0) + do { 0x4 store } while(0)
c) do { sh y; 0x400 store; sb 0x78; 0x4 store; sh 0xE; vsum...; } while(0) — the whole tail
d) `y` computed inside a do-while with the store.
e) reorder: put the 0x4 store before the 0x400 store? (changes order)

Let me write them. First let me see the exact source lines 105-131 of orig.c.
