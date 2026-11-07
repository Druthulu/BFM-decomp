---
ts: 2026-11-06T17:01:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HPS5CJc26GKKchMRFkuW
---
z3's first modulo: n = s0 (the subu at 8e08), but the intermediate q copy is v1 (crosses the call). Target has the q copy in s0.

The target's expansion uses s0 for the q copy too. So in the target, the `%` temp's q copy is s0 (crossing the call), and the result (also s0) is n. So the expansion temp crosses the call AND is s0.

In z3, the temp (q copy) is v1 and the result n is s0. So the temp and n are different pseudos; the temp doesn't cross a call in z3's RTL? Actually the temp (v1) IS used after the call (subu s0,v1,v0 at 8e08 after jal 8e04) — so v1 crosses the call! But v1 is call-clobbered... That means the value in v1 across the jal is destroyed by the call! Wait, `subu s0,v1,v0` uses v1 which was set at 8dec before the jal at 8e04 — the jal clobbers v1! That would be a bug... unless the call doesn't clobber v1? MIPS calls clobber v0,v1,a0-a3,t0-t9. Hmm, but the target's rand() might preserve v1? No, the ABI says caller-saved.

Wait, look: 8dec `move v1,v0`; 8df0 `bgez v1,8dfc`; 8df8 `addiu v0,v1,4095`; 8dfc `sra s0,v0,0xc`; 8e00 `sll v0,s0,0xc`; 8e04 `jal rand`; 8e08 `subu s0,v1,v0`. So v1 = q, used after the call. v1 is call-clobbered! Unless... this is a compiler bug? No — maybe the callee preserves v1? Actually rand() is a library function; it may preserve v1 in practice, but the compiler can't rely on that.

Hmm, wait: maybe this is fine because the call is to rand() and the register allocator treats v1 as call-clobbered; using it across the call would be a bug. Unless the value in v1 is re-loaded... no.

Let me re-read: 8e04 jal rand — the second rand. 8e08 subu s0,v1,v0. v0 is the new rand result; v1 is q (the first rand result). If the call clobbered v1, the result would be wrong. So either the compiler knows rand doesn't clobber v1 (impossible) or... 

OH WAIT. Maybe z3 is WRONG code (miscompiled) — but the delever tool only checks instruction match, not semantics. But gcc wouldn't produce a clobber bug.

Hmm, unless the MIPS ABI's call-clobbered set... In GCC 2.7.2's MIPS config, the call-used registers are defined by CALL_USED_REGISTERS. Let me check: for the PSX, maybe only a0-a3, t0-t9, v0, v1? v1 is definitely call-used. Hmm.

Actually, maybe I misread the order: the `jal rand` at 8e04's delay slot is `sll v0,s0,0xc`? No: 8e00 sll v0,s0,0xc; 8e04 jal; 8e08 subu. The delay slot is the insn at 8e08? No — the jal's delay slot is the NEXT insn (8e08) in the object listing? In the objdump listing, the instruction after `jal` is its delay slot. So `subu s0,v1,v0` at 8e08 is the DELAY SLOT of the jal — it executes BEFORE the call takes effect! Yes! In MIPS, the delay slot instruction executes before the branch/call transfers. So the subu runs before rand() executes, using v1=q and v0=the result of the PREVIOUS rand (the `sll v0,s0,0xc` set v0). 

So the order is: 8e00 sll v0,s0,0xc; 8e04 jal; 8e08 (delay slot) subu s0,v1,v0. So the subu uses v0 = s0<<12 (the rounded value) and v1 = q. Fine, no bug. And v1 doesn't cross the call.

So z3's temp v1 does NOT cross the call (it's consumed in the delay slot).

And the target's temp is s0 for the same computation. So the pin's s0 is the difference.

OK. Let me think about what makes the `%4` temp s0 in the target's original. Since the pin is a hard-reg pin, the target's s0 for the temp is the pin. But the target is the original game's code... The decompiler's pinned source reproduces the original, so the original's allocation had the temp in s0. 

Maybe in the original, the `%4` temp crossed a call. Let's test the hypothesis: what if the original computed the two velocity values with a shared expression that made the temp cross? 

Alternatively, maybe the original source used `%` on a *variable* whose value crosses calls: e.g.:
```
q = rand();
n = q % 4;
m = n << 16;
```
`q % 4` expansion: temp = q; q<0? +3; >>2; <<2; q - temp. The temp here is q itself? No, gcc's expansion creates a copy of q.

Hmm.

Let me try: what if we compute `n = q % 4;` instead of the manual expansion? The `%` expansion is the same code. Then `m = n << 16;`. Let's test that — it's cleaner C and might allocate differently (n as the result of %).

Actually our source currently expands the modulo manually (decompiler style). The original probably had `rand() % 4`. Let me try the natural form:
```
q = rand();
m = (q % 4) << 16;
if ((rand() & 1) == 0) m = -m;
```
and similarly for the second. This is the natural C. Let me test.

But the target's expansion: `move s0,v0; addiu s0,v0,3; sra s0,s0,2; sll s0,s0,2; subu s0,v0,s0` — this is exactly `q % 4` where q is the rand result. The temp is the q copy. local-alloc would give it... v1 (no call crossing). Hmm, unless the `%` temp is live across the sign call.

Wait — actually in the target, look at the sign call position: the `subu` (which ends the % expansion) is at 8ea4, BEFORE the sign jal at 8ea8. So no crossing. The temp is s0. So the original's temp was s0 for a non-crossing range. That means local-alloc picked s0 over v1. Why?

find_free_reg picks the lowest-numbered free register. At the temp's birth (right after the rand call), which registers are live? v0 = q (live), v1 = free, a0-a3 free, s0 = ? In the target, s0 is FREE at that point? Let's see: s0 was used for the first modulo temp and `move a1,s0` at 8e50; after the func_8012B0B4 call, s0 is free. Then at 8e90 the `%4` temp is born. v1 is free, so find_free_reg would pick v1... unless v1 is live (holding something). 

In the target, after the call at 8e54, v0/v1 are clobbered. The `lw v1,16(sp)` at 8e5c loads sp10. Then `sra v1,v1,0x10` etc. Hmm.

Let me look at the target's lreg dump (pinned) to see which pseudo the %4 temp is. Actually, with the pin, the source's n is $16, so the temp IS the hard reg. So the target's temp-in-s0 is entirely the pin.

So the original's allocation must have had the temp in s0 for a different reason. Let me consider: maybe the original source is:
```
n = rand() % 4;
m = n << 16;
```
where n is a *function-scope variable used across the whole function* — then n's live range might cross calls if used later. In the target, n is used in comp1 and comp2; if the variable n's value from comp1 were still live... no.

Hmm, hold on. Let me reconsider the target's register s0 across the function:
- 8df0-8e04: first modulo temp (q copy) — crosses the jal at 8e00? The subu is at 8e04 (after jal 8e00)? Look: 8e00 `jal rand`; 8e04 `subu s0,v0,s0` — the subu at 8e04 is the delay slot of the jal at 8e00? The objdump shows 8e04 as the instruction after jal 8e00, so yes, it's the delay slot. So the temp doesn't cross.
- So NO s0 use crosses a call in the target! Then why s0? Because the pin.

Therefore, without a lever, gcc would use v1 (as mine does). The pin is load-bearing and the real C must make gcc choose s0.

Hmm, is there a real C move that makes a *block-local* temp allocate to a callee-saved register? Yes: if the temp crosses a call. So we need to make it cross a call in the RTL.

Idea: reorder the source so the `%4` computation is split across the sign call:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
s32 bit = rand() & 1;   /* call */
m = (q - n) << 16;
if (bit == 0) m = -m;
```
z1 tried this and got worse (119). Because the sign variable took s3? Let me look at z1's disassembly to understand.

Actually, maybe the trick is to keep the rand() call in the `if` but make n used after it:
```
if ((rand() & 1) == 0) {
    m = -((q - n) << 16);
} else {
    m = (q - n) << 16;
}
```
z2 tried and got 123 (the expression duplicated).

Hmm, what about:
```
m = (q - n) << 16;
if ((rand() & 1) == 0) m = -m;
```
The target. n dies before the call. To make n cross, we need the (q-n) after the call.

What if we compute `n` and then the sign bit in one expression:
```
m = (q - n) << 16;
```
no.

Alternatively, use the fact that gcc's `%` expansion temp might cross the call if the expression is `(rand() % 4) << 16` *inside a larger expression with another call*. E.g.:
`m = ((rand() % 4) << 16) + (rand() & 1 ? 0 : ...)` no.

Hmm, what if the sign rand is evaluated BEFORE the modulo? The target's order is: modulo, then sign rand. So no.

Let me look at the problem from the allocator's side: maybe there's a real C move to make local-alloc prefer s0 without crossing a call: e.g. occupy v1 with another live value at the temp's birth. The target's block: after the call at 8e54, `lw v1,16(sp)` — v1 holds sp10! In the target, v1 = t (sp10) from 8e5c to 8e80 (`sra v1,v1,0x10`). So v1 is busy with t during the first vel computation? Let's see: at 8e90 (`bgez v0`) the temp is born. Is v1 live then? `lw v1,16(sp)` at 8e5c; `sra v1,v1,0x10` at 8e80; `addu v0,v0,v1` at 8e84; then v1 dies. So v1 is free at 8e90. Hmm.

But wait — in the target, the first vel computation's temp is s0. What occupies v1? Nothing at 8e90.

OK, I'm stuck on theory. Let me try a few empirical variants:

V1: use `q % 4` natural form.
V2: declare n at function scope but use a single n for both the first modulo and the %4 (z3-like but natural %).
V3: make the temp cross the call by computing `m = (q - n) << 16;` after the sign with the sign in a temp (z1 was worse).

Let me try V1: replace the manual expansion with `q % 4`:
```
q = rand();
m = (q % 4) << 16;
if ((rand() & 1) == 0) m = -m;
```
The compiler expands q%4 to the same sequence. Let's test.
