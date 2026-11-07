---
ts: 2026-11-06T10:24:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ceQpywe0lajBeVJFUQZb
---
j4 (single expression `(div << 16) >> 16`) → score 2 (temp issue). j1 (cur before shifts) → 22.

So the caller-saved shift persists with the two-statement form.

Time: 03:37. I've spent ~37 min on item 3. This is past the 30-min wall budget. I should record it. But I'm so close (score 2). Hmm.

Let me reconsider: the score-2 residual is the sign-ext temp. Let me try to make the temp use s0.

Idea: make the sign-extension temp's qty get s0 by making it cross a call? No.

Idea: what if the divisor's sign-extension is done via a `union` or a struct field? no.

Idea: what if `div` is assigned the sign-extended value through a *second* variable that is also used, creating a copy preference? E.g.:
```
s32 div2;
div = arg3;
...
div2 = (s16)div;   // sign-ext
...
q = diff / div2;
```
Then div2 is global (used in the divisions), and div is local-ish. The sign-ext temp would be tied to div2? Hmm.

Actually, the sign-ext `div2 = (s16)div` produces `sll temp,div,16; sra div2,temp,16`. If div2 and temp are tied... div2 is global, temp is local. Hmm.

Let me try s1-style (separate dd) with the do-while for item 3. Earlier s1 (separate dd, no do-while) scored 27. Let me combine with do-while.

Actually, let me take stock: I have a score-2 body. The remaining diff is 2 instructions (sll/sra temp). If I can't fix it, the best is 2. That's still a WALL (best=2) unless I get 0.

Hmm, but wait — maybe I should try the OTHER approach for the sign-extension: make it in-place by ensuring the temp gets s0. 

Let me look at the temp's allocation in f2/h1. In h1 (score 2), the temp is v1. Let me dump h1's alloc and find the temp.

Actually, let me try a completely different spelling: `div = (s16)(div & 0xFFFF);`. This is `andi temp,div,0xFFFF; sll...; sra...`? No.

Or `div = (s32)(s16)div;` — same as (s16)div.

Hmm.

What if I use a cast to `s16` on a *copy*: `div = (s16)(div + 0);`? The +0 folds.

What about `div = (s16)div | (div & ~0xFFFF);`? That's a no-op identity (sign-extension preserve) — a launder, forbidden.

OK, let me try the separate-variable approach with do-while. And also try making the temp get s0 by making the sign-ext happen in a context where v1 is busy.

Actually — here's an idea: in the score-2 body (h1), the sign-ext temp is v1 and cur is in a0? Let me check h1's asm. If h1 has cur=a0 and the temp=v1, then the target has cur=a0 but no temp. So the target's `sll s0,s0` is in-place and cur=a0. If I remove the temp, cur might shift (as in i1). 

Hmm, so the target has BOTH in-place shifts AND cur=a0. That means in the target, v1 is free at cur's birth but cur still got a0 (global-alloc). And the shifts are in-place (s0). 

Wait — how can the in-place shift happen without a temp? `sll s0,s0,16; sra s0,s0,16` requires div to be in s0. In the target, div IS in s0. The sign-extension pattern `(set (reg div) (sign_extend (subreg (reg div) 0)))` with div in s0: the expander emits `(set (reg temp) (ashift (reg div) 16)); (set (reg div) (ashiftrt (reg temp) 16))`. If the temp is allocated to s0 (same as div), the assembler output is `sll s0,s0,16; sra s0,s0,16` (in-place). So the temp IS in s0 in the target!

So in the target, the sign-ext temp (a local qty) got s0 — a callee-saved register — despite not crossing a call. Why? Because at its birth, all caller-saved regs were busy! Or because local-alloc's reg order for this qty... Hmm.

Actually, if the temp is short-lived (born and dies at the sign-ext), local-alloc gives it the first free reg. In the target, at that point v0 (ang) is busy, v1 maybe busy... and a0, a1, a2, a3? The temp's live range is 2 insns. local-alloc picks the first free in reg_alloc_order: v0 (busy, ang), v1 (free?) → v1. Unless v1 is busy.

Hmm, in the target, at the sign-ext (3a1c), what's live? ang in v0 (live until 3a24), a in s1, div in s0. v1 was used at 3a14 (delay slot) and is free after. So v1 is free → the temp should get v1. But the target's shift is in-place (s0).

Contradiction! Unless the target's sign-ext temp is NOT a separate pseudo but the pattern writes in-place.

Hmm, maybe the MIPS extendhisi2 pattern is:
```
(define_insn "extendhisi2"
  [(set (match_operand:SI 0 "register_operand" "=d")
        (sign_extend:SI (match_operand:HI 1 "memory_operand" "m")))]
  ...)
```
and for register sources there's a different pattern. Let me check the reference mips.md for extendhisi2 and the sll/sra sequence.

Actually, gcc 2.7.2's MIPS `extendsidi`/`extendhisi2` for a register operand might use `sll`+`sra` with a temporary in the pattern. Let me look.

Let me grep mips.md for extendhisi2.
