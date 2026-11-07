---
ts: 2026-11-06T10:14:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_A3fg44jPxaVjwTpthmdd
---
Item 3 is the same pattern: `div` (s0) and `a` (arg2) swapped. The target has div in s0, a in s1. Mine has div in s1, a in s0.

In item 3, the function signature: `s32 func_8012BB3C(s32 arg0, s32 arg1, u32 arg2, s32 arg3)`.
```
s32 a;   /* $s1 */
register s32 div __asm__("$16"); /* $s0 */
s32 q;    /* $v1 */
s32 d;    /* $v0 */
s32 ang;
s32 diff;
u32 cur;
a = arg2;
div = arg3;
ang = ratan2(...);
ang = ang - 0x400;
__asm__ __volatile__("" : : "r"(ang));  // keepalive
div = (s16)div;
a = a & 0xFFF;
cur = ang & 0xFFF;
...
```
Target: div→s0, a→s1. Mine: div→s1, a→s0.

Here `a = arg2; a = a & 0xFFF;` — a is the masked value (used later). `div = arg3; div = (s16)div;`.

In mine, a (the masked, multi-use) gets s0 and div gets s1. In the target, div gets s0 and a gets s1.

Interesting: here `a` is assigned `a = a & 0xFFF` (self-set, so a is one pseudo, global?). Let me check: a is used in `if (a == cur)` (block 0) and `diff = cur - a`, `t = a + 0x1000`, `t = a - 0x1000` — multiple blocks → global.

div is used in the divs (blocks) → global.

So both global. The target has div (pri?) > a (pri?) → div gets s0.

Let me get the alloc table for item 3's nopin.

This is the same class as item 2 but with both variables global. That's more tractable: adjust the priorities.

Let me write item 3's nopin and dump.

Actually, item 3's structure is EXACTLY like item 2's g1 variant (a = a & 0xFFF, self-set, global). So item 3 is the "clean" version of the g1 idea. And the target has div=s0, a=s1.

So for item 3: div vs a priorities. If div's pri > a's, div gets s0. Let me check the current (nopin) priorities.

Let me create item 3's nopin and dump.

Item 3 body (lever-free):
```
s32 func_8012BB3C(s32 arg0, s32 arg1, u32 arg2, s32 arg3) {
    s32 a;
    s32 div;
    s32 q;
    s32 d;
    s32 ang;
    s32 diff;
    u32 cur;
    a = arg2;
    div = arg3;
    ang = ratan2(...);
    ang = ang - 0x400;
    div = (s16)div;
    a = a & 0xFFF;
    cur = ang & 0xFFF;
    ...
}
```
Let me write it and dump the alloc table.

Note: the `extern s32 ratan2` is outside the def. The body span starts at `s32 func_8012BB3C(...)`.

Let me write.
