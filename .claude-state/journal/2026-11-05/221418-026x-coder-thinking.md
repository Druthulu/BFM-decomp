---
ts: 2026-11-06T05:14:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9TSPlgvPbVT6z7GwYPXw
---
The kept TU is the n1 body (s32 raw) — stale from the previous --try? Actually p3 might be a different run. It shows s32 raw which is n1, not n2 (u8). Whatever.

Rather than fight with dumps, let me think about the mechanism more cleverly, and use a fast batch of candidates with sc.sh.

Key: we need two real copy instructions. The catalog says "real 2nd set" breaks cse. Here the 2nd set of raw is `raw = t` but cse equates them. What if raw gets a value that is NOT provably equal to t, but still the same at runtime? Like the dead-reset trick: `raw = t; raw = t;`? Hmm.

Alternative approach: use a *different variable* for the store and make the target's structure emerge. Wait — maybe reconsider: what if we make `raw` a `s16` and `t` a `s16` too? Then t = raw - 0x10 in HImode; the compare `t < 0` in HImode → gcc might do sll/sra. Target has `addiu v0,v1,-16` and `bgez v0` — SI mode. So no.

What about making the truncation explicit with a u8 temp: 
```c
u8 raw;
...
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
...
raw = t;      // truncate
t = (u8)raw;  // zero-extend
```
Same as before.

Hmm, why didn't the u8 version produce moves? Possibly gcc's cse equated them anyway because the SUBREG is simplified by combine before cse? Let's check the .cse dump.

Let me set up a dump properly: use cc1_dumps_tu.sh on the kept TU with DUMP_ROOT under my item dir. But the TU there is n1's body; I want n2's. Let me instead re-run --try with --keep for n2 and copy the TU immediately.

Actually simpler: I can construct my own TU copy: take the src TU and replace the function body. But that's more work. Let's just rerun --keep with n2 and copy.

Actually, wait. Maybe I'm overcomplicating. Let me check the .rtl/.cse dump to see how raw/t look.

Plan: run --try --keep with n2.c, then copy the resulting TU to my item dir as tu_n2.c, then dump.

Let me do that.
