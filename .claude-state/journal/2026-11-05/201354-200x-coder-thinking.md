---
ts: 2026-11-06T03:13:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hbLCnoxqmLwSm7MAx6Ei
---
mark_jump_label replaces a label reference with the LAST of consecutive labels. So if TAIL and TAIL2 are consecutive, both branch refs become TAIL2 → identical again. But note: `cross_jump` is 0 in the first passes, 1 in jump2. The combining happens in each pass. So consecutive labels get unified. ✗

Unless the labels are not consecutive: e.g., put TAIL2 after some insn? Then it's a different address. ✗

Hmm. What if the else's goto targets a label that is NOT at TAIL but at a point that falls into TAIL after a jump? That adds a jump.

What if the else's branch targets a label placed right before TAIL but with a NOTE in between that breaks the consecutive-label scan? The scan skips NOTEs (except LOOP_BEG/FUNCTION_END when !cross_jump). A NOTE_INSN_LOOP_BEG between the labels would break the combine in the non-cross_jump passes, but in jump2 (cross_jump=1) it would skip it (the `else if (! cross_jump && ...)`). Hmm, in jump2, a LOOP_BEG note is skipped → combined. ✗

What about a NOTE_INSN_FUNCTION_END? Same.

What about a real insn between them? Then the addresses differ.

Hmm.

OK, let me step back and consider the *value* of continuing: item 4 has been ~30 min with 12 tries. Let me try a few more high-value ideas and then WALL.

Idea: make the else arm's test branch to TAIL via a *different jump target that is the same block* but reached via a chain: e.g., the else's `goto TAIL2` where TAIL2: is placed at the START of the TAIL block, and TAIL: is a label at the same address — combined. ✗

Idea: change the *condition* in the else arm so the beqz's operand differs: e.g., use `if (d > 0x200)` in the if arm and `if (d > 0x1FF)` in the else arm — different constants → slti 512 vs 513 → different insns → no merge. But the target shows both 513! Wait, let me double check the target: 4be4 slti v0,v0,513 and 4bfc slti v0,v0,513. Both 513. So the else's test is `d > 0x200` = `d < 513` → slti 513. If the else's were `d > 0x1FF` = `d < 512` → slti 512. Target 513. So no.

Idea: make the else's beqz target a *different* label by using a different goto: e.g., the else's `goto TAIL` could be replaced by `goto TAIL;` where TAIL is at the end but the else's block ends with a *different* branch structure: e.g., `if (d <= 0x200) goto REST; goto TAIL;` — the beqz would be `bnez`/`blez`? Let me think: `if (d <= 0x200) goto REST;` → `slti v0,d,513; bnez v0,REST` (branch if d<513). Then `goto TAIL` unconditional. The target has `beqz v0,TAIL` — different. ✗

Idea: use a `switch` on the comparison? no.

Idea: make the else arm's test a `while` loop? no.

Let me try the idea of preventing the *inversion* that leads to the merge. In mine, the merge produced `bgez` (the outer branch inverted). What if we prevent the outer inversion by making the if-body end with a `goto REST` that is NOT the last insn... hmm.

Actually, maybe the merge can be prevented by making the if-body's `j REST` NOT a simplejump at jump2 — e.g., if the if-body's end has a delay slot filled? No, reorg is after.

What if the if-body ends with a *conditional* jump to REST? no.

Hmm, let me look at the cross-jump call: for the if-body's `j REST` (simplejump), find_cross_jump(insn=j, JUMP_LABEL=REST, minimum=1). i2 = prev of REST = the else's beqz. If we can make REST's predecessor at jump2 be something else — e.g., a NOTE that is not skipped? All notes are skipped.

What if REST's label is preceded by a *CODE_LABEL* that is not combined (e.g., two labels with a NOTE between that breaks combining in jump2)? In jump2 (cross_jump=1), the scan skips notes except... it breaks on a non-note, non-label, non-USE/CLOBBER insn. So a NOTE between labels is skipped → combined. A USE/CLOBBER insn between labels is skipped too (cross_jump=1). Interesting! A USE or CLOBBER insn between the labels would be skipped → combined.

Hmm.

What about making REST's label have a different predecessor because the else body is not physically before it? E.g., put the else body AFTER REST? Then the layout changes: the else body would be after the rest of the code, changing the target's layout. ✗

OK, what if we make the *else's beqz* not be the fall-through predecessor of REST by adding a `goto` at the end of the else body to a label placed right before REST, where that label is combined... same.

I think item 4 is a WALL. But wait — n2 (two ifs) got 113 ins and a mostly-right structure. Maybe we can fix n2's residuals with C moves:
- The `bgez v1,4c08` vs `j 4c08`: in n2, the second `if (d < 0)` is tested after the first; the compiler emits `bgez` to skip. If we write the second if as `if (!(d >= 0))` the same.
- What if we write the two ifs as `if (d >= 0) {...} else if (d < 0) {...}`? That's the original if-else.

Hmm.

What if we write the if-else but with the else body's test using a *different variable* so the cross-jump's insns differ? E.g.:
```
if (d >= 0) {
    if (d > 0x200) goto TAIL;
} else {
    d = buf1 - unkA;
    { s32 e = d; if (e > 0x200) goto TAIL; }
}
```
The else's test uses `e` (a copy of d) → the slti's operand is e's pseudo (allocated to v0?) and the beqz's operand likewise. The target has slti v0,v0,513; beqz v0. If e is allocated to v0, the insns are identical to the target's. But the cross-jump compares the two beqz insns: the if arm's beqz operand is d (v0), the else's is e (v0 after alloc) — at jump2 both are v0 → identical. Hmm, unless the pseudos differ at jump2? After reload, both are hard v0. So identical.

Unless e is allocated to a DIFFERENT register than d! Then the target bytes would differ (slti v1,v1,513). ✗

Hmm.

What if the else's test is a `!=` form: `if (d > 0x200) goto TAIL;` vs `if (0x200 < d) goto TAIL;` — same.

OK, let me try one more structural idea: use `else if` with a *nested* if that the compiler lays out differently:
```
if (d >= 0) {
    if (d > 0x200) goto TAIL;
} else if ((d = buf1 - unkA) > 0x200) {
    goto TAIL;
}
```
This might produce the target's structure (else-if with a goto body). Let me test.

Also:
```
if (d >= 0) {
    if (d > 0x200) goto TAIL;
} else {
    d = buf1 - unkA;
    if (d > 0x200) {
        goto TAIL;
    }
}
```
(braces) — o? tested similar.

Let me test the else-if form and a couple of variants:
p1: `} else if ((d = buf1 - unkA) > 0x200) { goto TAIL; }`
p2: `} else { d = buf1 - unkA; if (d > 0x200) { goto TAIL; } }`
p3: `} else { d = buf1 - unkA; if (d > 0x200) goto TAIL; return; }`? no.
p4: reverse the arms with the goto: `if (d < 0) { d = ...; if (d > 0x200) goto TAIL; } else { if (d > 0x200) goto TAIL; }` (n1, merged).

Let me test p1/p2 and also a variant where the else's body is a `do { if (d > 0x200) goto TAIL; } while (0)`? o4 tested (merged).

Let me test p1, p2.
