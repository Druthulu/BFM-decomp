---
ts: 2026-11-06T05:13:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_V536Q11AjvDW00dbToWx
---
Identical to n1. So the u8 change had no effect on the copies (cse still merged? or the u8 got optimized).

Let me look at the RTL to understand. Actually let's think differently: what if I make `raw` used later so it can't be merged? No — target has raw dead after `t = raw`.

Alternative: make the copy chain such that cse can't equate. In the target, raw = t; t = raw. What if the source is:

```c
t = raw - 0x10;
if (t < 0) ...
raw = t;
*(u8*)(s1+0x24) = raw;  // use raw
```
That's the same value as t.

Hmm, actually maybe the real source is different: maybe there is no `t = raw`; instead the stores use `raw`:
```c
raw = t;
*(u8*)(s1+0x24) = *(u8*)(s1+0x25) = *(u8*)(s1+0x26) = raw;
```
Then: raw = t gives move v1,v0; stores read raw (v1). But target's stores read v0 (`sb v0,38(s1)`). So target stores read t (v0), meaning `t = raw` after `raw = t`. So both copies exist.

Hmm, so target's `move v0,v1` then sb v0. Right.

What real-C construct keeps both copies? Since the whole pair is a no-op, plain C normally eliminates them. The launder was the mechanism. We need an equivalent that isn't a "lever". Options from catalog:
1. `do{}while(0)` — no.
2. Dead reset (C0414): `raw = 0;` then use? That would change value.
3. HImode copy escapes cse — tried u8, no.
4. Make the second value have a different mode AND make cse not merge.

Wait — maybe the issue is different: maybe the copies are there but got eliminated because raw is dead. Let me test: make raw live after `t = raw`, e.g. store raw somewhere that doesn't change the code? No extra insns allowed.

Hmm, think about the actual target RTL. The pin `raw` $3 and `t` $2 means: raw is a *hard-reg variable*. In the RTL, the copies between them are real moves. The launder re-sets raw.

Lever-free approach per catalog: "real 2nd set". For example `raw = (s16)t;` where raw is s16? Tried u8 → no.

Maybe the copies were eliminated earlier than cse: combine? Let's check the actual generated asm of n2 vs orig to see where they differ. The diff shows mine lacks both moves and has different regs. So gcc eliminated the copies.

Let's think about cse behavior: after `raw = t`, cse records raw ≡ t (SI mode). Then `t = raw` → t ≡ raw → already, deleted. The stores use t. Fine.

To break the equivalence we need raw to be re-set to something cse can't prove equal. Options:
- `raw = t; if (some_always_true) ...` no.
- Make t a different value: e.g., `raw = t & 0xFF;` where t's range... combine folds.
- `raw = (u8)t;` → subreg set, QImode. cse might still equate? We tried with raw declared u8, which is `raw = t` (implicit truncation). Same.

Hmm. Maybe the HImode trick needs the *source* operand to be HImode too. E.g., in moves line 202: "u16 i; u16 j: the HImode copies of arg0/arg1 escape cse". There both sides are HImode variables, and the copy is between two HImode pseudos (a SUBREG copy). Here raw is u8 and t is s32 — the copy `raw = t` is a QImode subreg set of t; the truncation is a real SUBREG, cse probably handles as a different mode.

Let me actually check the RTL. Use cc1 dumps: tools/cc1_dumps.sh? Let me look at what's available for dumping the candidate TU. The brief mentions tools/cc1_dumps_tu.sh + tools/alloc_table.py (TU dumps), hdump.sh (header pass dumps). Let me check cc1_dumps_tu.sh usage.

Actually maybe faster: let me test a few variants quickly with sc.sh:
- n3: raw as s16, t as s32.
- n4: raw as s32 but `raw = (s16)t;` 
- n5: use a separate u8 temp for the truncation.

Let me think about what generates two moves. Actually maybe the answer: the two moves come from a *different* source structure. Consider that `raw` might not be dead: what if the source is:

```c
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
if (t < 0) { ... return; }
raw = t;
t = raw;
```
The target's move v1,v0 is in the bgez delay slot — it's on the fall-through path (bgez taken → 4fc). Wait: bgez v0,4fc means if t>=0 jump to 4fc. The delay slot 4e8 executes regardless. So `move v1,v0` executes both paths. Then the t<0 path calls and returns. So `raw = t` is executed before the branch, i.e., hoisted/scheduled into the delay slot. That means in the RTL, `raw = t` is in the entry block before the branch? No — reorg fills delay slots from the fall-through/taken? Reorg fills from the fall-through path (the insn after the branch in layout). The insn at 4e8 is the delay slot of bgez at 4e4. The next insn in layout after the delay slot is 4ec (jal). So the delay slot was filled from... hmm, actually the branch is `bgez v0,4fc` — taken target 4fc (the fall-through-ish continuation). The insn at 4e8 (delay) = move v1,v0. The instruction after the branch block is at 4ec (jal). So reorg took move v1,v0 from somewhere (the target block at 4fc, i.e., the taken path!) and put it in the delay slot. Because it's safe: on the not-taken path (t<0) raw is dead after.

OK so source: after the if, `raw = t; t = raw;` then stores.

Hmm what if the source is:
```c
if (t >= 0) {
    raw = t;
    t = raw;
    stores...
}
```
Same.

Let me look at this from a different angle: what does gcc 2.7.2 do with a *volatile*? Not allowed (lever).

What about making raw a `s32` but assigning through a pointer? Not allowed / changes code.

Hmm, "real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, `&&`/`||` folds, pointer reuse)". So widths are explicitly listed. Let me try s16 raw.

Actually wait — maybe the issue is the *order*: `raw = t; t = raw;` — cse processes in order. If instead we write `t = raw;` first... no, semantics.

Let me try to see the RTL. Let me check cc1_dumps_tu.sh.
