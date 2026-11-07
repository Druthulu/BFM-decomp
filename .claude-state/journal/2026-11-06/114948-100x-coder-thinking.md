---
ts: 2026-11-06T18:49:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wUheNTdk7v5sLjRhEV4M
---
The .greg RTL (after global alloc): insn 14 sets (reg 3 v1) = symbol; insn 17 sets (reg 7 a3) = (reg 3 v1). So 74→$3 and 76→$7 in the actual RTL.

But the dispositions line said "74 in 7 76 in 3". So the dispositions line must be misread: "72 in 4 73 in 6 74 in 7 75 in 5 76 in 3" — hmm, maybe the dump_global_regs prints `%d in %d` = regno in renumber. 74 in 7 means pseudo 74 → hard reg 7. But the RTL shows 74 → $3.

Contradiction within the same dump. Unless the dispositions are printed BEFORE the renumbering of the RTL? In global_alloc, dump_global_regs is called after allocation, and the RTL shown is... hmm, maybe the RTL printed in the .greg dump is the *pre-allocation* RTL? No, it shows hard regs.

Hmm, wait: maybe `reg_renumber` vs the actual assignment differ because reload reassigned? The .greg dump is emitted after global_alloc but the RTL printed is after `reload`? The pass order: global_alloc calls reload() at its end; the .greg dump is printed by global_alloc before reload? Actually `dump_global_regs` is called at the end of global_alloc, after the allocation and before reload. The RTL dump (print_rtl) in the .greg file shows the RTL *with* reg_renumber applied? The regs in the dump show hard reg numbers (3, 7), which come from reg_renumber.

So: pseudo 74 → reg 3 per the RTL, but the dispositions say 74 in 7.

Unless the dispositions list is sorted differently: "72 in 4  73 in 6  74 in 7  75 in 5  76 in 3" — this is `for (i = FIRST_PSEUDO_REGISTER; i < max_regno; i++) if (reg_renumber[i] >= 0) fprintf("%d in %d", i, reg_renumber[i])`. So 74→7, 76→3.

But the RTL shows 74 as $3 and 76 as $7. The RTL printing uses `reg_renumber` too (print_rtx maps pseudo → hard reg if reg_renumber >= 0)? Hmm, in print_rtx, if `reg_renumber` is non-null and REGNO >= FIRST_PSEUDO_REGISTER, it prints the renumbered reg. So both should agree.

Unless the .greg dump's RTL section is printed from a *different* function state... I'm confused. Let me look at the .lreg dump (local-alloc output) for the same insns. Local-alloc assigns block-local pseudos; 74/76 are global (not in .lreg's table?). The .lreg dump shows the RTL with local regs only.

Hmm, actually, wait: maybe the .greg dump's RTL was printed with the OLD reg_renumber (from local-alloc), and the dispositions with the NEW one? That would be a dump artifact. The .s is authoritative: `la $3; move $7,$3`.

So the candidate's actual code: the symbol → $3 (v1's role in the target? or a7's?).

Let me settle which register plays which role in the candidate vs target:
- Candidate asm: $3 = the pointer used for `lhu 0($3)` and `sh 0($3)` (the "current" pointer = v1 in the source), $7 = the pointer returned (`move $2,$7`) and incremented alongside.
- Target asm: $3 (v1) = lhu 0(v1), sh 0(v1)?? Let me re-read the target:

```
e74: lui a3,0
e78: addiu a3,a3,0     ; a3 = &D_8011FD10
e7c: move v1,a3        ; v1 = a3
e80: li a1,832
e84: lhu v0,0(v1)      ; v0 = *v1
...
e94: lw v0,8(a0)
...
eac: sh v0,0(v1)
...
f08: addiu a3,a3,104   ; a3 += 0x68
f0c: addiu v1,v1,104   ; v1 += 0x68
f10: addiu a2,a2,1
f14: slti v0,a2,20
f18: bnez v0,e84
f1c: addiu a1,a1,104
f00: j f24; f04: move v0,a3   ; return a3
```
So target: $3 (v1) = the current pointer (lhu/sh); $7 (a3) = the returned pointer. Same roles as the candidate! The only difference is the *initialization*: target `a3 = symbol; v1 = a3` (symbol first into $7), candidate `$3 = symbol; $7 = $3` (symbol first into $3).

So both end up with the same roles; only the init copy direction differs. The fix: make the symbol materialize into a7 (which is $7 in the target) and then copy to v1. In the candidate, a7 got $3 and v1 got $7 — but the roles show the current pointer = $3 = v1's role. Hmm, wait: in the candidate, the *current* pointer is $3, and the returned pointer is $7. In the source, v1 = the current pointer and a7 = the returned pointer. So candidate: v1=$3, a7=$7. Same as target!

Then why does the init go `la $3; move $7,$3`? If a7=$7 and v1=$3, the init should be `la $7; move $3,$7`. The candidate's asm is the opposite, meaning at the init, the registers are swapped: the symbol goes into $3 (which later becomes the current pointer) and is copied to $7.

OH. I see: the source is `a7 = &D_8011FD10; v1 = a7;`. The candidate assigned a7→$3 and v1→$7 initially, but then the *loop* uses $3 for v1's role and $7 for a7's role?? That can't be — the registers are fixed per pseudo.

Unless the .s I read is from a *different* compile than the .rtl dump (the t2.s might be from an earlier run in the same dump dir?). The dump dir was rm -rf'd and recreated, so all files are from the same run.

Hmm, let me re-examine: in the candidate's asm:
- $3: lhu 0($3), sh 0($3), addu $3,$3,104 → the current pointer = v1.
- $7: addu $7,$7,104, move $2,$7 → the returned pointer = a7.
- init: la $3, D_8011FD10; move $7,$3 → the symbol into $3 (v1), copied to $7 (a7).

So the C source `a7 = symbol; v1 = a7;` was compiled as `v1 = symbol; a7 = v1`?! That would be wrong semantics... unless the compiler proved a7 and v1 are equal and assigned the symbol to whichever register it liked: `v1 = symbol; a7 = v1` is semantically equivalent since a7 and v1 are equal thereafter.

Right! The compiler (cse/regalloc) can swap which pseudo gets the symbol since they're copies. The RTL: insn 14 (74 = symbol), insn 17 (76 = 74). If 74→$3 and 76→$7, then a7=$3 and v1=$7. But the loop shows the current pointer in $3 = a7, and the return pointer in $7 = v1. But the return is `return a7` and the loop increments both equally, so returning v1 would be equivalent! The compiler could have swapped the roles semantically (both are equal). So the actual assignment: a7=$3, v1=$7, and the return `move $2,$7` returns... v1 ($7)? But the source returns a7. Hmm, since a7 and v1 are equal, returning v1 is fine.

Wait, but the target returns a7 ($7) and the current pointer is v1 ($3). The candidate returns $7 too. So the *values* are the same. The only diff is which pseudo is in which register and thus the init direction.

OK so the semantic is fine. The diff is just the init copy direction: candidate `la $3; move $7,$3` vs target `la $7; move $3,$7`.

To flip: we need a7 in $7 and v1 in $3 with the symbol materialized in a7. The candidate's allocation gave a7=$3, v1=$7.

Hmm, but the dispositions said 74 in 7, 76 in 3 — the opposite of the asm. So the dispositions are unreliable here (or I misread the dump). Let me trust the asm.

Now: how to swap? The allocno order: 75 (a6, pri 28333), 76 (v1, 20000), 72 (a0, 18000), 73 (a5, 11666), 74 (a7, 5833).

Dispositions (whatever they mean): 75→$5 (a1), 72→$4 (a0), 73→$6 (a2), and 74/76 → $3/$7.

The target wants: a6 = $6 (a2), a5 = $5 (a1), a0 = $4, v1 = $3, a7 = $7.

In the candidate: a6 (75) → $5? The asm: `li $6,8` — the loop counter a6 is in $6! (asm line: `li $6,0x8`). And `li $5,0x340` = a5 in $5. So a6=$6, a5=$5 — matching the target. And a0=$4 (the loads lw 8($4)). So the only difference is a7/v1 = $3/$7 vs $7/$3.

So the allocnos: 75 (a6) → $6, 73 (a5) → $5, 72 (a0) → $4, and 74/76 → $3/$7.

The target: 74 (a7) → $7 and 76 (v1) → $3.
The candidate: 74 (a7) → $3 and 76 (v1) → $7 (per the asm).

The allocation order is 75, 76, 72, 73, 74 (by pri): 
- 75 (a6, pri 28333) → first: prefers? none → lowest free = $2? But the asm shows a6=$6. Hmm, the order and the conflicts matter: 75 conflicts v0,v1,sp. $2 (v0) is used by the block-local temps (r79 etc. → $2). $3, $4... hmm.

Let me get the real dispositions from the .lreg (local-alloc output) and the .greg order. This is getting confusing because the .greg RTL and dispositions disagree. Let me look at the .lreg dump (which shows local-alloc's assignments) and the .s.

Actually, the .s is the ground truth: a6=$6, a5=$5, a0=$4, v1=$3? No wait — in the asm, the current pointer (v1's role) is $3. Is that v1 or a7? The RTL says 76 (v1) → the loop pointer. The asm's loop pointer is $3. So v1=$3 and a7=$7. That MATCHES THE TARGET!

But then the init: `la $3` (v1 = symbol) and `move $7,$3` (a7 = v1). The source: a7 = symbol; v1 = a7. The compiler swapped: v1 = symbol; a7 = v1. Semantically equal.

So the candidate has v1=$3 and a7=$7 (target's roles), but the init order is v1-first vs the target's a7-first. Since the source order is `a7 = &D_8011FD10; v1 = a7;`, the compiler kept the *statement* order but assigned... hmm, the RTL insn 14 sets 74 (a7) and insn 17 sets 76 (v1). The .s shows insn 14 → $3 and insn 17 → $7. So a7=$3, v1=$7. Then the loop's current pointer is v1=$7? But the asm's loop pointer is $3.

I'm going in circles because the RTL and asm seem inconsistent. Let me carefully map the asm to the source:
- `lhu $2,0($3)` = `v0 = *v1` (source: v0 = v1; if (*v0 != 0)). The RTL: insn 27 (77 = 76), insn 30 (78 = mem(77)), insn 31 (79 = zero_extend(78)). So the load's address is 77 ← 76 = v1. The asm's `lhu $2,0($3)` → $3 = v1.
- `sh $2,0($3)` = `*v1 = *a0` → $3 = v1. ✓
- `addu $3,$3,104` = `v1 += 0x68`. ✓
- `addu $7,$7,104` = `a7 += 0x68`. So a7 = $7.
- `move $2,$7` = `return a7`. ✓

So: v1 = $3, a7 = $7. Now the init: `la $3, D_8011FD10` sets $3 = v1 = symbol; `move $7,$3` sets a7 = v1. So the compiler emitted `v1 = symbol; a7 = v1;` — the reverse of the source order!

But the RTL (from .rtl dump) is: insn 14 sets 74 (a7) = symbol; insn 17 sets 76 (v1) = 74. So a7 gets the symbol first. With a7=$7 and v1=$3, that's `la $7; move $3,$7`. The asm shows the opposite.

Therefore the RTL/asm mismatch means the .rtl dump I read is from... wait, the .rtl dump shows `(set (reg/v:SI 74) (symbol_ref))` and `(set (reg/v:SI 76) (reg/v:SI 74))`. The .greg RTL shows `(set (reg/v:SI 3 v1) (symbol_ref))` and `(set (reg/v:SI 7 a3) (reg/v:SI 3 v1))`. So after global allocation, 74→$3 and 76→$7. So a7=$3, v1=$7 per the RTL.

But the asm's loop pointer (v1's role, from insn 30's address 77←76) is $3 → v1=$3. Contradiction with 76→$7.

Unless insn 30's address is 77 and 77 is a local pseudo that got $3, and 76 (v1) is $7! Let me check: insn 27 `(set 77 (reg 76))` — a copy of v1 into a local temp 77; insn 30 `(set 78 (mem (reg 77)))`. So the load uses temp 77 = v1's value. If v1=$7 and 77=$3, the copy `move $3,$7` would appear... but the asm has no such move! Hmm, unless 77 was coalesced (copy) and the load uses $7 directly. The asm: `lhu $2,0($3)` — the address is $3.

So the load's address register is $3. If 76 (v1) = $7 and 77 = $3, there'd be a `move $3,$7` (or the copy coalesced). Hmm.

I think the RTL dump and the .s are genuinely inconsistent, which suggests the .greg RTL dump is printed with reg_renumber from a *different* stage. Let me stop relying on the dumps and use the empirical asm: the candidate's asm differs from the target ONLY in the first 3 instructions (the symbol's destination register and the copy direction), and in the target the symbol goes to $7 (a3) first.

So: I need the symbol materialized into $7 and the copy into $3. In C: `a7 = &D_8011FD10; v1 = a7;` produces the symbol → the register of a7, copy → v1. So the target has a7=$7, v1=$3. The candidate has a7=$3, v1=$7 (per the asm's init) — but the loop shows v1=$3.

Ugh, the candidate's init `la $3; move $7,$3` means: the symbol → $3 and the copy → $7. If a7=$7 and v1=$3 (as the loop shows), then the RTL's insn 14 (a7 = symbol) should write $7. It writes $3. So the RTL insns must have been swapped: i.e., the compiler assigned the symbol to v1 and the copy to a7 — which means the *pseudos* 74/76 are a7/v1 but the assignment is 74=$3, 76=$7... and the loop uses 76 ($7) as the address? But the asm's address is $3.

I clearly can't reconcile the dumps; let me instead trust the score diff and try C-level variations. The diff says only 5 register substitutions: 4 places where mine uses v1 where target uses a3, and 1 where mine uses a3 where target uses v1. Hmm, that's more than the init: "v1->a3 x4, a3->v1 x1". Let me get the full diff to see all the mismatched insns. dt.sh with a bigger tail.
