---
ts: 2026-11-06T05:15:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Y5KmM4JKsSPhXDdVqWae
---
So cse folded t = zero_extend(raw) into t (they were equal), and the QI copy became insn 43 which writes to a temp 79 which is then stored — no, insn 43 sets reg79 = subreg(t). It's a QI pseudo 79 which local-alloc will assign... The final asm shows `sb v0,38(s1)` etc. so 79 got coalesced with t (76) — no move.

In the target, the QI store value is in v0 (t's reg) too, and the extra move is `move v1,v0` from raw=t (raw in v1) and `move v0,v1` from t=raw.

So the crux is that in target, raw and t are *hard registers* (pinned), so they can't be coalesced. Lever-free, gcc coalesces.

Hmm. So how can plain C prevent coalescing? The moves must be non-coalescible. E.g., if raw is used across a call? Or if raw's live range overlaps in a way that forces a separate reg... but raw is dead.

Wait, in target: raw(v1) is set by lbu, read by addiu, set by move v1,v0 (dead after). t(v0) set by addiu, read by bgez and sb's and move.

What if we make `raw` live across the first call? No, the first call is a return path.

Hmm, what about making the code shape different so that the copy is needed? Let me reconsider: maybe the real source has raw as a `u8` *local variable whose address is taken*? No.

Alternatively: maybe use a pointer-based reuse: `p` holds the pointer, and raw is read via p? No.

Let me reconsider the problem: the target has `move v1,v0` in the delay slot and `move v0,v1` after. This is the classic "pinned hard regs" artifact. Can plain C reproduce it? The moves catalog has many MATCH entries where pins were replaced. E.g., line 147: "the copy through an s16 temp escapes cse2's equivalence class, so v1 keeps its own register instead of being merged with v0". That's exactly our situation! func_8017E204: "the copy through an s16 temp escapes cse2's equivalence class, so v1 keeps its own register instead of being merged with v0 (G06)".

So the move: `s16 tmp = <val>; <var> = tmp;` where the copy through an s16 temp escapes cse2. Let me look at that example body if available. Search the shard dirs for func_8017E204.

But here we need the reverse: raw (v1) = t (v0) and t = raw. Hmm, two copies.

Wait — maybe I'm misreading which values are raw/t. Let's map target registers:
- v1: lbu raw, addiu uses v1, move v1,v0 sets v1.
- v0: addiu dest, bgez tests v0, move v0,v1, sb v0.

Yes.

So what plain C produces "move v1,v0" (copy to a *dead* variable) followed by "move v0,v1"? Only if raw is a real variable that gcc keeps. But it's dead after the copy... unless the copy `t = raw` is the *use* of raw.

Actually, here's a thought: if raw and t are *different modes* such that the copy t=raw requires a conversion instruction, e.g., `t = (s16)raw` when raw is u8 → zero_extend which combine turns into a move. But cse merged them because it knew equality.

What if we prevent cse from knowing equality by making the value flow through a *memory* or a function? Not allowed extra insns.

Hmm, but what if we make raw a *separate variable that is not equal to t* but the moves still appear? For instance:

```c
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
if (t < 0) { ...; return; }
raw = t;      // move v1,v0 (raw gets t)
t = raw;      // move v0,v1
```

The second move is `t = raw` — if cse eliminated it, t keeps v0 and raw keeps v1, and the stores use t (v0). That's exactly the target except the two moves. Wait! In the target, after `raw = t` (move v1,v0), the stores use t (v0). If cse removes `t = raw`, then we'd have only the first move and stores from v0. That would be 1 insn short (46) — and indeed mine is 46. Hmm, so which move is missing in mine? Mine has neither (raw and t coalesced).

So what we need: keep `raw = t` as a real move while cse merges t=raw. If cse equates them, it also removes raw=t.

What if we swap: 
```c
t = raw - 0x10;
...
raw = t;
```
and stores use `raw`? Then only one copy... no, target has two.

OK here's another thought: what if the target source was:
```c
raw = s1->unk24;
t = raw - 0x10;
if (t < 0) { ... return; }
raw = t;
t = (u8)raw;   // or something
```
We already tried.

Let's look at what the pinned version produces in the *first* cse pass to understand why the moves survive there. Actually with pins, the moves are between hard regs; cse's reg_eqv is per-register and hard regs are not equivalent. So no elimination.

Lever-free alternative that keeps a variable in a specific reg? That's a pin — not allowed.

Hmm, but moves.md has many MATCHes replacing pins with real C. Let's search for a case where the pin forced a *copy between two variables*. E.g., func_8017E204 "the copy through an s16 temp escapes cse2's equivalence class, so v1 keeps its own register instead of being merged with v0".

Let me find that item dir and read its win.c to understand the pattern.
