---
ts: 2026-11-06T09:28:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_w4i85h6DraUox5g1lJ0A
---
Hmm, the clock says 02:28 now (earlier 02:29?). The timestamps are inconsistent-ish but fine. Item 2 started 02:13, now 02:28 → 15 min. Still need 20 min. Let me try a few more real ideas; the wall criterion is time AND tries. I have ~50 scored tries.

Let me think harder about K1 while waiting.

K1 mechanism confirmed: REG_DEAD on t0 at the AND → local-alloc assigns pseudo 126 to t0. Target: v0.

Wait — maybe I can prevent pseudo 126 from getting t0 by making the AND's *result* live across a call or in a different block. If the &0x10 test were moved to an earlier block... no.

Alternative: make the AND result used *twice* (so it can't be trivially assigned the dying reg? no, that doesn't matter).

What if the test is written so that the AND operand is not t0 but a copy? E.g., `if ((bVar1 & 0x10) != 0)` — bVar1 is t0. If we made bVar1 a *word* variable in another register... no.

What if we change the C so that the *last* use of bVar1 is not the AND but something after, using real semantics: is there any real semantics after? What if the function's return used bVar1? The function is void. What if we made it return bVar1? Signature change — not allowed ("no signature or decl change outside the body (callers stay as they are)").

Hmm, what about using bVar1 in the call? `func_8013AA24(iVar11, param_1)` — no.

OK: what if the &0x10 test is computed via a *pointer* to bVar1? No.

I'm confident K1 is a wall. K3 might be crackable but resists 15+ variants.

Let me do one more angle on K3: the target has fc=a1 because... maybe the *first* use order matters: target loads fc (74) then limit (75). Mine too. Hmm.

Let me look at the local-alloc (lreg) dump for the fc/limit pseudos: .lreg shows `(reg:SI N)` with hard regs assigned? The .lreg dump shows insns with pseudo numbers; alloc_table maps them. Let me grep the alloc table for entries with "2 bytes" (s16 loads) and pri — r137/r149 pri 7500 (2 bytes) are probably the limit loads. Which one is fc? fc is a register var pinned a1, so it's not in the greg table.

In the .lreg dump, the pseudos are numbered; the AND temp 126 got t0. In the target build, the equivalent pseudo got v0. The difference: t0's REG_DEAD.

Honestly, K1 = wall. For K3, the fc pseudo is a hard reg (a1) — wait! fc is declared `register int fc __asm__("$5")` — pinned to a1. So fc is ALWAYS a1! Then how did mine put fc in v1? Because... hmm! Let me re-read the source: P35 had `register int fc __asm__("$5");`, but the current src (P37 t4_HD1) has `int fc;` at line 25? Let me check the current header: line 25 `int fc;` — yes! The P37 batch changed it to plain `int fc;` (the "restruct" commit). So fc is no longer pinned. The w3 diff with fc=v1 vs a1.

Ah, that's important: the current source has fc unpinned. So a real-C lever to give fc a1 could be... re-pinning is not allowed (pin is a lever; and kinds=keepalive only, but adding a pin is "no new lever of any kind" — forbidden).

OK. So fc's allocation is a local-alloc priority issue: fc needs to beat the limit pseudo. fc: 3 refs, live 26? The alloc table row r84: `r84 - 769 2 26 None TIE conflicts v0,v1,a1,t0,sp` — pri 769, 2 refs, live 26. Hmm. r137/r149: 7500, 3 refs, live 4, 2 bytes. Those high-priority short-lived 2-byte pseudos are the limit loads (7500). fc (3 refs, live ~26) has pri ~1000. So the limit pseudo (pri 7500) gets a1 first; fc gets v1.

Target: fc=a1, limit=a0. So in the target, the limit's first pseudo got a0, not a1. a0 vs a1: the allocator picks the first available reg in the class order? If a0 was free, why did mine give the limit a1? Because in mine, a0 was taken at that point by something else. What occupies a0 in mine? Let me look at mine's insns 74-77: `lh v1,12(a2)` fc; `lh a1,14(a2)` lim; slt v0,v1,a0 — wait, a0 in the slt! In mine, insn 77 is `slt v0,v1,a0` — a0 holds the limit?? But 75 loaded the limit into a1. Hmm, the slt uses a0. So the limit's first pseudo is a0 in mine too? Let me re-read the w3/s251 diff:

s251_57 mine:
```
74 lh v1,12(a2)   | target lh a1,12(a2)
75 (same) lh a1,14(a2)? 
77 slt v0,v1,a0   | target slt v0,a1,a0
79 move a1,v1     | target move v1,a1
```
The diff only shows changed lines; insn 75 isn't shown, meaning mine and target both have `lh a1,14(a2)`?? But then mine's slt uses a0 for the limit — inconsistent unless a0 is the limit... Let me print mine's 74-95 for s251_57 to see.

Actually the diff shows insn 75 unchanged = same in both. Target 75 = `lh a0,14(a2)`? Earlier target listing said 75 `lh a0,14(a2)`. Wait no, in the target listing from insns.py: 74 `lh a1,12(a2)`, 75 `lh a0,14(a2)`. And the s251 diff shows 74 changed, 75 NOT shown → mine 75 = `lh a0,14(a2)` = same. So mine: fc=v1, lim=a0; target: fc=a1, lim=a0! The limit is a0 in both. Then 77: mine `slt v0,v1,a0` (fc=v1, lim=a0); target `slt v0,a1,a0` (fc=a1). And 79: mine `move a1,v1` (iVar7=a1, fc=v1); target `move v1,a1` (iVar7=v1, fc=a1).

So the ONLY difference: fc is v1 in mine vs a1 in target; iVar7 takes the other. So fc's pseudo gets v1, iVar7 gets a1 (copy preference ties iVar7 to fc's reg? no — iVar7=a1, fc=v1, so the move is a1<-v1).

The copy iVar7 = fc: local-alloc copy preference should tie iVar7's reg to fc's reg. If fc=v1 then iVar7 should prefer v1, but it got a1. Hmm.

In target: fc=a1, iVar7=v1 — the move is v1<-a1, so iVar7 (dst) = v1, fc (src) = a1. The copy preference would tie iVar7 to a1 too, but it got v1. So no tie.

OK so what makes fc get a1? Local-alloc priority: fc (3 refs, live 26?) vs other pseudos. a1 is caller-saved; it's free at that point. fc's priority ~1000. The limit pseudo (pri 7500) got a0 — fine. Which pseudo took a1? iVar7 got a1 in mine (the move dst). So iVar7 (pri?) got a1 before fc. In target, fc got a1 and iVar7 got v1.

iVar7's live range: from the move to its uses (t = iVar7 ± 0x400). Short. refs: 2-3. If iVar7 has high priority, it gets a1 first. To give fc a1, fc's priority must exceed iVar7's, or iVar7 must be constrained.

The keepalive K3 (`__asm__("" :: "r"(fc))` after the block) extends fc's live range and adds a ref — that lowers fc's priority (refs/live)... but it worked in the target.

Hmm, actually maybe the K3 effect is different: it forces fc to stay in a register *across the whole block* (live), so the copy iVar7=fc can't coalesce? 

The real-C equivalent: use fc after the block. Nothing.

OK — but maybe there's a *real-C* way to make iVar7 not take a1: give iVar7 a genuine use that ties it elsewhere, or reorder so iVar7's live range starts later (after a1 is taken?). Hmm.

What if we compute `iVar7 = fc + zr` *later*, e.g. inside the branches? Then iVar7's live range is short and it may still take a1. Tried y1 (compile error due to decl placement) — let me fix y1 properly: declare `int t;` at top and assign inside.

y1 fix:
```
int iVar7;
...
if (fc < lim) {
    iVar7 = fc + zr;
    t = iVar7 + 0x400;
```
with `int t` declared at the top (or use the existing `int t` declarations inside, but with iVar7 assigned before the declaration — that's a statement before a declaration → C89 error). So declare `int t;` at block top.

Let me try that (y1b, all-removed version y6b too). Also try declaring iVar7 inside each branch (both branches declare their own iVar7): `if (...) { int iVar7 = fc + zr; int t = iVar7 + 0x400; ...}` — that's valid C89 (declarations first). And in the else branch too. Then iVar7 is block-local per branch. Target: `move v1,a1` in the delay slot at 79 (first branch only) — the second branch at 93 uses v1 = iVar7 from the delay slot (the move at 79 executes on both paths). If iVar7 is branch-local, the second branch would have its own move → extra insn. So no.

Let me try y1b and a few final ones, then wall.

Also, an idea for K1: make the AND result pseudo *not* short-lived by making the branch condition use the AND result *and* keeping bVar1 live via... no.

Let me just do the final batch and wall. Time check ~02:28-02:30; item start 02:13. I need ≥20 min. Let me spend until 02:35.

Final candidates:
w1: allrm + `int t;` declared at top + iVar7 assigned inside first branch only (second branch uses iVar7 too but assigned inside each? no). Hmm, iVar7 must be assigned before both uses; assigning inside each branch duplicates the move → wrong.

Skip. Let me instead try:
f1: allrm + declare `int t;` at top, keep iVar7 assignment before if (no change to logic, just decl move) — tested y8-like but with allrm. 
f2: allrm + fc load earlier + `int t` at top.
f3: K1 kept + fc load earlier + `int t` at top.
f4: allrm + iVar7 as `s32`.
f5: allrm + fc load earlier + iVar7 s32.
f6: allrm + limit comparisons using `(int)*(s16*)` casts removed? e.g. `if (fc < *(s16*)(param_1+0xe))` already int.

Let me generate f1-f5 and score, then wall.
