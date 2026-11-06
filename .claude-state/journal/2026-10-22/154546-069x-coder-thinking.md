---
ts: 2026-10-22T21:45:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YBaNXsB2XCF3dlieH857
---
Same. sw ra at slot 4 instead of 3.

Since slot 3 is `move s0,a0` and slot 4 is sw ra... in mine sw ra is at slot 4? "insert target[3] sw ra; delete mine[4] sw ra" means mine has an extra insn at index 3 and sw ra at index 4. So mine: [3] = li v0,-64, [4] = sw ra. Target: [3] = sw ra, [4] = li.

I've tried ~29. Let me try 3 more with a different angle: what if `loc` is declared with an initializer via a *designated* first element only, e.g.:

`S16_SC02_005_8017F7CC loc = {{0}};` — zeros all 16 bytes → 4 sw or 8 sb. Let me just test it to see (cheap).

And: `s16 loc16[2] = {0, -0x40};` with the b copy at `((u8*)loc16) + 8`:
```
s16 loc16[2] = {0, -0x40};
*(M8_SC02_005_8017F7CC *)((u8 *)loc16 + 8) = D_801E2DD8;
```
Let me test that — if the frame stays 40 and the offsets are 16/18/24, it could be a MATCH.

Let me also test the variant with a following `s32 pad[2];` to force the frame.

Run 3 tests.
