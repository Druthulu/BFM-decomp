---
ts: 2026-11-07T00:18:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Gcqy1CbJP3rft8LYGrvW
---
The .lreg doesn't print "in" lines here. Hmm.

Let me just use the assembly mapping from mine (the diff):
Mine: a0=s1, tp=s4, s1var=s2, s4var=s3.
Target: a0=s2, tp=s3, s1var=s1, s4var=s4.

So the allocation order (mine): a0→s1, s1var→s2, s4var→s3, tp→s4.
Target: s1var→s1, a0→s2, tp→s3, s4var→s4.

Hmm. In mine, a0 (r74, pri 212, last in the order) got s1 — the FIRST callee-saved reg. That means a0 has a *preference* for s1, or the order isn't what I think.

Hmm, wait: maybe s0 is taken by v1var (local-alloc), and then the globals take s1..s5 in *their* order. If a0 got s1, a0 must be first among the callee-saved globals. But a0 is r74, last in the .greg order (pri 212).

Unless find_free_reg assigns based on preferences: a0 (the parameter) has a copy preference for the parameter register a0... but a0 is caller-saved; a0 crosses calls so it can't use a0.

Hmm, `find_free_reg` in global.c uses `reg_preferred_class` and preferences.

Honestly, this is another deep allocation puzzle. Let me consider the time: item 4 started 17:15, now ~17:22. Budget 20-30 min.

Let me try a few empirical things:
1. Fix the launder (const-addr fold) — maybe the block structure.
2. Reorder statements.

Let me first try the launder fix since it's the 3-insn issue. Ideas:
a. Move `tp = (u16 *)&D_80126B58;` after the `s4 = ...` / `kind = ...` lines (later).
b. Move it before `r0 = rand();`.
c. Put it inside the if.
d. Add a second assignment.
e. Use a goto to make the use block have 2 predecessors.

Let me test a batch.

Also, for the register swaps, maybe statement reordering helps.

Let me generate ~15 candidates.

Actually, wait. Let me reconsider the launder. `__asm__ __volatile__("" : "=r"(tp) : "0"(tp));` — the key is it's VOLATILE, so cse clears its table. 

Lever-free alternative to clear cse's table: a function call? cse doesn't clear for calls. Hmm.

What about a `setjmp`? no.

Hmm, what about a volatile *read*? Not allowed (barrier).

What about making tp's assignment happen in a block that cse can't follow into the use block? Let me test moving tp's assignment into the if-block and see... that would make it fold worse.

Hmm, what if the assignment is in the if-block but AFTER a label with 2 predecessors?

Let me think about the control flow:
```
r0 = rand();
tp = &D_80126B58;
s4 = *(s32*)(a0+0x1C);
kind = (r0&1) ? 0xF : 0xE;
v1 = func_8012913C(kind);
if (v1 != 0) {
    ...uses of tp...
}
```
The uses are in the then-block. cse follows from block 0 through the branch into the then-block.

If I restructure:
```
if (v1 == 0) goto done;
...uses...
done:
```
The uses block has 1 predecessor (the fall-through from the branch). cse follows.

What if:
```
if (v1 != 0) {
    ...uses...
}
```
same.

What if there's a loop:
```
while (v1 != 0) {
    ...uses...
    break;
}
```
The loop creates a back-edge; cse would start fresh at the loop head. Hmm, but loop.c might optimize.

Hmm, what about `do { ...uses... } while (0);` inside the if? That's the C0535 trick — it splits an EBB. But do-while(0) is removed by jump1 (before cse? No: jump1 runs after cse1? Let me recall the pass order: jump (jump1) runs BEFORE cse? In gcc 2.7.2: ... jump, cse, ... Actually the order is: jump, cse, loop, cse2, flow, combine, sched, ... Hmm, no: `to_optimize`: jump_optimize (jump1), cse, loop, cse2, ... Hmm, I think jump1 is before cse.

Actually the standard gcc order: `jump_optimize` (jump1) then `cse` then `loop` then `cse2`... Let me check toplev.c.

If jump1 runs before cse, then do-while(0) would be removed before cse, so no effect. Hmm.

But C0535 says "do{}while(0) splits cse1 EBB" — so it DOES affect cse1. That means jump1 runs after cse1? Or the do-while creates a NOTE_INSN_LOOP that cse respects.

Let me check the pass order in toplev.c.

Actually, let me just try it empirically.

Let me generate candidates:
1. tp assigned later (after kind/v1 call)
2. tp assigned inside the if
3. do-while(0) around the uses
4. goto structure
5. tp assigned twice
6. tp via an intermediate u8* variable
7. `tp = (u16 *)((u8 *)&D_80126B58 + 0)` 
8. `tp = &D_80126B58[0]`
9. `tp = (u16 *)((s32)&D_80126B58)` 
10. reorder statements

Let me write the generator.

Hmm, the launder removal also affects the *pin* removal. Let me focus on the launder first: keep the pin, remove the launder, and see if any variant gives 0 (that would be PARTIAL:pin). Then separately handle the pin.

Actually — PARTIAL:pin would be a valid result! "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". So if I can get score 0 with the pin kept (launder removed), that's PARTIAL:pin.

And PARTIAL:launder if I can get 0 with the launder kept (pin removed).

So I don't need both fixed! I need at least one lever gone with score 0.

Let me focus on the launder removal with the pin kept (nolau, currently 18 with 82 insns). Fix the const-addr folding → maybe 0.

Hmm, but the pin removal (nopin, 15) is the other option: fix the 3-cycle allocation.

The launder removal is the more tractable (const-addr folding is a known pattern). Let me search variants with the pin KEPT.

Wait, but "PARTIAL:pin" means the win.c keeps only the pin. The kinds in <dir>/kinds are launder,pin. So PARTIAL:pin = launder gone, pin kept, score 0. Yes.

Let me work on nolau (pin kept).

The issue: without the launder, tp's constant address gets folded into the loads (3 extra insns). Let me try to prevent the fold with C structure.

Let me test candidates with the pin kept.

Ideas to prevent the constant fold:
a. Assign tp in a different block from the uses such that cse can't follow.
b. Make tp multi-set.
c. Use a second path.

Let me try (b) first: 
```
tp = (u16 *)&D_80126B58;
tp = (u16 *)&D_80126B58;
```
Hmm, cse would record the constant again.

What about assigning tp from an unknown but equal value:
```
u16 *p = (u16 *)&D_80126B58;
tp = p;
```
Hmm.

Let me think about the real mechanism differently: the target's tp is in a register because... the launder's asm output makes tp's value unknown to cse. What C construct makes a variable's value "unknown"? A function call returning it, or a load from memory.

What if `tp` is loaded from a global pointer? No, the value must be &D_80126B58.

Hmm, unless... wait. What if the original source used the address of a local or a struct? No.

Hmm, what about `tp = (u16 *)((s32)&D_80126B58 & ~0);`? The `& ~0` folds.

OK, what about making the *uses* not directly addressable: e.g., `tp[7]` where tp is cast through a union? The RTL would still be (mem (plus (reg tp) 14)).

Let me try the structural approaches empirically.

Actually — here's an idea I like: assign tp inside a conditional that cse can't fold:
```
tp = (v1 != 0) ? (u16 *)&D_80126B58 : (u16 *)&D_80126B58;
```
jump1 might merge. But if the two arms differ syntactically... 

Hmm, what about:
```
if (r0 & 1) {
    tp = (u16 *)&D_80126B58;
} else {
    tp = (u16 *)&D_80126B58;
}
```
Both arms the same → jump1 merges into one.

Hmm.

What about a loop that assigns tp:
```
do {
    tp = (u16 *)&D_80126B58;
} while (0);
```
Hmm.

OK, let me think about cse's `qty_const`: a pseudo holding a constant. cse folds it into a use. To prevent, cse must not know it. 

What if the assignment is `tp = (u16 *)((u32)&D_80126B58);`? A cast through u32. cse sees a symbol_ref cast — might still be constant.

What if `tp = (u16 *)&D_80126B58 + 0;`? Pointer arithmetic with 0 → folds.

Hmm.

What if the address is `&D_80126B58` but D_80126B58 is declared as an array `u16 D_80126B58[]` and we use `tp = D_80126B58;`? Same.

Let me look at how other shards cracked cse-const-addr launders. From moves.md:
- `launder | func_801497A8 | WALL cse-const-addr — cse: single-set const addr r73 folded into lone use lbu 73(sym) even past a 2-use join label; s1 never held`
- `launder | func_8017CF48 | WALL cse-const-addr — tp=D_801274F0 const sym ptr rematerialised lui+lh per use; launder kept it in s0; pin removal shifts base s2->s0, frame 44 vs 48; best 46`

So cse-const-addr is a documented WALL with a launder. Hmm. "even past a 2-use join label" — so even a join label doesn't stop it.

Hmm. But the moves also have MATCHes for const-addr launders:
- `launder | func_801A31CC | MATCH — pointer reuse: a1 = (u8 *)link; *(s32 *)a1 = 0; keeps the store base in the link reg`

Hmm, that's pointer reuse.

- `launder | func_8018C2D8 | MATCH — reuse m for next ptr (m = s1+0xD0; dv = m) and m1 for col: reassignment kills the cse sym class`

"reassignment kills the cse sym class" — so a reassignment of the pointer kills the constant class. Let me think: if tp is reassigned to a *different* value before the uses, cse's class is killed. But then the value would be wrong.

Hmm, "m = s1+0xD0; dv = m" — reassigning m.

Hmm, what if tp is assigned from a computed base that cse can't constant-fold? Like `tp = (u16 *)((u8 *)&D_80126B58 + (s4 - s4));`? Hmm, s4-s4 = 0; combine might fold.

Hmm, what if `tp = (u16 *)((s32)&D_80126B58 + (r0 & 0))`? `r0 & 0` → 0, folds.

Hmm.

Let me look at the target's assembly again: `lui s3,0x0; addiu s3,s3,0` — tp is materialized once. So tp is a register.

Hmm, what if the ORIGINAL source had tp as a parameter or a global? No.

OK, let me just try a batch empirically. If nothing works, record the wall.

Given time, let me try ~15 variants with the pin kept.

Actually, let me reconsider: the nopin body (launder kept) scores 15 with the right insn count (79). The remaining is a 3-cycle. If I could fix the 3-cycle, that's PARTIAL:launder. The 3-cycle is s1→s3, s3→s2, s2→s1.

Hmm.

OK, let me try both: a batch of launder-replacement variants (pin kept) and a batch of statement orders (nopin).

Let me write the generator for the pin-kept launder variants.

Actually, let me time-box: it's 17:22ish. Let me do one batch of ~12 and then record.

Let me write it.
