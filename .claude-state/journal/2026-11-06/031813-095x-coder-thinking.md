---
ts: 2026-11-06T10:18:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eTKeMMUxs0aDTgx7VZuO
---
a (r76):
- insn 17: def (1)
- insn 57: and (use + def = 2)
- if_then_else ne (use) = 1
- subu (use) = 1
- plus (use) = 1
- plus (use) = 1
Total = 7. 

So both 7.

Hmm. To flip, I need a ref count difference or a live-length change.

What if I make the `if (a == cur)` comparison use a *copy* of a, so a's refs drop? E.g., `if (a == cur)` → the comparison uses a once. If I wrote `if (a - cur == 0)`? That changes the comparison but might still be one use.

Hmm.

What if I remove the `a = a & 0xFFF` self-set by masking at the comparison and uses? Then a's def is `a = arg2`, and the mask `a & 0xFFF` appears in multiple uses → more refs.

Alternatively, make a's live LONGER: a's death is at the last `plus` (insn ~319). If I move the `if (diff < -0x800)` block BEFORE `if (0x800 < diff)`, a's last use changes. The target's asm order: `slti v1,2049` (0x800 < diff) then `slti v1,-2048`. So the >0x800 check comes first. If I swap, the asm changes.

Hmm.

What if I move the `cur = ang & 0xFFF` statement after `a = a & 0xFFF`? Doesn't change a's live.

What if I move `a = a & 0xFFF` EARLIER (right after `a = arg2`)? Then a's birth is earlier (same) but the mask is earlier — doesn't change birth/death.

Hmm.

What if a's birth is LATER? `a = arg2` is the first statement. If I move it after `ang = ...`, a's birth is later → shorter live → higher pri (worse).

I need a's live LONGER → birth earlier (impossible) or death later.

Hmm, death later: the last use of a is in the `if (diff < -0x800)` block. What if I add a use of a after the divisions? That would add an instruction (unless it's a copy that's optimized).

What if `d = q;` becomes `d = q + (a & 0)`? identity, optimized away.

Hmm.

OK, what about increasing div's refs by using it in the `t = a + 0x1000` expressions? No.

Let me reconsider: maybe the target's `a` is NOT global. What if in the target, `a` is local? a = arg2 (block 0), masked (block 0), used in `if (a == cur)` (block 0). Then a's uses in `diff = cur - a`, `t = a + 0x1000`, `t = a - 0x1000` are in LATER blocks → global. So global.

Unless the `if (a == cur)` branch structure means those uses are in the same block? The `else` block (diff = cur - a) is a different block.

So a is global.

Hmm, so both global. div's live longer → lower pri. Yet target has div s0.

UNLESS the original's `a` had a LONGER live range. E.g., if a were used after the divisions. Hmm.

Wait — what if the original source's `a` was actually `arg2` used directly (no local copy) and the mask was applied to a temp? Then `arg2`'s pseudo is live from entry to the last use. Its birth is the function entry (insn ~0) vs div's birth (~insn 8). So a's live would be LONGER (death - birth with birth ~0). If a's live becomes 30+, its pri drops below div's!

Let me think: if `a` is the raw arg2 parameter (u32 arg2), its pseudo is born at the function entry (the incoming a2 hard reg → pseudo). The mask `a & 0xFFF` would be a separate temp. Hmm, but the target has `andi s1,s1,0xfff` in-place.

Hmm, if `a` is the parameter and `a = a & 0xFFF` overwrites it, the pseudo's birth is at entry (insn 0) and death at the last use → live longer by ~8. Then a's live ~31, pri = 2*7/31 = 4516 < div 5384 → div wins s0! TARGET!

But wait: does the parameter pseudo start at insn 0? In the RTL, the parameter arrives in a2; the pseudo `a` is defined by the incoming value. gcc's `(set (reg a) (reg a2))` at function entry? Actually, gcc uses the parameter's hard reg directly if possible, or creates a pseudo with an initial move. In the nopin, `a = arg2` is a separate statement creating a move at insn 17. If we use `arg2` directly (no `a = arg2`), the pseudo for arg2 is born at the function entry.

Let me test: remove `a = arg2;` and use `arg2` in place of a:
```
div = arg3;
ang = ...;
div = (s16)div;
arg2 = arg2 & 0xFFF;   // can't assign to a parameter? Actually yes, parameters are lvalues.
cur = ang & 0xFFF;
if (arg2 == cur) ...
```
Hmm, but modifying a parameter is fine in C. Let me write:
```
u32 a = arg2;  →  just use arg2 and mask it in place
```
Actually, if I write `arg2 = arg2 & 0xFFF;` the pseudo for arg2 is the parameter pseudo (born at entry). Let me test.

Similarly for div: `arg3 = (s16)arg3;` — the parameter pseudo born at entry. Hmm, that would make div's birth earlier too.

Let me test a variant where `a` is the parameter (no local copy) and div stays a local:
```
s32 div;
div = arg3;
ang = ...;
div = (s16)div;
arg2 = arg2 & 0xFFF;
cur = ang & 0xFFF;
if (arg2 == cur) ...
```
But arg2 is u32; assigning to it is fine.

Let me test this. Also test the symmetric: div as parameter.

Let me create d1.
