---
ts: 2026-11-06T17:37:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0jw6htmN2AOuRWUTMY4z
---
Time 11.5 min. All 7 except f6.

Let me try a different lever: maybe the pin can be replaced by a C construct that makes the *angle* be in v0 so that the preference chain gives 75 v0.

The angle: `angle = func_80029D3C(cmp79);` The call result is v0. If angle is used ONLY in the shift and the store... The store `p[0x79] = angle` forces angle to live across the branch (the store is before the branch). Hmm, actually the store is before the if, so angle dies at the store? No, the shift uses it after (in the then arm). So angle is live across the branch.

What if we store the call result directly and use p[0x79] in the shift (x1, 7)?

Hmm, x1: `sh16 = p[0x79] << 16;` in the then arm. cse forwarded the stored value.

Let me try to see what x1's asm looks like — maybe it changed the preference. All still 7.

Let me try: make angle a *u16* (the value is a u16 angle)? The call returns s32; `angle` is used as s32. If angle were u16, the store and shift would need andi.

I think this is a wall. Let me spend the remaining time (8.5 min) with a few more, then record a WALL with best 7.

Actually, wait. Let me reconsider the problem: the target's temps are v1 and sh16=v0. What if I make the *first temp* (148) be v1 by construction? 148 = sh16 >> 16. If the source sh16 is v1 (mine), 148 takes v0. If I add a constraint making 148 prefer v1... The temp 148's preference: `set_preference(148, src=75)` → 75's reg (v1). So 148 prefers v1! But local-alloc already assigned 148 (v0) before global.

In the target, 148=v1 (following the preference).

Hmm.

What if sh16 were assigned by local-alloc (block-local)? Then 75 and 148 would be allocated together by priority: 75 (4 refs) vs 148 (2 refs) → 75 gets v0, 148 gets v1 (the preference). That's the target!

So: make 75 block-local. How? 75's defs are in the then/else blocks; the use is in the join block. It's global.

Unless the two arms are in the SAME block as the join! In the CFG, the then arm and the join might be the same basic block (the then arm falls through to the join). The else arm is a separate block (branch target). So 75 is defined in block A (then+join) and block B (else) → global.

What if we eliminate the else block by making the else path a separate function call? no.

What if the else arm's assignment happens in the join block? E.g.:
```
if (r[0x49] == 5) {
    sh16 = angle << 16;
} else {
    if (func_8014CB7C() == 0) goto LAB;
    sh16 = p[0x79] << 16;
}
```
The else block defines 75 and jumps/falls to the join. Since the else block ends with a jump to the join (or falls through), 75 is live from the else block to the join → global.

Hmm, unless the join block is only reachable from the then arm... no.

OK: another approach — make the *then* arm's def the only one and compute the else's value in the join block via a conditional? E.g.:
```
s32 v;
if (r[0x49] == 5) {
    v = angle;
} else {
    if (func_8014CB7C() == 0) goto LAB;
    v = p[0x79];
}
sh16 = v << 16;   // join block: 75 local!
```
This changes the code: the sll moves to the join block (after the merge) — the target has the sll inside each arm (in the delay slot of the beq!). The target's `sll v0,a0,16` is in the branch delay slot (bc18). So moving the sll out would not match.

Therefore the target's 75 is global, and the pin is the only way... unless a different C body yields the same bytes.

Given 141 includers and a 3-instruction residual, I'll record a WALL with best 7.

I need 20 min: currently 11.7. Let me continue with variants for ~8 more minutes.

Let me try things around the angle variable:
g1: `angle = func_80029D3C(cmp79);` → `angle = (s32)func_80029D3C(cmp79);`
g2: declare angle as `s32 angle;` (already)
g3: move the `p[0x79] = angle;` store into each arm? no.
g4: use `sh16 = (angle << 16);` (parens) — same.
g5: `sh16 = (s32)(angle << 16);` — same.
g6: make cmp79/angle types differ.

These are noise. Let me instead try the *expression* that the original source likely had: maybe the target's C used a different expression producing the same bytes. The target's chain:
```
sra v1,v0,16
srl v0,v0,31
addu v1,v1,v0
sra v1,v1,1
sh v1
```
This is `(sh16 >> 16) + ((u32)sh16 >> 31)` then `>> 1`. Our expression matches.

The allocation difference is only which reg sh16 has.

Let me try making the expression use sh16's value in a way that changes 75's qty priority: e.g., use sh16 3 times instead of 2: `((sh16 >> 16) + ((u32)sh16 >> 31) + (sh16 & 0))` — adds an and.

No.

Let me try `sh16` declared as `long` (4 bytes) — same.

I'll run a few more and then record.

Actually — one more idea: the preference is per *allocno*; if 75's allocno could be *coalesced* with another allocno that has a v0 preference... global-alloc's coalescing merges allocnos connected by copies (via expand_preferences at line 815: IOR the preference sets of coalesced allocnos). If we add a copy `sh16 = x` where x is in v0, the allocnos might coalesce and inherit v0's preference.

E.g., `sh16 = p[0x79] << 16;` in the else arm (x1) — no copy.

What about `sh16 = (s32)(p[0x79] << 16);`? no.

A copy: `sh16 = angle << 16;` can't be a copy.

What if we compute `sh16 = angle; sh16 = sh16 << 16;` (y1: 8) — the first is a copy from angle (a0 preference) → the allocnos may coalesce → preference a0, not v0.

Hmm, what if we copy from something in v0? `s32 tmp = p[0x79]; sh16 = tmp << 16;` — tmp is a load temp in v0/v1.

Let me try: in the else arm, `{ s32 lv = p[0x79]; sh16 = lv << 16; }` and in the then arm `{ s32 av = angle; sh16 = av << 16; }`.

Time: let me run these.
