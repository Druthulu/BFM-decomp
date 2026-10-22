---
ts: 2026-10-22T08:27:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_8FzBErZP2cGSZZg4Zk8A
---
w02 (the one-step u16 cast from the load): score 4 — the compare keeps the load ✓ but there's an andi. Hmm, 4 (worse than 2).

OK, ~30 scored tries now on 8018302C. Let me record it as a WALL with best 2 and the new evidence, then move to 8017E6EC.

Actually, wait. Let me think about the WALL tag. The walls.txt has "cse-copy-merge" (from G05's note: "pin | func_8018302C | WALL cse-copy-merge — target `move v1,v0` is `plus v,$0`: a hard-reg addend combine cannot fold, so cse keeps the copy; a C-level zero is a constant -> combine folds -> cse propagates (best 2)").

My new evidence: the s16-temp copy trick (from G06) makes the copy survive as `or v1,v0`, but then combine rewrites the `slti`'s operand to the copy (the compare reads v1 instead of v0); the u16 variant keeps the compare on the load but adds `andi v1,v0,0xffff`. So the new tag could be "cse-copy-merge" (existing) — the wall is the same mechanism. I'll use the existing tag "cse-copy-merge" and put the new evidence in the evidence column.

Hmm, the results.tsv evidence column: "gcc pass + mechanism ≤ 140 chars".

Let me now move to 8017E6EC. Its residual (from the notes):
- score 6: the register swap: the constant 0x10 gets v0 and the loads get v1; the target has the constant in v1 and the loads in v0.
- The note says: "the group `t4` is a GLOBAL pseudo (its value crosses the goto lab_e958), so global-alloc gives it a register only after local-alloc has already handed $2 to the block-local constant 0x10 (live 104..107, overlapping t4's 105..156) — t4 therefore gets $3/v1 and the constant gets $2/v0".

Hmm, so in the target: t4 (the global) → $2 (v0) and the constant 0x10 → $3 (v1).

In my current win.c (score 6): the constant → v0, t4 → v1.

Hmm, and the other diff hunk (at 154-157): `lhu v0,52(s1)` vs mine `lhu v1,52(s1)` — the same swap for the second load.

So I need: t4 (and the loads feeding it) in v0, and the constant 0x10 in v1.

The note's attempt 3 (splitting the reused local into one name per value) got score 6 with 172 ins — the current win.c. Attempts 4-7 (splitting c, u16 t4, do-while, decl order) → no change.

Ideas for 8017E6EC:
1. The constant 0x10 is materialized in case 2 (`unk1C = 0x10`). What if we make it NOT a separate local pseudo? E.g. `((Unkstruct_800B5CB8 *)arg0)->unk1C = 0x10;` — the constant needs a register. What if the store were `unk1C = t4` hmm no.

2. The note says local-alloc hands $2 to the block-local constant. To flip, the constant must not be the first local pseudo needing $2. Hmm — what if the constant's pseudo is used in a place that makes it live longer/earlier?

Hmm. Let me look at the target asm around 104 to understand.

Let me disassemble the target for 8017E6EC.

Actually, let me first check the score-6 diff again (from my earlier run):
```
replace mine[104:106] target[104:106]
    104  li v0,16        | li v1,16
    105  lhu v1,52(s1)   | lhu v0,52(s1)
replace mine[107:108] target[107:108]
    107  sw v0,28(s1)    | sw v1,28(s1)
replace mine[154:155] target[154:155]
    154  lhu v1,52(s1)   | lhu v0,52(s1)
replace mine[156:158] target[156:158]
    156  addiu v1,v1,1   | addiu v0,v0,1
    157  sh v1,52(s1)    | sh v0,52(s1)
```
So mine: the constant 0x10 in v0 (`li v0,16`, `sw v0,28(s1)`), the loads in v1.
Target: the constant in v1 (`li v1,16`, `sw v1,28(s1)`), the loads in v0.

So I need to swap the allocation of the constant pseudo and the load pseudo.

The note says: the constant is a block-local pseudo (live 104..107) and t4 is a global pseudo (crossing the goto). local_alloc runs first and gives v0 to the constant; then global_alloc gives v1 to t4.

To flip: the constant must be allocated AFTER t4, or the constant must not be a local pseudo, or t4 must be local.

**IDEA**: what if the constant 0x10 is stored via a variable that is global (crosses a block boundary)? E.g., in case 2 the store `unk1C = 0x10` — what if the constant is assigned to t4 first? No, t4 holds unk34.

**IDEA**: what if the `li v1,16` constant is materialized in a different block — e.g. hoisted? The constant is used only by the store in case 2.

Hmm, what if the store's value 0x10 is written as a variable that's also used elsewhere, making it global? Hmm.

**IDEA (from the note's mechanism)**: local-alloc assigns $2 to the constant because the constant is the first local pseudo. What if there were ANOTHER local pseudo that grabs $2 first, and the constant gets $3? Then the loads (which are local pseudos too) would get... hmm, the loads also need regs. In the target, the loads get v0 and the constant v1.

So in the target, the LOAD's pseudo got v0 (before the constant) and the constant got v1. So in the target, the load was allocated $2 first, and the constant $3!

So: the load pseudo (a local) is allocated before the constant. In mine, the constant comes first.

Why? The allocation order within local_alloc is by "qty" (the number of references) or by the pseudo's birth order. The constant 0x10 has 1 ref; the load has 1-2 refs.

Hmm! The note says the loads are t4's source: `t4 = arg0->unk34` → `lhu v0,52(s1)` — that's the load of unk34 into t4's reg (t4 is global). Hmm, so the load at 105 is the load for t4 (a global pseudo) — the load's result IS t4's value (t4 = the load).

Hmm, wait: in the target, `lhu v0,52(s1)` at 105 — that's the load of unk34 (offset 52 = 0x34) → so v0 holds unk34 → that's t4's value! And `li v1,16` is the constant.

So in the target: t4 (the global) → v0, the constant → v1.
In mine: the constant → v0, t4 → v1.

The note: local-alloc gives $2 to the block-local constant, then global-alloc gives $3 to t4.

Hmm, so how does the target get $2 for t4? If local-alloc gave $2 to the constant, the constant would be v0 ✗.

So in the TARGET, the constant did NOT get $2 from local-alloc. Hmm! Why? Maybe because in the target, the constant's pseudo is NOT block-local: maybe it's a global pseudo (crossing a block boundary)! Hmm, the constant 0x10 is stored in case 2 and the store is `sw v1,28(s1)` — the constant's pseudo is used only there → block-local.

Hmm, unless in the target's source the constant is a variable that's live across blocks.

Hmm! What if the constant 0x10 comes from a variable that ALSO appears in another case? E.g., if the same variable `t4` held 0x10 in one place and unk34 in another → then t4 is global and the constant would be... hmm.

**IDEA**: what if the constant 0x10 is assigned to a variable that is live across the goto (a global pseudo), so global_alloc gives it a reg BEFORE local_alloc? Hmm, global_alloc runs after local_alloc.

Hmm, hmm. Let me reconsider: in gcc 2.7, the order in allocate_registry is: local_alloc first, then global_alloc? Or the reverse? The note says local-alloc handed $2 to the constant and then global-alloc gave $3 to t4. So local first.

For the target: t4 (global) → $2 and the constant (local) → $3. That means the constant did NOT get $2 from local_alloc. So local_alloc gave $2 to something else — the load pseudo? Hmm, the load IS t4's value (a global pseudo), so it's not local.

Hmm! Unless in the target's source, the load `lhu v0,52(s1)` is into a LOCAL pseudo (not t4 itself) and t4 is assigned from it... Hmm, but then there'd be a copy.

Hmm, hold on: maybe in the target, `t4` is NOT global: maybe the goto's structure differs. Let me look at the target's asm around 104 to see the block structure.

Let me disassemble the target for 8017E6EC and look at the region.

Hmm, this is a big function (172 ins). Let me look at the relevant part.

Actually, maybe a better approach: try things.

**IDEA**: What if we make the constant 0x10 a GLOBAL pseudo by storing it in a variable that's live across the goto? E.g.:

In the target's source (the given one), case 2 does:
```
t4 = arg0->unk34;
arg0->unk1C = 0x10;
goto lab_e958;
```
and lab_e958 does `t4 = t4 + 1; arg0->unk34 = t4;`

Hmm, so t4 crosses the goto ✓ (global).

What if the constant 0x10 were ALSO stored in a variable that crosses the goto? E.g.:
```
t4 = arg0->unk34;
unk1C = 0x10;   /* hmm */
```
Hmm.

**IDEA 2**: what if the constant is assigned to `c` (the existing s32 c variable)?! In the source, `c` is used in cases 1, 2 (c = arg0->unk94, c = arg0->unkFE). If in case 2 we wrote `c = 0x10; arg0->unk1C = c;` — then c is a global pseudo (used in multiple cases) → global_alloc would give it a reg... hmm, but global_alloc runs after local_alloc, so it'd get $3 or whatever is left. Hmm, but then the constant would be in a global reg — and the target has the constant in v1 ($3) ✓ and t4 in v0 ($2) ✓!!

Hmm! But wait: would global_alloc give c ($3) and t4 ($2)? global_alloc allocates the global pseudos in some priority order. If t4 has priority over c, t4 gets $2 ✓ and c gets $3 ✓.

Hmm, that's promising! But careful: using `c` for the constant changes the source's semantics? In case 2, `c = arg0->unkFE; if (c != 6) break;` — c is used BEFORE. Then `c = 0x10` after. That's fine semantically (c is dead after).

Hmm, but the value 0x10 must be materialized as `li v1,16` ✓ (the same).

Hmm, but would gcc keep `c` as a separate pseudo? c is used in cases 1 and 2 → it's a global pseudo (live across blocks) ✓.

Hmm, but c's live range: from case 1 to case 2 — hmm, cases 1 and 2 are different blocks → c is global ✓.

So: `c = 0x10; ((Unkstruct_800B5CB8 *)arg0)->unk1C = c;` — hmm, but then the constant's pseudo is c (global) and the load... hmm.

Hmm, but hold on: in the TARGET, the `li v1,16` is a separate insn from the load `lhu v0,52(s1)`. If c (global) holds 0x10, then c's reg = v1 ✓ and the constant is materialized there ✓.

Hmm, but would the ORDER work out? The target:
```
104: li v1,16
105: lhu v0,52(s1)
106: ???
107: sw v1,28(s1)
```
Hmm, `li v1,16` then `lhu v0,52(s1)` then (106) then `sw v1,28(s1)`.

Hmm, in the source order: case 2 does `t4 = arg0->unk34;` (the load) THEN `arg0->unk1C = 0x10;` (the constant + store). But the asm has the constant FIRST (104) then the load (105)! So the scheduler moved the `li` before the load ✓ (independent).

OK, so my plan: in case 2, write:
```
c = 0x10;
((Unkstruct_800B5CB8 *)arg0)->unk1C = c;
```
Hmm, but wait: c is used in case 1 too (`c = arg0->unk94; if (c == 0x10)`) — and case 1 comes BEFORE case 2. So c's live range spans cases 1→2 → c is a global pseudo.

Hmm, but in case 1, c = arg0->unk94 and the comparison `if (c == 0x10)` — hmm! If c holds 0x10 in case 2 and the comparison in case 1 compares c with 0x10 — that's a coincidence.

Hmm, hmm. But hold on: would that create a problem: in case 1, `c = arg0->unk94; if (c == 0x10) { ... }` — the constant 0x10 there is a comparison constant (not materialized in a reg). Fine.

Hmm, but there's a risk: gcc might CSE the two 0x10 constants (c = 0x10 and the comparison's 0x10) — no, one is a comparison constant.

Let me try it! Also, the current win.c splits the reused `t` into t1..t5. Let me apply the change to the current win.c:

case 2 becomes:
```
    case 2:
        func_8017ECC4((s32)arg0, 0);
        ((void (*)(void *))func_8017EB34)(arg0);
        c = ((Unkstruct_800B5CB8 *)arg0)->unkFE;
        if (c != 6) {
            break;
        }
        t4 = ((Unkstruct_800B5CB8 *)arg0)->unk34;
        c = 0x10;
        ((Unkstruct_800B5CB8 *)arg0)->unk1C = c;
        goto lab_e958;
```
Let me score that.

Also, another idea: maybe the fix is to make the CONSTANT global and the LOAD local. Hmm.

Let me try the c=0x10 variant. Let me write it and score.

Time: let me move fast now.
