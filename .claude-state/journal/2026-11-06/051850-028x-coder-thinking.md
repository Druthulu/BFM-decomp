---
ts: 2026-11-06T12:18:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sG62maqxxK8Vh4f9Wc2Y
---
Identical to a2! That means gcc's scheduler/optimizer produced the same code — the C difference didn't matter, likely because gcc's flow/cse transformed it. Hmm: `s32 a1s = arg1; if (!(arg1 & 1))` — gcc's combine might fold `a1s = arg1` ... no.

Wait, maybe the objdump is stale from the previous --keep (same path p3). The --keep run rewrote cand.o. Should be fresh. Both a2 and a3 produce identical code? Let me verify by scoring both and comparing. Possible: `a1s = arg1` coalesced and arg1's use in the test is the same as a1s's... no, coalescing would mean a1s IS arg1 (same reg) and then no copy. Then the code would be: arg1 used 3 times, andi into v0 — that's exactly what we see (move t4,a1 is gcc's own copy). Hmm.

So gcc chose to copy arg1 to t4 and compute the test in v0. It didn't coalesce a1s into a1 because... hmm, actually maybe it DID coalesce: a1s and arg1 same pseudo? Then arg1 (3 uses) got t4 as its home? No, a param can't move.

Actually let me look: `move t4,a1` then all later uses use t4 (in a1.c's diff we saw andi v0,t4,0x8000 at c98 in mine). So gcc moved the param arg1 into t4 and used t4. Why? Because local-alloc gave the arg1 pseudo... no, params are hard regs.

Wait, maybe gcc's "register allocation of parameters": arg1 is a pseudo with hard reg a1 preferred; but it's copied to t4 by the prologue? Actually the copy `move t4,a1` at b08 is right at the top — gcc decided arg1's pseudo lives in t4 (a caller-saved temp) and emitted the copy at entry? That seems odd but possible: since arg1 is used 3 times and a1 is needed elsewhere?

Hmm no. Let me think about gcc 2.7.2: parameters come in as pseudos with REG_PARM_STACK...; local-alloc may assign them a different reg if the hard reg is needed elsewhere, inserting a move at the top. That's what happened: arg1's pseudo got t4, and the entry move t4,a1.

And the first test's andi went to v0 because arg1 (=t4) is live after.

In target, the launder/pin made a1v in a1, forcing the copy t3,a1 and letting andi write a1.

So to get target's shape in real C, I need the first test's andi to be the LAST use of the arg1 pseudo, so the allocator can write in place. But arg1 is used later — unless the later uses are of a COPY that is live simultaneously, which we tried... but gcc coalesced/moved.

The issue: gcc put the arg1 pseudo in t4 (not a1). Then a1s = arg1 would be a copy from t4... but we saw no such thing; the copy move t4,a1 is gcc's param move.

Hmm, actually maybe in a3, a1s coalesced with arg1's pseudo (both live simultaneously? no...). If a1s coalesced, then a1s's later uses read the same pseudo as arg1 → all uses from t4. That matches! a1s = arg1 coalesced because gcc's copy propagation sees a1s as identical. Wait, coalescing requires non-overlapping live ranges; a1s is born at entry and arg1 lives until the first test — overlapping. Hmm, but if a1s = arg1 at the very top and arg1 is never modified, they can share.

Whatever the mechanism, gcc unifies them.

So I need a REAL second set. Let me think differently: which real C produces `move t3,a1; andi a1,a1,1`?

What if the first test uses a value computed from arg1 by a real operation that gcc can do in place and that kills arg1's pseudo? E.g. `arg1 & 1` where the arg1 pseudo is dead after because ALL later uses go through a1s that was computed as a REAL function, not a copy.

For instance: `a1s = arg1 + 0;`? Same copy.

What about making the later uses read a1s where a1s is a real computation that happens to preserve the needed bits: `a1s = arg1 & 0xFFFF;`? The later uses are `& 0x8000` and `& 1` — both unaffected by masking to 16 bits! So `s32 a1s = arg1 & 0xFFFF;` is semantically safe for those uses. But it emits `andi t3,a1,0xFFFF` instead of `move t3,a1` — one insn either way, but the opcode differs (andi vs move) → mismatch. Unless the value fits and gcc uses `andi`... target has `move t3,a1` (addu/or). Hmm, `move` is `addu t3,a1,zero`. So a1s = arg1 must be a plain copy.

OK, different angle: maybe don't fight the top. Perhaps use the "do{}while(0)" or ordering tricks to shift register allocation. The moves catalog has "greg-pri-refs": adding real refs changes priority. The register allocation choice between t3 and t4 is a priority/order thing.

Let me look at what's different: in mine, the arg1 pseudo is t4 and arg2's pos is t3. In target, arg1 copy is t3 and arg2 copy is t4. Also in mine the arg1 pseudo is moved at entry (move t4,a1) while target copies arg1 at b08 (move t3,a1) — same position. Both copies are "at entry". So really the only difference is: which pseudo got t3 vs t4, and the andi destination.

What if I swap the declaration order or the birth order of pos and the arg1 use? In target, the order of the moves: t3 (arg1) first, then t4 (arg2). Mine: t4 (arg1) first, then t3 (arg2). So gcc allocates in birth order? Both born at entry; the order in the insn stream decides. In mine, move t4,a1 is at b08, move t3,a2 at b14 (delay slot). In target, move t3,a1 at b08, move t4,a2 at b14. So the same positions, just different registers. So it's purely the allocator's choice of which pseudo gets t3 first.

The order gcc assigns temps: local-alloc processes pseudos by priority (number of refs / live length). The first allocated gets the lowest available temp (t3? or t0?). Actually register order: $8..$15 = t0..t7, then $16..$23 = s0..s7, $24.. = t8,t9. Temps allocated: t3 = $11? Hmm, MIPS: $8=t0, $9=t1, $10=t2, $11=t3, $12=t4, $13=t5, $14=t6, $15=t7.

t2 is arg0's copy (move t2,a0) — arg0 pseudo got t2. So allocation order gave arg0 t2, arg1 t3 in target, arg2 t4. In mine arg0 t2, arg2 t3, arg1 t4. So target allocated arg1 before arg2; mine allocated arg2 before arg1.

Priority: number of refs. arg1 has 3 uses (test &1, &0x8000, &1) plus the copy = 3? arg2 has uses: (s16)arg2 twice + pos+2/pos-2 (2) = 4 uses. Hmm, arg2 has more refs. Higher refs → allocated earlier (higher priority) → arg2 would get t3 first in mine. Target has arg1 first.

In target, a1v's launder added an operand use of arg1 (the asm) — that's +1 ref to arg1, making it 4+? and pos is a separate variable.

So maybe adding a real extra use of arg1 early could raise its priority. But the ref count affects which pseudo is allocated first among ALL pseudos. Hmm, but arg1 here is a param pseudo, and pos/arg2 etc.

Actually, wait: in target, arg2 = pos is a pinned $12 (t4). The pin forced t4! And arg1's a1v pinned $5 forced the copy t3. So the target's registers were literally forced by pins. Real C must reproduce them by allocation priorities.

So the plan: manipulate the priority so that the arg1-copy pseudo is allocated before the arg2/pos pseudo, and make the andi write in place.

Since the andi in-place requires arg1's pseudo to die at the andi, and the later uses read a copy... Let me examine what the compiler does with:

```
s32 a1s = arg1;
s32 pos = arg2;
if (!(arg1 & 1)) ...
```
We got: arg1 pseudo in t4, a1s merged, andi v0.

What if instead:
```
s32 a1s;
s32 pos;
pos = arg2;
a1s = arg1;     // copy AFTER pos
if (!(arg1 & 1)) ...
```
Order might change allocation order.

Or use `a1s = arg1;` but force arg1 to be used for the first test with the copy NOT provably equal: use `a1s` in a context where the compiler must copy: e.g. `a1s = arg1;` then `if (!(a1s & 1))`... same.

Hmm, what about this trick: make the later uses read `a1s` where a1s is assigned from arg1 AFTER the first test? No, it needs the original value.

What if the later tests use the param arg1 but the first test uses a computed temp that gcc will allocate in a1... 

Let me look at the actual gcc 2.7.2 behavior for `andi` in-place: the MIPS md pattern for AND with constant: `(define_insn "" [(set (match_operand:SI 0 "general_operand" "=d,d") (and:SI (match_operand:SI 1 "general_operand" "dI,i") (match_operand:SI 2 "immediate_operand" "I,I")))]` with alternative 0 = "andi %0,%1,%x2"? Let me check the actual md.

If the pattern is 3-operand (dst separate from src), then gcc CAN allocate dst==src only via local-alloc tie when src dies. So we need src (arg1 pseudo) to die at the andi.

To make arg1's pseudo die at the andi, the later uses must be of a different pseudo. The later uses currently get merged because a1s = arg1 is a copy that gcc propagates.

To prevent copy propagation of a1s = arg1, make a1s's value not provably equal: `a1s = arg1 + 0`? gcc folds. `a1s = arg1 | 0`? folds. Hmm.

But wait: if a1s = arg1 is propagated, then a1s is the same pseudo and arg1 dies only at the last use. Copy propagation would then make the first test use the same pseudo.

What if the copy is created by an operation gcc can't fold but is still a `move` in the target? The target's `move t3,a1` — what real C op compiles to `move`? Assignment of a value to a variable (addu dst,src,zero) when the copy can't be coalesced.

Coalescing fails when the two live ranges overlap and the allocator can't share. If a1s = arg1 at entry and arg1 is used later, the ranges overlap → cannot coalesce into one reg → must emit move t3,a1! But we observed it did coalesce... Did it? In a3, the copy at entry was `move t4,a1` and later uses used t4 — that's the arg1 pseudo in t4 with a1s merged into it (same pseudo). If they were separate, we'd see move t3,a1 (copy) and later uses of t3, while arg1 stays a1 for the first test. That's what we want.

Why did they merge? Because copy propagation (flow) replaced uses of a1s with arg1 (or vice versa) since a1s = arg1 and neither is modified. So a1s disappears.

To keep them separate, the copy must not be a simple `a1s = arg1`... but then it won't be `move t3,a1`.

UNLESS: use a1s in a way that makes the compiler keep the variable, e.g., `a1s` is a struct field? Or the copy is `a1s = arg1` but arg1 is modified later? We can't modify arg1 semantically... but wait, can we? The later uses are `arg1 & 0x8000` and `arg1 & 1`. If we assign `arg1 = arg1` no. 

Hmm, what if we restructure so that the FIRST test uses a1s and the later tests use arg1, with a1s = arg1 computed BEFORE and arg1 being used later. Same merge.

OK, alternative: maybe we don't need to reproduce the "copy arg1 to t3" at all — maybe another real-C shape scores 0 with a different but equivalent codegen? No — score 0 means exact match, so we must match target exactly.

Let me look at how other tasks cracked similar launder shapes. The moves file: "launder->pv = *p; pv &= 0xFF000000 split (real 2nd set)". For our case, the launder is an input launder creating a copy. Hmm.

Maybe the right approach: since a1v is only tested with &1, we can make the first test use a REAL second computation whose result is arg1&1 but computed in place... Let me test what `if (!(arg1 & 1))` alone gives (no a1v/a1s at all, arg1 used later). That's my a1.c: move t4,a1; andi v0,t4,1; later uses t4.

So with only arg1 uses, gcc moves the param to t4 and uses t4 everywhere, andi into v0. Target instead keeps arg1 in a1 for the first test and copies to t3 for later.

Key difference: the number/order of uses. In target, arg1's pseudo (the one in a1) dies at the andi. So the compiler considered the a1v's input as the param directly, and the later uses as a separate copy. The copy t3 was created because the launder's asm needed arg1 in a1 and the later uses needed the value elsewhere.

Real-C equivalent: we need a genuine second value. What about:

```
s32 a1s = arg1 & 1;
...
if (!(arg1 & 1)) ...
```
No...

Think about it from the value-flow: the value that dies at the andi is arg1 (a1). The later uses read t3 which is a copy of arg1 made before the andi. So there IS a copy in the C: some variable holding arg1's value used later. The compiler must not propagate it. It didn't propagate in target because the asm is opaque.

Real C that defeats copy propagation while compiling to a plain move: hmm, gcc 2.7.2's copy propagation is quite aggressive.

What about declaring the copy as a different type, e.g. `u32 a1u = arg1;`? The later uses are `& 0x8000` and `& 1` — same for u32/s32. Copy propagation across types? gcc's C front end would insert a conversion? Same type size, no conversion. It might still merge.

What about `s16 a1h = arg1;`? The later uses `a1h & 0x8000` — with s16 promoted to int, sign-extended; `(s16)arg1` vs arg1: `arg1 & 0x8000` on the sign-extended value: if arg1 has bits above 16, (s16)arg1 differs. But the uses only test bits 15 and 0: bit15 of the sign-extended value equals bit15 of arg1; bit0 same. So semantically equivalent! And `s16 a1h = arg1;` compiles to... a store? No — a local s16 variable assigned an s32: gcc truncates with `sll/sra` (2 insns) when used as int. That adds insns. Unless gcc keeps it in a register with a sign-extend at assignment: `sll t3,a1,16; sra t3,t3,16` = 2 insns. Target has 1. No.

What about `u16 a1h = arg1;`? Zero-extend = `andi` = 1 insn, but it's `andi t3,a1,0xFFFF`, not `move`. Mismatch.

Hmm. So the copy must be a plain move.

What if the copy is a pointer? `s32 *a1p = (s32*)arg1;` no, changes type; uses & 0x8000 on a pointer would be weird.

What if the copy is used in a context that requires the variable to exist, like being passed by address? `&a1s` — but no calls, and taking the address forces a stack slot. Bad.

Hmm, let me reconsider: maybe gcc's copy propagation didn't merge in target because arg1 is a *parameter* and a1v comes from an asm. But we can't use asm.

Let me look at the moves for similar "input launder" cases and how they cracked them. Line 9: `barrier,launder | func_8002B0B4 | PARTIAL:launder cse-const-addr — ... cp launder->cp = D_800760C0 = f(cp); 2 m launders: cse reuses void-call arg sym pseudo`.

Hmm. Let me search moves.md for "launder->" entries.
