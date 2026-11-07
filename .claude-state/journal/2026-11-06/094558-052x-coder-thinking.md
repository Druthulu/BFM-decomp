---
ts: 2026-11-06T16:45:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_b83tAIRPEkgcYmCuubwj
---
Item 3: pin $3 (h). The orig has:
```
h = *(s16 *)((u8 *)s1 + 0x70);
...
func_8012C658(0x19B, (s16)(*(u16 *)(t + ((h << 4) + (s32)s2)) + a), (s32)s1);
```
The pin h=$3. Target:
```
2738: lh v1,112(s1)       <- h in v1 ($3)
2740: sll v1,v1,0x4
2744: addu v1,v1,s2
2748: addu v0,v0,v1
274c: lhu a1,0(v0)
...
```
So h is loaded into $3 and used. Without the pin, h might go to v0 or another reg.

Interesting: note the target's structure is very similar to item 2's twin: `sll a0,s0,0x9` before the loop and in the delay slot. And the loop body starts at 2734 (`sll v0,s0,0x1`). So this function's C is likely:

```c
s1 = arg;
s0 = 0;
s2 = D_80189644;
do {
    a = s0 << 9;
    t = s0 << 1;
    h = *(s16 *)((u8 *)s1 + 0x70);
    s0 = s0 + 1;
    func_8012C658(0x19B, (s16)(*(u16 *)(t + ((h << 4) + (s32)s2)) + a), (s32)s1);
} while (s0 < 8);
```
Same as item 2 but with `a = s0 << 9` at the loop head. The orig has `a = s0 << 9` inside the loop at the top already! Yes: `a = s0 << 9;` is the first statement. And there's no pre-loop a computation. Good.

So the only lever is the pin $3 for h. Remove it and find real C that puts h in $3.

Let me first score the plain body (remove the pin line).

The pin is `register int h __asm__("$3");` → plain `int h;` or `s32 h;`.

Note: h is `int` (s32) but assigned from a s16 load (sign-extended). Then used as `(h << 4)`. So h is s32 holding a sign-extended s16.

Let me test the plain body.
