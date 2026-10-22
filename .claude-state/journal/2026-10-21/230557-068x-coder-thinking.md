---
ts: 2026-10-22T05:05:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_FiS6VbkLMrmjd4K3sAEc
---
In the PINNED version:
- r103 (hard v0, pri 10000) — a local allocno with hard v0.
- r107 (v0), r118 (v1), r125 (v1), r128 (v0) — the temps.
- r102 (v1), r112 (v1), r116 (a0), r123 (v0) — other temps.

In the LEVER-FREE (vV2_direct):
- r102 (v0), r106 (v0), r111 (v0), r117 (v0), r124 (v1), r127 (v0), r101 (v1), r109 (v1), r115 (v1), r122 (v0).

So in the pinned version, the temps are spread over v0, v1, a0 (not all v0/v1) — because v0 is taken by the pinned pseudo (and the pinned pseudo's chain).

Hmm, this is a complex allocation. The key difference in the tail:
- pinned: `lh a0,6(s0)`, `lh v1,160(s0)` → the temps in a0/v1.
- lever-free: `lh v1,6(s0)`, `lh v0,160(s0)` → v1/v0.

So the pinned version's temps start one reg higher. That's because v0 is reserved for the pinned `r`.

So again: the same wall mechanism — reserving $2.

Hmm, BUT: here the value `r` in the target is in v0 and the temps in a0/v1. In the lever-free nopin, `r` is in a0 and the temps in v1/v0.

Hmm, so in the lever-free version, the temps take v0/v1 (the two lowest) and the value takes a0.

Interesting: in the nopin version, the local `r` is a global allocno? Let me check: the nopin .greg order would include r (`r` is the local). Let me dump nopin and read the table — I need the local `r`'s pri/refs/live and whether it's global.

Actually, let me think about what would make the value pseudo take v0 in the LOCAL allocation: it must be a local allocno with pri > the temps' (10000).

The temps: pri 10000 (refs 2, live 2) and 6666 (refs 2, live 3).

The value pseudo `r`: in nopin, `r = 1; if (...) r = X; return r;` → the local `r` has refs 3 (2 defs + 1 use) and live ~? If it's live from the `li 1` to the return → maybe 10+ insns → pri = 3*10000/live = 3000 → low ✗.

To make `r` win: shorten its live range and/or add refs.

Hmm! What if `r` is assigned the boolean FIRST and the 1 later? E.g.:

```
if (cond) { r = X; } else { r = 1; }
return r;
```
(vV3_else) → the local r's live range is short (just the branch) → pri = refs 3?/live 3 → hmm. vV3_else scored 9 (same as vV2_direct).

Hmm, but vV3_else has a different structure than the target: the target has `li v0,1` in the delay slot of the first bne → the "1" is materialized BEFORE the second comparison, i.e. the `r = 1` default comes first. So the target's structure is `r = 1; if (a==b && c==d) r = X; return r;` (the nopin form).

Hmm, but in nopin the `li a0,1` is in the delay slot ✓ (the same position as the target's `li v0,1`) ✓✓. So nopin's structure matches; only the registers differ.

So for nopin: the local `r` must get v0 and the temps a0/v1.

The local `r` in nopin: `li a0,1` → so `r` is in a0 in nopin. And the temps in v1/v0.

To flip: the local `r` must have a higher priority than the temps AND be a local allocno (or the temps must be pushed).

Hmm, since the temps are LOCAL allocnos (hard regs assigned in local allocation), the local `r` must ALSO be local and beat them.

Why isn't `r` local? Probably it conflicts with a hard reg (e.g. the value is used by a call? no) or crosses a call (no, it's at the end).

Hmm, in gcc 2.x, the local/global split: a pseudo is local if it doesn't conflict with any hard register. "Conflict with a hard reg" means: the pseudo's live range overlaps a hard reg's live range where the pseudo is not the value... Hmm.

Actually in gcc 2.x's global.c, `find_local_pseudos`:
```
/* Return true if we should not allocate this pseudo in a hard register... */
      /* If the pseudo is live across a call, it can't be in a hard reg (clobbered) */
      ...
      /* Don't allocate pseudos that conflict with hard regs in the global allocation */
```
The rule (from the gcc 2.7 source, `global.c`):
```
	  /* Now that we have the hard reg conflicts, we can determine which
	     pseudos are local.  */
```
A pseudo becomes global if it conflicts with a hard reg: e.g. a pseudo whose value is used in a call's argument, or which is live across a call, or which conflicts with a fixed hard reg.

In nopin, the local `r` — is it in the .greg order? The order line for vV2_direct was "73 103 77 74 75" (5 global allocnos, no `r` since vV2_direct has no local r).

Let me dump nopin and see. That's the key data: is `r` global or local, and its pri/refs/live.

Let me do it.
