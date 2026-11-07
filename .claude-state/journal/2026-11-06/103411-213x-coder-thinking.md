---
ts: 2026-11-06T17:34:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hDWfHeeJ5WaO4Jinaq5N
---
No. Time 8.2 min.

Let me think about the "preference: 3" once more. I could dump the sched1 RTL (nd.i.sched) and look at the insns around 396-424 to see if any copy to/from a hard reg exists (e.g., REG_NO_CONFLICT notes).

Actually, let me look at the local-alloc dump for the block containing the sh16 code to see which pseudo got which hard reg and their order.

Alternatively, consider: the preference might come from `(set (reg 75) (ashift (reg 77) (const_int 16)))` where the *shift count* is a constant... no.

Hmm, wait: maybe 75's qty includes the pseudo for the `angle` variable AND the shift output, and there's a copy `angle = func(...)` from v0. The suggestion would be v0 (2), not v1 (3).

Let me look at the greg dump's note for 75: "75 conflicts: 72 73 75 2 29" — 75 conflicts with v0 (2) but not v1 (3). And the preference is 3. If the preference is v1, it gets v1.

Where does v1 come from? Let me grep the flow dump for `(reg:SI 3 v1)` near the sh16 insns... The `move a0,v0` etc. are expand-time copies.

Actually! Maybe the preference comes from the *second* shift's source 147: `(set (reg 147) (zero_extend (reg:HI 146)))`. 147 might be tied to v1 somewhere.

I'll stop this line. Let me consider the "no-c-spelling" possibility: the target's sh16=v0 arises from the pin only; lever-free the preference (v1) wins. This is a `lreg-qty-priority` or `global-copy-pref` wall.

Actually the wall tag list has `global-copy-pref`: "call-result copy keeps its hard-reg copy preference; the local result conflicts it, so the target's move is coalesced". Hmm, not quite.

The preference for v1 is the driver: `global-hardreg-reserve`? No.

Let me classify: the shift's output prefers a register (v1) that the target gives to the temps; the target's sh16=v0 needs the preference broken. Tag: `lreg-qty-priority` (local-alloc's qty preference) or `global-copy-pref`.

I'll spend a few more minutes trying to break the tie. One idea: make the shift's source *not die*, so no tie/preference. The source 77 (angle) dies at the first shift (it's the last use). If we add a use of angle AFTER the shift (dead or not), the tie disappears.

A free use: `p[0x79] = angle;` is before. What if we move the store after the shift? The target's order has the store before the branch, so moving it after would change the bytes... but let me test: the store is at insn 396-ish (before the branch). If we move `p[0x79] = angle;` to after the if/else (before the final store), the code changes a lot.

What about using angle in the else arm? no.

What about making the shift source a *copy* that stays live: `s32 a2 = angle; sh16 = a2 << 16;` — a2's last use is the shift (dies) — same tie.

Hmm.

What if the shift is written as `sh16 = angle; sh16 <<= 16;` (y1, score 8).

Let me try `sh16 = (angle << 16) | 0;` — combine folds.

I'll try 2-3 more and then record the WALL at 20 min (currently 8.5).

Actually, let me reconsider the whole item: the header has 141 includers; the body must score 0 on all. Even if I cracked k=0, I'd need to verify all 141. The residual is small (7) but the allocation is pinned by a preference.

Let me try one more idea: change the *order* of the two statements `p[0x79] = angle;` and the if? The store is before the if in the source:
```
angle = func_80029D3C(cmp79);
p[0x79] = angle;
if (r[0x49] == 5) {...}
```
The target's asm: jal; move a0,v0; sh v0,242; lbu; li; beq; sll v0,a0 (delay). So the store and the branch as expected.

What if we remove the `angle` variable and use the call result twice? `p[0x79] = func_80029D3C(cmp79);` then `sh16 = p[0x79] << 16;`? That changes the store's value source (still the call result) but the second use would reload or CSE. The target's `move a0,v0` exists because angle is used twice (store + shift): the value is copied to a0.

Hmm.

Let me try: `p[0x79] = angle;` → keep, but change the then arm to use `p[0x79]` (x1 tried, 7).

OK let me try to see whether the preference changes if the second def's source is different: make the else arm's shift use a *named* load: `s32 lv = p[0x79]; sh16 = lv << 16;` (adds a pseudo, maybe same insns).

Let me test that plus a variant with `sh16 = (s32)(u16)p[0x79] << 16;`.
