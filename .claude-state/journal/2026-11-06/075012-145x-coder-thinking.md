---
ts: 2026-11-06T14:50:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vkiwT0oM9wK5ScCfo1VU
---
This is complex. Let me look at how cse's fold_rtx uses the recorded equivalence. The key: `record_jump_cond` adds a REG_EQUAL note and sets the register's equivalent constant. Then `fold_rtx` on the next comparison folds it.

For our case, after `bne t,5,after`, the fall-through records t == 5. Then `if (t != 3)` folds to `5 != 3` = true.

To prevent, I need cse to NOT record t==5 on the fall-through. `record_jump_cond` returns early if `do_not_record` is set (e.g., the operand is in memory/struct or volatile). Or if op0/op1 are already equivalent.

Hmm. What if `t` is marked as "in memory" (e.g., its address is taken)? Then `hash_arg_in_memory` is set and do_not_record -> no equivalence recorded. Taking the address of t would force it to memory (extra code), but maybe not if it's just `&t` used in a way that's optimized? Hmm.

Actually, wait. Let me reconsider. Maybe the fold is NOT cse but jump.c's `thread_jumps` or the `if` conversion. Let me verify by looking at the .cse dump (after cse1) and comparing the branch count with .rtl.

Let me count the branches in the case 5 region. The case 5 block in the RTL: let me find it. The target asm's case 5 starts at $L67. In the RTL, the case 5 code is after the switch dispatch.

Let me grep the .rtl and .cse2 dumps for the sequence of comparisons on the t register. The t register in the RTL is a pseudo (not 16). Let me find the pseudo.

Hmm. This is slow. Let me take a step back.

Alternative approach: maybe the crack is to change the C so the redundant check is on a value that's genuinely unknown. For example, instead of `if (t != 3)`, use `if ((t & 0xFFFF) != 3)` where t is s32 and the mask makes the value differ from the known 5? No, t==5 -> 5&0xFFFF=5.

What if the check is `if ((u32)t >= 4)`? Given t==5, it's true. The compiler would fold (5>=4). Hmm.

What if the check is `if (t - 3 != 0)`? Given t==5, 2 != 0 true. Folds.

All foldable given t==5.

The ONLY way is opacity. And real C can't make a local opaque without extra code.

Wait — unless the check is on a value derived from a FUNCTION CALL that the target already has. Look at the code after the t==5 block:
```
if ((func_800291B4(D_801802E4[t]) & 0xFF) == 0) goto call_45F;
```
This is after the if. If the `if (t != 3)` check were AFTER this call, the compiler couldn't fold (the call might change t? No, t is a local; a call can't change it unless its address is taken). Hmm.

Actually, a call CAN change a local if the local's address is passed to it or if it's a global. t is a local not passed. So the compiler knows t==5 across the call.

Hmm.

What if `t` is a GLOBAL variable? Then a call could change it, and the compiler couldn't fold. But making t global changes the code (loads/stores). The target uses t in a register.

OK, this is looking like a genuine WALL (flow-known-value / cse-jump-equiv). 

But wait — let me reconsider the target's structure once more. The target has `bne t,3,L73` which is redundant. The launder prevents cse from recording t==5. Is there a real-C way to prevent cse from recording t==5 on the fall-through of `bne t,5,after`?

Idea: make `t` "in memory" for cse's purposes by taking its address somewhere harmless. E.g., `s32 *pt = &t;` and never use pt. The compiler might optimize away pt (unused). Then no effect. If I use pt in a way that's optimized... hmm.

Idea: `t` is used in `D_801802E4[t]` (an array index) — that's a use, not an address-take.

Idea: make `t` a `volatile` — extra loads/stores.

Idea: use a struct field or a union to hold t, which cse treats as "in memory/struct" and refuses to record. Hmm! cse's `hash_arg_in_memory`/`hash_arg_in_struct` flags: if the operand is a MEM or a struct reference, do_not_record is set, and record_jump_cond returns early. So if `t` is loaded from a struct (e.g., `((struct *)&t)->field`), cse might refuse to record the equivalence.

But the target's t is a plain register (s0). If I make t a struct field, the code might change.

Hmm. Let me think about the "in_struct" flag: `hash_arg_in_struct` is set when hashing a MEM with MEM_IN_STRUCT_P. If t is a local variable in a struct... no.

OK, let me look at whether the fold is really cse by checking the dumps. Let me count the branches in the .rtl vs .cse2 for the case 5 region. If cse1 folded, the .cse dump has 2 branches where .rtl has 3.

Let me find the case 5 region in the .rtl dump. The switch is on idx. Case 5 corresponds to... let me find the `const_int 5` comparison. Hmm.

Let me instead just count `if_then_else` in the function across the dumps. Actually, let me compare the total insn count in .rtl vs .cse2. If cse folded a branch, the count drops.

Let me grep the .rtl and .cse2 dumps for the function and count `jump_insn`.

Actually, let me look at the specific branches. In the .cse2 dump, search for `(if_then_else (ne:SI (reg:SI` with `const_int 3`. The t register... let me find it. In the .cse2 dump, `const_int 3` appears at lines 627, 1286, 1369, 1518. Let me look at those.

This is getting long. Let me just accept that this is a WALL of the known class and record it. But first, let me try a couple more real-C ideas that might work:

1. Make `t` a `union`/struct field to trigger cse's do_not_record.
2. Use `t` via a pointer.
3. Restructure the switch to avoid the known-value propagation.

Actually, wait — the moves.md says the flow-known-value WALL was at G22 and the mask trick "keeps it but costs 1 andi (best 10)". So maybe for our case the mask trick keeps the check. Let me test v2 more carefully — v2 was `(t & 0xFFFF) != 3` and scored 4 (MIXED). Did it keep the check? The diff would show. Let me check v2's diff.

Actually, v2's diff was the same as c1's (4). Let me look at v2's asm to see if the andi appeared. If the andi appeared, the score would be different (COUNT). It's 4 (MIXED) with 279 ins = target. So the andi didn't appear (folded). So the mask didn't help.

Hmm.

Let me try the "in_struct" idea: make t a field of a local struct. E.g., declare `struct { s32 t; } ts;` and use `ts.t`. cse hashes `(mem (reg ts))`? No, a local struct is scalar-replaced by the compiler (it becomes a pseudo). So cse sees a register. Hmm.

What about taking the address: `s32 *pt = &t;` and using `*pt` in the check. The compiler might keep t in memory (extra loads) or scalar-replace. Let me test.

Let me test v10: `s32 *pt = &t; if (*pt != 3)`. And v11: make t `volatile`. And v12: use a union.

Actually, let me reconsider. The launder `__asm__ ("" : "=r"(t) : "0"(t))` has an output constraint "=r"(t). This makes t a register variable that's set by the asm. cse sees the asm as a set of t, invalidating the equivalence. The asm also forces t into a register (s0).

Real-C equivalent: a function call that returns a value assigned to t? `t = some_func();` — but there's no such call, and adding one changes code.

What about `t = t` after the branch? Identity (deleted before cse by jump.c's no-op move deletion? or flow's, which is after cse). Hmm — if the self-copy `t = t` is NOT deleted before cse, cse would see a set of t and invalidate. Then flow deletes it. But identity launders are FORBIDDEN by the brief ("identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack"). And `t = t` is a pure identity, definitely forbidden.

What about a non-identity dead set? `t = t | 0`? folds. `t = t + 0`? folds. These are identity launders anyway.

Hmm.

What about `t = (t & 0xFFFF)` where t is s32? This is NOT an identity (for negative t). It's a real operation that emits an andi. But maybe cse/fold can eliminate the andi in the specific branch context? Let me test v13: `t = t & 0xFFFF;` before the check.

Actually, v2 was the inline `(t & 0xFFFF) != 3`, which folds. But `t = t & 0xFFFF; if (t != 3)` might behave differently: the assignment is a real set (andi), cse sees it and invalidates t==5. Then the check `t != 3` can't fold. But the andi adds an instruction. Unless the andi is deleted as dead? No, t is used. So extra code. Score would be COUNT, not 0.

Hmm.

Wait — but maybe the target's `bne t,3` after the launder is exactly this: the launder is like `t = <opaque>`, and the compiler emits `bne t,3`. If I use `t = t & 0xFFFF`, the compiler emits `andi t,t,0xFFFF; bne t,3`. The target has just `bne t,3`. So the andi would be extra. Unless the andi is optimized away because the compiler knows t is (s16)a1 and thus in range? Hmm, if the compiler knows t is sign-extended s16, then `t & 0xFFFF` is NOT a no-op (negative values). But it might still emit the andi. Let me test.

Actually, the moves.md wall says the mask "keeps it but costs 1 andi (best 10)". So the mask adds an instruction. For us, that would be best ~5-6 (COUNT).

Let me think about whether there's a mask/operation that's a NO-OP for the compiler (folded away) but still a SET that cse sees. There isn't, because if it's a no-op the front-end removes it before cse.

Hmm, unless the operation is at the RTL level after cse... no.

OK, let me reconsider the problem from a different angle. Maybe the target's structure can be achieved by reordering the C so that the two comparisons are NOT in the same basic block. For example, if the `t != 3` check is in a block that's reached from a path where t isn't known to be 5, cse won't fold.

The target's `bne t,3,L73` is reached only from the t==5 fall-through. cse records t==5 on that fall-through. To prevent, I could make the check block have another predecessor.

Let me design:
```
if (t == 3) goto sel_054;
if (t == 5) goto check;
goto after;
check:
    if (t != 3) goto sel_094;
sel_054:
    sel = &D_8018C520;
    goto set_sel;
sel_094: ...
after: ...
```
Here `check` has one predecessor (t==5). cse records t==5 -> folds.

To give `check` two predecessors, route the t==3 path through it too:
```
if (t == 3) goto check;
if (t == 5) goto check;
goto after;
check:
    if (t != 3) goto sel_094;
sel_054: ...
```
Now `check` has two predecessors: t==3 and t==5. cse can't record a single value for t at the block start (it would need to merge). So `t != 3` can't fold! The emitted code: `beq t,3,check; bne t,5,after; check: bne t,3,sel094; sel054: ...`.

But the target is: `beq t,3,sel054; bne t,5,after; bne t,3,sel094; sel054:`. 

In my design, `beq t,3,check` where check is the `bne t,3,sel094` instruction. For t==3, executing `bne t,3,sel094` is false, so fall to sel054. So the t==3 path executes an extra (false) branch. The machine code: `beq t,3,Lcheck` where Lcheck = the bne insn. The target: `beq t,3,Lsel054` where Lsel054 is after the bne. So the branch TARGET differs (Lcheck vs Lsel054), which are different addresses. So the code differs.

BUT — maybe the assembler/compiler lays it out such that... no, the target explicitly has `beq $16,$3,$L70` where $L70 is `la $2,D_8018C520` (after the check). So the target skips the check on t==3.

In my design, the t==3 branch targets the check, not sel054. Different.

Hmm, unless the compiler optimizes `if (t==3) goto check; ... check: if (t!=3)...` by noticing that at check from t==3, the bne is false, so it could redirect `beq t,3,check` to `beq t,3,sel054` (skip the check). That's exactly the target's optimization! If the compiler does that, my design would produce the target code! And it wouldn't fold the check for the t==5 path (since check has two predecessors). 

Wait, but if the compiler redirects `beq t,3,sel054`, then at the `check` block, only the t==5 predecessor remains, and cse could then record t==5 and fold. Circular.

Hmm. But the passes are ordered: cse runs before jump threading. Let me just TEST the two-predecessor design. If cse doesn't fold (because of the merge) and jump.c redirects the t==3 branch, we might get the target.

Let me test v13 (two-predecessor check).

Also, let me test v14: make the check block have two predecessors by routing t==3 through it in a different way.

Let me write v13:
```
        if (t == 3) {
            goto sel_054;
        }
        if (t == 5) {
            if (t != 3) {
                goto sel_094;
            }
        sel_054:
            ...
```
I need to change the `goto sel_054` (t==3) to `goto chk` and add `chk:` before the `if (t != 3)`:
```
        if (t == 3) {
            goto chk;
        }
        if (t == 5) {
        chk:
            if (t != 3) {
                goto sel_094;
            }
        sel_054:
            ...
```
Hmm, the `chk:` label inside the t==5 block. And the t==3 goto targets it. Let me write this. But the C flow: if t==3, goto chk (inside the t==5 block), then `if (t != 3)` false, fall to sel_054. If t==5, enter the block, reach chk, `if (t != 3)` true, goto sel_094. Good.

But wait, the t==5 block also needs to be entered only when t==5. Let me write:
```
        if (t == 3) {
            goto chk;
        }
        if (t == 5) {
        chk:
            if (t != 3) {
                goto sel_094;
            }
        sel_054:
            sel = (u32)&D_8018C520;
            goto set_sel;
        sel_094:
            ...
        }
```
This should be semantically equivalent. Let me test v13.

Actually, there's a subtlety: the `if (t == 5)` block contains `chk:`. If t==3, we jump into the block at chk, skipping the `if (t == 5)` check. That's fine (goto into a block is allowed in C).

Let me test v13. If it produces the target structure, great.

Let me also test v14: two predecessors via a different arrangement.

Let me write v13 and score.
