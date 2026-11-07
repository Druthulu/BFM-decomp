---
ts: 2026-11-06T16:48:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_J2ofXc4TC0MHWzqJlPPk
---
Now the RTL at local-alloc time (after sched1):

Block 1 insns:
- 23: 78 = 73 << 9      (a = s0 << 9)
- 30: 76 = sign_extend(mem[74+112])  (h load)
- 25: 77 = 73 << 1      (t = s0 << 1)
- 35: 81 = 76 << 4      (h << 4); 76 dies
- 37: 82 = 81 + 75      (+ s2); 81 dies
- 39: 83 = 77 + 82      (t + ...); 77 dies, 82 dies
- 41: 84 = mem[83]      (lhu); 83 dies
- 33: 73 = 73 + 1       (s0++)
- 45: 86 = 84 + 78      (+a); 84 dies, 78 dies
- 46: 88 = 86 << 16
- 49: a0 = 411
- 51: a1 = 88 >> 16
- 53: a2 = 74
- 55: call
- 60: 89 = 73 < 8
- 61: branch

So the "h" variable (76) lives from insn 30 to 35 (2 insns of life: 30→35). nrefs 4? Hmm, reg 76 has nrefs 4: def at 30, use at 35, and maybe the mem operand? Whatever.

Reg 84 is the u16 load (2 bytes). Reg 77 = t.

Priorities: all nrefs 4, size 1, so pri = 4/life (in units of insn numbers? life = death - birth in insn indices ×2?). The life values: qty_birth/death are in "insn_number" units ×2? In alloc_qty, birth = 2*insn_number. death similar. So life = 2*(insn gap).

- 76 (h): birth at insn 30, death at 35 → gap 5 → life 10.
- 77 (t): birth at 25, death at 39 → gap 14 → life 28.
- 78 (a): birth 23, death 45 → life 44.
- 81: birth 35, death 37 → life 4.
- 82: birth 37, death 39 → life 4.
- 83: birth 39, death 41 → life 4.
- 84: birth 41, death 45 → life 8.
- 86: 45→46 → 2.
- 88: 46→51 → 10.
- 89: 60→61 → 2.

Priority = floor_log2(4)*4*1/life = 2*4/life = 8/life.
- 86: 8/2 = 4 (highest)
- 89: 4
- 81,82,83: 8/4 = 2
- 84: 8/8 = 1
- 76: 8/10 = 0.8
- 88: 0.8
- 77: 8/28 = 0.28
- 78: 8/44 = 0.18

Allocation order (highest first): 86, 89, 81, 82, 83, 84, 76, 88, 77, 78 (ties by qty number).

Now, each qty gets a register. The order determines who gets $2 (v0). Let's see: 86 (life 2) gets $2? But the target has 86 (= the sum) in... let me check the target's registers:
- 86 = h<<4 + s2 + ... hmm let me map the target:
```
2730: sll a0,s0,0x9      78 -> a0
2734: sll v0,s0,0x1      77 (t) -> v0
2738: lh v1,112(s1)      76 (h) -> v1
273c: addiu s0,s0,1      73
2740: sll v1,v1,0x4      81 = 76<<4 -> v1
2744: addu v1,v1,s2      82 = 81+75 -> v1
2748: addu v0,v0,v1      83 = 77+82 -> v0
274c: lhu a1,0(v0)       84 -> a1
2750: move a2,s1         74
2754: addu a1,a1,a0      86 = 84+78 -> a1
2758: sll a1,a1,0x10     88 -> a1
275c: li a0,411          49
2760: jal
2764: sra a1,a1,0x10     51
2768: slti v0,s0,8       89 -> v0
276c: bnez v0
2770: sll a0,s0,0x9      78 -> a0
```

Target allocation:
- 78 (a) = a0 ($4) — because it's used as the call arg? No, 78 is added to a1. Hmm, in the target a is in $4 (a0) and gets overwritten by li a0,411. Interesting: `sll a0,s0,0x9` at 2730, then later `li a0,411` at 275c. So a=78 is in $4 and is *dead* before the li (used at 2754). OK.
- 77 (t) = $2 (v0)
- 76 (h) = $3 (v1)
- 81,82 = $3 (v1)
- 83 = $2 (v0)
- 84 = $5 (a1)
- 86 = $5
- 88 = $5
- 89 = $2
- 74 = $6

So in the target: 77 (t) got $2 and 76 (h) got $3. But by priority, 76 (0.8) > 77 (0.28). Unless the allocation isn't purely by priority — the tie loop! Let me check the tie loop at insn 35: `81 = 76 << 4` with 76 dead → 81 ties to 76. So 76 and 81 share. At insn 37: `82 = 81 + 75` with 81 dead → 82 ties to 81. At 39: `83 = 77 + 82` with 77 dead and 82 dead → 83 ties to... one of them (the tie loop tries operands in order: operand 1 first? r1 = operand 1 = 77, which is dead → 83 ties to 77!). Hmm, but the target has 83 in $2 and 77 in $2 — yes! 83 tied to 77. And 82 in $3 (tied to 81→76). Wait, target: 82 = $3 (v1), 76/81 = $3. Yes.

So the tie chain: 76=81=82 ($3), 77=83 ($2). Then 84 ties? At insn 41: `84 = mem[83]` — a load, operand 0 is a memory, so no tie (output is a MEM). At 45: `86 = 84 + 78` with 84 and 78 dead → 86 ties to 84 (operand 1, 84 dies) → 86 = 84's reg ($5). At 46: 88 ties to 86 ($5). At 51: a1 = 88 >> 16, 88 dead → hard reg a1.

So the tied groups: {76,81,82} and {77,83} and {84,86,88}.

Now the allocation of the groups by priority: the group priority is that of the qty (the first reg in the qty?). For tied qty, `qty_phys_reg` etc. The group's priority uses the qty's nrefs/size/life (of the qty as a whole, which spans all tied regs).

In MINE: h=76 got $2 and t=77 got $3. So the group {76,81,82} got $2 and {77,83} got $3. In the TARGET, {77,83} got $2 and {76,81,82} got $3.

The group priority: {76,...}: qty_birth = birth of 76 (insn 30), qty_death = death of 82 (insn 39)? The qty's death is the last death among tied regs. Life = 39-30 = 9. nrefs = sum? qty_n_refs for the qty = reg_n_refs of the first reg? Let me check: `qty_n_refs[qty] = reg_n_refs[regno]` at alloc_qty (first reg). When tying, combine_regs updates qty_n_refs? Let me look at the tie code after combine_regs (lines 1850+).

Actually, this is getting deep. Let me instead think about what changes the outcome: the target has {77,83} (t group) allocated BEFORE {76,81,82} (h group). The group priorities determine this.

Group t {77,83}: birth = 25 (77), death = 39 (83) → life 14 (in insn index units, ×2 = 28). nrefs: 77 has 4? The stats said 77 used 4 times across 4 insns. 83 used 4 across 2. Group nrefs = 4 (or sum 8?).
Group h {76,81,82}: birth 30, death 39 → life 9 (×2=18). nrefs 4 (76).

pri_t = floor_log2(4)*4*1/28 = 8/28 = 0.285
pri_h = 8/18 = 0.44

So h group > t group. Mine allocates h first → $2. Target wants t first.

To flip: make the h group's life longer or nrefs lower, or the t group's life shorter/higher nrefs.

Real C options:
1. Move the h load EARLIER (before the t computation) → h's birth earlier → longer life → lower priority. But the RTL order after sched1 shows the h load at insn 30, between a (23) and t (25). The target's *instruction* order is sll a0; sll v0; lh. Hmm, the sched1 dump (base.i.sched) shows the RTL order after sched1: 23, 30, 25, 35... So the h load (30) is between a (23) and t (25). If I move the h load in the C to the very first statement of the loop (before a = s0 << 9), then its birth is earlier → longer life → lower priority.

But wait, the target's *final* instruction order has the lh AFTER the two slls. sched1 reorders; the final order after sched1 is what matters for local-alloc, and the lreg dump shows 23, 30, 25 — i.e., lh at 30 after sll a at 23 and before sll t at 25. The final .s target shows sll a0 (2730), sll v0 (2734), lh v1 (2738). Hmm, that's a, t, h — different from the lreg order (a, h, t). The difference: after local-alloc, sched2/reorg may reorder. Whatever.

So the lreg order is a(23), h(30), t(25). Hmm, the insn numbers are not in increasing order in the dump: 23, 30, 25 — that's the *source/RTL* order? The dump shows insns in execution order: 23 → 30 → 25 → 35... So the RTL execution order is a, h, t, h<<4...

If I move the h load to the first statement in C, the RTL order would be h, a, t. Then h's birth is earliest → longest life → lowest priority among them. That could flip the allocation!

But the final instruction order must remain a, t, h (target). sched1 might reorder. Let me just try: move `h = *(s16 *)((u8 *)s1 + 0x70);` to before `a = s0 << 9;`.

2. Alternatively, lengthen h's life by moving the h load earlier and/or its use later. Can't move the use.

3. Make t's life shorter: move `t = s0 << 1;` later (after the h<<4 stuff). The RTL order would change but sched1 may restore.

4. Change h's nrefs: the h variable is used twice (<<4 and +a? no). h's uses: `h << 4` (insn 35). Actually the C is `(h << 4)` — one use. But reg 76 has nrefs 4? Hmm, reg_n_refs counts def + uses; maybe 76 = the sign_extend pseudo (h) has 2 refs... the stats say 4. Whatever.

5. Change t's nrefs: t is used once (in the addu). Can't.

6. Introduce an extra use of t (e.g., reuse t later) — changes code.

Let me try the reorder of the h load first. Also try moving t's computation before a's.

Actually, let me reconsider: the target's final .s order is a, t, h. Our current .s (mine) is: let me check mine's final .s. The diff showed mine[10:12]: `sll v1,s0,0x1; lh v0,112(s1)` — so mine's final order is a, t, h (same as target). So the final order is already right; only the allocation differs.

If I change the source order, sched1 may produce a different RTL order and the final order might change. Risky but worth trying.

Let me try a batch of variants:
1. h load first (before a).
2. t computation first (before a).
3. h load after t but before s0++? (current is: a, h, t, ...). Hmm the current C order is a, t, h! Wait:

C:
```
a = s0 << 9;
t = s0 << 1;
h = *(s16 *)((u8 *)s1 + 0x70);
s0 = s0 + 1;
func(...);
```
The RTL after sched1 is a(23), h(30), t(25) — sched1 moved h before t. Interesting.

4. Split the h load into a separate variable used twice.

Let me also try changing `h` from `int` to `s16` (HImode): the qty size is the same, but the subreg might affect ties: insn 45 `86 = (subreg:SI 84) + 78` — 84 is HImode. In the RTL, 84 is the loaded u16 value (movhi). If h is s16 (int in C), the load is sign_extend:SI into an SImode pseudo (76). If h is s16 (C short), the load might be `(reg:HI)` then extended when used — different RTL! Let me test: `s16 h;` in C.

Actually the current C has `int h` and the RTL load is `(set (reg/v:SI 76) (sign_extend:SI (mem:HI ...)))` — a sign-extending load into SImode. If h were `s16`, the RTL might be `(set (reg:HI 76) (mem:HI ...))` then `(sign_extend:SI (reg:HI 76))` for the use — which combine folds back into the load? Maybe. If the pseudo is HImode, its qty life/refs might differ, changing the allocation.

Let me test a batch:
a) h load moved to the top of the loop.
b) t moved to the top (before a).
c) h as s16.
d) h as u16.
e) t declared/assigned after h in source.
f) `a` moved after t.

Let me write these.

Also note the `register int h __asm__("$3")` pin: removing it and declaring `int h` is the base. The target wants h in $3 naturally.

Let me generate.
