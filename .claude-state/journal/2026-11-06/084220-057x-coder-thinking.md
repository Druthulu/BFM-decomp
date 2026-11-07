---
ts: 2026-11-06T15:42:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CWzBp1ouNzQwDO9IQ8cr
---
Item 2 started around 08:33 (after item 1 done ~08:31). So ~9 minutes. The wall rule requires ≥20 min AND ≥30 scored tries. I have 31 variant files, but some are the same? All scored. That's ≥30 scored tries. But time is only ~9 min. Hmm, "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I need both: 20 min and 30 tries. I have 31 tries but only 9 min. I should continue working ~11 more minutes on this item before declaring a wall.

Let me use the time productively: investigate the cse source to find a real-C lever, and try more variants.

Key insight to explore: cse's `equiv_constant` substitution. In cse.c, when a register is set to a constant, it's put in reg_equiv_constant if `rtx_varies_p` etc. Then uses are replaced. The replacement of `mb + 0x18` with the constant happens in fold_rtx: it looks up the register's known value in the `table` (local value table). Since mb was set to the symbol constant, fold_rtx substitutes.

To prevent substitution, the register must not have a known constant value at the use. Options in C:
- A second set between the set and the use (tested).
- The set is conditional.
- The register's value comes from memory/function.

Wait — what about making the assignment `mb = (u8 *)&D_800AF630;` happen *inside a branch that's always taken*? E.g. `if (param_1 != 0) mb = ...; else mb = ...;` — that's a real conditional and adds branches.

What about `switch`? no.

What about a loop that runs once? `for (i=0;i<1;i++) mb = ...;` — loop.c might unroll; adds code.

Hmm.

Actually, here's a thought: the launder is a *non-volatile asm* with "=r" output. What if we replace it with a *real* operation that produces the same value but cse can't fold, and costs zero instructions? E.g. `mb = (u8 *)&D_800AF630; ... mb = mb + 0x18;` then use `mb`? That changes the add: target wants base+24 per call.

What about:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = mb + 0x18;
func_800491AC(mb);      /* mb = base+24 */
```
The second call's arg is mb (base+24). Target has addiu a0,s0,24 — if gcc keeps base in s0 and computes mb into... it would need to add. Actually with `mb = mb + 0x18`, gcc computes addiu s0,s0,24 (destroying base) then move a0,s0. Target has addiu a0,s0,24 and keeps s0=base. So not matching. Tested b → 6 (same residual).

What about:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
func_800491AC(mb + 0x18);
```
where the *second* addition is done through a different variable that cse sees as `mb + 0x18` but whose addition isn't folded because the variable is `volatile`? A volatile pointer read from a register... volatile local forces memory.

Let me look at the target once more: maybe I'm wrong that the base is held; the two addiu could each be `a0 = s0 + 24` where s0 = base. Yes.

Alternative: what if the *source* used a local `SVECTOR`/matrix variable at D_800AF630 accessed as `&D_800AF630 + 0x18` where D_800AF630 is declared as a *struct instance* (not array) and the +0x18 is byte arithmetic on a `(u8*)&D_800AF630` cast — same.

I could also try making mb `s16`/`u16`-based pointer arithmetic? no.

Let me try one thing: a *second set of mb to the same constant* but placed between the two calls AND a use of mb as a value in an intermediate expression that cse can't fold... e.g. `mb = (u8 *)((u32)mb);` identity (disallowed).

Honestly the wall looks right. Let me use remaining time to double-check the wall evidence with a dump: show that cse substitutes the constant into the register use (cse pass dump). The evidence line needs "gcc pass + mechanism ≤ 140 chars".

Let me run hdump.sh or cc1_dumps_tu to see cse behavior. There's tools/cc1_dumps_tu.sh. The dt.sh --keep candidate dir. Let me use .run/P40/T10/dump.sh? It works with .run/P40/T10/$fn/tu. I can make my own dump helper based on it, using my item dir. Let me copy dump.sh logic into my shard.

Actually the brief points to .run/P40/T10/hdump.sh for header pass dumps and tools/cc1_dumps_tu.sh + tools/alloc_table.py for TU dumps. Let me write a dump helper for my item using the T10 dump.sh pattern (it uses .run/P40/T10/$fn/tu — not mine). I'll adapt.

Let me first check if cc1_dumps_tu.sh needs an absolute outdir (the constraint says hdump.sh needs absolute outdir under shard dir; cc1_dumps_tu maybe too).

Time is limited; the wall evidence can cite the known cse mechanism: "cse reg_equiv_constant substitutes &D_800AF630 into mb's uses; +24 folds to (const (plus sym 24)), materialised once in $s0; CONSTANT_ADDRESS_P (cse.c:2656) skips find_best_addr". That's a mechanism backed by the source and the diff.

But the brief says "evidence = gcc pass + mechanism ≤ 140 chars (read dumps when unsure)". I have the diff + source. Good enough.

Let me do a cse dump to be certain and to have the pass evidence. Actually, let me be efficient: I'll spend a few more tries with a couple of remaining ideas, then dump cse for evidence, then write the WALL row.

Remaining ideas (cheap):
- ce: `mb = (u8 *)&D_800AF630; func_8004914C(mb + 0x18); mb = (u8 *)&D_800AF630; func_800491AC(mb + 0x18);` tested a.
- cf: use a *function-scope static* pointer? adds a load.
- cg: `mb = (u8 *)&D_800AF630; func_8004914C(mb + 0x18); func_800491AC((u8 *)&D_800AF630 + 0x18);` tested w-ish.
- ch: split the addition as `mb2 = mb + 0x18;` then both calls `mb2`? cse folds mb2 to constant.
- ci: use a `u8 *` array: `u8 *mbs[1]; mbs[0] = &D_800AF630; func(mbs[0]+0x18)` → memory.
- cj: `mb = (u8 *)&D_800AF630; func_8004914C(&mb[0x18]); func_800491AC(&mb[0x18]);` tested p.

Hmm what about using the *address of the symbol* passed to the first call directly and mb only for the second? Target needs addiu per call.

Let me try one last promising idea: the "dead reset" placed *immediately after the use* per C0414, i.e.:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = 0;
mb = (u8 *)&D_800AF630;
func_800491AC(mb + 0x18);
```
tested d (6).

And:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = 0;
func_800491AC((u8 *)&D_800AF630 + 0x18);
mb = (u8 *)&D_800AF630;   /* restore for next site */
```
That was vk (6).

OK. Let me also try the variant where the second call's base is a *second set of the same variable* but with a different *type*: `mb = (u8 *)(s32)&D_800AF630;` same.

I'll accept the wall. Let me produce a cse dump for evidence. Use the T10 dump.sh adapted. Actually maybe simpler: use `tools/cc1_dumps_tu.sh` directly on the TU with -dcse? Let me check its usage.
