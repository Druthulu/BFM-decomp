---
ts: 2026-11-06T10:11:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nnnEKOTDE8FFUfwpKgKt
---
With the keepalive (orig body):
- r77 (i1): pri 22500 (refs9 live12), conflicts v0,v1,sp
- r234 (giv): pri 14000 (refs7 live10), conflicts v0,v1,sp
- r177 (limit): pri 1363, conflicts v0,v1,sp
- f (r75) — it's pinned to $3, so it's not in the global order (pinned hard reg).

The order: 80 114 232 77 230 79 234 236 ... So i1 (r77) has higher priority than giv (r234), and i1 conflicts with v0,v1 now (because the keepalive extends its live range across v1?).

Since f is pinned to v1, v1 is taken by f. Then r77 (i1) takes a0, r234 (giv) takes a1.

So with the pin, f=v1 (forced), and the other allocations follow.

In the lever-free mine: f is not pinned, pri 5000, order 234 before 77 before 75. 234 (giv) takes v1, 77 (i1) a0, 75 (f) a1.

Target: f=v1, i1=a0, giv=a1 — same as the pinned version.

So to crack lever-free, I need f to have priority > giv (and > i1?) so that f takes v1. Note in the keepalive version, r77's pri rose to 22500 and it CONFLICTS with v0,v1 (because its live range spans the loop). 

Hmm, so how do we raise f's priority above 234's (14000) and 77's (22500)?

f's priority in mine: 5000 (refs4 live16). To beat 234 (15555 in mine), f needs pri > 15555. pri = floor_log2(refs)*refs/live*10000. With refs=4: floor_log2(4)=2, 2*4=8, /live*10000 = 80000/live. live=16 → 5000. To get >15555 with refs=4, live must be < 5.14 → live ≤5. But f's live range spans the loop... Hmm.

With refs=6: floor_log2(6)=2, 2*6=12, live 16 → 7500. refs=8: 3*8=24, live16 → 15000. refs=9: 3*9=27 → 16875 (beats 15555). So if f has ≥9 refs with live 16, it would beat the giv.

But f only has 4 refs (set 0, set 1, read at !=1, maybe the keepalive...). In the original, f was pinned so no priority needed.

Alternatively, reduce the giv's priority. In mine the giv is 15555 (refs7 live9). If the giv's live length increased or refs decreased... 

Hmm. But note: the keepalive version has the giv at 14000 (refs7 live10) and i1 at 22500. The keepalive *increased i1's refs* (9 vs 7) and live (12 vs 11), and the giv's live (10 vs 9).

Wait — in the target (pinned f), f=v1, i1=a0, giv=a1. In the lever-free body, if we could make f take v1, the rest follows: i1 a0, giv a1. We need f's priority > giv's.

But f's live length is 16 and refs 4. To raise pri: add refs to f.

Real-C way to add refs to f without adding instructions? The read at `f != 1` is one ref. The sets are refs. 

Hmm, what if f is read inside the loop (e.g., `if (f == 0 && cond) f = 1;`)? That adds a compare instruction — but maybe the compare can be folded? `if (f == 0 && cond)` → needs a branch on f, extra code.

What if we write `f |= cond` (v2)? That gave 220 ins (2 fewer) — different code.

What if we restructure f's live range: make it shorter. live=16. If f were only live inside the case-1 block (16 insns), hmm.

Actually — the allocno live_length counts instructions where f is live. f is live from its first set (insn 301) to its last use (after the loop). That's ~16 insns.

If we could make f's live range shorter by moving the `f != 1` read closer... it's right after the loop.

Alternatively, make the *giv's* priority lower: its live length is 9; if we extend it (e.g., use the giv later), pri drops. But that changes code.

Hmm, what about making f's refs 5-8 with the same live? pri for refs=5: floor_log2(5)=2, 2*5=10, /16*10000=6250. refs=6: 7500. refs=7: 2*7=14→8750. refs=8: 15000. So need refs≥9.

Alternatively reduce live to 8 with refs 4: 2*4/8*10000=10000 — still < 15555. live=5: 16000 > 15555. But f's live spans the loop.

Hmm, what about the giv: if its live length grows to 12 (refs 7): 2*7/12*10000 = 11666 < f's 5000? No, still > 5000.

OK, what if we make f's live length smaller? f is set to 0 before the loop and read after; its live range covers the whole loop. What if f is set inside the loop only? E.g., restructure:

```
for (i1 = 0; i1 < 5; i1++) {
    if (cond) { f = 1; }
}
```
f=0 before the loop. What if we instead compute a different way: `s32 f = 0;` at declaration? No.

Alternatively, note that the target's f is v1 — which is what the PIN forces. Without the pin, the natural allocation gives f a1. The decomp author marked the pin "NEEDED DIFFERS", implying they tried and failed. So this is likely a real wall (greg-pri / lreg-v0-local-first style).

BUT: the brief's shard is specifically about *cracking* these. Let me try harder with a few targeted moves:

1. Add a reference to f inside the loop that generates no code: e.g., make the condition use f: `if (f == 0) { if (cond) f = 1; }` — adds a compare+branch. No.

2. Change f's type to `u8`/`s16`: HImode copies. The HImode set `f = 1` might be a different insn (movhi), changing refs/live and maybe allocation. Let's try `s16 f;` and `u8 f;`.

3. Use a different variable for the loop result: e.g., `s32 f;` but set it via `f = cond ? 1 : f;`.

4. Split f into two variables.

5. Move the `f = 0;` initialization into the declaration at function top? That would add an insn at top and shorten f's live range? No — f would be live from the top.

6. Make the loop counter i1 `s16` — changes the loop code.

7. Reduce the giv's priority by adding a use of the giv after the loop? That would be dead.

8. Use the array base as a local pointer: `s32 *t = D_801AECD8;` then `t[i1]`. loop.c would still make a giv but from t.

Let me try a batch: f as s16/u8, t pointer, etc.

Actually, wait. Let me reconsider: maybe we don't need f to beat the giv. The target allocation order might be achieved differently: if the giv conflicts with v1 (like i1 does in the keepalive version), it would skip v1 and take a0; then i1 takes... hmm.

In the keepalive version, r77 (i1) conflicts v0,v1,sp. Why? Because the asm use of i1 extends its live range into the block where v1 is used by f (pinned). Actually the conflict is computed from live ranges: i1 is live at insns where v1 is live? v1 is f's register (pinned). f is live across the loop, so i1 (live across the loop) conflicts with v1. Yes!

So: if f were in a register that i1 conflicts with... but f's assignment is what we're solving.

Hmm, in the lever-free mine: 234 (giv) conflicts v0,sp (not v1). 77 (i1) conflicts v0,sp (not v1). 75 (f) conflicts v0,sp.

Why doesn't i1 conflict with v1 in mine? Because no pseudo is pinned to v1; conflicts are between pseudos, and v1 is a hard reg conflict only if a pseudo is live where a hard-reg value is needed. Hmm, actually "conflicts v0,sp" means the allocno conflicts with hard regs v0 and sp (due to fixed uses like calls/return). v1 isn't in the conflict set, so any of them could take v1.

So the first allocated among {234,77,75} takes v1 (lowest free). In mine, 234 (giv, 15555) is first → v1.

To get f into v1, f must be allocated first among them: pri(f) > 15555.

Alternatively, make 234 and 77 conflict with v1 so they skip it. They conflict with v1 only if some hard-reg v1 value is live across them. Hmm — v1 is used by local-alloc'd temps (slt results). If a local temp in v1 is live at a point where the giv is live, the giv conflicts with v1.

That's what happened with i1 in the keepalive version (i1 conflicts v0,v1). Because the asm use of i1 extended its live range to cover a point where v1 is live (the slt temp? or f's v1?).

Hmm, so maybe I can extend f's live range to cover a v1 local temp, making f conflict with v1... no wait, we WANT f to be in v1.

We want the giv and i1 to conflict with v1 so they skip it, leaving v1 for f. 

In the keepalive version: i1 conflicts v0,v1; giv conflicts v0,v1; f is pinned v1. Order: i1 (22500) first: conflicts v0,v1 → takes a0. giv (14000): conflicts v0,v1 → takes a1. f: pinned v1.

In the lever-free mine: giv doesn't conflict with v1, so it takes v1.

So if I can make the giv and i1 conflict with v1 *without* the pin/keepalive, f would get v1. How? Make some v1-hard-reg value live across the loop. What hard-reg value is in v1 during the loop? Local temps assigned to v1 by local-alloc. If a local temp in v1 is live across the giv's live range...

Hmm, this is getting deep. Let me try the empirical batch:
- f as s16, u8
- t pointer local for the array
- different loop spellings

Let me also try: what if `f` is declared `s32 f = 0;` and the `f = 0;` statement removed? Then f is live from the top (function start) — its live length grows a lot (pri drops) but it might conflict with v1 elsewhere, forcing it out of v1? Hmm.

Actually, let me think about the local temp in v1: in the loop, `slt v0,a0,5` uses v0, not v1. The `lhu` result (r176) is local-alloc'd to v0. The `lw` result (r174) to v0.

What uses v1 in this function? The pin forces f to v1. Without the pin, nothing is in v1 in the loop.

OK let me just try variants empirically. Let me generate a second batch.

Variants:
- f as s16: `s16 f;` — set f=1 (HImode).
- f as u8.
- t = D_801AECD8 local pointer.
- `for (i1 = 0; i1 != 5; i1++)`.
- `while (i1 < 5)`.
- declare i1/f order swapped.
- f = 0 moved after the limit/pointer setup? no, it's before the loop.
- Reorder the `f = 0;` statement to after the for-init? Can't.
- `for (i1 = 0, f = 0; i1 < 5; i1++)` — moves f=0 into the for-init (same position roughly).
- `f = 0;` then `i1 = 0; while (i1 < 5) {...; i1++;}`.

Let me also try adding a real use of f that generates no code... 

Hmm, what about `f = f | (cond);`? v2 gave 220 ins. What exactly changed? Let me look at v2's diff. It might be 2 fewer because the branch was replaced by sltu+or. Score 22.

What about `f = (cond) ? 1 : f;`? Might generate a branch + move, same as if.

Let me try `f = f + (cond)` — changes semantics (f counts), but for experimentation.

Actually, hold on — semantic equivalence matters only for the final winner. Let me generate many and inspect.

Let me write batch 2.
