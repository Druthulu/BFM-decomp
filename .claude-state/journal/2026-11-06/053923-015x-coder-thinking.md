---
ts: 2026-11-06T12:39:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JvzVwb4MVCZMMrXOHtJm
---
Barrier 1 can be removed for free (b1 scores 0). Good. So the win.c only needs barriers 2, 3, 4 cracked.

b2 = barrier 2 removal: score 28.
b3 = barrier 3 removal: score 10, and count drops to 407 (one insn lost).
b4 = barrier 4 removal: score 2 (ORDER), just `lui a2,0xff00` moved.

Let's start with b4, the easiest (score 2, ORDER). The issue: `ott = (u32 *)(idx*4 + (s32)ot); barrier; mFF = 0xFF000000;` then `*(u32*)prim = (*prim & mFF) | (*ott & m24);`.

Without barrier, the order of `li mFF` and the `ott` computation flips. Since mFF is pinned to $6 (a2), the set of the pinned hard reg is placed first in its block. Hmm.

Target: `lui a2,0xff00` at 378, mine at 375. So mine computes mFF earlier. Need to move mFF's birth after ott's computation. Since the pin's SET is placed first in its block by sched1 ("a pinned hard-reg SET is placed FIRST in its block")... Hmm, that means the pinned set always comes first. So with the barrier, the block starts after the barrier; without, everything is one block and the pin set goes first.

Wait but b4 (barrier removed) has mFF at 375 and ott at 378? Target has mFF at 378 (later). So target's mFF is *after* ott. With the barrier (orig), score 0. Removing the barrier moves mFF *earlier* (375 < 378). Hmm, the barrier keeps mFF after ott.

So: need real C that makes mFF's birth depend on / come after ott. Options:
- Compute `mFF` as part of the expression? But it's a pinned var.
- Maybe the whole point: `ott = ...; mFF = 0xFF000000;` order in source. Without the barrier sched1 hoists the pinned set. Actually pinned hard-reg set first in block — but here the barrier splits the block so mFF's block starts at the barrier. Without barrier, mFF's set is in the same block as ott's computation and gets placed first.

To fix in real C: put ott's computation in a way that mFF depends on it? No, mFF is a constant.

Alternative: put the ott computation inside a `do { ... } while (0)` — that creates a barrier-ish? No, do-while(0) is an EBB split in cse1 per C0535. Hmm, but that's still a "lever"? do{}while(0) is allowed with `// !FAKE: do-while` comment. But does a do-while split sched1 blocks? It splits cse1 EBBs. Hmm.

Wait — actually the mechanism: the target has mFF load AFTER ott. If I write the store as two statements:

```
*(u32 *)prim = (*(u32 *)prim & mFF) | (*ott & m24);
```
with mFF used there... cse would keep the li. Hmm.

Alternative approach: reorder the source so that ott's computation happens and then mFF. It already is: `ott = ...; mFF = 0xFFFFFF;` wait no. Original order is:

```
m24 = 0xFFFFFF;
ott = (u32 *)(idx * 4 + (s32)ot);
barrier
mFF = 0xFF000000;
*(u32 *)prim = (*(u32 *)prim & mFF) | (*ott & m24);
*ott = (*ott & mFF) | ((u32)prim & m24);
```

Interesting: m24 = 0xFFFFFF (li a0? no, pin $5 = a1). Hmm wait $5 = a1, $6 = a2. So m24 in a1, mFF in a2.

Target order: `lui a2,0xff00` at 378. Mine (no barrier) at 375. What's at 375-378? Let me look at the actual diff with more context. Let me use --keep to get the object and dump. Or use dt.sh with more tail lines.

Actually, easier: since score 2 ORDER, I just need one more real-C move. Ideas:
1. Move `mFF = 0xFF000000;` assignment to be textually after a use of ott: e.g.
```
ott = ...;
*(u32 *)prim = (*(u32 *)prim & mFF) | (*ott & m24);
```
Hmm, mFF must be set before use.

2. Make ott's computation depend on... 

3. Change `m24`/`mFF` ordering: maybe set m24 after ott too?

Let me look at the target vs mine disassembly around there. Let me use --keep and objdump. Actually dt.sh prints the diff tail; let me see the full diff for b4.

Let me run dt.sh with tail 60.
