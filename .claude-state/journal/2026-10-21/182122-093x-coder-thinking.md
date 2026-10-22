---
ts: 2026-10-22T00:21:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_CJZh0J6qW6sgC4o8cdEG
---
p1 is identical to c1 (the store still uses s8 presumably, and the mask is still computed into s8).

So gcc still merged. Hmm, so cse propagated t into v's use (the store) — the store uses s8 ✓ (that's what I wanted) but the mask is still computed into s8 (the merge went the other way: v's use was replaced by t, and then the def merged into t).

Hmm. So the merge is in the DEF direction: the masked value's temp → t.

⇒ In gcc, `t = v` merges the two pseudos entirely.

So the copy CANNOT survive in gcc 2.7.2 when the source is dead... unless the source is live at a point where it must be in a different register class.

Hmm! What if `v` is live ACROSS A CALL? Then v must be in a callee-saved reg, and t (also callee-saved) — hmm, both would be callee-saved but different regs → the copy survives ✓✓!

So: if `v` is used after a call, the copy survives!

In our function: the calls happen in the loop. The value v is not used there. Hmm.

Hmm! But wait: what about `t`? `t` is live across the calls (used in the loop) ✓ and v is dead.

Hmm, so we need v to be live across a call. Semantically impossible without changing the behavior.

Hmm. Hmm! Unless the copy's SOURCE is a value that's live across a call for other reasons...

Hmm, hold on! What if the source of the copy is the result of a CALL? Then the copy is forced (v0 → s8) ✓. Our expression isn't a call...

BUT!!! What about this: what if the masked value is computed and then the copy is made, and the SOURCE is `v` which is ALSO used in the loop? Hmm.

Hmm, let me look at the problem from the target's perspective once more: the target has `move s8,v0` — v0 is a caller-saved reg. In gcc, when a value is copied from a caller-saved reg into a callee-saved one, that's the "call result → callee-saved" pattern.

Hmm! What if in the ORIGINAL source, the masked value came from a FUNCTION CALL? Hmm, the source reads a u16 from memory — no call.

Hmm, hmm.

OK, let me now think about the LAST possible mechanism: **combine's copy propagation is blocked if the source is a hard reg with a "preference"**... no.

Hmm. Let me look at the actual gcc 2.7 combine.c rule. I'll reason from the observed behavior:
- `t = v` where v is dead after → merged (the copy disappears).
- `t = v` where v is live after (the store) → STILL merged (p1).

So the merge happens regardless of v's liveness?! Hmm, in p1 v IS used after the copy (the store). And the result was `andi s8,v0,0xfff` + presumably `sh s8,256(a1)` → so cse replaced v's use with t ✓ and then the defs merged.

⇒ gcc 2.7.2 merges `t = v` copies unconditionally (when the modes match and the copy is a plain reg-reg copy).

⇒ To keep the copy, the copy must NOT be a plain reg-reg copy in the RTL. E.g.:
- a copy with a mode conversion (HImode→SIMode etc.) → the conversion generates extra insns ✗ (unless it's a zero/sign extension that's free).
- a copy where the destination is a hard reg with a preference (the pin).
- `plus(reg, reg)` (the $0 add).

Hmm, so we're back to the $0 add.

⇒ Conclusion: the $0-add opaque copy is NOT reproducible in plain C for gcc 2.7.2. It's a genuine lever (RC-12 in the project's own notes).

⇒ func_80181E64: WALL (best 3), tag "cse-opaque-copy".
⇒ func_800D0D7C: WALL (best 17), tag "cse-opaque-copy".
⇒ func_8003DF8C: let me check its score (34) and diff. It's the same mechanism (i = arg0 + zr).

Hmm, hold on. Let me look at 8003DF8C's diff to confirm it's the same mechanism.

And func_800D2650 and func_801415C0 remain.

Hmm, wait. Before I give up on the opaque copy: what about the HImode copy escape? The moves.md entry says an HImode copy escapes cse. Let me TEST it for 80181E64:

```c
u16 v;
s32 t;
v = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;   /* HImode */
t = v;    /* HImode → SIMode: zero extension → sll/sra? */
```
Hmm, the zero-extension of u16 → s32 in gcc 2.7 MIPS: `sll tmp,v,16; srl tmp,tmp,16` (2 insns) ✗.

Hmm, BUT: what if the value is known to be ≤ 0xFFF? gcc 2.7's combine might use `andi` (1 insn: `andi tmp,v,0xffff`) ✗ (the target has a move).

Hmm.

What if BOTH v and t are u16 and the later uses are adjusted?
- `*(s16 *)(arg1 + 0x100) = t;` ✓ (a 16-bit store, `sh s8,256(a1)` ✓ — the target's store is `sh s8` ✓!)
- `t += 0x600` → in HImode: `addiu s8,s8,0x600` — gcc 2.7 would emit the add and then... for HImode the upper bits are garbage; gcc 2.7 typically doesn't truncate after an add (it assumes the upper bits don't matter) → `addiu s8,s8,0x600` ✓ 1 insn! But then the value's upper bits are garbage → the later use `func_8004787C(t)` (a 32-bit arg) would pass garbage ✗ (semantics!).

Hmm, unless the addition's overflow doesn't matter... it does.

Hmm, but hold on: the target's `t += 0x600` — let me check the target's asm for the loop. If the target's t is 32-bit, `t += 0x600` = `addiu s8,s8,0x600` ✓.

Hmm, and in the target, is t ever used as a 32-bit value? `func_8004787C(t)` — hmm, let me check the target's loop code.

Let me look at the target's loop.

Actually, let me first check the target's insns for the loop to see how t is used. Let me read more of tgt.txt.

Time is short (4h in). Let me prioritize finishing the deliverables. But this HImode idea is promising enough to test quickly.

Let me look at the target's loop first (read tgt.txt lines 45-113).
