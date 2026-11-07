---
ts: 2026-11-06T17:36:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_B68FeLdecCUyUXA33Uqf
---
The setters are as I thought. set_preference(75, src=77) → 77's reg_renumber at global time.

77 = the `angle` variable. Where is it allocated? Let me check the lreg dispositions for 77: "77 in 4" (a0) from the nopin greg list: "72 in 16 73 in 18 74 in 17 75 in 3 76 in 4 77 in 4". So 77 in 4 (a0), and 75 in 3 (v1).

So the preference should be a0 (4), not v1 (3). Yet the dump says "75 preferences: 3".

Unless set_preference for the second setter: src=147, reg_renumber[147] = 2 (v0) — preference v0.

Hmm, so where does 3 come from? Maybe from the `(set (reg 75) ...)` where 75's allocno... 

OH WAIT. Maybe 75's allocno includes 77 (coalesced by local-alloc? no, 75 is global and 77 local).

Alternatively, `set_preference` is called with dest=75 and src=77 where 77 is in a qty that includes other pseudos with reg_renumber = 3.

Hmm, "77 in 4" from the dispositions.

I'm stuck on the mechanism. Time: 11.5 min. Need 20. Let me try 8 more minutes of variants.

Let me try a different lever: since the preference comes from the setter's source register, change the *source* of the second sll to be in v1 (then 75 prefers v1 — already) or make the first setter's source be in v0 (then 75 prefers v0, but the second setter's preference v0...). 

The preference set is the UNION over setters. If I can make the first setter's source (77=angle) be in v0, the preference would include v0; then find_reg would pick v0 (the lowest preferred?) if free.

How to make angle be in v0? angle = func_80029D3C(...) returns v0; the assignment angle = call_result creates a copy. In the target, angle is in a0 (a copy from v0) because the store and the shift use it. If angle stayed in v0... it can't (the store uses it, then the shift; v0 is also used for the call at func_8014CB7C in the else path).

Hmm, what if angle is used only once (no store)? The store is needed.

What if we store `angle` and use the *call result* directly for the shift? e.g.:
```
angle = func_80029D3C(cmp79);
p[0x79] = angle;
if (r[0x49] == 5) {
    sh16 = angle << 16;
}
```
To use the call result directly we'd need to keep it: 
```
angle = func_80029D3C(cmp79);
p[0x79] = angle;
```
same.

What if we write `p[0x79] = angle = func_80029D3C(cmp79);`? Same.

Hmm.

Let me try making the second setter's source (147) be v1 instead of v0: the load `lhu` destination. 147 is a temp; local-alloc gives it v0 or v1. If 147 were v1, then the preference would include v1 (same as now).

What if we make BOTH setters' sources v0? The first source is angle (a0), the second is the load (v0).

Honestly, the union preference is {a0, v0} = {4, 2}... but the dump says {3}. Something's off in my understanding. Let me just accept it.

Let me do a few more variants and then record a WALL at 20 min. Current 11.7 min.

Variants to try (spellings):
f1: `sh16 = (s32)((u32)angle << 16);`
f2: `sh16 = angle * 0x10000;`
f3: `sh16 = (angle << 16) + 0;`
f4: the else arm: `sh16 = (s32)((u32)p[0x79] << 16);`
f5: `p[0x79] = (u16)((sh16 >> 16) + ((u32)sh16 >> 31)) >> 1;`

Let me run a batch of 6.
