---
ts: 2026-11-06T16:50:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6zaSuKacMReGpjrICEnp
---
No twin of this exact function. Let me think about the allocation differently.

The h group has 3 tied regs (nrefs 12) vs t's 2 (nrefs 8). If I can make the h group tie fewer regs, or the t group tie more, the priority flips.

Idea: break the tie between 76 and 81. The tie happens at insn 35 `81 = 76 << 4` because 76 dies. If h were used again AFTER insn 35, 76 wouldn't die there → no tie → 81 becomes its own qty (born 10, dies 12, nrefs 4 → pri 2*4/2 = 4). And 76 alone: born 6, dies (last use) later, nrefs 4 → pri lower. Hmm, this could change things a lot.

Can I add a use of h after the <<4 without changing the instruction stream? The h value is used in `(h << 4)`. If I write the expression to use h twice, e.g., `((h << 4) + (s32)s2 + (h & 0))` — combine would fold `h & 0` to 0 and remove it. 

What about `((h << 4) + (s32)s2)` where the same h is used in the shift and... no.

Idea: make the t group tie more regs. t is used in `t + (...)`. If t were used in another computation... no.

Idea: change the expression to `t + ((h << 4) + (s32)s2)` vs `((h << 4) + (s32)s2) + t` — the tie at insn 39: `83 = 77 + 82` with both 77 and 82 dead. The tie loop tries operand 1 first (r1 = 77) → ties 83 to 77. If I swap the operands (commutative), the tie loop might tie 83 to 82 instead! That would change the groups: {76,81,82,83} (4 regs, nrefs 16) and {77} alone.

Hmm, then t (77) alone: born 8, dies at 14 (nrefs 4) → pri = 2*4/6 = 1.33. h group: nrefs 16, birth 6, death 16 → life 10 → pri = floor_log2(16)*16/10 = 4*16/10 = 6.4. Still h first.

Hmm.

What if the sum order is `(h << 4) + (s32)s2 + t`? The C is `t + ((h << 4) + (s32)s2)`. Let me try `((h << 4) + (s32)s2) + t` — gcc canonicalizes operand order anyway (commutative).

Let me think about the REAL original source. Maybe the original used a different variable structure, e.g.:

```c
s0 = 0;
do {
    a = s0 << 9;
    t = s0 << 1;
    h = *(s16 *)((u8*)s1 + 0x70);
    s0 = s0 + 1;
    func_8012C658(0x19B, (s16)(*(u16 *)(t + (h << 4) + (s32)s2) + a), (s32)s1);
} while (s0 < 8);
```
Same.

Hmm, maybe the original had `h` as `s16` and the load assigned differently. Let me look at the sibling function func_8017EA24 (right after in the TU) for style.

Actually, let me look at the moves.md for similar pin cracks where the target had h in $3. Search for "lh" or "$3" pins.

Actually, let me reconsider: maybe I can lower the h group's priority by making its life LONGER. The h group spans insns 30..39. If I move the h load earlier (before a), its birth is earlier. w6_htop (h first) gave 6 — same. Let me check its diff: maybe the swap persists.

Let me check the sched1 order for w6_htop. If the RTL order is h, a, t, then the h group's birth is earlier → lower pri. But it still scored 6 (maybe the same swap, or different).

Let me diff w6_htop.
