---
ts: 2026-11-06T06:07:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aikVIE8eR1KFZxdIqegb
---
n2: 67 ins vs target 65. Differences:
1. Frame 56 vs 48: mine saves s1 (extra callee-saved) — because `pa0 = s0` created a copy in s1, and the code uses `move a0,s1` for the calls (instead of `move a0,s0`).
2. The v1 pin: mine has `lh a0,0(at)` and uses a0; target `lh v1,0(at)` uses v1.

So:
(a) The launder (pa0 = s0) must be removed entirely: use `s0` directly instead of `pa0`. Then no copy, no s1.
(b) The v1 pin: v1 = D_80184CA8[...] must be in $3.

Let me first do (a): replace pa0 with s0 (remove the pa0 variable and the copy).

Then the code:
```c
{
    s32 v0, v1;
    v1 = (s32)&D_80184CCC[0];
    v0 = (((Unkstruct_800B5CB8 *)s0)->unk100 << 4) + v1;
    v0 |= 0x40000000;
    *(s32 *)(s0 + 0x58) = v0;
    *(s32 *)(s0 + 0x1C) = *(s16 *)(s0 + 0x70);
    func_8012AD50((void *)s0);
}
```

Let me test that.

And (b): the v1 pin at $3. The variable v1 is used in the first block:
```c
v1 = D_80184CA8[((Unkstruct_800B5CB8 *)s0)->unk70];
((Unkstruct_800B5CB8 *)s0)->unkFE = (v1 & 0xF000) >> 12;
((Unkstruct_800B5CB8 *)s0)->unk100 = v1 & 0xF;
v0 = ((Unkstruct_800B5CB8 *)s0)->unk20;
((Unkstruct_800B5CB8 *)v0)->unk12 = v1 & 0xFF0;
v1 = ((Unkstruct_800B5CB8 *)s0)->unk100;   // 2nd set
if (v1 == 2) { ... }
```
The target has `lh v1,0(at)` (the load into v1) and uses v1 for the masks. Note the target's `lw v0,32(s0)` comes later (insn 25).

Hmm, the pin makes v1 = $3 (v1). Without it, mine puts the loaded value in a0.

Let me first test (a) alone.
