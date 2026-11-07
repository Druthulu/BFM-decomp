---
ts: 2026-11-06T16:47:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TRZrwL74f2I565HWMX3i
---
Target: EVERY call materializes the symbol address fresh (lui/addiu) and the D_801BFCxx global is loaded fresh (lui/lw). So target has NO hoisting of the address constants into callee-saved registers at all. Mine without the launders hoists them (s2, s5 etc.).

Wait, mine hoists the *symbol address* (a constant) into s-registers. That's cse's doing: cse may hoist a constant address (the `(s32)D_8018E2DC` constant) into a register? Actually no — constants don't get registers; GCC would emit lui/addiu each time unless... Hmm, mine's `move a1,s2` means s2 holds the address. Where did that come from? Maybe cse kept the symbol_ref in a pseudo (a "constant" pseudo) and the register allocator put it in a callee-saved reg since it's used across calls.

The asm launder made the value "opaque", forcing a fresh load each time.

Real-C fix: prevent cse from keeping the constant address in a register across the calls. Options:
1. Reorder the statements so the address is used within a single call? It already is.
2. Write the address expression differently at each use so cse doesn't see them as the same value: e.g. use different equivalent spellings. But identity address spellings don't count as a crack.
3. The real original source probably had a different structure: maybe a loop over a table! The repeated calls with different constants (D_8018E2DC, E2E8, E2F4 at offsets 0x84,0x90,0x9C) look like an unrolled loop over an array. The target's fresh lui/addiu per call suggests the original source passed the addresses as... hmm.

Wait — look at the structure: 
- group A: base D_801BFCC4, offsets 0x84/0x90/0x9C, sources D_8018E2DC/E2E8/E2F4 (stride 0xC)
- group B: base D_801BFCBC, same offsets/sources
- group C: base D_801BFCBC, offsets 0x3C/0x48/0x54, sources D_8018E27C/E288/E294
- group D: base D_801BFCB4, same offsets/sources as C

So it's like a 2x2 of (dest base, source base). Maybe the original is a loop over two dest bases and two source arrays:
```
for (j = 0; j < 2; j++) {
   for (i = 0; i < 3; i++) func_8017D8A4(base[j] + off[i], src[k], src[k]+0x30, 0, 1);
}
```
But target's code is fully unrolled with immediate lui/addiu, so no loop.

Hmm. The key difference is register allocation of the constant addresses: target keeps NO constant in a callee-saved register. Mine (without launders) does. That's a global-alloc effect: the constant pseudo (address) has many refs and long live range, so it's allocated a callee-saved reg.

But wait — target ALSO has these addresses used many times (D_8018E2DC used in groups A and B = 2 times; D_8018E27C in C and D = 2 times). Yet target emits lui/addiu at each use. So in the target's RTL, each use had its own constant (not cse-merged). The launder prevented cse from merging them.

How does cse merge two identical symbol address constants? `(s32)D_8018E2DC` is a constant; cse records it in the hash table and reuses the register across blocks? cse's constant handling: it may create a REG_EQUIV and keep the value in a register. Across the calls, cse can't keep a value live across a call in a call-clobbered register... but a constant can be rematerialized.

Hmm, the s-registers in mine: s2, s5, s4, s1, s3, s0, s6, s7 — 8 callee-saved. Mine's frame is 64 vs target 48 (one extra s-reg).

The real question: what real-C source makes GCC not hoist? Maybe the original used *different expressions* for the same address: e.g. `D_8018E2DC + 0` vs `D_8018E2DC`, or `&D_8018E2DC[0]` vs `D_8018E2DC`. Those are identity address spellings (forbidden as a crack).

Alternative: the original source may have used a local variable for the source pointer that is reassigned between calls, e.g. `q = D_8018E2DC; ... q = D_8018E2E8; ...` — cse would still merge.

Hmm, but the C0505 catalog mentions: "A named derived pointer `q = p - k` that cse keeps as a REGISTER address" and "pointer reuse". And "A twice-set pointer `p = &D; p += x;` as one expression".

Let me think about what cse does with `(s32)D_8018E2DC` when D_8018E2DC is declared as `u8 D_8018E2DC[]`: the expression is a constant address. GCC's cse processes `(symbol_ref)`, records it as a constant with a pseudo. It may allocate a register to hold it if it's used multiple times (cse's "constant" optimization: it can put constants in registers and keep them). The register is live across calls → global alloc gives callee-saved.

If the original source used the address only once per call and cse didn't merge across calls... but the launder is exactly what prevents cse merging.

What if the C used a *volatile pointer load*? e.g. `*(void **)&D_8018E2DC`? That changes semantics.

Hmm. What about the `func_8017D8A4(D_801BFCC4 + 0x84, ...)` part: `D_801BFCC4 + 0x84` — D_801BFCC4 is likely a `u8 *` global? Target does `lui a0; lw a0,0(a0)` then `addiu a0,a0,132` in the delay slot — so D_801BFCC4 is a pointer variable loaded from memory each time! And mine also does lw each time (that part matches).

The m = (s32)D_8018E2DC is an address constant.

So the fix: make the compiler not hoist the address constant. Real C options:
- Use the address through a local variable declared in a narrow scope per call? cse works across blocks; scope doesn't matter.
- Change the type: e.g. `(void *)(s32)D_8018E2DC` vs `&D_8018E2DC[0]`. cse merges symbol_refs regardless.
- Use an intermediate `u8 *sp = D_8018E2DC;` — same.

Hmm, what made the target's compiler NOT merge them? The target's source presumably had something like:

```
func_8017D8A4(D_801BFCC4 + 0x84, D_8018E2DC, D_8018E2DC + 0x30, 0, 1);
```
Here `D_8018E2DC` is used twice in the same call (as arg1 and arg2 = arg1+0x30) — cse would keep it in a register within the call, materialize lui/addiu, and then `addiu a2,a1,48`. That matches target! And across calls, cse would NOT keep the constant in a register across the call because... hmm, but mine's hoisting shows it does.

Wait, mine's code: `move a1,s2; move a2,s5` — s2 and s5 hold two addresses (m and m+0x30) in callee-saved regs, live across calls. Why would the register allocator keep them? Because cse made pseudos for the constants that are live across the whole function (the value is loop-invariant across... there's no loop). 

Hmm, but maybe it's not cse but the *global allocator* keeping them because they're referenced many times. Let me look at mine's code more carefully: `move a1,s2` for the first laundered call... but the diff was for the win.c (no asm). Let me dump the RTL to see what happened.

Actually, a cheaper approach: try variants and score. Let me think about what the original C probably was.

Note the pattern in the source: the three laundered calls per group each use a *different* m. So m isn't reused across calls. The only reuse is D_8018E2DC in group A and group B (two calls, far apart). So cse merging those two is plausible.

Mine's `move a1,s2` in the FIRST group: s2 = address of D_8018E2DC. If s2 is used in group A and group B, then in group A it's already set. So the compiler hoisted the constant load to the top (before the first call in group A).

Actually, look at mine's diff: mine[164:165] `sw s7,16(sp)` vs target `sw s3,16(sp)` — mine uses s7 for the constant 1 (the 5th arg), target uses s3. Mine's register allocation is different overall because of the extra hoisted constants (s2,s4,s5,s6...).

So the fix must prevent hoisting the 4 distinct address constants (D_8018E2DC, E2E8, E2F4, E27C, E288, E294, E300 = 7 constants) into registers. Target materializes each fresh at each use.

How? Real C: pass them as *arguments computed inline*, which is what we do. Hmm.

Maybe the difference is the declaration type of D_8018E2DC. If it's declared `u8 D_8018E2DC;` (a scalar u8), then `(s32)D_8018E2DC` is a *load* of a byte (lbu), not an address! Target shows `lui a1,0; addiu a1,a1,0` = the ADDRESS of the symbol, not a load. So D_8018E2DC is an array or the code takes its address.

Hold on: `(s32)D_8018E2DC` where D_8018E2DC is `u8[]` → array decays to pointer → (s32) casts the pointer to s32 → address constant. Yes.

Now, what if the original source wrote `D_8018E2DC + 0x30` etc. as `(s32)D_8018E2DC` — same.

Let me test a simple variant: remove the launder and change the m declaration to be *inline* in the call: `func_8017D8A4(D_801BFCC4 + 0x84, D_8018E2DC, D_8018E2DC + 0x30, 0, 1);` — no local m. That might change cse behavior? Probably the same.

Another idea: the original may have used a *u8 pointer* variable with the addition expressed differently: `(void *)(m + 0x30)` where m is s32 vs `(void *)&m[0x30]`.

Hmm. Let me try the most likely original: since these are 6 calls with sources at 0xC stride, maybe the source is a loop over an array of pointers... but the target is unrolled with constants. GCC 2.7.2 at -O2 does not unroll loops (no -funroll-loops). So no.

Let me look at the actual difference more carefully: maybe the issue isn't cse but *loop.c* or global alloc. Let me dump the RTL for win.c (no asm) and compare with the orig (asm) version, focusing on the constants.

Actually, maybe the simplest fix: the constants are hoisted because cse puts them in registers and global alloc keeps them live. If we prevent cse from seeing them as constants, e.g. by making the value *appear* to change: assign to a variable that's re-set. But that's a launder.

Wait — maybe the original source used `u8 *m;` and set `m = D_8018E2DC;` right before each call, then `func_8017D8A4(..., m, m + 0x30, 0, 1);`. A pointer variable assigned before each call: cse might still merge. But the *type* being u8* vs s32 might matter for the pointer arithmetic (`m + 0x30` scales by 1 either way).

Let me just test a batch of variants:
1. Inline the address expression (no local m): `func_8017D8A4(D_801BFCC4 + 0x84, D_8018E2DC, D_8018E2DC + 0x30, 0, 1);`
2. Use `u8 *m = D_8018E2DC;` local pointer.
3. Use `(void *)D_8018E2DC` directly.

Let me first test #1.
