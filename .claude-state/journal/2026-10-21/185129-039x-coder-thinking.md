---
ts: 2026-10-22T00:51:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_avAYd5qMP83W9hqpz2Rr
---
Script execution under .run is blocked. Fine.

Let me look for a tools/ script that dumps an object's instructions. `tools/lever_census.py`? It prints "selftest: instruction mnemonics not recorded". Let me grep tools/ for a CLI that prints mnemonics of an object.

Actually, `tools/masked_diff.py <a.o> <b.o> fn` prints counts only. But `diff_object_s`? no.

Hmm, what about `tools/cc1_dumps_tu.sh`? It dumps the compiler's RTL passes for a TU — which includes the final "final" RTL with the scheduled instructions! That's for a TU I compile though.

Hmm, but here's the thing: I want the TARGET's listing. The target = the current src def. If I dump cc1's RTL for the current src (with the launder), I'd see the final instruction sequence = the target's.

But wait, that's a lot of output and I'd need to read it.

Alternative pragmatic approach: I can infer the target's tail from the diff. I know:
- target[83] = li a0,2366
- target[84] = ori a1,a1,0x3000
- target[85] = or a1,a1,a2

and mine (cand03):
- mine[83] = ori a1,a1,0x3000
- mine[84] = li a0,2366
- mine[85] = or a1,a1,a2

So I need to swap two adjacent instructions: the li a0 before the ori.

Since both are independent (the li a0 is the constant arg, the ori is the vol|flg chain), the scheduler's choice depends on LUID/priority.

The ori in the target is part of the argument expression `((vol|flg)|x)&0xFFFF` (in the original source). In the target the ori has a LUID AFTER the li a0. Hmm, that means in the target, the constant was materialized BEFORE the expression's ori.

Why would gcc materialize the constant first? Because the constant is CHEAP and the arg expression is a chain... no, gcc materializes constants at the point of the call in the arg-setup group.

Hmm, hold on! What if in the target, the `ori a1,a1,0x3000` is NOT vol|flg but the `| 0x3000` folded into the final expression differently. Let me reconsider: maybe the target computes:
- a1 = vol (from the launder's asm output, in a register)
- ori a1,a1,0x3000 → a1 = vol|0x3000
- or a1,a1,a2 → a1 |= x
And the li a0,2366 at 83.

In the target, the sequence order is: ..., 82 (?), 83 li a0,2366, 84 ori a1,a1,0x3000, 85 or a1,a1,a2, 86 jal.

The jal is the call. The arg setups (li a0, ori a1, or a1) are all in the arg-setup group before the jal.

So in the target's RTL, the LUID order is: li a0 < ori a1 < or a1. So the constant was materialized BEFORE the or-chain.

In MIPS gcc, the call args are set up in the order a0, a1, a2 (the arg-setup pseudo). The RTL for the call: `call f (a0, a1, a2)` with the args as parallel sets. The LUIDs of the arg values are determined by when they were computed. For a constant arg, gcc creates the constant at... hmm, in RTL, `call` with a constant operand → the constant is materialized into a pseudo reg first (during expand) with the LUID of the call's expansion.

For a complex expression arg, the expression's insns get LUIDs earlier (when the expression is expanded, before the call).

So: constant arg → li has a LUID at the call site; expression arg → its insns have earlier LUIDs. Hence expression first, constant second — mine's arrangement!

But the target has the constant FIRST. So in the target, the constant's li must have gotten an EARLIER LUID than the expression's ori.

How? The launder! The asm is an insn with a LUID. Hmm, but that's earlier still.

Hmm, what if the ori in the target is NOT part of the arg expression, but a separate statement (like in cand03) — and its LUID is after the li? In cand03 the ori IS a separate statement but its LUID is BEFORE the li (statement before the call).

Unless the statement order in the source is: the call first?? No.

Hmm, what if the ori is a separate statement AFTER the constant's materialization, e.g.:

```
{
    s32 flg = 0x3000;
    s32 c = 0x93E;    /* hmm */
```

OK here's another thought: what if the constant 0x93E is materialized early because it's used as the FIRST argument and gcc evaluates args LEFT to right when... hmm.

Let me look at this from a completely different angle: maybe the target's tail is:
```
82 ori a1,a1,0x3000    ← no...
```

Let me just try things empirically. Variants for cand05:
(a) `s32 c = 0x93E;` declared and assigned right before the call, and pass `c`:
```
{
    s32 flg = 0x3000;
    vol = vol | flg;
    s32 c = 0x93E;
    func_8002D4C8(c, (vol | x) & 0xFFFF);
}
```
Hmm, but then c's li is created at its statement (before the call) → LUID before the ori? No: the ori statement comes before the c statement in source order. Ugh. I'd put `s32 c = 0x93E;` BEFORE the ori statement:
```
{
    s32 c = 0x93E;
    s32 flg = 0x3000;
    vol = vol | flg;
    func_8002D4C8(c, (vol | x) & 0xFFFF);
}
```
Then c's li has an earlier LUID than the ori. But gcc's front end may propagate the constant and materialize it at the call site (the constant is a "constant" pseudo, and gcc 2.7's expand creates the li right before the call in the arg-setup). Hmm, but if c is assigned and then used, expand might keep it as a reg set (li) at the assignment point.

Risk: the value would be in a pseudo → `li v0,2366` then `move a0,v0` (2 insns) → +1 insn → worse.

(b) Alternative: swap the argument ORDER? Not allowed (semantics).

(c) Alternative: make the ori LATER by moving the `vol = vol | flg;` statement after the x computation (it already is after). Hmm, in cand03 the order in source is:
```
x = (x + 0xA0) / 0x14;
if (x == 0x10) x = 0xF;
x = x << 8;
{
    s32 flg = 0x3000;
    vol = vol | flg;
    func_8002D4C8(0x93E, (vol | x) & 0xFFFF);
}
```
The ori statement is immediately before the call. Its LUID is just before the call's LUID. The li a0,2366 is created by expand at the call. So the ori has an earlier LUID → ori first. To flip, the constant must be created BEFORE the ori statement.

So: put the constant's creation earlier in the source:
```
s32 c93e = 0x93E;    /* at the top of the function, or before the if */
```
then use `func_8002D4C8(c93e, ...)`. The li would then be created early (if gcc keeps the assignment as a real set) → LUID early → scheduled before the ori.

But if the front end folds the constant into the call (likely), we're back to square one. However, there's a trick: if c93e is used TWICE, gcc can't fold it into one use... but then it needs a register → `li v0,2366` + `move a0,v0`? Hmm, actually gcc's copy propagation would coalesce.

Hmm, what if the constant is declared at the top and used once — gcc's "constant propagation" (in expand) replaces the pseudo with the constant, and the li is emitted at the use point. So no.

What if the value is not a constant at the RTL level but computed? E.g. `s32 c93e = 0x93E;` where 0x93E is spelled as `0x900 + 0x3E`? gcc folds constants.

Hmm, what about `0x93E` as a `u16`? `s32 c93e = (u16)0x93E;`? hmm, that's 0x93E as u16 = 0x093E (same). The li would be `li a0,0x93E` → addiu a0,zero,0x93E. Fine, but the LUID issue remains.

Hmm. What if the difference isn't LUID but the delay-slot filling? The `li a0,2366` might be scheduled into a delay slot of a preceding branch! In the target, `li a0,2366` at 83 might be in the delay slot of the `bne` at 79? No, too far.

Let me get more context: what are the insns at 80-85 in mine and target? Let me use the diff on a candidate that differs more, so the diff prints the region. Actually, the diff prints only the changed blocks; the region 79-85 was partially printed.

Let me try to see the full target listing via a different route: cc1 dumps of the CURRENT src (which matches the target). tools/cc1_dumps_tu.sh — let me check what it does and whether it can run on the tree's src file with a dump dir under my shard.

The dumps would show the final RTL (insn sequence with LUIDs?). GCC 2.7 dumps don't have LUIDs, but the "final" dump shows the scheduled RTL. That would give me the exact instruction order of the target.

Let me check cc1_dumps_tu.sh usage.
