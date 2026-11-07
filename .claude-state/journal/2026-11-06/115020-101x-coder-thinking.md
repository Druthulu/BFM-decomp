---
ts: 2026-11-06T18:50:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_S280u5w4jBYNtemGSj9t
---
Only one replacement group (insns 1-3), but the count says v1->a3 x4 and a3->v1 x1. The diff shows only the first group; maybe the tool shows only the first N groups (tail 40 should show all). The "count 4" and "count 1" refer to register-pair substitutions across the function: mine uses v1 where the target uses a3 in 4 places (the init: lui, addiu, and 2 more?) and mine uses a3 where target uses v1 in 1 place.

Since the diff only shows one hunk (insns 1-3), maybe the other substitutions are within those same insns or the tool collapses. Hmm, "replace mine[1:4] target[1:4]" shows 3 lines. The pairs count: v1->a3 x4 = 4 instruction operands where mine has v1 and target a3; a3->v1 x1.

The 4 v1->a3 could be: lui v1 (1), addiu v1,v1 (2 operands: dest + src = 2), move a3,v1 (1) = 4 operands. And a3->v1 x1: move a3,v1's dest. Yes! So all the mismatches are within the first 3 insns: mine `lui v1; addiu v1,v1; move a3,v1` vs target `lui a3; addiu a3,a3; move v1,a3`. Everything else matches — including the loop using v1 for the current pointer and a3 for the return pointer in BOTH.

Wait, that means: in mine, the symbol is materialized in $3 and copied to $7; in the target, materialized in $7 and copied to $3. And the rest of the function uses the same registers ($3 for the current pointer, $7 for the returned). So in mine, a7 = $3?? But the rest uses $7 for a7's role (addu $7,$7,104 and move $2,$7). Hmm, if a7=$3 in mine, the `addu $7,$7,104` would be v1's increment.

Let me map mine's roles:
- mine insn 1-3: $3 = symbol, $7 = copy.
- Then the rest (matching the target): `lhu $2,0($3)`, `sh $2,0($3)`, `addu $7,$7,104`, `addu $3,$3,104`, `move $2,$7`.

So mine: the symbol goes to $3 (which is the current pointer v1's register!) and is copied to $7 (a7). So mine has v1 = $3, a7 = $7, but the *init* is `v1 = symbol; a7 = v1` — the reverse statement order!

The source is `a7 = &D_8011FD10; v1 = a7;`. Mine emits `v1 = symbol; a7 = v1`. That's because the RTL's insn 14 (a7 = symbol) → $3 and insn 17 (v1 = a7) → $7, i.e., a7=$3, v1=$7 in the *init*, but then the loop's uses are consistent with a7=$7, v1=$3?! Impossible unless... 

OH WAIT. I bet the register allocation assigned a7 = $3 and v1 = $7, and the loop's "current pointer" is a7 ($3) and the "returned pointer" is v1 ($7). Since a7 and v1 are always equal, the roles are interchangeable: the load `lhu 0($3)` reads *v1 = *a7 (equal), the store `sh $2,0($3)` writes *v1 = *a7 (equal), the increments are equal, and the return `move $2,$7` returns v1 = a7 (equal). So the code is semantically correct with the roles swapped.

So in mine: a7=$3, v1=$7. In the target: a7=$7, v1=$3. The init direction follows: mine `a7($3) = symbol; v1($7) = a7` → `la $3; move $7,$3` ✓. Target: `la $7; move $3,$7` ✓.

So I need to flip the allocation of a7 (74) and v1 (76): a7 should get $7, v1 $3.

Allocno priorities: 76 (v1) pri 20000, 74 (a7) pri 5833. Order: 75(a6), 76(v1), 72(a0), 73(a5), 74(a7).

At allocation time:
- 75 (a6, pri 28333): conflicts v0($2), v1($3), sp. Free regs: $4,$5,$6,$7... it got $6? The asm: a6=$6 (li $6,8; addu $6,$6,1; slt $2,$6,20). Hmm, why $6? Maybe 75 prefers $6? No prefs listed. The lowest free: $2 is conflicted (v0), $3 conflicted (v1), $4 (a0) free? But 72 (a0) has a pref for $4 and is allocated later. Hmm, 75 could take $4. But it got $6. Maybe because $4 and $5 are... 75's conflicts: "72 73 74 75 76 2 3 7 29" (from the earlier wrong dump) — with 2 (v0) and 3 (v1). So $4 is free → 75 should take $4. But the asm shows a6=$6.

Hmm, the dispositions from the correct dump: "72 in 4  73 in 6  74 in 7  75 in 5  76 in 3". So 75→$5 (a1), 73→$6 (a2), 72→$4 (a0), 74→$7 (a3), 76→$3 (v1).

But the asm shows: a6 (the loop counter) = $6? `li $6,0x8` — hmm, maybe a6 is 73 and a5 is 75! Let me re-map: the source: a6 = 0x8 (init 8), a5 = 0x340 (init 832). The asm: `li $6,8` and `li $5,832`. So the variable initialized to 8 is in $6 and the one initialized to 832 is in $5. Which pseudo is which? The RTL: insn 11 sets 73 = 8 (a6), insn 20 sets 75 = 832 (a5). Dispositions: 73 in 6, 75 in 5 → a6=$6, a5=$5. ✓ (matches the asm).

So: 72 (a0)→$4, 73 (a6)→$6, 75 (a5)→$5, 76 (v1)→$3, 74 (a7)→$7.

THE DISPOSITIONS SAY 74 in 7 (a7→$7) and 76 in 3 (v1→$3) — EXACTLY THE TARGET! But the asm shows the opposite init.

So the dispositions are the *intended* assignment but the asm... hmm. Unless the .s asm's `la $3` is NOT insn 14. Let me look at the .s again:
```
li $6,8
la $3,D_8011FD10
move $7,$3
li $5,832
```
If 74 (a7) → $7 and 76 (v1) → $3, the RTL insn 14 (74 = symbol) should be `la $7` and insn 17 (76 = 74) `move $3,$7`. The .s shows the reverse.

So the .s disagrees with the dispositions. This is bizarre. Unless the .s is from a different pass: sched2/reorg can't swap registers.

OR: the pseudo numbering in the .rtl dump (74/76) differs from the .greg dump's because cse/combine created new pseudos? The .rtl dump is the *initial* RTL (before cse/combine). The .greg dump is after. The .lreg table lists 14 pseudos. In the .rtl, a7 = 74, v1 = 76. But after cse/combine, maybe the pseudos were *renumbered* (cse can create new registers? no; combine can).

Hmm, but the .lreg dump lists registers 72-93, and the .greg order line says 75 76 72 73 74. The .lreg table's "Register 74 used 7 times across 24 insns" etc.

I wonder if the .s corresponds to a different *includer* than the .greg dump? The dump compiled dbody.c (my standalone copy). The dt.sh score compiles the includer TU. Both should produce the same function.

Hmm, hold on: maybe the standalone dbody.c compile is NOT faithful because the header in the real includer is included *inside* a TU with other functions, and the function's codegen could differ if e.g. `flag_...` differs? No, per-function.

Let me directly compare: compile the dbody.c with the same flags and compare the .s to the target. The .s I read shows `la $3; move $7,$3` — which per the dt.sh diff is MINE. So the standalone compile matches the includer compile (mine). Good.

Then the dispositions (74→7, 76→3) must be wrong/misleading, OR my mapping of 74/76 to a7/v1 is wrong. Let me recheck the .rtl: insn 14 `(set (reg/v:SI 74) (symbol_ref D_8011FD10))` — that's the `a7 = &D_8011FD10;` statement (the first). insn 17 `(set (reg/v:SI 76) (reg/v:SI 74))` — `v1 = a7`. So 74 = a7, 76 = v1. Dispositions: 74 in 7, 76 in 3 → a7=$7, v1=$3. The asm should be `la $7; move $3,$7`. But the .s shows `la $3; move $7,$3`.

Unless the .s's `la $3,D_8011FD10` is insn 14 with dest 74→$3... 

Let me check the .lreg dump (local-alloc output) for this function to see the insns with registers. The .lreg is before global; global then assigns the globals. The .greg RTL should show the final. Let me grep the .greg RTL for insn 14 and 17 (I did: `(set (reg/v:SI 3 v1) (symbol_ref))` and `(set (reg/v:SI 7 a3) (reg/v:SI 3 v1))`). So per the .greg RTL, 74→$3 and 76→$7. The dispositions line says 74 in 7, 76 in 3 — contradictory.

Hmm, is the .greg RTL printed BEFORE the dispositions with an older renumber? Let me look at the order of the dump: dump_global_regs prints the dispositions and then... the RTL is printed by toplev after global_alloc. Hmm.

Whatever. The .s is the truth: mine has a7=$3, v1=$7. The target has a7=$7, v1=$3.

So I need to flip the allocation. Order: 75, 76, 72, 73, 74 with prefs.

Let me think about what determines the assignment:
- 75 (a5? or a6?): got $5.
- 76 (v1): pri 20000, got $3.
- 72 (a0): pri 18000, pref $4, got $4.
- 73: got $6.
- 74 (a7): pri 5833, got $7.

If that's right, then v1=$3 and a7=$7 — the target! But the asm says otherwise.

Hmm, maybe my pseudo→variable mapping is inverted: maybe 74 = v1 and 76 = a7! Let me recheck the .rtl: the source order is `a7 = &D_8011FD10; v1 = a7;`. In the RTL: insn 14 sets 74 = symbol; insn 17 sets 76 = 74. So 74 = a7 (first statement) and 76 = v1. Unless the compiler reordered the statements (it could: `v1 = a7` after `a7 = symbol` — the RTL preserves the source order here).

OK, let me settle it by looking at the .lreg dump's register table: "Register 74 used 7 times across 24 insns" and "Register 76 used 10 times across 15 insns". In the RTL, 76 (v1) is used many times (the loop pointer), 74 (a7) also. Hmm.

Let me look at the .lreg RTL for the loop to see which pseudo is the load address: insn 30 `(set 78 (mem (reg 77)))` where 77 = 76. So v1 = 76 is the load address. And 74 (a7) is the return pointer.

In the final asm, the load address is $3 → 76 → $3 = v1. And the return pointer $7 → 74 = a7 → $7. So a7=$7, v1=$3 — the target's assignment. Then the init: insn 14 (74=a7) = symbol → $7 → `la $7`. But the asm shows `la $3`.

I'm stuck on this inconsistency. Let me look at the actual .lreg dump RTL for insn 14 to see the local allocation (the .lreg dump is local-alloc's output, where block-local pseudos get regs; the globals stay pseudos). Let me check whether insn 14/17 have hard regs in the .lreg dump.

Actually, maybe the .s dump in the dump dir is from the *cpp'd TU* that includes the header TWICE or something. Hmm, dbody.c contains the header body + padding.

Wait — maybe the .s function I read is from a DIFFERENT compile: the dump dir contains t2.s from cc1; that's it.

Let me just re-run the standalone compile manually and check the .s. Actually, let me look at the .lreg dump's RTL for insn 14/17.
