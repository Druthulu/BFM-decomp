---
ts: 2026-11-06T10:24:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MaSKtj0Gw6qLnPxZfGWs
---
i1: the residual is that iVar4/q is in a3 (mine) vs v1 (target), and cur is in v1 (mine) vs a0 (target). So the caller-saved regs shifted by one.

The target's caller-saved allocation: cur=a0, iVar4=v1, q=v1.
Mine: cur=v1, iVar4=a3, q=a3.

Hmm, a3 is the 5th caller-saved (v0,v1,a0,a1,a2,a3). Why would a3 be used? Because v0, v1, a0, a1, a2 are occupied at the qty's birth.

In the target, iVar4/q is in v1 — the 2nd caller-saved. So in the target, v0 is busy but v1 is free.

Hmm, the difference: in mine, cur is in v1, so iVar4 can't use v1 → a3. In the target, cur is in a0, freeing v1 for iVar4.

So the key is cur's allocation: target cur=a0, mine cur=v1.

Why does cur get a0 in the target? `cur = ang & 0xFFF` — ang is in v0. cur is a new qty. local-alloc assigns by priority. cur's birth is after ang. At that point, v0 is busy (ang), v1 maybe busy (the sign-ext temp?), so cur gets a0.

In mine (i1), the sign-ext is in-place (no temp), so v1 is free → cur gets v1.

In the target, there must be a temp occupying v1 at cur's birth! So the target's sign-extension DID use a temp v1?! But the target's sll/sra are in-place (s0). Hmm.

Wait, let me look at the target's full asm again:
```
3a18: addiu v0,v0,-1024    # ang - 0x400
3a1c: sll s0,s0,0x10       # div sign-ext
3a20: andi s1,s1,0xfff     # a mask
3a24: andi a0,v0,0xfff     # cur
3a28: bne s1,a0
3a2c: sra s0,s0,0x10
```
So cur is in a0. v1 is NOT used here. But later `subu v1,a0,s1` (iVar4 in v1). So v1 is free at cur's birth, yet cur got a0. That means v1 was occupied by something else at cur's birth (a qty that dies before iVar4?).

Hmm, or local-alloc's allocation order gave cur a0 because a0 was preferred/first available. The reg order is v0, v1, a0, ... If v1 were free, cur would get v1. So v1 must be busy.

What occupies v1 at cur's birth in the target? Maybe the `a` mask temp or the div sign-ext temp. In the target, the div sign-ext is in-place (s0), so no temp. Hmm.

Unless there's a temp for `ang - 0x400`? ang = ratan2(...) - 0x400 → `addiu v0,v0,-1024` in-place (v0).

Hmm. What about the `a = a & 0xFFF` → `andi s1,s1,0xfff` in-place.

So no v1 occupant. Yet cur got a0.

Wait — maybe the allocation order isn't simply "first free". local-alloc processes qtys by priority, and a qty's live range determines which regs are free. cur's live range: from `andi a0,v0,0xfff` to the `bne`. If v1 is live at that point (some other qty), cur can't use it.

In the target, is v1 live at cur's birth? Let me look at the target's full asm before the div. From the objdump:
```
39e4: addiu sp,-32
39e8: sw s1,20(sp)
39ec: move s1,a2
39f0: sw s0,16(sp)
39f4: move s0,a3
39f8: sw ra,24(sp)
39fc: lh a2,10(a0)
3a00: lh v0,10(a1)
3a04: lh v1,2(a1)
3a08: lh a1,2(a0)
3a0c: subu a0,a2,v0
3a10: jal ratan2
3a14: subu a1,v1,a1
3a18: addiu v0,v0,-1024
3a1c: sll s0,s0,0x10
3a20: andi s1,s1,0xfff
3a24: andi a0,v0,0xfff
```
At 3a24, v1 was last used at 3a14 (delay slot). So v1 is free. Yet cur got a0.

Hmm, so local-alloc didn't pick v1 for cur. Why? Maybe because cur's qty has a *preference* for a0 (copy preference from ang=v0? no).

Or maybe the allocation order: cur is a global qty (used across blocks? no, cur is used only in block 0: `if (a == cur)` and `diff = cur - a` — the latter is in the else block! So cur IS used in a later block → GLOBAL. So cur is allocated by global-alloc, not local-alloc.

Ah, cur is global (used in `diff = cur - a` in the else block). So its allocation is by global-alloc priority. cur's refs/live determine it.

In mine, cur is in v1; target a0. Hmm.

OK, this is a global-alloc caller-saved allocation difference. Hard to control precisely.

Given the time (03:36), I've spent ~35 min on item 3 and I'm at score 2. Let me make a decision: continue a bit more or wall it.

Actually, the score-2 body (f2/h1) is very close. Let me try a few more variations to fix the sign-ext temp. 

Idea: what if the sign-extension is written as a `(s16)` cast of a *different* expression that produces in-place? E.g., `div = (s16)(div + 0);`? adds.

Idea: `div = (s32)(s16)div;` same.

Idea: What if div is `s32` but declared `volatile`? no.

Idea: use a union? no.

Hmm, what about the C spelling `div = div << 16 >> 16;` (f4) — that gave the temp too (score 2). And `div = div << 16; div = div >> 16;` gives in-place but shifts caller-saved.

What if I use the two-statement form but keep a temp alive to occupy v1, restoring cur→a0? E.g., add a dummy... no, that's a lever.

Alternatively, in the two-statement form, move `cur = ang & 0xFFF;` to before the shifts, so cur's birth is earlier and its allocation changes. Let me test: i1 with cur before the div shifts.

Also test: i1 with `a = a & 0xFFF;` before the shifts.

Let me batch a few.
