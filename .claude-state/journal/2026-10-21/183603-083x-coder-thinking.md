---
ts: 2026-10-22T00:36:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_kUu0qYhBW1CNqeAp9kYp
---
Target structure (func_801813B0):
```
4ae0: move t1,zero       ; i = 0
4ae4: li t3,-150         ; constant -150 in t3
4ae8: li t2,4            ; constant 4 in t2
4aec: lui a2,0x0 / addiu a2,a2,0   ; a2 = idx
4af4: lui v0,0x0 / lw v0,0(v0)      ; v0 = D_801937DC
4afc: lui t0,0x0 ...
loop:
4b10: lw a3,12(v0)       ; src = *(D_801937DC + 0xC)  (re-loaded each iteration!)
4b14: lwl v0,3(a3) / lwr v0,0(a3)   ; copy 4 bytes
4b1c: lwl v1,7(a3) / lwr v1,4(a3)
4b24: swl v0,3(t0) / swr v0,0(t0)
4b2c: swl v1,7(t0) / swr v1,4(t0)
4b34: lh v1,2(a3)        ; v = *(s16*)(src + i*8 + 2)
4b3c: bne v1,t3,4b4c     ; if (v != -150)
4b40: li v0,-139         ; delay slot: v0 = -139
4b44: j 4b88
4b48: sh t2,0(a2)        ; idx[i] = 4
4b4c: bne v1,v0,4b60     ; v0 holds -139
4b50: li v0,-106
4b54: li v0,3
4b58: j 4b88
4b5c: sh v0,0(a2)        ; idx[i] = 3
4b60: bne v1,v0,4b74     ; v0 = -106
4b64: li v0,-57
4b68: li v0,2
4b6c: j 4b88
4b70: sh v0,0(a2)        ; idx[i] = 2
4b74: bne v1,v0,4b84     ; v0 = -57
4b78: li v0,1
4b7c: j 4b88
4b80: sh v0,0(a2)        ; idx[i] = 1
4b84: sh zero,0(a2)      ; idx[i] = 0
4b88: addiu a2,a2,2
4b8c: addiu t0,t0,8
4b90: addiu t1,t1,1
4b94: slti v0,t1,65
4b98: bnez v0,4b10
4b9c: addiu a3,a3,8
```

Interesting: the target's comparison chain is:
- v == -150 → idx = 4 (t2 holds 4)
- v == -139 (v0) → idx = 3
- v == -106 (v0) → idx = 2
- v == -57 (v0) → idx = 1
- else → 0

And the "li v0,-139" etc. are in the *delay slots* of the bne's, so the constants are materialized lazily.

In my c1 (no asms), GCC hoisted ALL the constants (li t7,-150, li t6,4, li t5,-139, li t4,3, li t3,-106, li t2,2) before the loop — 6 extra instructions (52 vs 50) and a different comparison structure (bne v1,t7 / bne v1,t5...).

So the lever (12 asms) changed the *scheduling*: the constants are materialized in the delay slots rather than hoisted.

Why? The asms make v "opaque" — hmm, the asms are on v, and v is compared with the constants. With the asm, GCC can't fold/hoist the comparisons... Hmm, but the target still compares.

Hmm, the difference: in c1, GCC hoisted the constants into registers (t7,t6,t5,t4,t3,t2) — 6 registers. In the target, only 2 constants are hoisted (t3=-150 and t2=4) and the others are materialized in the delay slots.

This is a *scheduling/register-allocation* difference. The 12 asms add refs to v, raising v's priority... but the effect here is on the constants.

Hmm, what if the lever's effect is simply that GCC's scheduler can't hoist the constants because... hmm.

Let me think about the C: the comparison chain is:
```
if (v == -150) idx[i] = 4;
else if (v == -139) idx[i] = 3;
else if (v == -106) idx[i] = 2;
else if (v == -57) idx[i] = 1;
else idx[i] = 0;
```
GCC 2.7.2 turns this into a chain of compares. In c1, it materialized all 6 constants up front (probably because the "li" instructions are cheap and the loop body is entered once?). In the target, only -150 and 4 are hoisted.

Why would the asm change that? The asms are between the load of v and the comparisons. The asm makes v's value *unknown*, so GCC can't use... hmm, GCC's compare chain doesn't depend on v's value.

Hmm! Maybe the difference is this: with the asm, GCC doesn't know that v is loaded from `*(s16*)(src + i*8 + 2)` — no, it does.

Hmm, what if the asm's effect is on the *scheduling*: the asm acts as a barrier-ish for the scheduler? The empty asm with a tied output might prevent the scheduler from moving the `li` instructions into the loop preheader.

Hmm, in c1, the 6 `li`s are hoisted *before* the loop (in the preheader). In the target, 2 are hoisted and 4 are in the delay slots.

The delay-slot filling in MIPS puts the `li` in the delay slot of the `bne` — that's the *filler* (mips.c's final_prescan_insn / delayed branch scheduling). GCC's delay-slot filler will put an instruction into the delay slot if it can. The `li v0,-139` is in the delay slot of `bne v1,t3,4b4c` — the li is *after* the branch in the source order (the else-if chain) so it can be hoisted into the delay slot.

Why would the asm prevent this in c1? In c1, GCC hoisted all the li's into the preheader instead, so there was nothing left for the delay slots.

The choice between "hoist the constant into a reg before the loop" and "materialize it in the delay slot" is a register-allocation/scheduling decision. With the asm, GCC apparently decided to keep only 2 constants in regs.

Since the target's structure has 2 constants in regs (t3=-150, t2=4) — those are the *first* comparison's constant and the *first* store's value. And the rest are materialized on demand.

Hmm, in c1, GCC hoisted 6 constants into 6 different regs (t7,t6,t5,t4,t3,t2) — using up the caller-saved regs. The target uses only t3, t2.

What determines this? The register allocator: if the loop body's live range allows, GCC hoists constants into regs (loop-invariant motion). The *cost* model: hoisting 6 constants costs 6 registers in the loop; the alternative is to rematerialize them in the delay slots (free). GCC's "rematerialization" decision: constants are cheap to rematerialize, so the register allocator prefers to *not* keep them in regs... but it did keep 6 in c1.

Hmm, the difference must come from the asm's effect on the *live ranges*: the asm forces v into a register (a specific one), which changes the pressure.

Honestly, this looks like a register-allocation coin flip. The lever (12 asms) adds 12 refs to v → v's priority rises → v gets a better register → the constants get worse regs → different hoisting.

Plain-C ways to add refs to v: hmm. The 12 asms are 12 refs. In plain C, a "real" use of v adds 1 ref. E.g. `v = v;`? identity.

Hmm, what about restructuring the comparison chain so that the *values* are materialized differently? E.g. write the chain as a *switch*? A switch on v with cases -150, -139, -106, -57 → GCC 2.7.2 would generate a jump table or a comparison chain. The target's chain compares against constants in a specific order with the values materialized in the delay slots.

Alternatively: write the chain so the *store values* are constants in the delay slots.

Hmm, what if the difference is simply the *order* of the comparisons? The target's order: -150 (4), -139 (3), -106 (2), -57 (1) — the same as the C.

Let me try a few variants:
c2: reorder the chain to put the most common first? changes semantics? no, same semantics but different asm.
c3: use a switch statement.
c4: use `if/else if` with the *values* written as expressions.

Honestly, the key question: what makes GCC hoist 2 constants instead of 6? Let me test: what if the value `v` is used in a way that forces it into a register? E.g. what if the comparison chain is written as:

```
if (v == -150) { idx[i] = 4; }
...
```
vs
```
switch (v) { case -150: idx[i] = 4; break; ... }
```

Let me try the switch version (c2) — GCC 2.7.2 might generate a jump table (bad) or a chain.

Alternatively, maybe the trick is that the *asm* prevents the *loop-invariant motion* of the constants? Hmm, in the target, -150 and 4 ARE hoisted.

Wait, actually, maybe the real difference is this: in c1, GCC hoisted the constants because it could *reuse* the registers t7..t2 (6 regs) — and the *number of available regs* was enough. In the target, the 12 asms forced v into a register, consuming one, and the pressure changed.

Hmm, what if in c1, the *loop body* has more live values?

Let me try to think about what plain C could reproduce: the target keeps 2 constants in regs and materializes 4 in the delay slots. GCC's delay-slot filler would happily put a `li` in a delay slot *if* the constant is rematerializable there. GCC's decision to hoist the constant into a reg before the loop is made by the *register allocator* (loop invariant reg allocation): a constant used in a loop is normally kept in a register if there are enough registers; otherwise it's rematerialized in the loop body.

So in c1, GCC had enough registers (6 constants + others) — hmm, but MIPS has only 8 caller-saved t regs.

In the target: t3 = -150, t2 = 4, and t0, t1 are used for the loop pointers/counter. So 4 free t regs (t4-t7) were NOT used for the other 4 constants. Why? Because in the target, the *li* instructions for -139, -106, -57 are in the delay slots — i.e. the scheduler put them there. The delay-slot filler runs *before* the register allocator? No: in GCC, the RTL is register-allocated first, then the final delay-slot filling happens on the machine code (mips_final_prescan_insn / machine_out-of-place). Hmm, actually the delay-slot filling happens in the "final" phase (reload), and it can *rematerialize* a constant into a delay slot if the reg is available.

So the target's shape: the constants -139, -106, -57 were NOT allocated to regs (they're rematerialized in the delay slots), while -150 and 4 were.

Why would the allocator keep 2 and not 4? Because of *pressure*: in the target, more registers are occupied by other things (the asm forcing v into a reg, etc.).

So: the lever increases the register pressure (v is forced into a reg) → the allocator has fewer regs for the constants → it keeps only 2 and rematerializes the rest.

Hmm! So to reproduce without the asm, I need to *increase the register pressure* in a legitimate way... e.g. by using more live variables. Hmm, but "no new levers" — adding a dummy variable to create pressure is a hack.

Alternatively, restructure the comparison chain so that fewer constants need registers: e.g. use a *subtraction-based* chain: `v + 150 == 0`, etc.? That changes the instructions.

Hmm, what if the chain is written as:
```
if (v == -150) idx[i] = 4;
else if (v == -139) idx[i] = 3;
...
```
vs
```
switch (v) {
case -150: idx[i] = 4; break;
case -139: idx[i] = 3; break;
case -106: idx[i] = 2; break;
case -57: idx[i] = 1; break;
default: idx[i] = 0; break;
}
```
Let me test the switch (c2). GCC 2.7.2's switch on 4 sparse cases → probably a comparison chain (or a jump table if dense enough: -150, -139, -106, -57 — the range is 94 → too big for a jump table; GCC 2.7.2 would use a decision tree or a chain).

Let me test c2 (switch). Also, another idea: what if the *store values* (4,3,2,1) and the *compare constants* (-150,...) are the same registers in the target? In the target: t3 = -150 (compare) and t2 = 4 (store value); the other store values (3, 2, 1) are materialized as `li v0,3` etc. in the delay slots.

So in the target, the *first* comparison's constant and the *first* store value got registers; the rest are in delay slots.

Honestly, this smells like a pressure/priority effect. Let me try a couple of variants and see:
c2: switch.
c3: the chain with the *store* values written as literals in a different order? no.
c4: the chain written with `else if` but with the comparisons in a different *expression* form: e.g. `if (v + 150 == 0)`. Hmm, that changes the instructions (addiu).

Let me just try c2 (switch) and c5 (the same chain but with the *first* comparison's store value 4 written as a literal — it already is).

Hmm, hmm. Let me think about the *asm*'s effect once more: `__asm__("" : "=r"(v) : "0"(v))` × 12. This forces v into a register 12 times → v is live across... no, v is dead right after.

Hmm! Actually, maybe the asm's real effect is *different*: it makes the value of v *unknown* after the load, so GCC can't do the "compare and branch" folding of the *first* comparison? Hmm, the target has `bne v1,t3` — a real compare-and-branch.

Wait, here's a cleaner hypothesis: without the asm, GCC *knows* v is loaded from memory and can use "load and compare" optimizations (e.g. `lh` + `bne` with the loaded value). With the asm, the value is opaque → GCC must materialize it in a reg.

But the target DOES have `lh v1,2(a3)` then `bne v1,t3`. So the value is in a reg.

Hmm, so in c1, what does the code look like? Let me disassemble c1 to see. That's the fastest way to understand the difference.

Let me do that.
