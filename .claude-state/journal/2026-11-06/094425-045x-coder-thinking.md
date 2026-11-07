---
ts: 2026-11-06T16:44:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sTU3iQDidIHz4ZUE18MS
---
The orig.c matches src (fresh). Good.

Now the launder: `__asm__ __volatile__("" : "=r"(s0) : "0"(s0));` — it forces s0 into a register and redefines it. The target's s0 loop counter is in $16 (s0 callee-saved). Hmm.

The task: remove the launder, find real C that keeps the codegen. The launder is at the top: after `s0 = 0; s2 = ...;` it launders s0.

Why was the launder needed? The dump says "NEEDED DIFFERS". The launder prevents some optimization (probably it stops gcc from knowing s0==0, or forces s0 to be materialized in a register rather than const-folded).

Without the launder, `a0 = s0 << 10` with s0=0 → gcc const-folds a0 = 0. But then the loop recomputes a0 = s0 << 10 each iteration. Hmm, in the target:
```
1a3c: move s0,zero
...
1a50: sll a0,s0,0xa     <- a0 = s0 << 10 (first iteration s0=0, but still emitted)
```
So the target has `sll a0,s0,0xa` computed from the register s0, not the constant 0. Without the launder, gcc would know s0=0 at the first iteration and emit `move a0,zero` or fold.

So the launder's effect is to make s0 opaque (not known to be 0). We need real C that has the same effect without asm.

Ideas:
1. Make s0's initial value not a constant: e.g., `s0 = a0p - a0p;`? gcc folds.
2. Use a variable the compiler can't fold: `s0 = 0;` is constant. What if s0 is initialized from a global or an argument? The target has `move s0,zero` — the initial value IS zero. So the C has s0 = 0 but gcc must not propagate it.
3. A launder replacement: use a *volatile* variable? e.g., `volatile s32 z = 0; s0 = z;` — that's a real load from the stack (extra insn). Not good.
4. Statement order: move the `a0 = s0 << 10` computation BEFORE... hmm. If `s0 = 0;` then `a0 = s0 << 10;` gcc folds a0=0. In the target, a0 is computed from the register. The launder makes s0 opaque.

What real C makes a variable opaque without an insn? Maybe declare s0 and assign from a function? No.

Wait — actually, the launder might have been needed for a different reason: to prevent gcc from *eliminating* the `a0 = s0 << 10` before the loop and hoisting it, or to force s0 into a register at that point (the register assignment). Let me test the plain body first and see the diff.

Plain body: remove the asm line. Let me score.

Also note the pins $4/$5 remain.

Let me write the plain body and score.
