---
ts: 2026-11-06T07:44:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iaKbLLCUIb0NfcuOHQJM
---
Score 1 is close. The move "R12 width tmp0 u32->u16 @413" — a width change on tmp0 at line 413. Line 413 in the TU? The trace refers to the body line? Let me see what candidate text that was. The trace doesn't store text. But maybe the moves are applied to the lever-free body and "tmp0" is a generated temp from a previous move. The chain: parent 5, depth 2.

Let me look at the parent chain. Actually, this suggests the engine found score 1 by changing a width. The residual score 1 might be a single instruction mismatch. Let me reproduce: the engine's moves are named R12 (width), R8 (temp), R7 (block). "tmp0" suggests an earlier move introduced a temp `tmp0`. Hard to reconstruct.

But my job is the lever-free body (no keepalive) scoring 0. The engine's best lever-free-ish text scored 1. I need to find the exact source.

Let me try real-C variants. Key: extend twicep's live range past w3c's. What if I add a variable that holds twicep and is used in the L.w3C assignment? E.g.:

```
u32 w3c;
u32 *tw = (u32 *)twicep;   // named pointer, live through
...
L.w34 = *(u32*)oncep;
L.w38 = *tw;
w3c = *tw;
...
L.w3C = w3c;
```
Then `tw` is live through w3c's range (used at both loads). But `tw` would be in a register (a1?) and the loads use `lw v0,0(tw)`, `lw a0,0(tw)` — target uses s5 as the base. Hmm, target's base is s5 (twicep). If `tw` is a separate pointer, the base register could be a1 or s5. Not target.

What if the original parameter is used directly but with a dummy third use that's free? 

Let me look at the target's r77 live length in the ORIGINAL (with keepalive): 116. The keepalive is at a specific point; live length 116 means from birth to the keepalive. In the target binary, the natural C must have r77 (twicep) live similarly long. But there's no instruction. 

Wait — maybe r77 is not twicep! Let me verify which pseudo is twicep. r77 in s5, "crosses 4 calls", "pointer". The param twicep is loaded from 180(sp) into s5 at entry, used at insns 37,40. Live length 44 in w1 ≈ insn 40. Yes, r77 = twicep.

In orig, live length 116 → the keepalive extends it to insn ~116 (the keepalive point). 

For the target, the natural live length must be long enough to conflict with w3c (r79, live 26, range ~40..59). So twicep must live to at least ~59.

What if the natural C uses `twicep` for the `L.w3C = w3c;` assignment differently: e.g., `L.w3C = *(u32 *)twicep;` — a third read at ~59. That's +1 load instruction, but the target has 132 insns same as mine. Unless the compiler reuses the earlier loaded value because `*(u32*)twicep` is CSE-able: cse would CSE the two loads if no intervening store that might alias. There ARE intervening stores to the stack (L fields). Can cse prove `*(u32*)twicep` is not aliased by stack stores? cse's alias analysis for a pointer param vs stack stores: in GCC 2.7, non-addressable stack slots vs arbitrary pointer stores — cse might treat them as non-aliasing? Actually `twicep` is a pointer parameter; stores to `L` (a local struct on the stack) could alias it in general, but GCC knows the local struct's address doesn't escape? It passed `L.mat` to functions, so the struct's address DOES escape (func_80013F3C(L.mat) takes a pointer). Hmm, but `L.w3C` is at sp+60; the pointer twicep could point there. cse likely can't prove non-aliasing → second load stays.

Let me test the idea anyway: maybe the compiler CSEs it and no extra insn. Try variant: move the `w3c = *(u32*)twicep` to just before `L.w3C = w3c;`? No.

Let me instead try the "third read" variant:
```
w3c = *(u32 *)twicep;   // at line 40
...
L.w3C = w3c;
w3c = (u32)L.o1;
```
→ change `L.w3C = w3c;` to `L.w3C = *(u32 *)twicep;` and drop the early w3c? Then there's one load at ~59. Target has the load at 40. Different schedule but sched1 might hoist the load to 40! Since the load is independent, sched1 could move it up. Actually target's load at 40 is early (right after L.w38's load). If the source stores `L.w3C = *(u32*)twicep;` at line ~59, sched1 might not hoist it that far. Hmm.

Let me just test a batch of variants:
1. v1: `L.w3C = *(u32 *)twicep;` (third read, remove early w3c load? keep w3c for pointer).
   Actually keep: `w3c = *(u32*)twicep; ... L.w3C = *(u32*)twicep;` → two loads.
2. v2: separate pointer variable `u32 *tw = (u32 *)twicep;` used for both loads.
3. v3: make w3c `u32` already; try `s32 w3c`? no.
4. v4: assign `L.w3C = *(u32*)twicep;` and `w3c = (u32)L.o1;` later.
5. v5: use `w3c` as `void*`? 
6. v6: add a real use of twicep after the GTE block that is free: `if (twicep == oncep) ...`? would emit code.
7. v7: change `L.w38 = *(u32 *)twicep;` to use w3c: `w3c = *(u32*)twicep; L.w38 = w3c;` — this merges the two reads into one, making w3c live earlier (from insn ~36). Then w3c's range starts earlier, overlapping twicep more. Could change allocation. And the target: `lw v0,0(s5); sw v0,56(sp)` (L.w38) and separately `lw a0,0(s5)` (w3c) — two loads in target. If source uses one value for both, there'd be one load. Target has two loads (insns 37,40). So no.

8. v8: declare w3c as `volatile`? That's a lever (class C). No.

Let me look at the diff more carefully: in w1, w3c got s5. In orig (keepalive), w3c got a0. The simplest real-C fix: make w3c's live range not reuse s5 by extending twicep. But maybe instead change w3c's *priority* so global-alloc picks a0 anyway. The .greg shows r79 priority 3076, conflicts. If we increase w3c's refs (e.g., use it more) its priority changes. But bytes must stay.

Alternatively, shorten w3c's live range so it doesn't conflict with s5? In w1 it already reuses s5.

Hmm, actually, maybe the natural C has w3c as TWO variables: the loaded value and the pointer. Then the loaded value's range ends at L.w3C store (59), the pointer starts at 59. Neither would conflict with s5? The loaded value's range 40..59 still overlaps s5's death at 40. But if the load's value is stored to L.w3C immediately (no named variable), then the loaded value is a short temp (40..41) and doesn't need a0. But target keeps it in a0 until 59, so it IS named.

Wait, maybe the target's a0 at insn 40 is NOT w3c! Let me re-examine: `lw a0,0(s5)` at 40; `sw a0,60(sp)` at 59 = L.w3C. And later `addiu a0,sp,16` = L.o1, then `sh t4,0(a0)`. So a0 holds the loaded value 40..59, then the pointer. Yes.

What if the source used a SINGLE variable for both, but that variable is declared as `void *` or `u32`? Same.

Let me try the engine's near-miss: "R12 width tmp0 u32->u16". Maybe the crack is a width change on `w3c`! `w3c` is `u32`. If we make it `u16` or `s16`, the allocator might give it a0. But then the store `L.w3C = w3c` would be a halfword store, changing bytes. Unless the width is on a different temp. The move says tmp0 u32->u16 at @413 — likely a temp introduced by an earlier move (R8 temp), not w3c.

Let me reconstruct the parent chain: entry "parent 5". Let me look at rows with depth 0/1 and id 5. The trace has no ids? It has "parent": 5. Let me print rows with index and see. Let me dump the trace entries with their fields.
