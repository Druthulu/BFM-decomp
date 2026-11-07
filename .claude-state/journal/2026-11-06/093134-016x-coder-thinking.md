---
ts: 2026-11-06T16:31:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nm7C7Uo5Phv8UFQXOfOf
---
Excellent! w1_r16 gives:
```
16  move v1,v0       (matches target 16)
17  andi v0,v1,0xffff  <- extra
18  beqz v0,388       <- instead of beqz v1
```
So the move v1,v0 IS there, and ret is in v1, m in v0 (andi v0,v1,...). But the HImode `ret == 0` test inserts `andi v0,v1,0xffff` (zero-extend) then beqz v0. The target does `beqz v1`.

So if I can make the zero-test on HImode use beqz directly, we'd have score 0 except that the andi zero-extend is what kills it. Why does gcc zero-extend? Because it's comparing an HImode value to 0 and the upper bits are unknown; it uses `andi 0xffff` then `beqz`.

Can we avoid the extension? If the compare were on the SImode value... but the test must be on v1 (ret). Hmm.

Alternative: make ret's test use a construct where gcc knows the upper bits. E.g., if ret is `u16` and the value was loaded/created such that gcc knows it's zero-extended. `ret = (u16)t` — gcc doesn't know.

What if the comparison is `if ((u16)ret == 0)`? Same.

What if ret is `s16` and the test `ret == 0`? Sign-extend needed → `sll; sra`. Worse (w1_s16 was 106).

What if we make ret a `s32` but the copy HImode? Like `s32 ret; s16 tmp; tmp = (s16)t; ret = tmp;` — then ret is SImode extended from tmp: `sll/sra` pair. Not a plain move.

Hmm. What if the test is `if ((s32)ret == 0)` where ret is u16 — cast to s32 requires zero-extension, same.

OK, different angle: keep ret s32 (so the test is a plain beqz), but make the copy survive via a different mechanism. The copy v1←v0 for an SImode value. To keep it, the source must be live or the insn untieable.

What if the call result is used twice: once for ret and once for the andi, but the andi's operand is ret? Hmm.

What if we write:
```c
s32 t;
s32 ret;
t = func(...);
ret = t;
if (ret == 0) ...
```
t is dead after ret=t → tied. Unless we use t later in a way that flow keeps. Could use t in the m computation: `m = ret & 0x8000` — no.

Hmm, what if the andi's operand is t and the result m, and ret is the test? Then andi reads t (v0) → `andi v0,v0,0x8000`, not target.

What if the target's andi reading v1 comes from m = ret & 0x8000 and ret being v1, where ret is the copy. So we need the copy to survive.

Idea: use `t` in the else arm's call? The else arm calls func_80146E90((s32*)a0, 0x20) — no use of ret.

Idea: make the copy a `plus` — impossible without a hard-reg addend.

Idea: make the copy untieable by having different modes (SImode→DImode? no).

Hmm, what about the HImode copy but with the test on a SImode value? Suppose:

```c
s32 t;
s32 ret;
u16 h;
t = func(...);
h = (u16)t;      // HImode copy → move v1,v0
ret = h;         // hmm, extend
```
No.

What about: the target test `beqz v1` — if ret were HImode and the test used `if (ret == 0)` gcc adds the andi. But what if the test is `if ((s32)(u16)ret == 0)`? Same.

What if the test compares ret against a *variable* zero? e.g. `if (ret == (u16)0)`? Hmm.

Alternatively, what if the andi zero-extend gets *combined* into something? The `andi v0,v1,0xffff` followed by `beqz v0` — could combine/cse eliminate the andi if the branch used `beqz v1`? No, semantics differ if upper bits nonzero.

Wait — actually, maybe the HImode test with `andi 0xffff` is only because of unsigned HImode. If ret is a *pointer*? no.

Let me think about the actual game source. This function is from md_MAIN_041. The original C probably had `s32 ret` and the pins were "NEEDED DIFFERS (P36 rung B t8_tus2)". So the original compiler naturally produced move v1,v0 for this source. Which means there IS a natural C spelling. Since the current banked src uses pins, maybe the original decomp never found it.

Hmm, but these W47x shards are the "singleton crack" shards — trying to crack the last pins with plain C. Some will be walls.

Let me think about the allocator more. Maybe the move v1,v0 arises not from a copy but from the *argument setup* of the next call? No, it's right after the call.

Let me look at gcc 2.7.2's expr.c for how a call's return value is assigned to a variable. If the target is a variable (not a temp), expand_call might do `emit_move_insn (target, hard_return_reg)`. And if the target is a hard register (pinned), it's a move v1,v0 that stays.

For a pseudo target, local-alloc ties it (move deleted). So how could the original source produce a move?

Unless the call is NOT assigned directly to a variable. E.g.:

```c
if (func_801638A0(...) == 0) ...
```
then the call result is a temp used once. Hmm.

What if the call's result is passed to something? no.

What if the source uses a *different* type: the function returns `s32`, assigned to `u32 ret`? Same.

What about `ret = (s32)func(...)` — cast, no.

Hmm, hold on: maybe the target's `move v1,v0` comes from the *and's* operand copy: gcc might first move the call result to v1 and then... no.

Let me look at the cc1 dump of the pinned build vs the natural build. That will show exactly where the move comes from. Let me use tools/cc1_dumps_tu.sh.

Let me check its usage.
