---
ts: 2026-11-06T10:10:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dY0uw3hlbu29GFxdNdHK
---
Good. Now copy to win.c for each clone. And item4 v02 to win.c.

Let me do the copies and then write notes.md files.

Wait — before finalizing, let me reconsider whether the clone wall might be crackable via the "keepalive replaced by return v0" move (func_80184D28 MATCH): that was a s32 function that returned nothing; here it's a void function that computes a value. The inverse. Hmm.

Actually, hold on. Let me reconsider the TU. The function `func_80182420` is declared `void` at its definition. But is it possible the *original* source had it as `s32` and the project's `void` is a mistake? The task forbids signature change. So the wall stands.

But wait, maybe there's a subtlety: gcc 2.7.2 K&R function definition `void func_80182420(a0, a1)` — what if we omit the return type? `func_80182420(a0, a1) s32 a0; s32 a1; {...}` → defaults to int! Then the function returns int, and `return rv;` would emit v0=rv. But then the callers declare `extern void func_80182420(...)` → conflicting types? Default int vs void → conflict. And omitting the return type changes the signature. Forbidden. Also the def line `void ...` is outside the body. Hmm.

Actually, what if the *definition* line is considered part of the "body file" we provide, and the scorer splices from the definition line. If we write `func_80182420(a0,a1)` (implicit int), the spliced TU has `int func_80182420(...)` then callers `extern void ...` → conflicting types error. Let me test? It's cheap and decisive. But it violates "no signature change". I'll skip; it's forbidden regardless.

OK, walls.

Let me now write win.c copies and notes.

For each item, notes.md should record: kinds, levers removed, variants tried, best, wall mechanism, evidence.

Let me write the files.

Actually, let me reconsider one thing about the clone wall: the keepalive-only body (b3) scored 6 with 26 ins and all instructions present (MIXED = register diffs). The diff was v1→v0 x1 plus delay slots. So the keepalive-only body is very close (6). If we could fix the register allocation, we'd get 0 → PARTIAL:keepalive. That's worth more effort! The score-6 diff:
```
15  li v1,-1       | li v0,-1
17  bnez v0,938    | bnez v0,93c
18  nop            | sll v0,a0,0x1
21  beqz v0,93c    | bnez v0,93c
22  li v1,31       | sll v0,a0,0x1
23  sll v1,a0,0x1  | li v0,31
```
So only rv's register ($3 vs $2) and two delay-slot order swaps. If we can get rv→$2, the delay slots likely fix themselves. 

How to get rv→$2 without the pin/return? The target's rv=$2 because it's the return value. In a void function with a keepalive, rv is a normal pseudo. Global-alloc chose $3. Could real-C moves make it $2?

Idea: make rv *die* in a way that its last use is at the end, and increase its priority so global-alloc assigns it first. Global-alloc sorts by priority = (floor_log2(refs) * loop_depth) and live length. rv has ~5 refs (defs count as refs? REG_N_REFS includes sets and uses). If we increase rv's refs (e.g., use it more), its priority rises and it might get $2. But adding uses adds instructions.

Idea: make the *other* pseudos (comparisons) avoid $2 by... they're local-alloc'd first. Hmm.

Idea: change the declaration order so rv is allocated first? global-alloc order is by priority, not declaration.

Idea: use `rv` in the keepalive twice? `__asm__("" :: "r"(rv), "r"(rv))` — that's adding refs but it's still a keepalive (kind kept). Could shift allocation. But it might not add instructions (asm with no output, no template). Let me test: keepalive with rv referenced twice. Hmm, that's a variation of the keepalive lever (kind kept), allowed for PARTIAL. Let me try.

Actually, the keepalive asm `__asm__("" :: "r"(rv))` forces rv into a register at that point. If we reference rv twice, it's still one input. To add refs, use `__asm__("" :: "r"(rv), "r"(rv))` (two operands). Does gcc count that as 2 refs? Possibly.

Let me test a few keepalive-boost variants on b3:
- k2: `__asm__("" :: "r"(rv), "r"(rv));`
- k3: keepalive at two points (e.g., after the first branch and at done)
- k4: `__asm__("" :: "r"(rv));` plus `if (rv) {}`? adds ins.

Also, maybe the delay-slot order (nop vs sll) is a sched1 issue that could be fixed by statement order. But first get rv→$2.

Let me test k2/k3. If one scores 0, that's PARTIAL:keepalive — a genuine crack (drops the pin).

Let me create these variants from b3 (the keepalive-only body, score 6).

b3 content: orig with rv plain and keepalive at done. Let me create k2, k3, k4:
- k2: replace the keepalive line with two-operand.
- k3: add a second keepalive right after `rv = 31;`? Hmm, the keepalive at done already covers all paths.
- k4: move the keepalive before the label (after rv=31) — but then the early-exit paths (goto done) skip it → rv not kept on those paths. Bad.
- k5: keepalive with `"+r"(rv)`? rw operand.

Let me test k2 and a version with the keepalive input on `rv` plus a dummy second input `rv`:
`__asm__("" :: "r"(rv), "r"(rv));`

Also, maybe declaring `rv` with `volatile`? No, that changes codegen.

Let me test k2. Also test a variant where `rv` is used in a *dead* real statement that gcc keeps until global-alloc but deletes after? That's a launder (not allowed for lever-free, but PARTIAL keeps keepalive only; adding a launder would be a new kind → not PARTIAL). So no.

Let me test k2/k5.
