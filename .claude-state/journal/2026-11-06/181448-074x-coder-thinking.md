---
ts: 2026-11-07T01:14:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Queaz6bKptEMlqXk3r21
---
Confirmed: after sched1, insn 46 (`a0 = r72`) is at position 40→43, i.e., BEFORE insn 43 (the store). In the pre-sched (combine/flow) order, insn 43 was 40→46 and insn 46 was 43→48 (store first). So sched1 hoisted the copy above the store. Then local-alloc replaced the store's base r72 → a0.

Note ";; insn 43 has a greater potential hazard, now 43 46" — a scheduling message.

So the mechanism is confirmed:
1. sched1 moves the call-arg copy (a0 = r72) before the store.
2. local-alloc's update_equiv_regs (or a related optimization) rewrites the store's base r72 → a0.

Now: how to stop sched1 from hoisting? sched1's decision is based on hazard/priority. The prior agent's 25 spellings failed.

One more idea: make the store and the copy *dependent* by using the same value: e.g., the store writes v0 and the copy is `a0 = s0` — independent. If the store used a value that the copy sets... no.

What if the copy is not a simple reg-reg copy: e.g., the call arg is `(u8 *)((char *)s0 + 0)`? The compiler folds to a copy.

What if the call is `func_80171990((u8 *) s0)` but s0 is of a type requiring a conversion? All pointers are SImode.

What if the call arg is an *offset* address like `(u8 *)((char *)s0 + 0x200)`? That would change the semantics (the call gets a different pointer). Unless the callee adds... no, the target passes s0.

OK. So the only lever is the schedule, which is sched1's hazard analysis. sched1 (the pre-reload scheduler) reorders within basic blocks. Could we make the store come earlier in a way that the scheduler keeps? The scheduler's order depends on the insn priorities and hazards. We tried do-while splits (worse).

Let me try: put the *second call's arg setup* explicitly in the source as a variable assignment AFTER the stores:
```
  u8 *p;
  ...
  v0 = 0x8; store1; v0 = 0x100000; store2;
  p = (u8 *) s0;
  func_80171990(p);
```
At RTL: `p = r72` (a copy) then `a0 = p`. cse merges p into r72 → `a0 = r72` after the store. Then sched1 may hoist it above the store again. Try it (x17).

Or assign p BEFORE the stores: `p = (u8*)s0; ...stores...; func_80171990(p);` → `a0 = r72` after the stores still.

Let me try a few more variants around this, plus some "different variable types" ones:
- x17: p assigned after the stores.
- x18: p assigned before the stores.
- x19: call via a function pointer variable? `void (*f)(u8*) = func_80171990; f(s0);` — that changes the call RTL (a call through a register) → different code. Probably worse, but try.
- x20: `((void (*)(u8 *))func_80171990)(s0);` — a cast on the callee.
- x21: the second store through `(char *)s0 + 0x204` with new_var removed (w02 = 1).
- x22: `new_var` assigned from a0 instead of s0 (after the call a0 is clobbered — invalid).
- x23: `s0 = a0;` inside a do-while at the top (the empty do-while exists; make it non-empty).
- x24: move the empty do-while to different positions.
- x25: two empty do-whiles.
- x26: `char *new_var = (char *) s0;` init at decl (declaration at top).
- x27: store through `new_var` with the cast `(s32 *)(void *)new_var`.
- x28: `*((s32 *) (((char *) s0) + 0x200)) = v0;` → `*((s32 *) (0x200 + (char *) s0)) = v0;` (commuted add — sched/hazard may differ).
- x29: swap the li/store pairs.

Let me generate ~15 more and score. That fills the time.

Also, the empty `do { } while (0);` at the top: does removing it change anything? w01 = 1 (same).

Let me write gen3.py.
