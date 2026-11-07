---
ts: 2026-11-06T12:33:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ymktfFVUkt34YzoOL83Q
---
Now the register pairs are only a0/v0/v1 swaps — ret is in v0 already! So removing the early ret uses made ret get v0. Score 55, 257 vs 261 ins (we added 2 li v0,0 and... hmm 257 = 256+2-1?).

Wait, mine 257 vs 256 before: two `return 0` insns added but one insn removed? Anyway, the diff at 72: target has `j; li v0,10; li v0,42` (branch delay slots with the arm's li v0,N as the delay insn — target fills the `j STORE` delay slot with the `li v0,N` of the NEXT arm? Actually cross-jumping).

Interesting: target's `j 1e38` at 72 and `li v0,10` in the delay slot then `li v0,42`. This is the classic pattern where the `j`'s delay slot is filled from the fall-through (the next arm's li v0,10 gets executed then overwritten).

Hmm wait, that's the target: `j .L; li v0,10; li v0,42` — the delay slot insn is the next arm's `li v0,10`?? That's reorg's fill.

So the target's arms each: `li v0,N; j STORE` with delay filled by the next arm's li? That can't be right... Let me look at the target's actual asm around those arms.

Let me now think about the remaining differences. Let me get the full diff for c2 and look at the target asm region.

Actually, first: since `return 0` costs insns, maybe there's a better way to keep the early returns as `return ret` while ret still gets v0. Ideas: ret declared and *initialized* at decl: `s32 ret = 0;` → ret is defined at entry, so the live range doesn't start uninitialized... but it still spans from entry (the def at entry) to the first arm use? No: with a def at entry, the live range from entry-def to the first use (line 55) crosses the calls? The use at line 55 (early return) is before any call except func_8012CAE4 which precedes it. The live range entry→line 55 crosses the call at line 54? The def at entry (move/li) then the call at 54 clobbers v0 → so ret must be in a saved reg. Same problem.

So the early returns must not use ret. What if they use a *different* variable? Like `s32 r2 = 0; ... return r2;`? Then r2 is a separate pseudo in v0 and would emit li v0,0 at entry (an extra insn). Hmm, but maybe the target's early return leaves v0 as-is because the pseudo is v0 and uninitialized (no insn at all).

Wait — what if the early return is `return ret;` but `ret` is a *parameter*? No.

Hmm, what about: what if the early returns return the value of the preceding call? Like `func_8012CAE4(...); return ret;` where ret is never defined yet — in the target that's a no-op. 

Alternatively, what if the C has NO early returns but instead a structure like:

```
if (cond) { call; goto RET; }
```
where RET: `return ret;`? Same as now.

Hmm, hold on: what about making the early returns use a *different uninitialized variable* that also ends up in v0 without a copy? E.g. declare `s32 rv;` uninitialized and `return rv;` in the early returns. rv's live range: entry (uninitialized use) to... only those two returns. Both uses are at points where v0 is free? A pseudo used only at returns (before any def) → global-alloc: it's live from entry to the use, crossing calls → callee-saved. Hmm, same issue.

Unless... at the early return, `return rv` where rv is uninitialized: gcc might even warn/delete. Actually gcc may treat an uninitialized pseudo as having undefined value; it still allocates it.

But wait: with the *pin* gone and `return 0` we got ret in v0. With `return 0`, does the target have `li v0,0` at those spots? Target at 1a88-1a94: jal; j 1e3c; nop. No li. So the target truly has no instruction, meaning the returned value is a pseudo that is already in v0 and doesn't need initialization.

Alternatively, maybe the target C's early return is `return ret;` and the whole function's ret IS v0 because in the *target's* C, ret is defined before those returns? No, target's asm shows nothing set before them.

OK, alternative approach: keep `return ret;` in the early spots but make ret's live range not cross calls... impossible with an uninitialized use at entry.

So: is there a C form where an uninitialized local returned early gets v0? What if we *pin* nothing but the pseudo has only these uses... Let me test: c3 = c1 but with a separate uninitialized variable for the early returns:

```
s32 rv;
...
return rv;   (early)
```
vs `return ret`.

Actually hmm, wait. Maybe simpler: the target's early return may be `return ret;` where ret IS initialized by... no.

Let me think about gcc 2.7.2's global-alloc: it does have special handling for return values? Search global.c for "return". Actually in gcc 2.7.2, there's `regno_reg_rtx[RETURN_VALUE...]`... The relevant thing: in `expand_return`, for `return x`, gcc does `emit_move_insn(return_rtx, x)` — but there's an optimization: if x is a pseudo and the function's return value... Actually in stmt.c `expand_return`: 
```
if (GET_CODE(...)...
  /* If the value being returned is a register, we can just use it. */
```
There IS a special case: if the expression is a VAR_DECL whose rtx is a pseudo, gcc uses `expand_value_return` which emits a move. But there's also the "tail recursion" case.

Hmm, but note: `emit_move_insn(return_rtx, x)` where return_rtx is (reg:SI 2) and x is a pseudo — the move is emitted. Later, the reload/global-alloc... The move `v0 = pseudo` might be coalesced away by local-alloc/global-alloc if the pseudo is allocated v0! That's the key: the pseudo gets v0 if it doesn't conflict with anything else, and then the move is deleted. That's exactly what happened: with the pin, ret=$2 and the moves disappeared.

So without the pin, we need global-alloc to choose v0 for ret. The choice: global.c computes priorities; for pseudos with short live ranges it uses call-clobbered regs. If ret's live range from entry crosses calls, it must be saved.

Now: which C form gives ret short live ranges only? Each arm's `ret = N` → use at STORE. Between the def and the use there's no call. So all live ranges are short, except the uninitialized entry use.

Hmm, but with `return 0` we removed the entry use, and ret got v0. So the fix is: get rid of the early `return ret` uses. The question is what to return there with no insn cost.

Idea: `return ret;` → but move the early return through the STORE label: `ret = <something>; goto STORE;`? That would add insns.

Idea: the early return could be `return param_1;`? That emits move v0,a0 — target has none.

Hmm, what if the early return is a *conditional* returning the call's result? Like `return func_8012C1B8();`? no.

Wait, let me look at the target's second early return: `beqz a0, 1e3c` — a0 holds ptr. And the first: `bnez v0, 1a98; nop; jal func_8012CAE4; nop; j 1e3c`. Hmm interesting: at 1a78-1a84: `lui s0,0; addiu s0,s0,0` then `bnez v0,1a98` with `nop` delay.

So the target really does `j 1e3c` right after the call with no value setup → the returned pseudo is v0 and dead/uninitialized.

Alternatively the C could be `return ret;` where ret is never assigned before — that's what orig has. Since we can't keep the pin, we need another way to make the entry-live range not cross a call... 

What if ret is declared inside the `if` blocks... no, it's shared with STORE.

New idea: what if we make the early returns return a *different* variable that is initialized to the same v0 the call left? No.

Hmm, what about this trick: make the early return `return ret;` where ret is assigned from a call's return value right before? The target at 1a90-1a94: after jal func_8012CAE4, `j 1e3c` (nop delay). func_8012CAE4 is void; v0 after it is whatever.

OK so maybe the target's C early return isn't `return ret`. Perhaps it's:

```
if (cond) {
    func_8012CAE4(param_1);
    return param_1;   /* ? */
}
```
No — that would move v0,a0.

Or maybe the target function's C returns nothing meaningful there and the banked source is a decomp guess. Since the *target* is the banked src itself (score compares against the compiled src which is byte-identical to the original .s), the C we write must produce the same asm. So we need a C form.

What about `return ret;` with ret declared as `register s32 ret;`? `register` keyword without asm — is that allowed? The constraint says "no `register` vars". So no.

What if ret is a `s16`? Hmm.

What if the two early returns use a *second* variable `s32 rv;` (uninitialized) declared at block scope? Then rv's live range is entry→use, crossing calls → callee-saved (s0?). Hmm, but does it? rv is used at line 55 (return) and line 60 (return). Its live range from entry to line 55 crosses the call at line 54 (func_8012CAE4). But wait — does the live range really start at entry? For an uninitialized pseudo, yes (live-in at entry).

But hold on: in the target, is there a callee-saved reg saved for it? The prologue saves s0 and s1. s1 = param_1, s0 = ? At 1a78: `lui s0,0; addiu s0,s0,0` — s0 = a constant address (probably &D_801ED5F0 or similar used in the arms: `addu v0,v0,s0`). So s0 is used as a base address register, not for ret. So no reg was spent on the early return value in the target.

So the early returns in the target's C must be `return ret;` with ret in v0, i.e. ret's live range... 

Wait! Maybe with `return ret` where ret is uninitialized, gcc 2.7.2 might optimize the uninitialized use to a `const0`? No, it produced a move in my c1.

Alternatively, maybe the target C uses a different construct entirely for those two early exits: e.g. `if (...) { func_8012CAE4(...); }` and then... no, the target does `j 1e3c` (jump to the epilogue).

Hmm, `j 1e3c` = jump to the return epilogue. What if the C were `goto STORE;` with ret unassigned? Then STORE does `unk2 = ret; return ret;` → the store would emit `sh v0,2(s1)` — target doesn't have that at 1a90.

What if the C is `return ret;` where ret is a *global* variable? Then it'd be lw v0,sym; j. No.

Hmm, what about the possibility that the C has ret as the function's return value through a "value return" that gcc treats specially: in stmt.c expand_return there's:

```
  /* If the result is a pseudo-register, and the return register is not
     used... */
```
Let me actually read stmt.c expand_return in the 2.7.2 source to see if there's a rule that makes the pseudo get the return reg.

Actually there IS a well-known gcc behavior: `expand_return` calls `expand_value_return(val)` which, for a pseudo `val`, does:
```
  /* If VAL is a REG, we can return it directly... */
```
Let me read the source.
