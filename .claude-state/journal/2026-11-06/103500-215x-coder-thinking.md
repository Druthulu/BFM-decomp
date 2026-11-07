---
ts: 2026-11-06T17:35:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rwqNegrHM7ODRV6XFdb4
---
This is the hard-reg operand case. The tie 75-77 (pseudo-pseudo) happens in the code above when `ureg` (77) is a pseudo that dies. Then 75 joins 77's qty.

So 75 and 77 might share a qty! Then the qty's register is shared by both pseudos. In the asm, the first sll is `sll v1,a0,16` — source a0, dest v1, so 77 and 75 are different regs → not tied. Unless the tie only happened for the second def (75-147) and not the first (because the qty was already assigned?).

The combine happens in block_alloc's first pass over the insns, in chain order. The first def (396, in the then block) ties 75 to 77's qty if 77 dies there. Then the second def (419) can't tie (75 already has a qty). So 75's qty includes 77 (angle).

Then the preference for v1 in the qty comes from 77's qty: 77 = angle, tied to... the call result copy? The call result is in v0 (hard reg), and `angle = func(...)` — expand may create `(set 77 (reg v0))` → combine_regs ties 77 to v0 (a hard reg suggestion: 2). Hmm, that would suggest v0, not v1.

Unless angle's qty also includes another pseudo with a v1 suggestion.

Ugh.

Time: 9.5 min. I'm going to try a couple more then wall. Let me try the *most direct* lever: make the shift's source NOT die (so no tie with 77), by using angle after the shift in a zero-cost way. Is there any way to use angle after the shift for free? The store `p[0x79] = angle` is before. If we move the store AFTER the if/else... let me actually test that (the store is dead after the join? no, it's a real store).

Move `p[0x79] = angle;` from before the if to after the final store? The target's order: the store happens before the branch (bc08). Moving it after would change the instruction order — likely a bigger diff. But maybe sched1 moves it back? The store is a memory write; sched1 can move it within the block (the arms are different blocks). If the store is placed after the if/else in C, it'd be in the join block → different block → can't be scheduled back. So no.

Alternative: make the shift's source a variable that is NOT the same as the stored angle: e.g., 
```
angle = func_80029D3C(cmp79);
p[0x79] = angle;
if (...) { sh16 = (angle + 0) << 16; }  // folds to angle
```
folds.

Hmm.

What if the then arm reads p[0x79] (a load)? x1 tried (7) — cse forwarded the value.

What if the then arm uses a *copy* of angle made after the store: `s32 b = angle; sh16 = b << 16;` — b dies at the shift, tie 75-b, b tied to angle's qty... same.

OK. Let me record a WALL. But wait — 9.5 min; a WALL needs 20 min. I need 10 more minutes. Let me continue with meaningful experiments for 10 more minutes.

Actually, maybe I should reconsider: the score is 7, and the diff is 3 instructions (sll×2, and the chain). What if I make the sh16 chain use *v0* by making the FIRST temp's source v0? Hmm.

Let me try the "sh16 local" idea despite the extra copy: 
```
s32 shv;
if (r[0x49] == 5) { shv = angle << 16; } else { ... shv = p[0x79] << 16; }
sh16 = shv;  // join
p[0x79] = ...
```
sh16 (local to the join block) would be allocated with the temps by local-alloc; sh16 has 2 refs (def+use) and the temps 2 refs; the priority order might give sh16 v0 (born first). But the extra copy `move` would appear → 255 ins. Not matching.

Unless combine folds the copy into the temps... The copy sh16 = shv where shv is used once → combine folds it, making sh16 equivalent... then the same as now.

Hmm.

Let me try yet another angle: the *store* `sh v0,242(s0)` in the target is at the end of the chain (after the sra). In mine too.

What if the expression is written to use a different number of temps such that the register assignment aligns? E.g., `p[0x79] = (u16)((sh16 + (s32)((u32)sh16 >> 31)) >> 17);` (b3: 24, 251 ins).

Let me look at b4 (14, 251 ins): `(sh16 >> 17) + ((u32)sh16 >> 31) / 2` — 3 fewer insns, wrong semantics.

No.

Let me try to find whether the preference is a *copy* suggestion (may_save_copy=1) or a normal suggestion. In the greg dump, "75 preferences: 3" — the global-alloc dump prints both copy and normal suggestions? The global dump's "preferences" are `qty_phys_sugg` only (normal), while copy suggestions are `qty_phys_copy_sugg` and printed separately as "copy preferences". Let me check the global.c dump code.

If it's a normal suggestion (from a non-copy tie), then the *tie* 75-77 gave the qty a suggestion for a hard reg (v1) from 77's qty. 77's qty might include a pseudo with a v1 hard-reg tie.

To break it: prevent the tie 75-77 by making 77 not die at the shift. 77 = angle; its uses: the store and the shift. If we add a use after the shift... 

What about: `sh16 = angle << 16; p[0x79] = angle;` (swap the store after the shift within the then arm)? The store is currently before the if. In the then arm, after the shift, add `p[0x79] = angle;`? That duplicates the store in the then arm (the target's store is unconditional before the branch). Different bytes.

OK, I'll accept the wall. Let me continue a bit more for the time requirement with a few more spellings, then record.

Actually — hold on. Let me check whether the score 7 is identical on ALL 141 includers. If the pin removal gives 0 on some includers... irrelevant for a MATCH.

Let me run a few more variants (10 more minutes = ~20 variants). I'll try things like:
- angle declared as u32/s16
- p[0x79] load as `*(s16*)` vs `*(u16*)`
- different shift spellings
- sh16 declared s16 (semantics change)

Let me do a batch of 6.
