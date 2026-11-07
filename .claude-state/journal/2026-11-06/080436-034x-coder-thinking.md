---
ts: 2026-11-06T15:04:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zOCKaxWcCUZXtUN6wNmI
---
Wait: `v1 = ((Unkstruct_800B5CB8 *)s1)->unk70;` but target has `lh v1,112(s1)` — 112 = 0x70. Yes.

Now let me generate candidates. I'll write a generator script.

Candidates:
c2: s0 declared s16 (line 4).
c3: s0 declared u16.
c4: `do { s0 = 0; } while (0);` instead of `s0 = 0;`
c5: `s0 = 0; s0 = s0 & 0;`
c6: `a0 = s0 * 0x400;`
c7: `a0 = s0 << 10;` moved to be after... hmm.

Let me also consider: maybe use the loop to initialize: change to
```
s0 = 0;
a0 = s0 << 10;
```
→
```
s0 = 0;
if (s1) { }
a0 = s0 << 10;
```
no.

Let me write the generator and score.
