---
ts: 2026-11-06T16:51:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eFx2JbpTXcrlPUdHS26T
---
`REG_ALLOC_ORDER` for MIPS defines the order. Let me check mips.h for REG_ALLOC_ORDER. The order likely starts with $2, $3, $4... or $4,$5,...? Actually the allocation gave $2 first for the highest-priority qty. Let me check.

Actually, this doesn't directly help. The priority order determines who gets $2.

Let me reconsider: is there a way to make the t group's priority higher? The t group {77,83}: nrefs 8, life 8 (birth 8, death 16). pri = 3*8/8 = 3.
The h group {76,81,82}: nrefs 12, life 8 (birth 6, death 14). pri = 3*12/8 = 4.5.

Wait, life = death - birth = 14-6 = 8 for h, and 16-8 = 8 for t. Same life, different nrefs (12 vs 8). So h wins because it has 3 tied regs.

To flip: make the t group have MORE refs than the h group, or the h group fewer.

What if I add a fourth reg to the t chain? The t chain: 77 (t) → 83 (the sum). If the sum were used in another tied operation, e.g., if the lhu address computation were folded... Hmm: `*(u16 *)(t + (...))` — the address is `t + (...)`, then the load. The load's output (84) is a memory operand so no tie.

What if the expression were `*(u16 *)(t + ... + 0)`? no.

What if the address is computed in two steps: `p = t + ...; ... *(u16*)p`? Then 83 = 77+82 (tie 83→77), and 84's address = 83 (used). No extra tie.

Hmm, what about the h chain: 76 (h) → 81 (h<<4) → 82 (+s2). Three regs. If I could break one tie...

The tie at insn 37: `82 = 81 + 75` with 81 dead → tie 82 to 81. The tie at 35: `81 = 76 << 4` with 76 dead → tie 81 to 76.

If h were used after the shift, the tie at 35 breaks. Can I make h used after? The C uses h once. What if the expression were `((h << 4) + (s32)s2) + (h >> 16)`? That changes semantics/insns.

What if h is declared `volatile`? Then it'd be spilled to the stack — extra insns.

Hmm. What if I change the *order* of the h chain and the t chain so that the t group gets 3 tied regs? E.g., if the expression is `(t + (s32)s2) + (h << 4)`? That changes the computation order: t + s2 first (83 = 77+75, tie 83→77), then + (h<<4) (new reg ties to 83). That gives the t group 3 regs: {77,83,new}. And the h group {76,81} 2 regs. Let me check if the semantics are the same: the address is `t + ((h << 4) + s2)`. Reassociating to `(t + s2) + (h << 4)` is the same sum (integer addition is associative). The instruction order would change: target has sll h,4; addu h,s2; addu t,h. If I write `(t + s2) + (h << 4)`, the order would be addu t,s2; sll h,4; addu. Different insn order → mismatch. Unless sched1 reorders to the target order! sched1 might. Worth trying.

Let me try: 
```c
func_8012C658(0x19B, (s16)(*(u16 *)((t + (s32)s2) + (h << 4)) + a), (s32)s1);
```
Hmm, but the RTL order would be: t+s2 first. sched1 may reorder. Let me test.

Another idea: reduce the h group to 2 regs by breaking the 76→81 tie: make h's use not the last use of 76. What if I write `(h << 4)` but also use `h` in the same expression somewhere harmless, e.g., `((h << 4) + (s32)s2)` where h is loaded once... no.

Alternatively, break the 81→82 tie: `82 = 81 + s2` — if s2 were not dead... s2 (75) is live across the whole loop, not dead. The tie is 82→81 because 81 dies. If 81 were used later... no.

Hmm, what if I make `(h << 4) + (s32)s2` into two separate variables:
```c
s32 hh;
hh = h << 4;
hh = hh + (s32)s2;
```
Same RTL.

OK, let me try the reassociation approach and a few others:
1. `(t + (s32)s2) + (h << 4)`.
2. `t + (s32)s2 + (h << 4)`.
3. Change the cast order: `(s16)(*(u16 *)((h << 4) + (s32)s2 + t) + a)`.
4. Use a temp for the address: `s32 idx; idx = (h << 4) + (s32)s2; idx = t + idx;`.
5. Declare h as `int` but load via `*(u16*)` then cast: `h = (s16)*(u16 *)(...)` — that's a zero-extend + sign-extend; probably different.

Let me test 1, 2, 3, 4.

Actually, another important idea: the target's tie groups are the SAME as mine ({76,81,82} and {77,83}), but the allocation order differs. So the original build's priorities differed. Since nrefs and lives are fixed by the RTL, and the RTL is the same (same instruction order), the priorities are the same... unless the RTL *isn't* the same (different sched1 order).

The target's instruction order is a, t, h. My RTL order at local-alloc is a, h, t. So the original's sched1 order was likely a, t, h — giving t a birth at insn n and h later.

Let me compute with the order a, t, h, s0++, h<<4, ...:
Block 1 insns (same set, different order):
1 label, 2 a, 3 t, 4 h, 5 s0++, 6 h<<4, 7 +s2, 8 t+h, 9 lhu, 10 s0++, ... 

Hmm wait, the C order is a, t, h, s0++, call. sched1 currently moves h before t. If the order were a, t, h:
- 78 (a): born 2 → birth 4; dies at the +a (later).
- 77 (t): born 3 → birth 6; dies at the addu (insn 8) → death 16.
- 76 (h): born 4 → birth 8; dies at the <<4 (insn 6) → death 12.
- 81: born 6 → birth 12; dies 7 → death 14.
- 82: born 7 → birth 14; dies 8 → death 16.
- 83: born 8 → birth 16; dies 9 (lhu) → death 18.
Groups:
- t {77,83}: birth 6, death 18 → life 12, nrefs 8 → pri = 3*8/12 = 2.
- h {76,81,82}: birth 8, death 16 → life 8, nrefs 12 → pri = 3*12/8 = 4.5.
Still h wins. Hmm.

So even with the target's order, h wins by priority. Yet the target has t in $2. So something else must differ.

Wait — maybe in the target, the t group is {77,83} but the h group is {76,81,82}, and the allocation order... Let me reconsider: maybe the first free reg isn't $2 for the first qty. REG_ALLOC_ORDER for MIPS might be $4,$5,...,$2,$3? Let me check mips.h.

If REG_ALLOC_ORDER starts with $4 (a0), then the first qty gets $4! But the target has a=78 in $4. Hmm, the target's a (78) is in $4. And 78's priority is low (0.5). So $4 wasn't given to the highest-priority qty.

Let me check REG_ALLOC_ORDER in mips.h.
