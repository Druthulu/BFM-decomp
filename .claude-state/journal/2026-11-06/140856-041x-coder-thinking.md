---
ts: 2026-11-06T21:08:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5pxrQkVqh8g0u9rNkeNj
---
Fine — other shards may append. Now item 2.

Item 2: func_8017F0D0, kinds keepalive,pin. Need both gone. Target: 
- pin $2 (rv)
- keepalive asm on rv.

The function:
```
void func_8017F0D0(s32 *a0, s32 a1, s32 a2) {
    extern s16 D_80126CBA;
    s32 sp10[4];
    s32 sp20;
    s16 *q;
    u16 *p;
    s16 t;
    register s32 rv __asm__("$2");
    q = &D_80126CBA;
    if (*q == 0) { p = (u16 *)(q - 3); CAST_WIDTH(s32, a1, 0xE0) = 0; }
    else { p = (u16 *)(a1 + 0x88); CAST_WIDTH(s32, a1, 0xE0) = 1; }
    *(s16 *)((s32)sp10 + 0x2) = p[0] + *(u16 *)a2;
    t = p[1] + *(u16 *)(a2 + 2);
    *(s16 *)((s32)sp10 + 0x6) = t;
    ((Unkstruct_80126B58 *)a1)->unk100 = t;
    *(s16 *)((s32)sp10 + 0xA) = p[2] + *(u16 *)(a2 + 4);
    func_8012B77C((s32)&sp20, a1 + 4, (s32)sp10);
    rv = sp20;
    *a0 = rv;
    rv = (s32)a0;
    __asm__ __volatile__("" : : "r" (rv));
}
```

Target:
- After the call: `lw v0,32(sp)` (sp20), `nop`, `sw v0,0(s0)` (a0 = s0), `move v0,s0` (rv = a0), then epilogue.
- So rv holds a0 (s0) and is moved to v0; rv's $2 pin makes `move v0,s0` land in v0. And the keepalive keeps rv live (void fn).

The comment in the src says: "(3) The TU declares extern void func_8017F0D0(...) at file scope 3x, so an s32 * return is a HARD cc1 conflicting types error. The trailing addu $v0,$s0,$zero therefore comes from a $2-pinned temp. (4) The pin is load-bearing twice: pinning the POST-CALL temp to $v0 is what stops sched2 hoisting the return copy into the load-delay slot... (5) rv = (s32)a0; alone is DELETED by flow ($2 is dead at the end of a void fn). The empty volatile asm keeps it live."

So this is the classic "expand-void-return" / flow-unused-result wall. The move v0,s0 at the end is a dead value in a void function. Without keepalive, flow deletes it. Target keeps it.

Walls: expand-void-return, flow-unused-result. Many PARTIAL/WALL in moves.md. To crack: find a real C use of the value that costs no extra insns.

Target's final: 
```
329c: lw v0,32(sp)      # rv = sp20
32a0: nop
32a4: sw v0,0(s0)       # *a0 = rv
32a8: move v0,s0        # rv = (s32)a0   <- dead
32ac: lw ra,44(sp)
...
```
So `move v0,s0` is dead. flow deletes dead sets of a reg. To keep it, the value must be used. But no use in target. So this is likely a WALL unless a real C use exists that emits zero bytes.

Hmm — but the shard is "singleton crack shard W50x" where each item has a chance. Let me think.

Actually, maybe the pin $2 can be replaced by a real return: if the function returned s32, the value would be live. But the TU declares `extern void func_8017F0D0(...)` 3x at file scope → conflicting types if we define it s32. Constraint: "no signature or decl change outside the body (callers stay as they are)". So we can't change the signature.

Hmm. But maybe we can make `rv` be used by a real statement that emits no code. E.g., `*a0 = rv;` uses rv. Then `rv = (s32)a0;` dead.

What if we reorder: `rv = (s32)a0; *a0 = rv;`? Then the store writes a0's value to *a0 — semantics differ (target stores sp20). No.

What real C could produce `move v0,s0` with a use? 

Idea: the function is void, but if the last statement is `*a0 = (s32)a0`? No, target stores sp20 then moves.

Hmm, what if the store uses the pinned rv: target `sw v0,0(s0)` where v0=sp20. If C is `*a0 = rv;` with rv=$2, then rv = sp20 → lw v0,32(sp) then sw v0,0(s0). Then `rv = (s32)a0` → move v0,s0 dead. 

What if instead we write the store as `*(s32 *)rv = ...`? no.

Let me think about a real use of a0 that yields `move v0,s0` and is live. E.g., if the function's last statement is a call passing a0? Target has no call.

This looks like a genuine WALL (expand-void-return / flow-unused-result). But maybe the pin can be dropped and the move still appear because of something else. Let me first try the obvious: remove keepalive, keep pin → score? Then remove pin too.

Let me test variants:
A. orig minus keepalive (pin kept).
B. orig minus keepalive and pin, rv as plain s32.

Then explore.

Note: item 2's row kinds = keepalive,pin. MATCH requires both gone AND score 0. PARTIAL:keepalive or PARTIAL:pin if one remains and score 0.

Let me test.
