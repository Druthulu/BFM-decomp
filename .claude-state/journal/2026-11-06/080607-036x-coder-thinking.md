---
ts: 2026-11-06T15:06:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hQlLr76IJRLOF27JElVw
---
As expected: without the launder, all spellings still fold s0=0 → move a0,zero. So we need a genuine way to keep s0 unknown.

Now, since the launder is the only blocker, we need plain C that makes s0 not provably 0 to cse. The candidates that didn't work because cse still knows s0=0.

Idea: introduce a second set of s0 that cse cannot fold AND is value-preserving. Options:
- `s0 = s0 + (s1 - s1);` folds.
- `s0 = s0 | (s1 & 0);` folds.
- Something involving a function call result? e.g. `s0 = s0 + (func() - func())` — no, calls change codegen.

Hmm, what about a value that's genuinely unknown but 0: a *global variable* that is known to be 0. D_8019B538 is an array; reading it changes codegen.

What about reading a stack slot? No.

Think differently: maybe we don't need s0 unknown; we need the *pre-loop a0 assignment* to be a shift of a variable. What if we reorder the code so that the pre-loop a0 is computed from a different, unknown value that equals s0<<10? For example, compute a0 at the loop bottom and then have the loop start... circular.

What if we restructure the loop to be a `while` with the a0 assignment hoisted, using a form where gcc can't prove the entry value:

```
s0 = 0;
a0 = s0 << 10;
do { ... } while (s0 < 4);
```
→
```
s0 = 0;
a0 = (s0 + s0) << 9;  // folds
```

Hmm.

What about making s0's initial value come from the *struct*: `s0 = ((Unkstruct_800B5CB8*)s1)->unk70 & 0;`? gcc folds x&0=0. What about `s0 = ((Unkstruct_800B5CB8*)s1)->unk70 - ((Unkstruct_800B5CB8*)s1)->unk70;`? gcc would load twice; no.

What about `s0 = 0; s0 += ((Unkstruct_800B5CB8*)s1)->unk70 * 0;`? folds.

OK, so cse's fold is robust for constants. The only plain-C things that defeat cse's known-value are: (a) asm (banned), (b) volatile (a lever? maybe), (c) a value that's genuinely not a constant to the compiler.

What value is genuinely unknown but 0? The *difference of two function results*? Calls: e.g. `s0 = func_8012C658(...)` no, that changes codegen and results.

Hmm, what about this: use the loop's own induction to produce the first a0. Restructure so the pre-loop a0 comes from the loop-bottom statement of a *previous* pass through the loop — i.e., change the loop to a `while` that checks at the bottom but enters with a0 already... no.

Wait wait. Actually, maybe a different route entirely: make the pre-loop `a0 = s0 << 10;` use a value loaded from a *variable* that the compiler sees as unknown but which is 0. For example, a `u16` bitfield? Hmm.

Alternatively: keep the launder's effect with a *plain* opaque operation that isn't classified as a lever: e.g., a function call to an extern that returns its argument? That changes instructions (jal).

Or: an inline function? gcc 2.7.2 no inline.

Or: `volatile` local. Is volatile a lever? The census AB_KINDS = {pin, barrier, launder, keepalive, instruction, gte-lever, asm-body}. A `volatile` local might be classified as a "barrier" or "class C/D" (byte-needed volatile). moves.md line 354: "volatile launder kept = score 2". So volatile is treated as a lever (launder). Not allowed.

Hmm.

What about making the shift count a variable? `a0 = s0 << k;` where k = 10? gcc with variable shift emits sllv. No.

What about `a0 = s0 * s2`? no.

Let me reconsider: maybe the fold happens not because s0=0 but because the *expression* `s0 << 10` is CSE'd with the loop-bottom `a0 = s0 << 10`? No, the loop-bottom uses s0 after increment.

Hmm, actually maybe the cleanest: change the loop structure so the pre-loop a0 assignment is moved *inside* a zero-trip-once construct... 

Alternative approach: make the loop a `for` with the update expression producing a0:
```
s0 = 0;
a0 = s0 << 10;
do {
   ...
   a0 = s0 << 10;
} while (s0 < 4);
```
Target: pre-loop sll + loop-bottom sll. What if we write:
```
s0 = 0;
for (;;) {
   ...
   if (++s0 >= 4) break;
   a0 = s0 << 10;   // hmm
}
```

Let's think about it as: the pre-loop sll has s0=0 known; the loop-bottom has s0 unknown. What if we *swap the roles*: make the pre-loop assignment use a variable whose value is unknown. E.g., initialize s0 = 0, then use a second variable `n` that is the loop counter, and a0 = n << 10 where n's first value comes from... 

What if we write the loop with a pointer increment and compute the shift from a *pointer difference*? e.g. `a0 = (s32)(p - base) << 10;` where p-base=0 initially. gcc might not fold pointer subtraction of identical pointers? Actually gcc knows p-p = 0? fold_rtx may not handle pointer differences... but the codegen would add subu instructions. No.

Hmm, what about an unsigned/signed wrap trick: `s0 = (s32)(0x10000 * 0) ...` folds.

What about the `&&`/`||` fold catalog: `s0 = 0 && s1;` folds to 0.

Hmm, what if the value comes from a `u8` read of a known-zero global? We could use a *new* global symbol... but adding globals changes the object and the function; and there's no guaranteed-zero global. But we could read from the struct field we know... no.

Different idea: maybe use `s0` as the loop counter initialized to 0, and compute `a0 = s0 << 10` *before* the loop but through an intermediate that gcc can't constant-fold: a cast to pointer and back? `a0 = (s32)((u8 *)0 + (s0 << 10));` — folds.

What about `a0 = (s32)((s0 << 10) & 0xFFFFFFFF);` folds.

What about making s0 a `u32` and shifting left then right? `a0 = s0 << 10;` — u32 known 0 folds.

Hmm, let me look at how other shards cracked "cse folds the const into the shift" — moves line 97 is exactly a counter case. Let me look at that item: func_800242D0, "loop counter declared s16 + t0--; while (t0 >= 0) (HImode add: no SImode copy class, sll reads v0)". Different mechanism.

What about moves line 25: keepalive, "c1 ($4 pin) dies at c1<<16; local-alloc ties sll temp to a0, target v0; mny keepalive cracked by do-while ref weight".

Hmm.

Let me step back and think about the actual cse fold mechanism. In cse.c, fold_rtx folds `(shift (const_int 0) 10)`? But s0 is a *register*, not a const. fold_rtx substitutes reg_known_value only if reg_known_value[reg] is set. reg_known_value is in sched.c (sched1), not cse. So cse's fold_rtx uses `reg_equiv_constant` — a reg is equivalent to a constant if cse found a `(set reg (const))` insn. In cse, when it processes `(set (reg s0) (const_int 0))`, it records the constant equivalence for that register in the current block and *substitutes* it into subsequent uses in the same extended basic block. That's cse's "constant propagation" within an EBB. To defeat it: split the EBB (do-while(0) does that? C0535 says do{}while(0) splits cse1 EBB) or make the set and use in different EBBs.

d4 (do{s0=0;}while(0)) scored 5 — it changed something but not enough. Hmm, C0535: do-while(0) splits cse1 EBB. But d4 wraps the assignment in do-while(0) — maybe that doesn't create the split we need, or the fold happens elsewhere.

Wait, but maybe the fold is in combine (combine processes each insn and folds using `reg_last_set_value`?). combine.c has `reg_last_set_value` tracking for constant folding: it records when a register was set to a constant and folds uses. Let me check: combine.c has `reg_last_set_value` / `reg_last_set_mode`. It only looks back within the same basic block? combine uses LOG_LINKS, which are within a block. So splitting the block (via do-while or a label) would block combine's fold too.

Actually combine's `reg_last_set_value` is updated in `try_combine`/`combine_insns`? Let me grep.
