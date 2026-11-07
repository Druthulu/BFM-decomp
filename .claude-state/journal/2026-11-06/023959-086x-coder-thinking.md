---
ts: 2026-11-06T09:39:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6BO7NHc37ZTgFgVaUlWs
---
Key: for a pseudo register (>= FIRST_PSEUDO_REGISTER), reading it adds a dependence on `reg_last_sets[regno]` (the last *set*), not uses. So a read-read pair has NO dependence. That's why the copy can move above the store in win (both read 74, no set of 74).

Then why does the asm get an anti-dep on the store? Because the asm branch (for non-volatile asm) only does `sched_analyze_2` on inputs — same as a normal read. Hmm, but the lreg dump showed `(insn 88 ... (insn_list:REG_DEP_ANTI 86 (nil)))` — an anti-dep. Where from? Maybe reg 74 is a *hard* register at sched1 time? s0 is a callee-saved variable, but before local-alloc, s0 is a pseudo (reg 74). Hmm.

Wait — maybe the anti-dep comes from the store's base being recorded as a use in `reg_last_uses[74]`, and the asm's input `(reg 74)` triggers `sched_analyze_2` → pseudo branch → only depends on sets. No.

Hold on, maybe the anti-dep 88→86 comes from a *memory* dependence: the asm has no memory operand, so no.

Hmm, let me look at the pre-sched RTL to see the actual dependency notes. Actually the lreg dump showed insn 88 with `(insn_list:REG_DEP_ANTI 86 (nil))`. That's after sched1 (lreg runs after sched1). The REG_DEP_ANTI note was added by sched1.

Let me look for where REG_DEP_ANTI is added for ASM: in `sched_analyze_insn`, for asm operands with no outputs? Let me look at the whole ASM_OPERANDS branch in sched_analyze_1 (for the outputs) and `sched_analyze_insn`.

Actually the branch I read is in sched_analyze_2. `if (code != ASM_OPERANDS || MEM_VOLATILE_P (x))` — for our non-volatile asm, skipped. Then inputs analyzed. So no anti-dep.

Unless... the asm is treated as an ASM_INPUT somewhere? The rtx is ASM_OPERANDS. Hmm.

Wait, maybe the anti-dep 86→88 is not from the asm's analysis but from the *store*'s analysis: the store is analyzed first (insn 86), and then when analyzing the asm... no.

Let me look at sched_analyze_insn for the case of an insn with no sets (pure use): it might do something special.

Actually, let me check whether the anti-dep direction: `(insn 88 ... (insn_list:REG_DEP_ANTI 86 (nil)))` means "88 depends on 86 with anti". In `add_dependence(insn, dep, REG_DEP_ANTI)` where insn=88, dep=86. This is called from the asm branch's loop over reg_last_uses: `add_dependence (insn, XEXP (u, 0), REG_DEP_ANTI)`. That loop runs only if `code != ASM_OPERANDS || MEM_VOLATILE_P (x)`. So either our asm is considered volatile (no) or the code is ASM_INPUT... 

Hmm wait, maybe MEM_VOLATILE_P(x) is true for the ASM_OPERANDS rtx because the asm has `__volatile__`? Our keepalive is `__asm__("" :: "r"(s0))` — NOT volatile. But the *other* keepalives in this header... this item has one keepalive. Let me check the exact text: line 27 of the header: `__asm__ __volatile__("" : : "r"(s0));` — YES, it's `__asm__ __volatile__`! I misread. So MEM_VOLATILE_P is true → the asm clobbers all hard registers, all pseudos, and memory → it's a full scheduling barrier, and it adds REG_DEP_ANTI from every last use and a set-dependence from every last set.

So the keepalive as a *volatile* asm is a barrier. Removing it lets sched1 move the copy up.

Real C that acts as a scheduling barrier: a real function call (calls are barriers), or a volatile memory access? In sched1, a volatile MEM read/write is handled: `case MEM: ... if (MEM_VOLATILE_P(x))` → treated like an asm? Let me check sched_analyze_2's MEM case for volatile.

But using `volatile` is a lever (it changes optimization). Is there a *real* C construct? A real function call between the store and the RMW would be a barrier, but the target has no call there.

What about a *loop*? No.

Hmm, so what did the original C have between the store and the RMW? The target's code shows the copy after the store, which means the original compiler's scheduler kept it there. Maybe in the original C, the store came *after* the copy in source and the scheduler moved the copy... no.

Let me reconsider: maybe the original C's statement order was:
```
*(u32 *)(s0 + 0x44) = *(u32 *)(s0 + 0x44) & 0xFFFFFFFB;   // RMW first
*(u16 *)(s0 + 0x188) = 0;                                  // store second
func_801553C0(s0);
```
And the target's order (store at 37, RMW at 39) — the scheduler reordered the store before the RMW? In t3 I tested exactly this and got score 2 with the store after the copy (at 40). Hmm, but t3's score was 2, meaning one 2-insn diff. So the store ended at 40 anyway.

What if the original C's RMW was *before* the store AND the call argument was computed differently? 

Alternatively, maybe the original C had the RMW *after* the call:
```
*(u16 *)(s0 + 0x188) = 0;
func_801553C0(s0);
*(u32 *)(s0 + 0x44) = ... & ~4;
```
Then the copy would be at the call (after the store) — matching the target's copy position! And the RMW after the call would use s0 (a0 is clobbered by the call...). But the target has the RMW *before* the call (lw/and/sw then jal, with the sw in the delay slot). Hmm, the sw at 43 is in the jal's delay slot (jal at 42, sw at 43). So the RMW is before the call, with its store in the delay slot.

Wait, actually: `jal` at 42, and the delay slot at 43 is `sw v0,68(a0)`. A delay slot instruction executes before the branch target but after the jal is issued. The store is part of the RMW. So the RMW is immediately before the call.

OK so what if the original C had the RMW before the store in source, and the scheduler moved the store up before the RMW but after... no.

Let me approach empirically: try source orders and see which yields score 0. I've tried: store-then-RMW (current) → 2; RMW-then-store (t3) → 2. Let me check t3's diff again — it was identical (store at 40 via a0). So no.

What if the store is *inside* the RMW statement via a comma:
`*(u32 *)(s0 + 0x44) = (*(u16 *)(s0 + 0x188) = 0, *(u32 *)(s0 + 0x44) & 0xFFFFFFFB);`
The comma sequences the store before the load. This creates a real dependency: the load (read) is after the store (write) to different addresses, but the compiler sees a sequence point; does it create an RTL dependency? The load and store are separate insns; the load's address uses s0; no dependency on the store. sched1 could still move the copy up. But the store would be before the load in the RTL order, and sched1 might keep it.

Hmm, honestly the copy position is a scheduling artifact.

Let me look at what happens with a real *use* of s0 that can't be rewritten: a second call? No.

What about the `func_801553C0(s0)` call itself: if the RMW were written *after* the call in source but scheduled before it... no.

Let me try the comma-expression and also try making the store's value depend on a variable that the copy defines (e.g., use a0 via a cast? no).

Actually — wait. What about the `v44` variable? In the target, the RMW uses a0. What if the source's RMW were `*(u32 *)(s0 + 0x44) = *(u32 *)(s0 + 0x44) & 0xFFFFFFFB;` and the store were written via a *different expression* that the compiler can't rewrite to a0 because it's before the copy... 

Let me think about it differently: the copy is placed by sched1 as early as possible (it's a "birth" insn with high priority). The target's copy is after the store. So in the original build, something prevented it — most likely a barrier: a volatile asm (like our keepalive!), a call, or a volatile access. In the original C, maybe there was a call or the store was volatile? The target's store `sh zero,392(s0)` is a plain sh.

OR: the copy is placed after the store because in the original RTL the copy insn is *later* and sched1's dependence on the store exists via reg_last_uses if the copy's source reg is a *hard* reg? No.

Hmm, what if the original C didn't have the `s0` copy at all: the call `func_801553C0(s0)` — the arg copy is a0=s0. The target has `move a0,s0`. So there is a copy.

What if the original C passed a *different* expression, e.g. `func_801553C0((s32)s0)` (t6 = 2, same).

Let me look at the target's insn 38 `move a0,s0` position: after the store, before the RMW load. This is exactly the natural place: the copy is needed for the RMW's uses (rewritten to a0) and the call. The scheduler put it there in the target. In ours, it went one insn earlier (above the store).

The only difference is sched1's choice. With the store before the copy in the schedule, local-alloc rewrote the store to a0.

What if we make the store's base *not* s0 but a separate expression that can't be rewritten, e.g., `*(u16 *)((u8 *)s0 + 0x188) = 0;`? The cast is a no-op; the base is still reg 74.

What if we compute the store's address into a variable before the store: `u16 *p188 = (u16 *)(s0 + 0x188); *p188 = 0;` — p188 is a pseudo = s0+0x188; the compiler would fold it back to s0+offset.

What if the store is `*(u16 *)(s0 + 0x188) = 0;` but written *after* the call in source and the compiler sinks it? no.

Let me try a few:
- comma expression
- store via a pointer variable declared at the top and assigned after the if
- swap: put the RMW *before* the 0x188 store and the call after (already t3)
- make the call argument `s1 ? s0 : s0`? no.
- introduce a real use of s0 between the store and the RMW: `*(u16 *)(s0 + 0x18A) = *(u16 *)(s0 + 0x18A);`? That's an identity store (real but pointless; changes codegen? It would add lhu+sh — target has no such). No.

Let me look at the problem from the "what if the store were a different width/type" angle: `*(u16 *)(s0 + 0x188) = 0;` — maybe the original was `*(s16 *)(s0 + 0x188) = 0;` — same insn.

Honestly, maybe this is a WALL too. But the budget: item 3 has 25 lines, 20-30 min. It's 02:40 now (started 02:32:49) = 7 min. I have time for ~15 more min of attempts.

Let me try the comma expression and a few more.

Actually, here's a thought: what if the original C had the 0x188 store *twice* — no.

What about the `deadlocal[2]` unused variable in item 2 — not here.

What if we make the store's base `s0` used by a *pointer* that is passed to the call: e.g., `func_801553C0((s32)(u8 *)s0);`? Same.

Let me think about local-alloc's copy propagation more: the copy `(set a0 74)` and the store `(set (mem (plus 74 392)) 0)`. Local-alloc propagates a0 to 74's uses if 74 is dead after the copy and the copy is before them. In the target, the store is before the copy → not rewritten.

The position of the copy in the schedule is what matters, and sched1's decision depends on the ready-list priorities. The store insn 86 has priority 1 and "greater potential hazard" — in win it was scheduled *after* the copy (T-13) because the scheduler preferred the copy at T-14. In orig, the store went first (T-15) because at T-15 the only ready insn was 86 (the asm at 88 was blocked by its anti-dep on 86).

So in win, both 86 and 97 were ready at T-14, and the scheduler chose 97 (copy) first, then 86. Why? "insn 86 has a greater potential hazard" — the store was delayed. This is the scheduler's hazard avoidance: stores have a hazard against the previous load? It picks the copy first to avoid a store-load hazard? 

Could a real-C change alter the ready list such that the store is chosen first? E.g., if the store had a different address mode (addiu+lh vs immediate offset)? The store is `sh zero,392(s0)` — immediate offset.

What if the store were `*(u16 *)(s0 + 0x188) = v44;`? no, v44 is a u32.

What if the store's value were a *variable* (e.g., a zero temp) rather than the constant 0? That would add an insn. Target stores zero.

Hmm, what if the source had `*(u16 *)(s0 + 0x188) = 0;` but with the store *before* the inner if? Then the join block order changes.

OK let me try the comma expression and pointer variants quickly, then decide. If nothing, WALL with best 2. But a WALL needs ≥20 min and ≥30 tries — I'd need ~20 more tries. Fine, I can generate variants.

Actually, wait! Let me reconsider: maybe the real C had the RMW *between* the store and the call but written as `*(u32 *)(s0 + 0x44) &= 0xFFFFFFFB;` and ALSO the call's argument as `s0` — the compiler's copy is at the RMW because the RMW uses s0... but our current source IS that. The difference is purely sched1's choice.

Let me look at the *target's* sched behavior: the target's compiler (same gcc 2.7.2) with the original C produced the copy after the store. So the original C's RTL must have had a barrier or different order. The most likely: the original C's statement order was RMW-then-store? Let me test that more carefully with the RMW's load/store in the target order... t3 gave score 2. Hmm.

Or the original C had the store *after* the call? Let me test that: store after the call — the target has the store before the copy/call, so the scheduler would have to move it up before the call (possible? sched1 can move a store above a call? No! Calls are barriers: `last_function_call` — sched_analyze_1 for a CALL sets all call_used regs clobbered and flushes pending lists. Insns can't move across calls in sched1).

So the store must be before the call in source.

What if the store was before the inner if? The target has it after the if/else join (insn 36 is the else-branch store, 37 the join store). If the store were before the inner if, it would appear at ~insn 16. No.

Hmm OK. Let me try the comma and a few oddities, then likely WALL.

Actually — another idea: the target's copy `move a0,s0` might be created not for the call but for the RMW's base if the RMW were written through a *different variable*: e.g., the original C might have had `p = (u32 *)s0; p[0x11] &= 0xFFFFFFFB; func_801553C0(p);` — then the copy a0=p... same.

Or the original might have had a local pointer variable `s32 *ps = s0;` used for the RMW and the call. The copy a0=ps would be born at ps's first use (the RMW), after the store! That's plausible: 
```
s32 s0 = *(s32*)(s1 + 0x4C);
...
*(u16 *)(s0 + 0x188) = 0;
ps = s0;                          // or ps used directly
*(u32*)(ps + 0x44) &= ~4;
func_801553C0(ps);
```
If `ps` is a separate variable assigned after the store, the copy would be born there. But the compiler would coalesce ps with s0 (copy propagation) — unless the assignment is after the store and s0 is still used... Let me try:
```
s32 s0 = ...;
...
*(u16 *)(s0 + 0x188) = 0;
s32 ps = s0;   // declaration after statement — C89 issue; declare at top, assign here
*(u32 *)(ps + 0x44) = ...;
func_801553C0(ps);
```
Let me try that (v6-like u4 but assigning after the store and using ps for both RMW and call). u4 did `s0b = s0;` after the store and used s0b for the RMW and call → score 2. Hmm, u4 already tested this. It gave 2.

OK, let me try the comma expression and a couple more, then wall.
