---
ts: 2026-11-06T09:19:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Q3WfuYZ3wV2FLIy2xwjO
---
This is deep. Let me instead empirically try variants. Time-box: ~10 variants.

Actually, wait. The target has `addiu s0,s1,4` and updates BOTH s0 and s1 by 24 each iteration. That's exactly what you'd get if the source had two independent pointers, e.g.:

```c
base = D_801DA130;
for (i = 0; i < 0x40; i++) {
    e = (Sub_80180A54 *)(base + 4);
    ...
    base += 0x18;
}
```
gives one biv base and a giv e=base+4; loop.c created a second biv for e? No—givs are strength-reduced to `e = e + 24` only if beneficial; loop.c's `strength_reduce` does that for givs with mult_val 1: it creates a new biv for the giv. That's exactly `addiu s0,s1,4` + `addiu s0,s0,24`. So target strength-reduced the giv e (kept as a separate biv). Mine did not (it folded e's offset into the accesses).

Why would loop.c do it in one case and not the other? `strength_reduce`'s giv handling: `record_giv` then `strength_reduce_givs` — it creates a new biv for the giv if `v->benefit` ... Actually in loop.c, givs get strength-reduced based on `loop_number` and whether it's used enough: `if (v->giv_count ...)`. Hmm, there's `v->same_insn`? 

Alternatively, the difference might be in the *number of uses* of e: in the pin version, `v0` ($2) is hard, changing nothing about e.

Hold on — maybe the difference isn't loop.c at all but combine/cse folding. In mine the accesses are `lh 6(s0)` with s0=base; target `lh 2(s0)` with s0=e. Both have a separate biv (s0), it's just initialized differently: target s0 = s1+4 (e), mine s0 = s1 (base). So loop.c in mine created a biv for `base` (s0) and kept `base` in s1 too? That's weird: two regs for the same value. Let me look at mine's full dump.
