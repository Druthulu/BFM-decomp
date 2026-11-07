---
ts: 2026-11-06T16:46:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HaIrhhmwlvEA0NrhAphb
---
In m02, the mapping is still v0→$v1, v1→$v0. Hmm, mine[31] `sll v0,v0,0x10` (the test) and mine[32] `sll v1,v1,1` (unk70*2). So $v0 is the test temp, $v1 is v0. Still rotated.

Interesting: the first block's ordering differs too: target `lh v0; lw a1; sll v0; lui at; addu; lhu v0; lhu v1,48(a1)`. Mine has a different order.

Let me look at the whole first block in mine. Let me objdump the kept object for w1 (no pin) and compare to target. Use --keep.

Actually, let me think about the local-alloc priorities. The four locals v0, v1, a0r, a1 (plus at). Target assignment $2,$3,$4,$5. That's exactly birth/priority order in the first block: v0 first, v1 second, a0r third, a1 fourth? But a1 is set before v0 in the source (`a1 = CAST_SIGN(...)` before `v0 = ...`). Hmm.

Wait, in target: `lw a1,32(s0)` (a1 = s0->unk20) comes after `lh v0,112(s0)`. So the scheduler reordered.

local-alloc allocates in order of `qty` priority. Let me use tools/localalloc_sim.py? The brief mentions tools/alloc_table.py and localalloc_sim.py (from C0505). But those are for the original TU, not the candidate.

Alternative approach: adjust ref counts to change priority. C0505: "Call-result temps of one type across cases → one function-scope variable (many refs, short live length outrank the self pointer)".

Hmm. Let me think about what natural source would give v0→$2. In gcc 2.7.2 local-alloc, the first block's quantities are allocated by `allocno_compare` (refs*... / live length). The pseudo with the highest priority gets the lowest-numbered free hard reg (in the block's allowed set). The target's order suggests v0 has the highest priority, then v1, then a0r, then a1.

In mine, the test temp (created by the `(v0<<16)` expression) is a separate pseudo that gets $v0. If it were merged into v0, v0 would likely get $v0.

Why does `(s32)(v0 << 16) < 0` create a separate pseudo? The shift result is used in a comparison, so expand creates a temp. combine/cse may not merge it with v0 because v0 is still live (used in the branch bodies? no, v0 is recomputed but the *pseudo* v0 is live into the branches? After the if, in the then-branch v0 is re-set; but liveness: v0's value after the load is used by the test and by... the `v1 = v1 + v0` earlier. So v0 is dead after the test? The test uses v0<<16. Then both branches redefine v0. So v0 is dead after the test. combine could tie the shift to v0? Apparently not.

In the target's compiled code, `sll v0,v0,0x10` — the same register. This could be because the shift temp was allocated to the same reg as v0 by local-alloc's copy preference/tie (the shift temp's live range starts where v0 dies, so local-alloc ties it).

In mine, local-alloc gave the shift temp $v0 and v0 $v1 — it did NOT tie them. Why? Because v0 is live *across* the test into... hmm, if v0's live range doesn't end at the shift, no tie.

So: make v0 dead right at the test. It already is (redefined in both branches). Hmm, but "redefined in both branches" means v0 is live-out of the test block? No: v0 is dead at the branch point (not used before redefinition in either branch). Liveness should show v0 dead.

Wait, maybe v0 IS used later without redefinition in one path? Let me re-read:

```
v0 = *(u16 *)at;
v1 = a1->unk30; v1 += v0; a1->unk30 = v1;
if ((s32)(v0 << 16) < 0) {
    v0 = unk70; v1 = (s16)v1; v0 = v0*2; at = D_8019C7CC+v0; v0 = *(s16*)at; a0r = v0; v0 = v0-0x30;
    if (v0 >= v1) { a1->unk30 = a0r; }
} else {
    v1 = (s16)v1; v0 = unk70; v0=v0*2; at=...; v0=*(s16*)at; a0r=v0; v0=v0+0x30; v1 = v1 < v0;
    if (v1 != 0) goto JOIN;
    a1->unk30 = a0r;
}
JOIN:
...
v0 = unk70; v0=v0*2; at=D_8019C7DC+v0; v0=*(u16*)at; s0->unk1C = v0;
...
K:
v0 = unk70; if (v0 == 0) func_8017F348(s0);
```

So v0 is recomputed everywhere. In the test, v0's last use is `v0 << 16`. So the shift temp and v0's live ranges meet → local-alloc should tie. But it didn't.

Hmm, maybe because `v0 << 16` is computed *before* the store `a1->unk30 = v1` in the RTL, and v0 is still live for `v1 = v1 + v0`? The order: `v1 = v1 + v0; store; if (v0<<16)`. So v0 dies at the shift.

Let me look at mine's actual first block to see the order. Let me objdump w1 with --keep.

Actually, maybe the difference is simpler: in mine, the shift temp is allocated $v0 and v0 $v1 because of *global* alloc, not local-alloc. The REG-caller class means caller-saved. Hmm.

Let me try to directly reduce the refs of v0 vs the shift temp. C0505: "One value per temp: a local that dies in several places is refused by local-alloc and goes global". 

What if I split v0 into two variables: `v0` for the u16 load and a separate `v2` for the shift? That's what's happening implicitly.

What if I make the shift explicit with a variable that has more refs... no.

Alternative: change the test to not need a separate temp: `if ((s32)(v0 << 16) < 0)` → write `if (v0 & 0x8000)` (m03, 38) or `if ((u16)v0 >= 0x8000)`. The target's `sll v0,v0,0x10` + `bgez` means the compiler used the shift as the sign test. If I write `if ((s16)v0 < 0)`, gcc might emit `sll v0,v0,0x10; bgez` too (m01 = 37 REG-caller, same).

Hmm m01 is 37 REG-caller — same as w1. So the test spelling doesn't matter.

Let me look at whether the pin's effect can be replicated by changing the *declaration order/scope* (C0505). E.g., declare v0 in an inner block? Or make v0 the *first* declared local?

Let me try a batch:
- n01: `s32 v0;` declared first (before s0).
- n02: v0 declared inside the function scope but after at.
- n03: rename v0 to something? no effect.
- n04: use `s32 v0 = 0;` init at decl.
- n05: make `a1` a pointer: `Unkstruct_800B5CB8 *a1;`
- n06: make `at` s32 but reused.
- n07: remove `s0` local, use `(s32)arg0` everywhere.
- n08: make `v0` `u32`.
- n09: `v1` as `s16` (target loads lhu into v1 then sra... v1 is s32).
- n10: merge a0r into v1?

Hmm. Let me look at the target's register set: $1(at), $2(v0), $3(v1), $4(a0), $5(a1), $16(s0). The unpinned gives $1, $2(temp), $3(v0), $4(v1), $5(a0r), $6(a1). So it's a clean rotation: each local gets the next register down, with the shift temp taking $2.

If the shift temp weren't a separate pseudo, we'd get the target. So the real goal: eliminate the shift temp pseudo.

How? In gcc, `(s32)(v0 << 16) < 0` — the comparison against 0 of a shifted value. fold might turn it into `v0 < 0` in the shifted domain? Actually `(s32)(v0 << 16) < 0` is equivalent to bit 15 of v0. The target uses `sll v0,v0,0x10; bgez v0` — so the shift is materialized into v0.

If the source were `v0 <<= 16; if ((s32)v0 < 0)`, the RTL would be `set v0 = v0<<16; if v0 < 0` — a self-set. m02 tried `v0 = v0 << 16; if (v0 < 0)` and got 38 with 66 ins. Hmm, why 66? Maybe the shift was moved into the branch or the `sll` was combined differently.

Let me look at m02's first block fully. Let me objdump. Use --keep on m02.

Actually, let me just try `v0 <<= 16;` (compound) and `if ((s32)v0 < 0)`.

Also, maybe the issue is that after `v0 = v0 << 16`, the compiler knows v0's low bits are 0 and the branch bodies recompute; but the register allocation changed.

Let me get the full asm of m02 vs target to see.
