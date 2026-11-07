---
ts: 2026-11-06T07:59:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XJtwNm2TkXEchOjaR8YN
---
v32 (adding a redundant L.w38 read late) gave score 3 with 2 extra insns — the redundant read emitted a load (not CSE'd). Close but extra insns.

The natural C must not have extra insns. Hmm.

Let me reconsider the whole thing. Maybe the answer is not about twicep at all, but about the ORDER of the parameter copies in the prologue. In the target prologue, the parameters are loaded in a specific order: s6=oncep (lw s6,176), s5=twicep (lw s5,180), s4=trns, s2=vsrc, s3=dsrc, s1=&mat, s0=angp. The register assignment (s5 for twicep, s6 for oncep) is determined by global-alloc. In w1, the same. Fine.

Let me look at the actual residual from the *target's* perspective: the target's r79 (w3c) is in a0. Maybe in the natural C, w3c is NOT global (dies in 2 places) but two separate local variables, and both get a0 as v5 nearly achieved. The remaining problem in v5 was the pointer's birth order (addiu before store). Maybe a different spelling of the pointer assignment makes the addiu come after the store.

In v5, source: `L.w3C = w3c; w3d = (u32)L.o1;`. sched1 hoisted the addiu before the store. In the target, the addiu is after the store. If I make the pointer assignment depend on w3c (so it can't be hoisted), e.g., `w3d = (u32)L.o1 + (w3c & 0);`? That's an identity launder (not allowed). Or `w3d = (u32)L.o1;` but placed after a statement that depends on the store? The store is to memory; the addiu is independent of it.

Alternatively, use the SAME variable w3c (natural reuse) but make it local by having it die once. How can a variable be reused but "die once"? local-alloc refuses a pseudo that dies in several places. w3c dies at L.w3C store and at gte_stsv use = 2 places. If we could make it die once... e.g., use it once after the reassignment. The load's value is used once (L.w3C). The pointer is used once (gte_stsv). So if they were separate variables, each dies once → local. But then the pointer's addiu order issue.

What if the pointer is used in `gte_stsv((u16 *)w3c)` directly without a variable:
```
L.w3C = w3c;   // w3c dies here (loaded value, local)
...
gte_stsv((u16 *)(u32)L.o1);   // or L.o1
```
But the target uses a0 for the pointer and the `addiu a0,sp,16` at 60, then `sh t4,0(a0)`. If gte_stsv takes `L.o1` directly, the macro would compute the address into a0 at the call point (insn 60). That might match! Let me try:
```
w3c = *(u32 *)twicep;
...
L.w3C = w3c;
L.v58[2] = 0;
...
gte_ldv0(L.v48);
gte_rtv0tr();
gte_stsv(L.o1);   // instead of (u16*)w3c
```
Then no w3c reassignment. The loaded value w3c dies at L.w3C store. The pointer to L.o1 is computed at the gte_stsv. Target: `addiu a0,sp,16` at 60, before the gte_ldv0 of v48 at ~62. Hmm, in the target the addiu is at 60, and gte_stsv is after the first gte block (~75). The source computes the pointer before the first gte call (`w3c = (u32)L.o1;` at line 452). So `gte_stsv(L.o1)` wouldn't hoist the addiu to 60.

Unless the source keeps the pointer variable but it's local. Let me try:
```
u32 w3c;
u16 *dst;
...
L.w3C = w3c;
dst = L.o1;
...
gte_stsv(dst);
```
That's v7 (score 5, same order issue).

What if the pointer variable is assigned BEFORE the L.w3C store? Source: `dst = L.o1; L.w3C = w3c;` — then the addiu comes first (target has store first). No.

The order in the target: `sw a0,60(sp)` (store) then `addiu a0,sp,16` (pointer). In v5/v7, the addiu is hoisted before the store. The difference: in target, the store's source (a0) and the addiu's dest (a0) create an anti-dependency. In v5/v7, they use different registers (a0 store, v1 addiu), so no dependency and sched1 hoists. So if the pointer gets a0, the order fixes itself. Circular but maybe a different spelling makes the pointer prefer a0.

Why did v5's pointer (r80) get v1? Because at its birth (insn 59, hoisted), a0 was live (w3c's value). If the pointer were born after w3c's death, it'd get a0. sched1 hoisted it because it's independent. To prevent the hoist, make the pointer assignment depend on the store's value in a legitimate way. For example, compute the pointer from `L.o1` but after a use of w3c... 

What if the pointer variable is assigned via the struct: `dst = (u16 *)((s32)L.o1);`? same.

What if we write the store and the pointer assignment as one statement using the comma operator? `L.w3C = w3c, dst = L.o1;` — the comma operator sequences them, but sched1 can still reorder independent insns within a basic block? RTL from a comma is two separate insns; sched1 can reorder.

Hmm, what about using the SAME variable for both but declared `u32 w3c` and making the allocator treat it as local by... Actually, let me look at why the single variable is global: "dies in 2 places". local-alloc.c:472 refuses a pseudo that dies in more than one place (because it would need different registers at different points? no, it's about register allocation correctness with `reg_live_length`). The source reuses w3c. 

What if the original declared TWO variables that the compiler COALESCES into one pseudo? E.g.:
```
u32 w3c;
u32 w3d;
...
w3c = *(u32*)twicep;
...
L.w3C = w3c;
w3d = (u32)L.o1;
```
That's v5 (two pseudos, not coalesced).

What if the original used `w3c` for the loaded value and then `w3c = (u32)L.o1;` (reuse) — the natural style. The allocator gives s5 due to the preference. The keepalive fixed it. So maybe this really is a WALL and the natural C is not expressible.

But the engine got to 1 with a temp+width move, which suggests a near-miss. Let me look at that score-1 diff by reconstructing the engine's body version. The trace's first move "R8 temp tmp0 @443" and second "R12 width tmp0 u32->u16 @413". The @413 in the trace is the struct field line, and the temp's type became u16. In the current body, the temp move at @443 creates `u16 tmp0`. Maybe the engine's body had the temp move at a different line and created `u32 tmp0`, then the width move at @413... 

Hold on: maybe the trace line numbers are offset because the lever-free body the engine used was from an older src (before the current one). The current src may have changed (the brief warns src moves). The trace is from P36 (old). So not directly reproducible.

Let me try a different real-C idea: introduce a temp for `L.v48[0]` (the engine's best first move) AND some other change. The temp `u16 tmp0 = *(u16*)vsrc; L.v48[0] = tmp0;` alone didn't change the score (6). Combined with the width change to u32/s32/s16/u8 also 6-7. The engine's 1 came from a different body.

Given time (~25 min on item2), let me make a decision: try a few more targeted ideas, then WALL with best 5 (v5/v7) or 6.

Wait — actually, let me reconsider the possibility that the natural C uses `twicep` for the L.w3C store via a *pointer variable that is the same as twicep's register*. Hmm.

Let me look at the sibling function func_800CB158's structure: it uses `arg0` directly and `a0` local. The code style in this file uses raw arg pointers. For our function, maybe the original didn't have `s0`; it used `arg0` directly. But target has `move s0,a0`. That move exists because arg0 is used after calls.

What if the original used `twicep` after the GTE block in a *dead* way that the compiler keeps because it's a store to a struct field that's later read? Hmm.

Let me look at the target's `L.w40 = 0x50000000` (sp+64) and `L.w34`, `L.w38`. The struct fields w34/w38/w3C/w40 are 4 consecutive u32. Maybe the original copied a 16-byte block from twicep/oncep? No.

Let me check the target's L.w40 usage: stored at 33 (`lui v0,0x5000; sw v0,64(sp)`). L.w34 from oncep at 35, L.w38 from twicep at 37. Then L.w3C from w3c at 59. So w3C is the 3rd of the 4.

What if the original wrote:
```
L.w38 = *(u32 *)twicep;
L.w3C = *(u32 *)twicep;   // 2nd read, no var
```
Then the second read at ~451; sched1 hoists to 40; the store at 59. That's v24_mix (score 18, 134 ins). The 2 extra insns suggest the hoist didn't happen and something else. Let me look at v24's diff to see if the load is at 59 or 40.
