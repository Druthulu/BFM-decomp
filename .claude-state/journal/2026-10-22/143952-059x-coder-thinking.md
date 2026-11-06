---
ts: 2026-10-22T20:39:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1wROa7sZXn9pIBJEx9To
---
Target confirms: `it` (D_80120194) in v1 stays live through the copy path (`move a1,v1` at 4660). And the loop uses v1 for the *second* base (D_801202A0) after reassignment at 4664.

So the source must use `it` for the first base and *another variable* for the scan pointer in the loop, OR the same `it` but the compiler couldn't fold... Actually if `it` is reassigned at `test:`, the first value is dead at `copy:` → fold. The target keeps it live → the copy path must use the *first* it. With one variable `it`, the copy path after the reassignment would use the new it (wrong semantics? no — the reassignment happens at test: before copy is reached; the C's `copy: p = it` uses the *current* it = D_801202A0, which would be wrong). Hmm! Look at the C: at `test:` it = D_801202A0, then `if (it == p) goto zero; body: if (*(u16*)it == 0) goto copy;` — at copy, it = D_801202A0. But `copy: p = it;` then p = D_801202A0 and goto found. Hmm, that's the C's semantics: if the scan finds a zero at the base pointer itself... wait no: `copy: p = it` with it = the scan pointer at that moment (D_801202A0 initially, then incremented). So copy: p = it (the current scan pointer). That makes sense: if *(u16*)it == 0, p = it (the found slot).

So `it` at copy IS the current scan pointer. Then why does the target keep the FIRST it (v1=D_80120194) live to `copy: move a1,v1`?

Look at the target's code again: at 4660 `move a1,v1` — v1 at that point... The copy path is reached from `beqz v0, 465c` (j to 465c → `j found` with a1 = ... wait, 465c is `j 4694` (found); the instruction at 4660 is `move a1,v1`, which is in the *delay slot* of the j at 465c! So the `move a1,v1` executes as the delay slot of the jump to found. So copy: p = it where it = v1 = the current scan pointer. And the `j 4664` at 4654 (goto test) has the delay slot `addiu a1,v1,25996` (p = it + 0x658C). So v1 = it (D_80120194 initially, then reassigned to D_801202A0 at 4664).

So the target's `it` is ONE variable, reassigned at test. And the first `it + 0x658C` is computed as `addiu a1,v1,0x658C` (not folded into a constant) because... gcc's cse did NOT fold `it + 0x658C` into the symbol constant! In mine it did (lui a1, symbol+0x658C directly).

Wait, mine: `lui a1,0x0; addiu a1,a1,25996` — the relocation shows R_MIPS_HI16 D_80120194 and the low part 25996 = 0x658C. So gcc folded symbol+0x658C into a single lui/addiu. The target computes `lui v1; addiu v1, lo(sym)` then `addiu a1,v1,0x658C` — a two-step add.

Why would gcc not fold? Because in the target's source, `it` is *not* a constant expression at that point — e.g., `it` is declared as a `s32` assigned from `(s32)D_80120194` and then `p = it + 0x658C`. cse can fold a constant. Unless the assignment `it = (s32)D_80120194` is followed by something that blocks cse (the launder in the src def!). Yes — the launder is exactly what stops cse folding `it` into `p = it + 0x658C`.

So this item's launder has a similar effect. Lever-free, we need `it` to be a real register value: since `it` is used at `copy:` (live), gcc keeps it in a register (v1) and computes p = it + K with addiu — but only if it doesn't fold the constant. The folding happens because cse knows it = constant.

In the target, it = v1 (a register holding the symbol). So the target's source has `it` as a non-foldable value. Since it's live to `copy:`, maybe the compiler must keep it in a register — and cse would still fold `it + K` into a constant (the fold is valid regardless of liveness; `p` is a separate variable). Then at copy, `p = it` needs it in a register — the target has v1.

Hmm, in mine (gen_base), `it`'s first value is dead (reassigned at test before copy can use it — the compiler's dataflow sees the reassignment dominates copy), so cse folds and it dies.

But in the target, the compiler kept it live — meaning the *CFG* has a path from `p = it + 0x658C` to `copy: p = it` where it wasn't reassigned. Look at the C: `goto test;` jumps to test which reassigns it. So all paths to copy pass through test. Unless the source's structure differs: maybe there's no `goto test` and the test block is entered differently.

Wait, look at the target's code: 
- 4654: `j 4664` (goto test) with delay `addiu a1,v1,0x658C` (p = it + K)
- 4658: `addiu a1,v1,25996`?? The listing shows 4654: j; 4658: addiu a1,v1,25996 (delay slot); 465c: j 4694; 4660: move a1,v1 (delay slot); 4664: test block.

Hmm, the objdump order is confusing: 4654 j 4664, delay slot 4658 addiu a1,v1,25996; then 465c j 4694 (found), delay slot 4660 move a1,v1; then 4664 test.

So the else branch: it=v1=D_80120194; p=a1=it+K; j test. The copy block (465c) is reached from the loop's beqz (467c: beqz v0, 465c). At that point v1 = the current scan pointer. So `copy: p = it; goto found` → a1 = v1, j found.

So the compiler DID keep it (v1) live and didn't fold `it + K`. Why not fold? Because `it` is live (used later), and cse... would still fold the *addition* into a constant for p. Unless the addition isn't `it + K` in the source but something else, e.g., the source computes p from a *different expression* like `p = (s32)D_80120194 + 0x658C`... that would fold too.

The target's `addiu a1,v1,0x658C` means the source is `p = it + 0x658C` with it in a register and NOT folded. cse folds `(plus (reg it) (const K))` only if it knows it's a constant (REG_EQUAL from `it = symbol`). In the target, `it = D_80120194` — a symbol constant. cse would know it. Unless the source spells it differently: e.g., `it` is loaded from memory? No, `lui/addiu v1` is the symbol address.

Hmm, maybe cse doesn't fold symbol+const additions in 2.7.2? Let me check: in mine, `lui a1,0x0; addiu a1,a1,25996` — the HI16 reloc is D_80120194 and the low immediate is 0x658C. That IS symbol+0x658C folded (the linker resolves lo16 of symbol + 0x658C... hmm, actually a HI16/LO16 pair with addend 0x658C: the relocation applies to the symbol; the 0x658C is added in the instruction, but the HI16 would need the carry from the low part. Since 0x658C < 0x8000, no carry issue. So yes, folded).

So in mine cse folded `it + K` where it = symbol. In the target it didn't. The launder prevented it. Without the launder, is there another way? The `it` variable is live; cse's constant folding of an add with a live operand... it still folds into p (a new value) — folding doesn't kill it.

So we need `it`'s value to not be a known constant. Real C: make `it` come from a non-constant expression. E.g., `it = (s32)D_80120194;` — a symbol address cast to s32. Constant.

Hmm, what if `it` is declared as a pointer? `u16 *it = (u16 *)D_80120194;` then `p = (s32)it + 0x658C`? Still constant.

What if `it` is `(s32)(u16 *)...`? no.

What if the source reads the address from a *variable that's used elsewhere*: e.g. `base` in the other branch... no.

What if `it` is assigned inside a *loop* or after a call? no.

Hmm, what about making `it` a *parameter-like* value: `it = a0 - a0 + (s32)D_80120194;`? Identity arithmetic, folded.

The prior coder tried 35 variants, all ≥4. This is the cse-const-addr wall (already a tag). Let me look at the best residual more carefully — 4 score, 52 ins: only the register pair issue (a1↔v1) and the fold. Mine at insn 21-24:
```
21 lui a1,0x0
22 addiu a1,a1,25996
24 nop
```
target:
```
21 lui v1,0x0
22 addiu v1,v1,0
24 addiu a1,v1,25996
```
So the target has 3 insns there (lui, addiu, addiu) and mine has 2 (lui, addiu) + nop. Wait, insn 24 in mine is a nop (a delay slot) and in the target an addiu. Actually the target's j at 4654 has its delay slot filled with addiu (line 4658), while mine has nop. So mine's p = it+K was folded into the lui/addiu and there's nothing to fill the delay slot.

So the residual = the fold. If I can keep `it` live as a value... 

Idea: make `it` live by using it at `copy:` in a way the compiler can't see is dominated by the reassignment. E.g., make the `test:` assignment conditional or move the reassignment so that a path to copy doesn't reassign it. But semantics must match the target: the target's copy uses the *current* it (the scan pointer), so the copy path must use the reassigned it.

Hmm, but the target's code keeps v1 across the reassignment — the same register, reassigned. The `addiu a1,v1,0x658C` is computed before the reassignment (in the else branch), where it = D_80120194. The compiler kept that value in v1 *because v1 is used at copy* — but copy uses the *new* v1. Wait, no: at 4660 `move a1,v1` in the copy path uses v1 = the current scan pointer (which was reassigned at 4664). So the compiler did NOT need the first it to be live! It just didn't fold the addition.

So the target's difference is purely the fold: `it + 0x658C` not folded. Why? Because in the target's source, the expression is not `constant + K`. Maybe it's `p = it; p += 0x658C;`? Same. Or `p = (s32)((u8 *)it + 0x658C);` — pointer arithmetic: `(u8*)it + 0x658C` — cse still folds.

OR the source might compute p differently: `p = it + 0x658C` where it is `(s32)D_80120194` but the *symbol* is used with a different base... 

Hmm, what if the source is:
```
it = (s32)D_80120194;
p = it + 0x658C;
```
and the target's compiler folded the *lui/addiu* into v1 for it, then addiu a1,v1,K — because it's LIVE (used at copy in the C, even though the compiler's CFG sees the reassignment...).

Wait, maybe the C's structure has the `test:` reassignment NOT dominating `copy:`. Let me re-read the C:

```
goto test;
copy:
    p = it;
    goto found;
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
body:
    if (*(u16 *)it == 0) goto copy;
    it += 0x10C;
    if (it != p) goto body;
zero:
    p = 0;
```
In this C, `copy:` is after `goto test`, so at copy, it has been reassigned (unless the goto test → zero path...). Hmm, but the compiler sees: entry to copy is from body (after test), so it's the new it. So the first it is dead → fold. And yet the target kept it!

Unless the target's source has `copy: p = it;` where `it` is a *different variable* than the loop's scan pointer. Let me check the target's code: at 4664 the test block sets v1 = D_801202A0. The loop uses v1 as the scan pointer. The copy path `move a1,v1` uses v1 (the scan pointer). So copy uses the scan pointer.

And the `addiu a1,v1,0x658C` uses v1 *before* the reassignment (v1 = D_80120194).

So the compiler computed p = it + K at the time it = D_80120194 (in the else block) — i.e., it kept the source structure `p = it + 0x658C` and did NOT fold. The fold would be legal but gcc didn't do it because... cse's constant folding: `it` has a REG_EQUAL note (symbol), and `p = it + K` — cse would substitute it → symbol + K. In mine it did. In the target it didn't.

What's different? Maybe in the target's source `it` is NOT `(s32)D_80120194` but something like `(s32)D_80120194 + 0`? no.

Or the source declares `it` as `u16 *` and p as `s32`; `p = (s32)it + 0x658C`? Hmm, pointer+int folding.

Or maybe the source is:
```
it = (s32)D_80120194;
p = it + 0x658C;
```
but with `it` being *volatile*? No.

Wait — maybe in the target, the `it` variable is the SAME as the loop pointer and the compiler's cse1 ran before... no.

Hmm, what if the target's source has the else branch like:
```
it = (s32)D_80120194;
p = it + 0x658C;
```
but `it` is used *between*: e.g. `if (it != 0)`? no.

Let me look at the launder in the src def: `it = (s32)D_80120194; __asm__("" : "=r"(it) : "0"(it)); p = it + 0x658C;`. The launder exists precisely to stop the fold. The src def also has a launder for the second `it = D_801202A0` (to stop folding of `it == p`? or the loop comparisons).

Lever-free, can we stop the fold with real C? The classic: make `it` a *different type* so the addition isn't a constant fold. E.g., `it` as `u8 *` and `p = (s32)(it + 0x658C)`. Folding still applies (address arithmetic on a constant).

Hmm, what about making the addition go through a variable that's not constant: e.g. `p = it + 0x658C` where `0x658C` comes from a variable? `s32 off = 0x658C; p = it + off;` — cse folds off to the constant then folds the addition. Maybe not: cse might keep off as a constant and still fold. Test.

What if `it` is assigned from the symbol via a *pointer cast through a struct member*? Constant.

What if the source uses `D_80120194` as a pointer variable declared at file scope... no.

Hmm, what about the type of `it`: if `it` were `u32` and `p` `s32`, the addition is the same.

The prior coder tried gen_addr_* (cast variants), gen_decl_* (types: long, ptr, u32, ull), gen_bound_* (bounds), gen_use2_* (second uses). All ≥4.

Maybe the trick is that in the target, `it` is live because `copy:` uses it — i.e., the CFG doesn't reassign it on the path to copy. That happens if the source has the loop structured differently, e.g.:

```
it = (s32)D_80120194;
p = it + 0x658C;
goto test;
copy:
    p = it;
    goto found;
test:
    it = (s32)D_801202A0;
    ...
```
This is the C. Since test reassigns, copy's it is new.

BUT what if the C instead is:
```
it = (s32)D_80120194;
p = it + 0x658C;
goto test;
copy:
    p = it;
    goto found;
test:
    it = (s32)D_801202A0;
```
same.

What if the source uses TWO variables and the target's copy uses the *first* it? Then the target's copy would be `move a1, <first it reg>`, but the first it is in v1 which gets reassigned at test... The target's copy path uses v1 *after* the loop, and v1 = the scan pointer. If the source had two variables (base1 in v1, scan in v0?), the copy would use scan. Hmm, the target's test block reuses v1 for D_801202A0, so the first it's register was reused — consistent with the first it being dead.

So the target's first it IS dead, yet the addition wasn't folded. So the fold was prevented by something else: the launder. Lever-free?

The launder's role: `it` becomes an opaque register value, so `p = it + K` is an add. Without it, cse folds. This is exactly `cse-const-addr` (already a tag: "cse folds or substitutes a constant/absolute address the target keeps base-relative").

Since the prior coder spent 42-ish tries (the item has 35 gen files) and got best 4, and I have the same wall as the first item's family, I should try a few fresh ideas but be quick.

Fresh ideas for stopping cse's fold of `it + K` with real C:

1. `it` declared as a pointer `u16 *it`, and `p` computed as `p = (s32)it + 0x658C` — hmm, (s32)it then +: constant fold likely.

2. Use a *union* or a struct field access to make the value opaque? No.

3. Make `it` assigned from the symbol *through a memory load*: e.g. `it = *(s32 *)&D_80120194;`? That loads the *contents* at D_80120194, not the address. Wrong semantics.

4. Compute `it` as `(s32)D_80120194` and use it in a way that cse can't fold: e.g. `it = (s32)D_80120194; if (it) ...`? no.

5. The classic real-C opaque: use a `volatile` variable? A volatile read of a *local*? `volatile s32 it;` — a volatile local assigned a constant then read: gcc keeps it in memory, loads it → different code (lw from stack). Might actually produce `lui/addiu v1; sw v1; lw v1` — no.

6. Make the address come from `a0`: e.g. `it = (s32)D_80120194 + (a0 - a0);` — folded.

7. Use `p = it + 0x658C` where it is of type `u16 *` and p is `s32`: pointer arithmetic scales by 2! No, `(u16*)it + K` would add 2K. If the source used `(u8 *)it + 0x658C`, fine.

8. What about assigning `it` from a *function call result*? No.

9. Make `it`'s value depend on a runtime condition, e.g. `it = (s32)D_80120194;` inside an if-else where both arms assign the same constant? cse merges.

10. Use the `base` variable from the other branch? no.

Given the prior coder's 35 variants and the same wall family as func_8012C2D0 (already WALL with cse-const-addr), this is very likely the same wall. But before walling, note the item's budget: the prior coder's time on this item is unknown (the item dir has files from 07:13, the shard started 06:37 — the prior run did items in order: 8012B4B8 (10:06), 8012C2D0 (10:29), then 8012C750 and 801372B0 dirs are from 07:13 — so the prior coder actually started with those two at 07:13? Hmm, the timestamps: func_8012C750 dir 07:13, func_801372B0 07:13. Those were probably created early with the gen files. The prior coder's log says it finished func_8012C2D0 and carried func_8012B4B8; it likely did 8012C750 and 801372B0 *before*? No, the results.tsv only has 8012C2D0. The dirs at 07:13 suggest work happened then.

I can't know the prior tries for this item. The brief says "Then func_8012C750, func_801372B0" — no budget carry noted for them, so treat them as fresh (20-30 min each).

Let me look at the gen files to see what's been tried, then try a focused batch of new ideas. Let me check a few of the more interesting gen files (gen_z* are latest?). Timestamps would tell. Let me look at the diff for gen_base (best 4) and think about the cse fold.

Actually, a promising idea: the target's `addiu a1,v1,0x658C` computes p from it. If `it` is used *twice* in the source (once for p, once elsewhere), cse might keep it in a register. But the launder's purpose... The prior coder's gen_use2_* files tried "second uses" (cmp_self, cmp_other, copy, dead, dup_base) and got ≥4/11.

Another idea: make `it` a *global-scope* or *static* variable? No.

What about `it = (s32)D_80120194; p = it; p += 0x658C;`? Two statements: p = it (a copy), then p += K. cse: p = it (constant), p += K → fold. Same.

What if p is computed *before* it? no.

Hmm, what about making `it` a *pointer to a struct* and p = (s32)&it->field? no.

Let me look at what the target's source might be by considering the second branch (the `if` branch at the top): 
```
s32 base = (s32)D_80120194;
p = base + 0x6480;
```
The target for that branch: let me see the full target disassembly (first lines).
