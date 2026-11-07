---
ts: 2026-11-06T17:26:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JSIocsytnL5h5iFFqibJ
---
Mine:
```
163 sll v1,a0,0x10     (sh16 = angle << 16)
...
170 sll v1,v0,0x10     (sh16 = p[0x79] << 16)
171 sra v0,v1,0x10     (sh16 >> 16)
172 srl v1,v1,0x1f     ((u32)sh16 >> 31)
173 addu v0,v0,v1
174 sra v0,v0,1
175 sh v0,242(s0)
```
Target:
```
163 sll v0,a0,0x10
170 sll v0,v0,0x10
171 sra v1,v0,0x10
172 srl v0,v0,0x1f
173 addu v1,v1,v0
174 sra v1,v1,1
175 sh v1,242(s0)
```
So the target has sh16 in v0 (the pin) and the result in v1. Mine has sh16 in v1 and the result in v0.

So the register of sh16 must be v0 (not v1), and the result of the shift computation goes to v1.

Lever-free: we need sh16 to get v0. Both sh16 and the result pseudo are block-local (in the block after the if). The result: `p[0x79] = (u16)(((sh16>>16) + ((u32)sh16>>31)) >> 1);` — the temporaries: (sh16>>16) → t1; ((u32)sh16>>31) → t2; sum → t3; >>1 → t4; store. The target's registers: sh16=v0, the sum/result in v1.

Mine: sh16=v1, result v0.

To swap: sh16 should be allocated first (v0), then the temps take v1... The allocation priority: sh16 (a few refs) vs the temps. In the target, sh16=v0 because of the pin.

Lever-free, the temps (short-lived) win v0 and sh16 gets v1.

Ideas:
1. Make sh16's life shorter/higher priority? sh16 is set in both arms and used once. Its life: from the assignment (in the if/else) to the use. The temps are shorter.
2. Split the computation so the result doesn't need a temp: `p[0x79] = ...` directly? Already.
3. Use s16/u16 widths for sh16: e.g., `s16 sh16`? Then `sh16 = angle << 16` truncates (the value is a shifted angle; s16 would keep the high half). Hmm, the semantics: sh16 = angle << 16; then (sh16 >> 16) = sign-extended angle. If sh16 were s16, the assignment would be a truncation — the subsequent >>16 would be wrong.

4. Make the result computation use sh16 directly with fewer temps: e.g., `p[0x79] = (u16)((sh16 + (s32)((u32)sh16 >> 31)) >> 17);`? That changes the instructions.

5. Rewrite as `p[0x79] = (u16)((sh16 >> 16) + ((u32)sh16 >> 31)) >> 1;` — the cast placement changes the ops.

Hmm, the target's instruction sequence:
```
sll v0,v0,16    ; sh16 = p[0x79] << 16  (v0 is p[0x79]? no: `sll v0,v0,0x10` where v0 held p[0x79])
sra v1,v0,16    ; t = sh16 >> 16
srl v0,v0,31    ; t2 = (u32)sh16 >> 31
addu v1,v1,v0
sra v1,v1,1
sh v1,242(s0)
```
Mine:
```
sll v1,v0,16    ; sh16 in v1
sra v0,v1,16
srl v1,v1,31
addu v0,v0,v1
sra v0,v0,1
sh v0,242(s0)
```
Same instructions, different regs. It's purely an allocation choice: sh16 should be v0.

How to make sh16 take v0? Priority: sh16 is set in two places (if/else) and used once. The temps are single-use.

Hmm, in the target, the first arm (angle<<16) is `sll v0,a0,16` — sh16=v0. In mine, `sll v1,a0,16`.

Maybe the difference is the *number of refs* of sh16 vs the temps. If sh16 had more refs (e.g., used twice), it might get v0.

Idea: use sh16 in a second place — e.g., compute the store from a temp and also... hmm.

Idea: make the result expression use sh16 twice (it does: sh16>>16 and (u32)sh16>>31 — 2 uses). So sh16 has 2 uses in the same statement + 2 defs. refs=4.

The temps: each 2 refs, short life. Priority = refs*log/life. sh16's life is longer (from the if to the use).

What if we shorten sh16's life by moving its computation into each arm right before the use? It already is (the arms are the if/else; the use follows the if).

Hmm. What if the two assignments are made into a single variable computed *before* the if? No, the values differ.

Alternative: make the *result* variable explicit and let it take v1: e.g.,
```
s32 r16 = (s32)((u32)sh16 >> 31);
p[0x79] = (u16)(((sh16 >> 16) + r16) >> 1);
```
Naming the temp might change the allocation: the named temp gets a pseudo created earlier (declaration at block start) with lower priority? Hmm.

Actually, let me think about the target: sh16=v0 means sh16 was allocated v0. The temps took v1. In local-alloc, the qty with the highest priority gets the lowest free reg (v0). The temps (short life) usually win. For sh16 to win, it must have higher priority — maybe by having a longer life? The formula divides by life, so a longer life LOWERS priority. Hmm, but refs raise it: 4 refs vs 2.

Let me compute: sh16: 4 refs → floor_log2(4)=2 → 2*4=8; life: from the first def (in the then arm) to the use, maybe 6-10 insns. The temps: 2 refs → 2; life 2-3.

pri_sh16 = 8/life_sh16; pri_temp = 2/life_temp. If life_sh16=8 and life_temp=2: 1.0 vs 1.0 — a tie! Ties broken by qty number: the earlier-created qty wins. sh16 is declared early (pseudo created at declaration? no, at first use in the arms).

Hmm.

Let me try empirical variants:
1. Declare sh16 as s32 at the top (it is).
2. Give sh16 an initializer? no.
3. Change the expression to use `(s32)((u32)sh16 >> 31)` (already).
4. Split the store into two statements with a named temp.
5. Use `u16` for the store value? it's cast to u16.
6. Change the shift to `sh16 / 2`? no.

Actually, the simplest: try naming the intermediate: 
```
{
    s32 t = (sh16 >> 16) + (s32)((u32)sh16 >> 31);
    p[0x79] = (u16)(t >> 1);
}
```
That may change the allocation (t gets a pseudo; the sum might be computed in v1).

Or restructure: `sh16 = (sh16 >> 16) + ((u32)sh16 >> 31); p[0x79] = (u16)(sh16 >> 1);` — reusing sh16 (assigning the intermediate back to sh16). Then sh16's last use is the shift; the result goes to a temp then stored. The target has the result in v1 and sh16 in v0 — if sh16 is reused for the sum, the sum would be in v0 and the store from v0 — not target.

Hmm.

Let me try the "named temp" and a few variants and score on includer 0. Since it's a header item, a crack must score 0 on ALL 141 includers (tryinc k=0..140). That's 141 scores per candidate — expensive (each ~1s → 2.5 min per candidate). The brief says MATCH only if score 0 on every includer. For exploration, I'll score on k=0 (fast) and then verify all 141 only for the final win.

Actually, the delever_search --try for a header tries the recipes in order? The wrapper rotates to k first; --try probably uses the FIRST recipe only (the k-th). To verify all, I need to run tryinc for k=0..140.

Let me first find a body scoring 0 on k=0.

Variants:
v1: named temp.
v2: sh16 as u32.
v3: expression with a helper variable declared at block start.
v4: `p[0x79] = (u16)((sh16 >> 16) + ((u32)sh16 >> 31)) >> 1;` (cast outside).
v5: use `s16`/`u16` widths for the temp.

Let me write these.
