---
ts: 2026-11-07T01:10:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LfMLk2Nz3ya3MlFHooZf
---
My generated code:
```
jal func_8017EE68
move $16,$4          (s0 = a0 in the delay slot)
li $2,8
sw $2,512($16)       (store 0x200, base s0)
li $2,0x100000
move $4,$16          (call2 arg = s0)
jal func_80171990
sw $2,516($4)        (store 0x204, base $4 = a0!)  <- delayed-branch slot
```
So the second store is in the delay slot of the call to func_80171990, using $4 (a0) as the base. Because `move $4,$16` set $4 = s0, and then the store `sw $2,516($4)` uses $4. That's the same value! The compiler reused $4 as the base for the store since it just copied s0 into $4 for the call.

The target:
```
jal func_80171990
sw $2,516($16)     (base s0)
```
So in the target, the store uses s0 ($16) instead of the just-copied a0 ($4).

The prior note says "reload_cse rewrites the 0x204 store base s0 -> a0". Right: after `move $4,$16`, reload_cse sees $4 == $16 and uses $4 for the store (the copy is available).

How to prevent this lever-free? Options:
1. Make the store use a value that isn't equal to the call arg at that point. E.g., call2 with a different expression: `func_80171990((u8 *)(s0 + 0))`? identity → same.
2. Compute the store address differently, e.g. `new_var` is a char* = (char*)s0; if the second store used `new_var` and the call used `s0`, the compiler may still see them as equal.
3. Use a different base spelling for the second store: `*((s32 *)((char *)s0 + 0x204))` vs `new_var + 0x204` — same value.
4. Make the second store's address not equal to the call arg: e.g., pass `(u8 *)new_var` to the call and store through s0? Same equality.

Hmm. The target's body (pinned) has the same source; the pin $16 makes s0 a hard reg, and `move $4,$16` happens (call arg copy). Then the store uses $16 because... the pinned body's store base is the hard $16, and reload_cse would still see $4==$16. Why does the target use $16 then?

Because in the target, the store's RTL base is the hard reg $16 and the call arg is the pseudo that was copied into $4 — reload_cse's reg_eqv tracks pseudos, and $16 is a hard reg (not equal to $4 in its table?). The reload_cse substitution works on pseudos; hard regs are fixed.

So lever-free, the store's base pseudo (s0) gets allocated to the same register as the call-arg pseudo (a0) after `move $4,$16` — i.e., reload_cse rewrote the store to use $4 since $4 was set to the same value.

To break this, make the call argument NOT be the same value as the store base. Options:
- Call with `(u8 *)((char *)s0)` — same.
- Call with a different pointer that's provably equal? no.
- Reorder: put the store BEFORE the `move $4,$16` (i.e., before the call setup). Statement order! The store `*((s32*)(new_var + 0x204)) = v0;` currently comes before `func_80171990(s0)` in the source. But sched1/dbr moved it into the delay slot. If we could keep the store before the call... The target has it in the delay slot too (`jal func_80171990; sw $2,516($16)`), but with base $16.

So the difference is only which register names the base.

What if the call arg is computed differently, e.g. `func_80171990((u8 *)s0 + 0)`? Same value, and the compiler would still emit `move $4,$16`.

What if we pass the argument as a *different variable* that isn't tied to s0, e.g.:
```
  u8 *p = (u8 *)s0;
  ...
  func_80171990(p);
```
Then p and s0 may be different pseudos but coalesced. Hmm.

What if the second store uses a *different* expression for the address, like `(char *)s0 + 0x204` vs new_var + 0x204? Already.

Key insight: the store base in the target is the hard reg $16 because the store's RTL uses $16 directly. Lever-free, the base is a pseudo that reload_cse maps to $4 (the call-arg copy) because the copy `$4 = $16` makes them equivalent.

To prevent reload_cse from substituting, the call arg must not be a copy of the store base at that point. E.g., if the call arg is `s0 + 0` computed as a separate pseudo? `move $4,$16` is exactly that copy.

What if the call is `func_80171990((u8 *)new_var)` where new_var is a char* pseudo? Then the copy is $4 = new_var's reg. If new_var's reg == s0's reg (they're equal values, coalesced), same.

What if we make the store use the *new_var* pseudo and the call use *s0*, with the two pseudos in different registers? Then the target's store would use new_var's reg — but the target uses s0 for both. Hmm, the target: store base $16 (s0) and call arg $4 (copy of $16).

So the target's store base is the s0 pseudo, and the call arg is a separate pseudo (a copy). Lever-free, the store base pseudo and the call arg pseudo are the same? No: in the source, the call arg is `(u8 *)s0` (a cast of s0) and the store base is `new_var` (= (char*)s0). These are two different pseudos (both copies of s0). The target keeps new_var's store on $16.

Wait, in the pinned body, `new_var = (char *) s0;` creates new_var = $16 copy. The store `*(s32*)(new_var+0x204)` uses new_var. cse/combine would fold new_var into $16 (the hard reg) → base $16. Then the call arg `(u8*)s0` → $16 → `move $4,$16`.

In the lever-free body, new_var is a pseudo copy of s0; the compiler folds it (cse) to s0's pseudo, and s0's pseudo is allocated... to $16? My generated code shows `sw $2,516($4)` — using $4 after `move $4,$16`. So the store base was rewritten to $4 by reload_cse (post-reload copy propagation), because $4 holds the same value.

The lever: make the call arg a value that is NOT a plain copy of s0. E.g., pass `(u8 *)((char *)s0 + 0)`? The compiler folds to a copy.

What if the call arg is `(u8 *)new_var` and the store base is `s0`? Then the copy is $4 = new_var = s0. Same.

What if the call happens BEFORE the store in the source? It already does? No: the source order is store 0x204 then call. But dbr moved the store into the call's delay slot. If we reorder the source so the store comes before the call's argument setup... the scheduler decides.

Hmm, what if the call arg is computed from a *different* pointer with an offset that cancels? e.g. `func_80171990((u8 *)(s0))` — no.

Alternative: make the store base a *different register* from the call arg by using a pointer that is live and distinct: e.g., store through `r` where `r = (s32 *)s0;` — a distinct pseudo that isn't the call arg. Then reload_cse might still equate them.

The real question: what makes reload_cse substitute? It records that after `move $4,$16`, reg $4 == $16 (a copy), and then rewrites uses of $16 to $4 (the "canonical" one) until one of them is clobbered. So ANY use of $16 after the move becomes $4.

In the target, the store's base is the hard reg $16, not a pseudo; reload_cse works on pseudos (its reg_eqv table covers pseudos that got hard regs?). Hmm, reload_cse (reload1.c reload_cse_regs) tracks regs including hard regs? It compares REGNOs; hard reg $16 vs $4: after `move $4,$16`, it records that $4 and $16 are equal and may substitute. But it did NOT in the target.

Why? Because in the target the store base is $16 (a hard reg) and the substitution is from the *pseudo* to the copy... In reload_cse, the equivalence is recorded for the destination (a pseudo or hard reg) from the source. If the source is a hard reg and the destination is a pseudo, the table maps the pseudo → hard reg, not the reverse. So uses of the pseudo get the hard reg; uses of the hard reg are untouched.

In my body: `move $4,$16` — $4 is a *pseudo* allocated to $4? Hmm, at reload time registers are already hard. The call arg pseudo (which got $4) is copied from $16: `move $4,$16` — dest $4 is hard (post-reload), source $16 hard. Both hard. reload_cse would then track both...

Actually, in reload_cse_regs (reload1.c), it tracks "reg_values" for pseudos and also hard regs. After `set $4, $16`, it knows $4 == $16 and can replace subsequent uses of $16 with $4 (or vice versa) as long as neither is modified. Since $4 and $16 both hold the same value, it replaced the store's base $16 with $4 (maybe because $4 is "cheaper" or because it's the last set).

In the target, the same `move $4,$16` exists! And the store uses $16. So why no substitution there? Maybe because the store in the target comes in the delay slot too... same.

Hmm, the difference: in the target the store's base is the *hard reg* $16 from the start; in mine it's a pseudo that got $16 and was then substituted. Maybe reload_cse's reg_values tracks pseudos only (REGNO >= FIRST_PSEUDO_REGISTER at that point — no, post-reload there are no pseudos).

Wait, reload_cse_regs runs *before* reload? Let me check: gcc 2.7.2 has `reload_cse_regs` called from `reload` after... Actually "reload_cse" runs in reload1.c after register allocation (before the actual reload pass? no). The note in the brief says "sched1 hoists the arg copy... then reload_cse rewrites the 0x204 store base s0 -> a0".

So reload_cse runs after allocation. It tracks both hard regs. Then why the difference?

Maybe the difference is the *order* of the move and the store in the RTL: in the target, the store (in the delay slot) may come before the move? Both have `jal; move $4,$16` then later `jal2; sw ...`.

Hmm, actually look at my asm: `move $4,$16` comes right after the first jal. Then `li $2,8; sw $2,512($16); li $2,0x100000; move $4,$16` — wait, there are TWO `move $4,$16`? Let me re-read:

```
jal func_8017EE68
move $16,$4          <- s0 = a0 (delay slot)
li $2,8
sw $2,512($16)
li $2,0x100000
move $4,$16          <- call2 arg
jal func_80171990
sw $2,516($4)        <- store in delay slot, base $4
```
The second `move $4,$16` is the call arg setup. Then the store in the delay slot uses $4.

In the target (pinned), the same `move $4,$16` exists, and the store uses $16.

reload_cse's substitution: after `set $4,$16`, it records reg_values[$4] = $16 (or $16 → $4?). If it records "$4 holds the value of $16", then a later use of $16 could be replaced by $4 (since $4 is a copy). Why would the target not?

Difference: in the target, $16 is a *fixed* hard reg that is used elsewhere; reload_cse may not substitute for fixed regs. In mine, $16 is a normal allocated reg (not fixed). Hmm, but post-reload they're both just regs; "fixed" info is gone.

Alternatively, the substitution may be the other way: reload_cse replaces uses of the *destination* with the source, or vice versa, depending on which was set. Let me look at the reload_cse code in gcc 2.7.2 (reload1.c). Let me grep for "reload_cse" and the reg_values handling.

Actually, the prior note already concluded this is a sched1-argcopy-hoist wall (25 spellings all score 1). Our job: try ≥30 new moves. Maybe there's a crack now.

Ideas to break the substitution:
1. Make the second store's base a *different* value that's not the same as the call arg: e.g., store through `new_var` and call with `(u8 *)(s0 + 0)` where the compiler can't prove equality? It can.
2. Change the call argument so it's not a plain copy: e.g., `func_80171990((u8 *)((char *)s0 + 0))` → same.
3. Make the store happen *before* the `move $4,$16`: reorder the source so the store is before the call (it is: store then call). The scheduler moved the store into the delay slot (dbr). If the store were kept before the call arg setup, no substitution. Statement order: the store is already before. The dbr moved it into the delay slot.

Hmm, in the target, the store is ALSO in the delay slot (`jal func_80171990; sw $2,516($16)`). So the delay-slot placement is the same; only the base reg differs.

4. Make the call arg copy come from a different pseudo: e.g. `u8 *p = (u8 *)s0; func_80171990(p);` — then `move $4, p_reg`. If p's pseudo gets a different reg than s0... but the copy would be `move $4,$16` again (p coalesced to s0).

5. What if we make the call arg `(u8 *)new_var` and the store base `new_var` too? Then `move $4,new_var_reg; ... sw $2,516(new_var_reg)` → same issue.

6. What if the store base is *not* a register but a memory address computed fresh: `*((s32 *)((char *)s0 + 0x204)) = v0;` — same.

7. Force the store to use a *different* base register: e.g., a second pointer `r = (char *)s0 + 0x204;` computed earlier (before the call), so its pseudo is live and distinct:
```
  char *r = (char *)s0 + 0x204;
  ...
  *(s32 *)r = v0;
  func_80171990((u8 *)s0);
```
Then the store's base is r, a pseudo. The target's store uses $16 (s0), not a separate address. If r's value is s0+0x204, the store would be `sw $2,0(r)` where r = $16+0x204 → the compiler would fold to `sw $2,516($16)`. Then the base is $16, and reload_cse might substitute $4 again.

8. Break the equivalence by *clobbering* one of them between the move and the store. E.g., after `func_80171990`'s arg copy... no, the store is in the delay slot.

9. Make the call arg a *different* register value: e.g., pass `(u8 *)(s0)` but force a copy through a variable whose live range conflicts... 

10. What about changing the ORDER: put the store AFTER the call in the source:
```
  func_80171990((u8 *)s0);
  *((s32 *)(new_var + 0x204)) = v0;
```
Then the store would be after the jal (not in the delay slot) → an extra instruction placement difference; the target has it in the delay slot. Probably scores worse.

11. What if the store uses `v0` (a different value) so it can't be in the delay slot? It already does.

Hmm. Let me look at reload_cse to understand the exact rule, since that determines the crack. Let me grep gcc 2.7.2 reload1.c for reload_cse.

This is the decisive pass. Let me read it.

Actually — the prior agent tried 25 spellings. Let me think about what could differ.

In the target (pinned), the RTL after reload has the store's base as the *hard reg* $16. In mine, the base is a pseudo (allocated $16). At reload_cse time (post-reload, regs renumbered), both are hard $16. So the difference must come from earlier: in the target, the store's RTL base was already the hard reg $16 (because the pin made the C variable s0 a hard reg from the start), while in mine it's a pseudo.

reload_cse's reg_values table tracks pseudos? If the pass runs BEFORE reload (i.e., on pseudos, then reload does the rest), then:
- In the target, the store base is $16 (hard) → not tracked as a pseudo → no substitution.
- In mine, the store base is a pseudo → tracked → substituted with $4.

That's likely: reload_cse_regs runs after global/local alloc but before reload (it's "reload_cse_regs" called in reload() early, before the reload pass, when pseudos have reg_renumber but RTL still has pseudos). Yes! In gcc 2.7.2, reload_cse_regs is called at the start of reload(), and it operates on pseudos: it records that a pseudo equals a hard reg, and replaces pseudo uses with the hard reg (or another pseudo).

So in the target, the store's base is hard $16 → untouched. In mine, the base is a pseudo that got $16; after `set $4, $16` (a move from the pseudo to... hmm).

Let me read the code to be precise.

Let me grep reload1.c.
