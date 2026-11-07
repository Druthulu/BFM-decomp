---
ts: 2026-11-06T08:32:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0Y8yJSNRXxqMIE83fki2
---
So without the asm, the `addiu a0,sp,24` is emitted after the branch (in the delay slot position of bnez), whereas target emits it before the beqz. The keepalive asm forced a0 to be set before the beqz. So we need real C that computes the address before `if (D_801270C8 != 0)`... Actually target: at insn 29, `addiu a0,sp,24` right after beqz (delay slot of beqz at 28), and then bnez at 33 without delay fill. So the address is computed between the two branches, i.e., before `if (D_801270CC == 0)`.

Lever-free real-C ways to make the address computed before the second test:
1. Use `a0pin` in the outer condition, e.g. `if (D_801270C8 != 0 && D_801270CC == 0)`? No.
2. Make a0pin a real pointer that's used to compute something before the inner if, e.g. `a0pin = sp18; sp18[0] = ...` before? But that changes order of stores.
3. Assign the address via a store that happens before the branch... Hmm.
4. Use `void *a0pin = sp18; if (a0pin != 0 && D_801270CC == 0)`? gcc would fold a0pin != 0 to true (known non-null) — flow-known-value wall.

The address is `sp+24` = sp18 (sp+0x18). Frame: sp10 at sp+0x10 (6 bytes), sp18 at 0x18 (20 bytes) → total 0x2C→ frame 0x30. So a0 = sp+0x18.

What real C makes gcc materialize the stack address early? Perhaps using sp18 as an argument to a different call? No.

Alternative: declare the pointer outside the if:
```c
if (D_801270C8 != 0) {
    void *a0pin = sp18;
    ...
```
The keepalive asm makes a0pin live from that point. Without it, gcc sinks the address computation into the delay slot of the bnez.

Real C that creates a use before the branch: e.g., `a0pin = sp18; a0pin = (void *)((u32)a0pin | 0);` — identity, doesn't count as a crack (launder). Hmm, but the constraint says identity-statement launders do NOT count as a crack. So we need a genuine use.

What if we pass the address to a dummy store before the branch? That adds instructions.

Another approach: make `sp18` itself used before the branch. E.g., hoist one of the stores: `sp18[5] = 0;` before `if (D_801270CC == 0)`? No—target has stores inside.

Look at the target instructions: at 28 beqz (test D_801270C8?) with delay `addiu a0,sp,24`; then bnez (test D_801270CC) at 33. So the address is computed unconditionally once past the outer test, before the inner test. That's exactly what the keepalive achieves.

Real C equivalent: use the address in the outer if condition somehow? Like:
```c
void *a0pin = sp18;
if (D_801270C8 != 0) {
    if (D_801270CC == 0) { ... }
}
```
Here a0pin declared outside the outer if. gcc might still sink. Unless a0pin is used in the condition: `if (D_801270C8 != 0 && D_801270CC == 0)` and then a0pin... no.

Hmm, what about the assignment to `a0pin` being a volatile? No.

Think about what real code the original had. Maybe the original C was something like:
```c
if (D_801270C8 != 0) {
    if (D_801270CC == 0) {
        ...
        func_8012C51C(sp18, param_1);
    }
}
```
and the compiler's target (original binary) computed `addiu a0,sp,24` before the second test — maybe because the original source had the array passed differently, e.g., the call was `func_8012C51C(&sp18[0], param_1)` and gcc hoisted the address? No, that would sink too.

Alternatively the target might have the address computed as part of something else: e.g., `sp18[0] = ...` uses sp+0x18 as a base; the addiu a0 could be a copy of a base register used for stores. Actually stores to sp18[0..] use `sh rX, 24(sp)` (base sp, offset 24). So a0 is a separate computation.

Real C that materializes an address early: passing `sp18` to a function whose call is... no.

What about making the address live across the inner branch by a *store through the pointer* before the branch? That's a new instruction.

Hmm — maybe use the pointer in the outer condition: `if (D_801270C8 != 0 && (a0pin = sp18, D_801270CC == 0))` — comma operator with assignment... that's a launder-ish but the assignment is real; gcc would still schedule.

Alternatively, restructure so the address is computed for a store that the target has anyway. Target insns 29 addiu a0,sp,24 — then later stores use 24(sp). Since a0 = sp+24 is computed anyway, maybe the original source had `func_8012C51C(sp18, param_1)` and something else using sp18 earlier.

Let me see the full target listing vs mine to know the whole function. Let me get the diff full listing (dt.sh tail 40).

Actually the diff only shows mismatches; I want the full target asm. Let me use delever_search with a way to dump? There's `.run/P40/T10/hdump.sh` for headers, tools/cc1_dumps_tu.sh for TU dumps. Simpler: the diff shows insns 28-35. Let me get a bigger tail maybe with context. Actually delever_search likely prints only mismatched regions.

Let me try a candidate that makes a genuine early use: assign the address to a variable that is also used in the inner body for the stores, i.e., replace `sp18[i] = x` stores with `((u16*)a0pin)[i] = x`. Then a0pin is used by stores after the branch, still sinking.

What if the *first* store is before the inner if? Not in target.

Idea: make a0pin used in the outer condition as an argument to something cheap? No.

Alternative real C: declare `u16 *a0pin = sp18;` and use it in a loop or in a comparison like `if (a0pin == sp18)`? That's identity.

Hmm, look at target: `addiu a0,sp,24` in the *delay slot of the beqz*. That means the compiler (GCC 2.7.2, reorg/dbr) filled the branch delay slot with the addiu — i.e., the addiu is placed right after the beqz. And then `bnez v0` at 33 with a nop delay? The target at 33-34: bnez v0, ... and then nothing (target has 57 insns total, so insn 34 exists in mine only: mine 58). The diff says mine[33:35] vs target[33:34]: mine has bnez + addiu, target has bnez only. So target's bnez delay slot is filled by the following insn (the `sw`/stores?) or it's a nop... Let me see more of the listing.

Let me dump both fully. How does delever_search produce its output? Maybe there's a --keep or a way to print. Let me check its --help.
