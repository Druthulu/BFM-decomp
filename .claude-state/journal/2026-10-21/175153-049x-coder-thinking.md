---
ts: 2026-10-21T23:51:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_twUugk8v8bme2T6va3uH
---
Item 8017FB50: The unpinned version is very close! The only difference: the callee-saved register assignment. Target: the `p_out` pointer (sp+48) is in $18 (s2) and `flag_out` (sp+52) in $17 (s1). My candidate: p_out in $17 (s1) and flag_out in $18 (s0).

So I need to swap the two callee-saved registers: p_out → $18, flag_out → $17. In the target, p_out (the 3rd arg) is in s2 ($18) and flag_out (4th arg) in s1 ($17).

The order of allocation of callee-saved regs: GCC allocates s0, s1, s2, ... in order of priority. The target has flag_out in s1 and p_out in s2. Mine has p_out in s1, flag_out in s0.

Interesting: mine used $16 (s0) and $17 (s1); the target used $17 (s1) and $18 (s2). So the target skipped $16! Why? Because $16 (s0) was taken by something else in the target? In the target, the diff shows `move s0,v0` (the RotTransPers return) — s0 is used for the return value of the first call (tmp). So in the target: s0 = tmp (the call result), s1 = flag_out ($17), s2 = p_out ($18). And the pins were: flag_out → $17 (s1), p_out → $18 (s2). ✓.

In my candidate: s0 = flag_out? No wait: mine has `addiu s1,sp,48` (p_out in s1=$17) and `addiu s0,sp,52` (flag_out in s0=$16), and `move s2,v0` (the return value in s2=$18).

So the difference is the *order* in which the three values get the callee-saved registers: target order: tmp→$16, flag_out→$17, p_out→$18. Mine: flag_out→$16, p_out→$17, tmp→$18.

So I need tmp (the RotTransPers return) to get $16, and then flag_out→$17, p_out→$18. In my version, tmp got the LAST callee-saved reg.

The allocation priority (in global-alloc, shorter live range → higher priority... for callee-saved regs in a loop, the priority is based on the "loop depth" and the number of refs).

Hmm, in the target: tmp = RotTransPers(...) result, used later in `idx = func_801823D4(tmp, -0x1A)`. So tmp's live range spans the 4 calls. flag_out and p_out are used in all 4 calls.

In my version, the assignment order differs. What if I make `tmp` a variable that is used earlier (shorter range)? No — tmp must live until the end.

What if the order of the args to RotTransPers changes? The 3rd arg is p_out, 4th is flag_out. The target: p_out in $18, flag_out in $17.

Since the callee-saved allocation order follows priority, and the target has tmp first ($16), then flag_out ($17), then p_out ($18)... Interesting: flag_out before p_out.

Hmm, what determines it? In global-alloc (gcc 2.7), the "qty" ordering for callee-saved regs: the first qty gets the "preferred" reg. The order of the qty list is by priority. In gcc 2.7's global-alloc, the priority for a qty is computed by `qty_compare` (same formula: shorter live range → higher priority) plus "loop depth" weighting.

So to match: tmp must have the highest priority (shortest live range relative to others?) — but tmp's live range is long (spans the 4 calls). flag_out and p_out are live across the whole block too.

Hmm, the live ranges: p_out and flag_out are set before the first call and used in all 4 calls; they're live the whole time. tmp is born at the first call and dies at func_801823D4 → its range is shorter (from call 1 to the end, not including the setup before).

By the formula pri = log2(n_refs)*n_refs*size/(death-birth):
- p_out: n_refs = 1 set + 4 uses = 5 → log2(5)=2 → 2*5=10; range long (from setup to the last call) → 10/L_p.
- flag_out: same → 10/L_f.
- tmp: n_refs = 1 set + 1 use = 2 → log2(2)=1 → 2; range = from call1 to the end (shorter than L_p? no, L_p is from before call1 to call4 → tmp's range is a subset, shorter) → 2/L_t with L_t < L_p.

So tmp: 2/L_t; p_out: 10/L_p. If L_t ≈ 0.6 L_p → tmp: 3.3/L_p vs p_out 10/L_p → p_out wins. So p_out should get $16 in the unpinned version — but in my candidate flag_out got $16.

Hmm, in my candidate: s0($16) = flag_out (sp+52), s1($17) = p_out (sp+48), s2($18) = tmp.

Interesting: flag_out got $16 over p_out. Why? Because in the call `RotTransPers(a0, a1, p_out, flag_out)`, the 4th arg... hmm, in MIPS the args are a0-a3; the 3rd/4th args are copied into a2/a3 at each call: `move a2,s1; move a3,s0`. Maybe the "move" ties create a preference: the reg preferred for the a2 copy is s1?

In the target: `move a2,s2; move a3,s1` (p_out in s2, flag_out in s1) and later `move a2,s2; move a3,s1` again. In mine: `move a2,s1; move a3,s0`.

So both use the same pattern: p_out's reg is copied to a2, flag_out's to a3. The difference is which callee-saved regs they get.

The key: in the target, $16 (s0) is used for tmp; in mine, $16 is used for flag_out and $18 for tmp.

What if I make tmp "more important" so it wins $16? E.g., give tmp an extra use (a longer n_refs) — but that changes the code. Or shorten the live range of flag_out/p_out: e.g. compute p_out/flag_out later? They're used in all 4 calls, so their range is inherently long.

Alternatively lengthen tmp's live range? No, that lowers its priority.

Hmm, what if tmp were used in a way that makes its range longer (e.g. tmp is assigned before the calls)? It IS assigned by the first call. Hmm.

Wait, maybe the mechanism is different: maybe the target's $16 (s0) is used for tmp because of a "REG_EQUAL"/copy preference: `move s0,v0` — the call's return value goes directly into s0. In the target, the first RotTransPers call's result is moved to s0 ($16). In mine, `move s2,v0` ($18).

For the copy preference, gcc's global-alloc prefers to allocate the destination reg for a pseudo that is the target of a copy from a call's return... Hmm.

Let me think about the "preferred register" logic in gcc 2.7's global-alloc: for each qty, there's a "phys_reg_sugg" — the call's return reg v0 is preferred for the qty holding the call result. Then the allocation order: qtys are sorted by priority and each gets a reg; the "reg alloc order" for callee-saved is s0, s1, s2, ....

But in the target, s0 is used for tmp — the call-result qty. So the call-result qty got the first callee-saved reg. In my candidate, the call-result qty got $18 (the third). So in mine, two other qtys outranked it.

Which two? flag_out and p_out. Their n_refs are 5 each (1 set + 4 uses) vs tmp's 2 refs. pri_p = 10/L_p vs pri_tmp = 2/L_t. Since L_t < L_p (tmp's range is shorter), pri_tmp = 2/L_t > 2/L_p but is it > 10/L_p? Only if L_t < 0.2 L_p. Not the case. So the arg pointers outrank tmp → they get $16, $17 and tmp gets $18. That matches my candidate!

But the target has tmp in $16! So in the target, the priorities must be different — because the PINS changed the allocation (the pinned regs are removed from the pool and the qty structure changes). Ugh: with pins, flag_out is $17 and p_out is $18 (hard), so tmp is the only qty left → gets $16.

Without pins, the arg pointers (5 refs each) outrank tmp. So to reproduce the target, I need tmp to outrank them, or the arg pointers to be less referenced.

Idea: make the arg pointers have fewer refs! E.g., instead of passing `p_out` and `flag_out` to 4 calls, compute them inline? The addresses are constant (&v[3] and &v[3]+1) — the target computes them once into regs and reuses. If I write the expressions inline in each call, GCC would compute the addresses each time → 4 addiu's → different code (more instructions). The target has them computed once (2 addiu's) and moved 4 times. Hmm, but GCC's CSE might merge the 4 identical address computations into one! Then the pseudo would have 4 uses anyway (the merged reg) — same as now.

Alternatively: increase tmp's n_refs! What if tmp is used more than once? The target: `move s0,v0` (tmp = the return of the 1st call) and then `idx = func_801823D4(tmp, -0x1A)`. So tmp has 1 use. Can't add uses without changing the code.

Hmm, alternatively reduce the arg pointers' n_refs: what if p_out/flag_out are used via a *pointer to pointer*? No.

What if the two pointers are combined into one struct/array so that they're adjacent and one base register is used with an offset? E.g. if flag_out = p_out + 1, then GCC could compute one address and use offsets: `RotTransPers(a0, a1, p_out, p_out+1)`. In the target, the two addiu's are separate (sp+48 and sp+52) — with the same base sp. Hmm, if I write `RotTransPers(a0, a1, (s32*)&v[3], (s32*)&v[3] + 1)` the compiler computes one address (sp+48) and then +4 → but the target has `addiu s1,sp,52` — a separate addiu from sp, not from s1! So the target computes both from sp.

What if I keep it as is but make the ORDER of the args such that the allocation changes? The allocation order of the callee-saved regs is by priority; the arg pointers have equal priority (5 refs each, same range) → tie broken by qty number (order of appearance in the RTL). p_out is set first (it's the 3rd arg), then flag_out. So p_out should get $16 and flag_out $17... but my candidate has flag_out in $16!

Hmm, so something else. Maybe the ranges differ: flag_out's range vs p_out's range.

Wait, maybe I should look at the actual RTL order: in the source, the block declares:
```
register s32 *flag_out __asm__("$17") = (s32 *)&v[3] + 1;
register s32 *p_out __asm__("$18") = (s32 *)&v[3];
```
flag_out is declared FIRST → in the unpinned version, if the declarations become plain variables, the init order is flag_out then p_out. But the calls use p_out as the 3rd arg and flag_out as the 4th.

In my candidate: flag_out → $16, p_out → $17. If the RTL order is flag_out first, then the tie-break gives flag_out $16. ✓ consistent with my reasoning.

So to match the target (p_out → $18, flag_out → $17, tmp → $16), I need the priority order to be: tmp > flag_out > p_out? No wait: $16 = tmp, $17 = flag_out, $18 = p_out. So the priority order must be tmp, flag_out, p_out — but tmp has only 2 refs vs 5 for the others!

Unless... hmm. But wait: the target was built WITH the pins. With the pins, flag_out and p_out are hard regs, so tmp (the only qty) gets $16. Without pins, the arg pointers (5 refs) outrank tmp.

So to match, I need tmp to have a higher priority than the arg pointers, OR the arg pointers to have a lower priority.

pri = log2(n_refs)*n_refs*size/(death-birth).

What if the arg pointers' live ranges were LONGER (bigger death-birth)? They're live from their init to the last call. If I init them EARLIER (e.g. before the v[] setup), their ranges get longer → lower priority → tmp (2 refs, shorter range) might win. Let's compute: if L_p is much larger than L_t: pri_p = 10/L_p, pri_t = 2/L_t. Need 2/L_t > 10/L_p → L_p > 5*L_t. tmp's range: from the 1st call to func_801823D4 (the end). Hmm, tmp's range is maybe 60% of the whole function; L_p would need to be 5x that. Not feasible.

Alternatively, reduce n_refs of the arg pointers: what if p_out and flag_out are the SAME variable? No, they're different addresses.

What if I pass them as a single struct? The call signature is fixed (RotTransPers(s32, s32, s32*, s32*)).

Hmm, what if the 4 calls are made with the pointers computed inside a loop? No, the target has 4 explicit calls.

What about making the pointers' uses fewer by hoisting: e.g. the 4 calls all use the same p_out/flag_out. If the code were restructured so that the pointers are only used in the first call and then... no.

Alternative: make tmp have more refs! What if the code assigned tmp from the first call AND used it in a way that adds a ref without adding instructions? E.g. `tmp = RotTransPers(...)` and then `if (tmp == tmp) ...`? That's a no-op removed by the compiler.

Hmm, what about the "loop_depth" factor? In global-alloc, qtys in loops get priority adjustments. Not applicable.

What about making the arg pointers "conflicting" with each other so they can't share... they don't conflict anyway (both are live simultaneously).

OK, so for 8017FB50: the target's callee-saved assignment requires the arg pointers to be in $17/$18 and tmp in $16 — with the pins removed, GCC's priority puts the 5-ref arg pointers first. This looks like a wall of the type "global-alloc-prio" — matching the moves.md tag "greg-pri-refs" (global-alloc priority by refs).

Hmm, but wait. What if the arg pointers' n_refs could be reduced by the compiler itself? E.g. if the 4 calls were in a loop, the pointers would have 2 refs. Not our case.

What if I introduce the pointers as *fields of a struct* and pass &struct.field? Same.

Hmm, what if p_out/flag_out are computed as `&v[3]` and `&v[3]+1` — GCC computes them into 2 pseudos. What if instead I make v[3] a 2-element array and pass `&v[3]` and `&v[3]+1`? Same.

What if the *order* of declaration in the C source changes the RTL order (and hence the tie-break)? Currently: flag_out first, p_out second → flag_out gets $16. If I declare p_out first, then p_out would get $16 and flag_out $17 — but the target needs p_out in $18 and flag_out in $17, with tmp in $16. So even the best I can do with the tie-break is (p_out $16, flag_out $17, tmp $18) or (flag_out $16, p_out $17, tmp $18). Neither matches.

Unless tmp can be pushed to $16 by making it outrank. Let me compute the formula more carefully using gcc 2.7's global-alloc (global.c) — the priority there might be different from local-alloc's. In global-alloc (gcc 2.7), the qty priority is:

```
  /* Compute the number of registers needed. */
  ...
  weight = ... 
```
Let me look at global.c's qty_compare/qty_suggest_compare in the reference source. Actually gcc 2.7's global.c has `qty_compare` similar. But also global-alloc processes "reg classes" and for a class it computes a "cost". Also, importantly, global-alloc has the notion of "loop depth" and "reg_pressure".

Let me look at how global-alloc picks among callee-saved regs: `global_alloc` → for each reg class, it calls `alloc_qty` for each qty in priority order, choosing a reg via `find_reg` (which prefers regs by "reg_alloc_order" and considers the "not_preferred_regs").

Given the complexity, the practical question: can I make tmp the highest priority? One classic trick: make the call-result pseudo have MORE references by using the value more than once — but the target has 1 use.

Another classic trick: make the arg pointers' live ranges longer by initializing them earlier in the function. Let me estimate: if p_out/flag_out are initialized at the very top of the function (before the v[] setup and the calls), their ranges would grow by ~20 instructions while tmp's range stays. L_p might become 1.3x L_t. Not 5x.

Hmm, what about the opposite: shorten tmp's live range? It's already minimal.

What if tmp is not a variable at all: `idx = func_801823D4(RotTransPers(...), -0x1A);`? But the 2nd-4th calls come after the first call... The first call's result is used at the end. If I inline the first call into the func_801823D4 call, the result's live range would shrink to just that call → but the 3 other calls come between → the value must live across them anyway. Unless I reorder: move the func_801823D4 call BEFORE the other 3 calls? That changes the semantics (order of calls) — the target has the 4 RotTransPers calls then func_801823D4. Reordering would change the instruction order → score would go up. Hmm, but actually: if I move `idx = func_801823D4(tmp, -0x1A)` to right after the first RotTransPers call, then tmp's live range is short (2 uses close together) → tmp gets a high priority → tmp wins $16! But the call order changes: the target's order is call1, call2, call3, call4, then func_801823D4. If I move func_801823D4 earlier, the instruction order changes → the score would be > 0 (COUNT/REG diff). Unless the scheduler... no, the call order in the asm would differ → not a MATCH.

Hmm.

OK, what about the possibility that the whole 8017FB50 target's callee-saved assignment could be matched with a different code structure? Let me look at the full target asm to understand better. Let me disassemble the target for 8017FB50.

Actually, let me think about "n_refs" more carefully. In gcc 2.7's global-alloc, the qty's n_refs is the number of references of the *registers* in the qty. For p_out: 1 set + 4 uses = 5 refs. But wait — global-alloc's qty grouping: p_out is used in 4 different calls, and each use is preceded by a `move a2,p_out` — a copy insn. The copy might "tie" the reg with a2? Not really.

Hmm, also: does the 4th call's `move a3,flag_out` count? Yes.

OK, let me consider: is it possible that the previous attempt's candidates (12, REG-callee) include some that differ only in the callee-saved assignment? All are 12. The score 12 = the register mismatch (4 moves with different regs).

Honest assessment for 8017FB50: the target needs tmp in $16 and the two arg pointers in $17/$18. Without pins, GCC's priority (n_refs 5 vs 2) puts the arg pointers first. The only lever: increase tmp's refs or decrease the arg pointers' refs — both change the code.

Hmm, wait! What about this: what if the arg pointers are NOT variables but computed expressions that CSE merges? Then GCC's CSE creates a reg with 4 uses (same as now). Same.

What if the 4 calls take the SAME pointer variable and the other is derived: e.g. flag_out = p_out + 1 → then the compiler would compute p_out once (5 refs) and p_out+1 (4 refs + 1 set) → 5 refs for a derived value, but the derived value's n_refs = 1 set + 4 uses = 5 as well, and its range starts later (shorter) → higher priority. Hmm, that changes the asm: the target has `addiu s1,sp,52` (sp+52 computed from sp) not `addiu s1,s2,4`. So the derived form would produce different instructions → not a match.

So 8017FB50: WALL (global-alloc priority by refs: the two 5-ref arg pointers outrank the 2-ref call-result tmp, so $16 goes to an arg pointer, not to tmp).

Hmm, hold on. Let me reconsider: is it possible that the target's $16 (s0) for tmp comes from a *copy preference* rather than priority? In the target, `move s0,v0` — the call result is moved to s0. In gcc 2.7 global-alloc, there's a "copy preference" mechanism: if a qty is the destination of a copy from a specific reg (like v0 from a call), it may get a preferred reg. The target's pinned regs are $17/$18, and the qty for tmp gets $16 — the first free callee-saved reg.

In my unpinned version, the arg pointers (5 refs) get $16/$17 and tmp gets $18. If the pins were removed, would the arg pointers really outrank tmp? The evidence says yes (my candidate).

So the wall mechanism: "global-alloc prio by n_refs: the 5-ref arg pointers take $16/$17, the 2-ref call result takes $18".

Can I flip it by making the arg pointers have fewer refs? What if I pass the same pointer variable to all 4 calls and compute flag_out from it in a way that keeps 4 uses of a *single* pseudo? E.g.:

```
s32 *p_out = (s32 *)&v[3];
s32 *flag_out = (s32 *)&v[3] + 1;
```
Both needed.

Alternatively, what if the args are passed as expressions so that each call has a *different* pseudo? Then each pseudo has 2 refs (1 set + 1 use) but the address computations would be duplicated (8 addiu's) → different code.

Hmm, unless CSE merges them into one pseudo with 4 uses (that's what happens now).

What if CSE does NOT merge them (because the address is computed from a variable that changes)? E.g. `&v[3]` — v is an array; the address is sp+48. If the address were computed from a pointer that changes between calls, CSE wouldn't merge, but then the asm would have 4 addiu's.

I think 8017FB50 is a WALL.

Now 8014CF04: the diff shows the target uses $17 (s1) for q and $16 (s2)? Let me re-read the target vs candidate:

target:
```
addiu sp,sp,-40
sw s2,24(sp)
move s2,a0
sw s4,32(sp)
move s4,a1
sw s3,28(sp)
...
sw ra,36(sp)
beqz v0,...
sw s1,20(sp)
addiu s1,s0,117     <- q = p + 0x75 in s1 ($17)
lhu v0,0(s0)
beqz v0,...
lhu v0,-25(s1)      <- *(u16*)(q-0x19)
...
lw a1,-29(s1)       <- *(s32*)(q-0x1D)
...
lh v0,-107(s1)      <- *(s16*)(q-0x6B)
...
lw a0,-85(s1)       <- *(s32*)(q-0x55)
...
sb v0,-1(s1)        <- q[-1] = 1
lbu a1,0(s1)        <- q[0]
...
addiu s1,s1,268     <- q += 0x10C
```
Wait, the target has `sw s1,20(sp)` (s1 = $17) — but the pin was `register u8 *q __asm__("$17")` → $17 = s1 ✓. And s2 = a0 (param_1), s4 = a1 (param_2), s3 = param_3? Let me see: `sw s3,28(sp)` and later `lhu v0,0(s3)` (param_3), `move a3,s3`. And s0 = p (the loop pointer).

candidate (unpinned):
```
addiu sp,sp,-48
sw s1,20(sp)
move s1,a0     <- param_1 in s1
sw s5,36(sp)
move s5,a1     <- param_2 in s5
sw s3,28(sp)
sw ra,40(sp)
sw s4,32(sp)
sw s2,24(sp)
addiu s4,s0,117   <- q in s4 ($18)
addiu s2,s0,116   <- an extra! (q-0x19?)
```
So the candidate has 4 extra instructions: an extra addiu (s2 = s0+116) and extra sw (s4) — because the candidate needs an extra register for `q-0x19` (it computed s2 = q-0x19 as a separate reg). And the frame is 48 vs 40.

The target: q in $17 (s1) and the accesses are `lhu v0,-25(s1)` (q-0x19) etc. — all offsets from q. The candidate: `addiu s4,s0,117` (q) and `addiu s2,s0,116` (q-0x19 = s0+116) — it materialized a second base for the -0x19 accesses, and the other accesses use s2 with different offsets (-24, -28, -106, -84) — i.e. it merged q-0x19 with the other offsets (q-0x1D = s0+116-... hmm).

So the difference: the target keeps ONE base (q) and uses offsets -0x19, -0x1D, -0x6B, -0x55 relative to it; the candidate uses two bases (q and q-0x19... wait, in the candidate: lhu v0,-24(s2) [q-0x19], lw a1,-28(s2) [q-0x1D], lh v0,-106(s2) [q-0x6B], lw a0,-84(s2) [q-0x55] — so s2 = q-0x19 = s0+116 and all the accesses are relative to s2 (offsets -24=-0x18? hmm: q-0x19 = s2, so *(u16*)(q-0x19) = *(u16*)(s2+0) → but the candidate shows lhu v0,-24(s2)... that doesn't match.

Let me recompute: in the candidate, `addiu s2,s0,116` → s2 = s0 + 0x74 = q - 1 (q = s0+0x75). Then:
- `lhu v0,-24(s2)` = s2 - 24 = q - 1 - 24 = q - 25 = q - 0x19 ✓
- `lw a1,-28(s2)` = q - 29 = q - 0x1D ✓
- `lh v0,-106(s2)` = q - 107 = q - 0x6B ✓
- `lw a0,-84(s2)` = q - 85 = q - 0x55 ✓
- `sb v0,0(s2)` = q - 1 = q[-1] ✓
- `lbu a1,0(s4)` = q[0] where s4 = q ✓
So the candidate uses s2 = q-1 as the base for the negative offsets and s4 = q.

The target uses a single base q (s1) with offsets -25, -29, -107, -85, -1, and +0 for q[0].

So the candidate needed 2 registers (s4 for q, s2 for q-1) and 2 extra instructions (the addiu + the extra sw). The target has 1 register.

Why does the candidate compute q-1? Because GCC decided to use a common base for the negative offsets (an "address optimization" / induction variable strength reduction in the loop: q-1 is loop-invariant relative to q, so GCC hoisted `q-1` into a register). With the pin, q is in $17 and GCC couldn't create the extra base? Hmm, the target has `addiu s1,s0,117` (q) only.

The candidate's frame is 48 (it saves s1, s2, s3, s4, s5, ra) vs the target's 40 (s1, s2, s3, s4, ra).

So to match, I need GCC to not create the q-1 base. That means the accesses should be relative to q directly. In C: `*(u16 *)(q - 0x19)`, `*(s32 *)(q - 0x1D)`, `*(s16 *)(q - 0x6B)`, `*(s32 *)(q - 0x55)`, `q[-1] = 1`, `q[0]`.

The candidate's C is the same as orig (it's the unpinned orig). So the difference arises from the pin: with q pinned to $17, GCC... hmm, why would the pin prevent the q-1 base?

Maybe because with the pin, the register pressure was lower (one fewer reg needed) — no. Or because the loop's induction variable optimization differs.

Actually, maybe it's the opposite: the target's asm was produced from a source where `q[-1] = 1` was written as `*(u8 *)(q - 1) = 1`? Both are the same. GCC's "address base" optimization chooses a base register and offsets; the candidate chose q-1 as the base because q-1 is used 5 times (4 loads + 1 store) vs q used 2 times (q[0] load and the increment). With the pin, the same choice should apply...

Unless the pin changed the register pressure such that GCC's decision differed. Hmm.

Wait, maybe the difference is in how the *loop* was structured. With `q` in a hard reg $17, the loop increments q by 0x10C. Without the pin, GCC might have strength-reduced the loop differently.

Let me look at the candidate's loop tail:
```
addiu s0,s0,268
addiu s2,s2,268      <- extra increment (for the q-1 base)
...
addiu s4,s4,268      <- q increment
```
So the candidate increments both s4 (q) and s2 (q-1) — an extra instruction in the loop.

To avoid the q-1 base, I could write the C so that the offsets are all relative to q and q-1 isn't a common base. E.g. write `*(u8 *)(q - 1) = 1;` instead of `q[-1] = 1;` — identical semantics, but maybe the address spelling changes the pattern. Hmm, unlikely to matter.

Alternatively: express the negative-offset accesses via a second pointer variable? That'd add instructions.

Hmm, what if the accesses are written with q as a `u8 *` but the compiler's choice of base is driven by the number of uses: q-1 is used 5 times (as a base). If I changed the spelling of one access to be relative to q (e.g. `*(u8 *)(q - 1)`), the count stays.

What if I use a different base for the group of 4 negative accesses, e.g. `s32 *r = q - 0x1D;`? Then the accesses would be r+4, r-0x4E, r-0x38 → different asm.

Hmm. Alternatively, maybe the *pin* isn't the cause: maybe the difference is that the target was compiled from a slightly different source (the "true" source) and the pin is a red herring. The task is: find a lever-free body that compiles to the target asm. The target asm has q in $17 with a single base. So I need to write C that produces that.

The single-base version is what GCC produces when it doesn't create the q-1 base. GCC's "address base" selection in the loop (loop.c's induction variable / address optimization) prefers the base that has the most uses. To make GCC pick q as the base, I could reduce the uses of q-1: e.g., write one of the four negative accesses relative to q instead of q-1? They're all relative to q in the source! The compiler chose q-1 as the base because q-1 is used 5 times.

Wait, why would GCC choose q-1 as the base? Because the offsets -0x19, -0x1D, -0x6B, -0x55 relative to q are all within a 16-bit range; relative to q-1 they're -0x18, -0x1C, -0x6A, -0x54. Both work. GCC's loop.c "address base" selection picks the base with the fewest distinct offsets? Or it picks based on "the base register that is incremented in the loop" (q) vs a derived one?

Hmm, GCC 2.7's loop.c has an optimization that hoists `q-1` (an address that's loop-invariant relative to the induction variable) into a register. Since q-1 is used 5 times, it's worth it. But the target didn't do it.

Difference: the target's q is a hard reg $17. With a hard reg, GCC's loop.c might treat the address differently.

Hmm, alternatively: in the target, is q really $17? `sw s1,20(sp)` + `addiu s1,s0,117` → s1 = $17 ✓ (MIPS: s0=$16, s1=$17, s2=$18, s3=$19, s4=$20, s5=$21).

The candidate: s4 = $20 for q, s2 = $18 for q-1, s1 = $17 for param_1, s5 = $21 for param_2, s3 = $19 for param_3.

The target: s1 = $17 (q), s2 = $18 (param_1), s3 = $19 (param_3), s4 = $20 (param_2), ra.

So in the target, the callee-saved usage: q → $17, param_1 → $18, param_3 → $19, param_2 → $20. In the candidate: param_1 → $17, q-1 → $18, param_3 → $19, q → $20, param_2 → $21.

So even the ORDER of the callee-saved allocation differs (q should be first!).

This item looks like a deep wall: the target's allocation has q (the loop induction pointer) in the first callee-saved reg, and no extra base.

Given the time budget, let me now prioritize:
- 8017EEB0: MATCH ✓ (already achieved).
- 8017E4E0: WALL at 11 (after ~60 variants).
- 8017D3A0: same shape as 8017E4E0 → run the same generator variants (cheap) to confirm 11, then WALL.
- 8017FB50: WALL at 12 (REG-callee) — but let me try a few variants (e.g. declaring p_out before flag_out, initializing them earlier, using different types like `u8 *`).
- 8014CF04: WALL at 34 — try a few variants (e.g. different spellings of the q-1 store, using `q - 1` explicitly, changing the loop to a for/goto, etc.).

Since the previous attempt already tried many variants for 8017FB50 and 8014CF04 (the candidate files), let me check what they tried (summarize.py) to avoid repeats, then try a few new ideas.

Time: ~18:45. I've used 70 min. Let me move fast.

First, let me record what I have: write notes.md for 8017E4E0, 8017EEB0 and append rows to results.tsv as I go. Let me do the results rows for 8017EEB0 (MATCH) now, then continue.

Actually, to be efficient: let me first run the 8017D3A0 variant generator (same as 8017E4E0 but with struct-member stores) to see if it cracks — maybe the struct-typed version allocates differently! The 8017D3A0 orig uses struct members ((Unkstruct_8017D3A0 *)p)->unk10 etc. That's a different code shape → maybe the allocation differs → could crack!

Let me write a generator for 8017D3A0 with the same knobs.

Note the struct field names: unk10, unk18, unk20, unk28, unk11, unk19, unk21, unk29, unk12, unk1A, unk22, unk2A, unkF, unk13, unk1C, unk2C, unk16, unk1E, unk14, unk24, unk26, unk2E.

Let me write gen_g06_d3a0.py.
