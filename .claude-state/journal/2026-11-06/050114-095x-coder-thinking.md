---
ts: 2026-11-06T12:01:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7QwxyrlWmgI8t9qHrP47
---
No help from the do-while boundaries. The store still sinks.

Let me think about the store sink differently. The target has:
```
29 sw v0,16(s0)    <- store 0x10
30 li a0,2432      <- func_8002D4C8 arg
31 lui v0,0x20
32 sw v0,20(s0)    <- unk14
...
```
Mine:
```
29 li a0,2432
30 sw v0,16(s0)
31 lui v0,0x20
32 sw v0,20(s0)
```

So the li a0 is placed before the store in mine. The store uses v0 (the computed v). The li a0 is independent. sched1 hoisted the li a0 above the store.

Wait, actually — maybe it's not sched1 but the order of the RTL. Let me think: the store `*(a0+0x10) = v` and then `unk14 = 0x200000` (a store to a0+0x14). The li a0 for the final call comes after. sched1 moves the li a0 up to fill a slot / reduce stalls.

To prevent, I need a dependence. If the store 0x10 used `a0` and the li a0 is a WRITE to a0, then the store must come before the a0 overwrite (RAW/WAR). Wait — the store uses `s0` (a0 was moved to s0). So no dependence on a0. But what if the store used `a0` directly instead of s0? Then the li a0=0x980 (write to a0) would have a WAR dependence with the store (which reads a0), forcing the store before the li!

Hmm, but the target uses `sw v0,16(s0)`. So the store uses s0. If I made the store use a0... the compiler would still use s0 (since a0 was moved to s0 for the parameter).

Wait, the parameter a0 is moved to s0 at entry (`move s0,a0`). All accesses use s0. So a0 is free after entry. The final call sets a0=0x980.

To create a WAR dependence, the store would need to read a0. But a0 holds the parameter only until it's moved to s0. After that a0 is free.

Hmm.

Alternative: what if the tail's stores are ordered such that the 0x10 store naturally comes first? Let me reorder the source tail:
```
    CAST_WIDTH(s32, (u8 *)a0, 0x10) = v;   // move this out of the middle block
    unk14 = 0x200000;
    ...
```
But v is block-local. Let me declare v at function scope (move `s32 v;` out) and put the store in the tail. Then the source order is: store 0x10, unk14, ... , final call. The scheduler might keep the store first. But the target has the store at 29 (right after the v computation and before li a0). If I move it to the tail, it's already before the other stores. Let me try.

Actually, the middle block computes v and stores it. If I move the store to after the middle block (function scope v), the store is still before unk14 etc. Let me test.

Variants:
- v_v_func_scope: declare `s32 v;` at function scope, remove the middle block braces (or keep), move the store after the block.

Hmm, the middle block has `s32 v;` inside. Let me restructure:
```
void func_80180F68(s32 a0)
{
    s32 v;
    { s32 *p; ... }   // first block
    func_8012B2CC(a0);
    func_8012B200((u8*)a0);
    v = CAST_SIGN(s16, (u8*)a0, 6);
    if (...) {...}
    CAST_WIDTH(s32, (u8*)a0, 0x10) = v;
    unk14 = ...
}
```
This moves v to function scope. Let me test.

Also, maybe the issue is that the store is at the end of a block and the scheduler treats the block boundary specially. Moving it to function scope might change it.

Let me try a batch:
- v_v_func: v at function scope, store after the if.
- v_store_before_unk14: same as v_v_func but explicit.

Let me also try: make the store depend on the final call's result? No.

Let me test v_v_func.

Actually, let me reconsider: the target's store at 29 is right after the `lui v0,0xfffd` (insn 28, the last v computation) and before `li a0,2432`. So the store immediately follows v's computation. In mine, the li a0 is between. 

If I reorder the source so the store immediately follows the v computation (it does), and the li a0 is for a LATER statement, the scheduler still hoists the li. 

Hmm. What if the store's value v and the li a0... no relation.

Let me try making the final call's argument NOT a constant, so the li isn't hoistable? E.g., `func_8002D4C8(0x980, 0)` — the 0x980 is a constant. If I load it from a variable... adds insns.

What if I reorder the tail so the final call comes before the stores? No, changes semantics.

Let me try v_v_func and a few order variants. Let me generate.

Actually, the simplest: maybe the store sink is a sched1 issue that's hard to fix. But let me try moving the store to function scope and reordering.

Let me write gen6.
