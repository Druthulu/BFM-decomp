---
ts: 2026-11-06T21:06:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wc4PPJvoo5FhNgHpHcua
---
Still folded. So the initializer doesn't matter; the sibling must have something else. Let me look at func_80148AFC's actual body more carefully: `register s32 tmp __asm__("$5") = ...; u16 sVar3; ... sVar3 = tmp;`. Hmm, `sVar3` is u16! So `sVar3 = tmp` is a truncation (subreg), not a plain copy. Combine can't fold a truncation into the andi because it changes the mode. That's why it survives! And the target for that function: `sVar3 = tmp` — u16 truncation. But our target's `move s0,a0` is a full 32-bit move, not a truncation. So that doesn't apply.

Hmm. So for item 1, we need a plain 32-bit copy that survives.

Let me reconsider. Maybe the target's copy can come from a different source construct. Let's look at what the target needs:
- andi a0, v0, 0xfff   (a = ...&0xFFF in $4)
- move s0, a0          (ang = a)

If combine folds, andi goes to s0. To prevent the fold, `a` needs a use other than the copy, before combine. The asm provided that. What real-C construct gives `a` another use?

Idea: use `a` as a value stored somewhere that the target also has? No store of a in target.

Idea: make the andi's result be `a` and then `ang = a` where `ang` is also used as `a`... no.

Idea: reorder so the copy is in a *different basic block* than the andi. E.g.:
```
if (1) { ... } 
```
No.

Idea: put the copy after the branch test but before the branches? The target has the copy in the beq delay slot, i.e., after the beq instruction. C-level: 
```
if (d == 0x53) { ang = a; goto final; }  // but ang needed elsewhere
```
Not all paths.

Actually, the copy is unconditional. Could we make it a conditional copy in each arm? Target has one move. No.

Idea: use a `&&`/`||` fold to consume `a`. E.g., `if (d == 0x53 && a) ...`? That adds a test on a; target has no test on a. No.

Hmm, what about the `d` load: target does `lbu v1, D_80126C01`. What if we make `a` be used to compute something that's dead but real? That's a launder (identity) if dead.

Wait — maybe we can avoid the merge by giving `a` and `ang` different *types* such that the copy is a subreg but still emits a plain move. E.g., `ang` declared as `s32` and `a` as `s32` — plain. What if `a` is `u32` and ang `s32`? Still same mode SI → plain move.

What if we declare `ang` as a pointer and cast? `ang` used in arithmetic — no.

Alternative approach: maybe the pin should be on a *different* variable so that the andi's destination is forced to $4 while the copy target is a distinct pseudo. E.g., don't name the andi result at all:
```
s32 ang;
register s32 a __asm__("$4");
...
a = ratan2(...) - 0x400;
ang = a & 0xFFF;
```
Here `a` = ratan2(...) - 0x400 (in $4), and `ang = a & 0xFFF`. Target: andi a0 (a & 0xfff) then move s0,a0. But here the andi result is ang directly → andi s0? Actually andi writes ang (s0) because the andi is `ang = a & 0xFFF`. Hmm, target andi writes a0 then move. So no.

What if: `a = (ratan2(...) - 0x400) & 0xFFF; ang = a;` — the andi writes a ($4) because a is the destination; then copy. Combine folds. 

What if we make the andi's destination a *real* use: `a = (ratan2(...) - 0x400) & 0xFFF;` and then `ang = a;` — no other use.

Could `a` be used in the final block via a copy that the target has? The target uses ang (s0) at 3558. a is gone.

Hmm, is the pin even necessary? What if we get `andi a0` because the value is used as a *call argument*? At 3550 ratan2 is called with a0 = (e&0xff)-0x80, a1 = 0x80-(e>>8). Not a.

What about at 348c the first ratan2 call: a0 = unk44-unk50. Not the andi.

OK here's another thought: maybe we can use the `a` variable in the `call` path as an argument to the table call, which the target doesn't show... no.

Let me look at this from the combine perspective. Combine folds `(set (reg a) (and x 4095))` followed by `(set (reg ang) (reg a))` into `(set (reg ang) (and x 4095))` only if `a` dies after the copy (single use). If `a` is used later, no fold. Is there any way `a` is used later that costs zero instructions? A use that's optimized away but still counts as a use at combine time... The asm is exactly that. A dead assignment that flow deletes later? E.g., `a = a;`? That's an identity launder (not allowed). `a = a + 0`? identity.

What about a use that's a real operation but the result is dead and flow removes it AFTER combine? Order: combine runs, then... flow runs before combine? Pass order: jump, cse, ... flow, combine? Let me check GCC 2.7.2 pass order: `cse` (cse1), `jump_opt`, `cse` (cse2)? Actually toplev.c: ... `cse_insn`? The sequence is: jump_optimize, cse (cse1), ... combine? Let me recall: 
```
rest_of_compilation:
  ...
  jump_optimize (insns, 0, 0, 1);   /* jump1 */
  ...
  cse (insns, ...);                 /* cse1 */
  ...
  jump_optimize (insns, 1, 1, 1);   /* jump2 */
  ...
  combine_instructions ...
```
Hmm, actually combine runs after cse1? Let me check tools/reference/gcc-2.7.2/toplev.c.

If flow (dead code elim) runs after combine, then a dead-but-real use added to `a` could survive combine (keeping a distinct) and be deleted later. But what real use? E.g., `res = a;` then res overwritten? That's a dead store; flow deletes. But is it a launder? It's not identity. Hmm, but the brief: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". A dead store `res = a` isn't an identity; but it's a fake use (launder-ish). The kinds list includes "launder" as a kind — if we add a dead use, that's arguably a launder lever, and "no new lever of any kind". So not allowed.

So we need genuine C. Let me reconsider whether the pin can be dropped and the target achieved differently.

Actually, wait. Let me reconsider the target. Is `move s0,a0` really a copy, or could it be the pin's effect? What if the C is:
```
s32 ang;
register s32 a __asm__("$4");
...
a = (ratan2(...) - 0x400) & 0xFFF;
d = D_80126C01;
ang = a;
```
and the pin forces $4; combine folds the andi+copy but then... the result must be in s0 (ang). Since `a` is pinned $4, maybe combine refuses to fold into a different hard reg? But we saw it fold. So no.

Hmm, let me look at the .cse dump (cse1) in w1 — maybe the fold is in cse, not combine. Actually the combine dump already showed it folded. But which pass did it? Let me check the cse dump (before combine) to see if insn 35 (set a) still exists.

Let me grep w1.i.cse for "reg/v:SI 4".
