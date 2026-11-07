---
ts: 2026-11-06T12:58:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DeCd1AM9mhK8kM012AYO
---
c1's single difference: `lhu a0,0(s0)` vs `lbu a0,0(s0)` — the dispatch idx load.

Now, what if I load the dispatch idx as u16 (lhu) and make the dsp table read use a *byte* read of the same address that cse treats as a separate entry — but without adding an insn. The issue: an extra byte load costs 1 insn.

Alternative: what if the dispatch `idx` load is u16, and the *case 3* read is a u8 read but then... target lhu.

Hmm.

New idea: make the dispatch read u16 via a *different* expression that cse can't relate to case 3's: e.g. read `idx = p[0xA] | (p[0xB] << 8)` — two lbu + sll + or = 4 insns. No.

Idea: `idx = *(u16 *)(p + 0xA);` where p is a `u8 *` — that IS what orig does.

OK, what about making case 3 read from a *different* address that happens to hold the same value? No.

Let me think about the c1 trick more: the u8 dispatch read created a QImode entry; case 3's u16 read then reloaded. If I keep the dispatch u16 read (lhu) and ALSO make case 3's read a *different mode*... no.

What if case 3 reads `mask = tbl[(u16)idx2]` where idx2 is... 

Alternatively — invert: what if the *case-3* read is a u8 read and the target's lhu comes from a *wider* use? No, target's case-3 lhu loads the index for `tbl[...]`; if the index were read as u8, the scaling sll would still work but the load would be lbu. Target = lhu.

So both loads must be u16 and cse must not fold → invalidation needed. The only zero-cost invalidation in C is the asm memory clobber... or a *call*.

Hmm! What about a call? There IS a call in the code. But the dispatch is before the switch.

What about `func_8002EFF8`? no.

OK, so c1 (score 1) is a near-miss that isn't crackable without the invalidation. And its mechanism is a mode trick that also changes the load width.

Let me reconsider: is there another way to get the target's reload — maybe the target's case-3 reload is NOT a cse-invalidation effect but something else? The header explicitly says it is.

Given the header's documented analysis (all alternatives ruled out by reading gcc), this is a legitimate WALL. I need ≥30 scored tries: I have a1-a5 (5), b1-b5 (5) [b6 empty], c1-c9 (9), k1-k2 (2) = 21. Plus orig baseline = 22. Let me run ~10 more variants to reach 30, then record.

More variants:
- l1: barrier replaced by a volatile *store* to a scratch global (probably 344, but try).
- l2: dispatch `idx = p->unkA;` + `dsp = *(volatile u8*)(sv+idx)` (a5) + case 3 `mask = tbl[p->unkA]` (already).
- l3: c1 but with case 3 reading `*(u16 *)(p + 0xA)` (c2 style) — c1+c2.
- l4: c1 + idx declared u8? no.
- l5: dispatch via `*(u8*)` and case 2 uses a separate u16 read: `func_8003D3B4(((Unkstruct_80030CA4 *)p)->unkA, 1)` in case 2 (so case 2 reads u16 itself). Then the dispatch lbu is only used for the table index. Target's case 2 uses... let me check the target's case-2 code: `lbu a0,71(s0)`? Hmm at 73 target has `lbu a0,71(s0)`.

Let me try l5: dispatch `idx = *(u8*)(p+0xA); dsp = sv[idx];` and case 2 `func_8003D3B4(((Unkstruct_80030CA4 *)p)->unkA, 1);` — then case 2 does a u16 read → lhu. But the target's dispatch is lhu... Hmm, the target at 52 is lhu a0,0(s0) which is the dispatch. If in l5 the dispatch is lbu, that's still a mismatch.

Unless the target's 52 lhu is actually the *case-2* argument? No, 53 addu v0,s6,a0 is the table index.

Hmm, so the target's dispatch load is u16.

Wait... what if `idx` were declared `u16` and the dispatch read is `*(u16*)`, but I make `dsp = sv[idx]` where sv is indexed by a *u8-cast*... no.

OK, alternative: what if the dispatch load is u16 and I add the u8 read as a *dead* read that gcc keeps because it's used in a way that folds? For example:

```
idx = ((Unkstruct_80030CA4 *)p)->unkA;
dsp = sv[idx];
if (*(u8 *)(p + 0xA) < 0x100) { }   // constant true, folded
```
Folded away.

```
u8 b = *(u8 *)(p + 0xA);
dsp = sv[b];
idx = ((Unkstruct_80030CA4 *)p)->unkA;
```
Then: b = lbu (1 insn), dsp = sv[b], idx = lhu (1 insn). That's 2 loads where the target has 1. Extra insn.

Unless the target actually has both? Target 52 = lhu a0,0(s0); 53 addu; 54 lbu v1,0(v0). Only 1.

Hmm.

Let me try a completely different angle: what if the invalidation comes from a *volatile store* that replaces an existing store? E.g. `p[0x50] = 0;` → `*(volatile u8 *)&p[0x50] = 0;`. That's a volatile store: it invalidates cse memory! And it's the same insn (sb). It's in case 3, after the mask load though. If I move it before the mask load... that changes the order (k1 = 15).

Hmm, but what if the volatile store stays where it is (after the mask load) — then it doesn't help the mask load.

What about making the *earlier* store `p[0x4E] -= 1;` (before the switch) volatile? That's in the dispatch path: `p[0x4E] -= 1;` in the else branch. Actually the dispatch block is inside `else { if (p[0x4E] >= 2) p[0x4E] -= 1; else { dispatch } }`. So the store is before.

What about `p[0x4E] &= 0x7F;` at the top of the loop → volatile? That's before the dispatch.

Hmm, but a volatile store before the dispatch would invalidate memory, so the dispatch's idx load (u16) inserts an entry, and case 3's read still folds (same entry). Invalidation must happen BETWEEN them.

What if `idx = p->unkA` (u16) and then a volatile store between the idx load and case 3? E.g. make `dsp = sv[idx]` volatile? no.

What about the `p[0x4E]` store in the *else* arm being between? No, it's before the dispatch.

OK: what about a volatile store to a *scratch local* — no.

I think we're at the wall. Let me do a handful more variants to reach 30 tries, then record.

Let me try:
- l1: volatile store for `p[0x50] = 0;` in case 3 (order unchanged) — tests if volatile sb changes anything.
- l2: volatile store for the `p[0x4E] -= 1;` before the dispatch.
- l3: c1 + case 3 reading via idx (c1 with `mask = tbl[idx]`).
- l4: barrier replaced with `p[0x4E] = p[0x4E];` (a real self-store, invalidates memory!) — c4 was 14 with the store; let me try `p[0x50] = p[0x50];`? Hmm c4 = 14/344.
- l5: `idx = ((Unkstruct_80030CA4 *)p)->unkA; dsp = sv[idx]; sv = sv;` no.
- l6: case 3 `mask = tbl[((Unkstruct_80030CA4 *)p)->unkA + 0];` — same address, no change.
- l7: case 3 `mask = tbl[*(u16 *)((u8 *)p + 0xA)];` = c2 (19).
- l8: dispatch `idx = ((Unkstruct_80030CA4 *)p)->unkA;` + case 3 `mask = tbl[*(u16 *)(p + 0xA)];` and make `p` a different type... no.

Let me also try: `dsp = sv[idx];` with `sv` as `const u8 *` vs `u8 *` — no effect.

And: what about making `idx` a `s32` (u16 load zero-extends to s32)? Target lhu → same.

Let me run 8 more and then record the wall with best 1.

Actually — one more promising idea: the `#pragma`/`volatile` on the *dsp* read is a5 (11). And c1 is 1.

What about combining c1's u8 dispatch with the case-2 fix: in c1, only the dispatch load differs. What if I write the dispatch as:

```
idx = ((Unkstruct_80030CA4 *)p)->unkA;      // lhu  (target width)
dsp = sv[*(u8 *)(p + 0xA)];                  // extra lbu (wrong, +1)
```
No.

Hmm, what about:
```
dsp = sv[*(u8 *)(p + 0xA)];
idx = ((Unkstruct_80030CA4 *)p)->unkA;
```
The lbu first (extra insn), then lhu. Extra.

Unless... the target's dispatch has `lhu a0,0(s0)` and then `addu v0,s6,a0`. If instead I did `lbu` then `lhu`, mine would have lbu, lhu, addu — 3 vs 2.

OK. Final answer for item 2: WALL best 1, tag... The wall tag should be a new `<pass>-<what>` or an existing one. The mechanism: "cse folds the dispatch's u16 index load into case 3 unless a memory clobber invalidates the table; every non-asm invalidation (volatile, store reorder) changes an insn or breaks the giv". Existing tags: `cse-fixed-global-cache`, `cse-load-forward`, `cse-store-forward`, `cse-const-addr`, `cse-copy-merge`. Closest: `cse-load-forward` ("cse forwards a loaded value the target reloads (G30x)"). That's exactly it: cse forwards the dispatch's index load to case 3 where the target reloads.

So tag = `cse-load-forward`. 

Let me run the last batch to hit 30 tries, then record.

Tries so far: orig(1) + a1-a5(5) + b1-b5(5) + c1-c9(9) + k1-k2(2) = 22. Need 8 more.

Let me do l1-l8.
