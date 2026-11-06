---
ts: 2026-10-22T16:19:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8r4z2OLJNF7zbr09RAe2
---
Now r1's C: it declared first. The RTL: insn 9 sets reg 72 = it (symbol A); insn 23 sets reg 73 = p = plus(72, K); insn 26 sets reg 72 = it (symbol B); the compare is `(eq (73) (72))` = (p, it).

The .s for r1:
```
la $3, D_80120194       # it = v1
j $L472
addu $4,$3,25996        # p = a0 = it + K  (delay slot)
...
test:
la $3, D_801202A0       # it = v1
beq ? 
```
This matches the target exactly so far! `la $3,D_80120194` (lui v1; addiu v1) and `addu $4,$3,25996` — wait, the target had `addiu a0,v1,25996`, mine here `addu $4,$3,25996`. addu vs addiu! The diff earlier showed `addiu a0,v1,25996` for target; if mine uses `addu`, that's a difference. But the score was 1 with only the beq differing... Hmm, maybe masked_diff normalizes addu/addiu? No — addu $4,$3,25996 is a 3-operand add with an immediate (macro) which expands to `addiu $4,$3,25996`? In the .s with `.set nomacro`, an `addu` with an immediate is not allowed... but it's printed under `.set macro` (the delay slot is between `.set macro` and `.set reorder`?). Actually the listing shows `addu $4,$3,25996` inside `.set nomacro` — hmm, that would be an error, but it assembled (score 1). Actually `addu` with an immediate in nomacro mode would be an error. Maybe the disassembler shows the final instruction as addu after macro expansion. Whatever.

The key: the compare in r1 is (73,72) = (p,it) — the swap persists even with it=72. So the swap is NOT by pseudo number; it's `(eq p it)` regardless.

So the target's C must produce (eq it p) in the RTL. In both q9 and r1, the C `if (it == p)` → NE(it,p) → invert → EQ(p,it). So the invert swaps operands. To get EQ(it,p), we need the pre-invert NE to be NE(p,it) → C `if (p == it)`. But q14 did that and still scored 1. Let me verify q14's RTL: maybe q14's expansion differs because of how `if (p == it) goto zero` is laid out. Let me dump q14.

Hmm, wait: maybe the invert does NOT swap, and instead the *combine* pass canonicalizes `(eq a b)` to `(eq b a)` when one operand is a REG_EQUAL symbol? In q9/r1: EQ(?, ?) after combine is (p,it). p = plus(symbol,K) (REG_EQUAL), it = symbol (REG_EQUAL). Hmm.

Let me look at the .jump dump (after jump1) to see whether the EQ is (it,p) or (p,it) right after the inversion. If .jump shows (it,p) and .cse shows (p,it), the swap is in cse1's fold_rtx. Let me check .jump.
