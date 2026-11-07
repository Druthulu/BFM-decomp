---
ts: 2026-11-06T11:37:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OthERfrJpNQkiTA5pblu
---
This is complex. Let me focus: the scan of the target thread (thread_if_true=1) starts at insn_at_target = ff8 (`move s1,v0`). stop_search_p(trial, !thread_if_true=0) → labels don't stop. It scans ff8 move s1,v0; ffc sll; 1000 sra; 1004 slt; 1008 bnez (JUMP_INSN → stop). So it examines move s1,v0, sll, sra, slt. It's looking for an insn that can be moved to the delay slot. `move s1,v0` sets s1 which is needed at the opposite thread? Hmm.

But the delay slot ended up being `addiu v0,s1,1`, not any of those. So my analysis of which thread is wrong. Let me reconsider: maybe the delay-slot fill isn't from the target thread but from the fall-through thread where the barrier stops the scan... no.

Hold on — maybe the delay slot insn `addiu v0,s1,1` is NOT a reorg fill at all, but the natural `i++` scheduled into the delay slot by sched2/reorg, and the "duplicate" is because... Actually let me reconsider the source. `i++; w++;` produces `addiu v0,s1,1; move s1,v0; addiu s2,s2,32`. Hmm.

Wait — the beqz at fdc is `if (D_80115158[i].h != 0)`. Its delay slot `addiu v0,s1,1`. The i++ is AFTER the if. So the compiler scheduled i++ into the delay slot? That's a classic speculative fill: i++ doesn't depend on the branch. But then the call clobbers v0, so i++ must be redone after. Actually no — the compiler would keep i++ after the call (it must, since v0 is clobbered). The target has BOTH. So one is the delay-slot fill (speculative, for the taken path where the call is skipped) and one is the real i++ after the call.

Hmm, but if h != 0 (call taken), the delay-slot `addiu v0,s1,1` executes, then the call clobbers v0, then ff4 recomputes. If h == 0, the delay-slot computes v0=i+1 and branches to ff8 where `move s1,v0` completes i++. So the delay-slot insn is essential for the taken path. That's a very deliberate reorg "fill from thread" where the thread is the target (ff8) and it needs v0=i+1 before move s1,v0. But addiu v0,s1,1 is at ff4, before ff8. 

Unless... the target thread's first insn is considered to be the insn before the label? No.

Wait, maybe I misread which insn the beqz targets. fdc `beqz v0,ff8`. Yes ff8. And ff4 `addiu v0,s1,1`. So reorg moved `addiu v0,s1,1` from the fall-through thread (it's in the fall-through thread, since the target label is ff8, and ff4 < ff8 is in the fall-through). So reorg stole it from the fall-through thread after the call, into the delay slot. But then it should have deleted it from the fall-through thread (if own_thread). It didn't delete it because... it's needed? No — reorg deletes stolen insns. But the target keeps it. 

Unless reorg determined it couldn't delete because the insn is used by `move s1,v0` which is the target of the branch — i.e., on the fall-through path, after the call, the value v0=i+1 is needed at ff8 (move s1,v0). So reorg can't delete it (it's needed at the target label which is reachable from the fall-through). So it copies it into the delay slot and leaves the original. That matches "reorg COPIES it into the delay slot" from the header comment!

So the mechanism: the fall-through thread scan finds `addiu v0,s1,1` after the call, and since it's needed at the opposite thread (the target), it copies rather than moves. But wait, the scan starts at the branch's next insn (fe4 move a0,s0) and the barrier stops it. Hmm. Without the barrier, it would stop... no. Let me re-read: with the barrier at fe4 (first insn of if-body), the fall-through scan stops immediately at fe4 (asm). So it finds nothing. Then it scans the target thread from ff8. That doesn't yield addiu v0,s1,1 either.

I'm clearly misreading the structure. Let me reconsider: maybe the barrier is at the head of the if-body which is the FALL-THROUGH, and the if-body is `{ __asm__(""); ot = call(); }`. The beqz at fdc branches to ff8 when h==0 (skip the if-body). So the if-body (call) is the fall-through. The barrier at the head of the if-body is the first fall-through insn → stops the fall-through scan.

But the target disassembly shows the delay slot filled with `addiu v0,s1,1` which is from AFTER the call. So reorg must have filled from the target thread somehow. 

OH WAIT. Maybe the branch at fdc is not the `if (h != 0)` branch. Let me recount. The beqz at fdc has delay slot fe0 `addiu v0,s1,1`. But maybe the beqz is from a different construct. Let me look again:
```
fc0: sll v0,s1,0x10
fc4: sra a2,v0,0x10
fc8: sll v0,a2,0x1
fcc: lui at,0x0
fd0: addu at,at,v0
fd4: lh v0,0(at)
fd8: nop
fdc: beqz v0,ff8        <- if (h == 0) goto skip
fe0: addiu v0,s1,1      <- delay: i+1
fe4: move a0,s0
fe8: jal call
fec: move a1,s2
ff0: move s0,v0
ff4: addiu v0,s1,1
ff8: move s1,v0
```
Hmm so the delay slot `addiu v0,s1,1` is definitely there. And ff4 also. 

Actually, maybe this is sched2 (not reorg) doing the fill? No, delay slots are filled by reorg (dbr). Actually gcc 2.7.2's reorg does branch delay slot filling. But also there's "dbr" (delayed branch) pass? The project has a "dbr" pass mentioned (walls: dbr-delay-fill). Let me check: in this MIPS port, is there a separate dbr pass? The wall tags mention "dbr | delayed-branch fill takes a fall-through insn the target leaves out". So dbr is a pass (maybe a separate reimplementation). Hmm.

Actually the wall tag "dbr-delay-fill — delayed-branch fill takes a fall-through insn the target leaves out of the slot (G18x)". So "dbr" = delayed branch fill, likely reorg.c is called dbr in this port? Or there's a dbr.c. Let me not go down this hole.

The key: the header comment already tells me the mechanism for lever 5: "reorg.c stop_search_p halts fill_simple_delay_slots' forward scan on an asm insn, so the `beqz` slot is filled from the branch TARGET instead — the duplicated `addiu $v0,$s1,1` the target has in both the delay slot and after the call."

So with the barrier, the forward (fall-through) scan halts, and the slot is filled from the branch TARGET. The branch target is ff8. But the insn is addiu v0,s1,1 at ff4. Hmm, "filled from the branch TARGET" — maybe reorg considers the target thread and the insn just before the target that computes a live-in value. Actually there's logic in fill_slots_from_thread: when scanning the target thread, if it needs a value that's computed in the opposite thread right before the target, it can steal it. Hmm.

Actually, maybe simpler: reorg's fall-through scan, without the barrier, would find `move a0,s0` (the first safe insn) and steal it into the delay slot — that's the "stealing addu a0,s0,zero" the header mentions. That would be WRONG (executing move a0,s0 before the branch is fine actually, but it changes the code). With the barrier, it can't, so it fills from the target, duplicating i+1.

So to reproduce without asm, I need to stop the fall-through scan. A CODE_LABEL in the fall-through stops the scan when labels_p=1 (which is the fall-through scan: thread_if_true=0 → labels_p = !0 = 1). So a label at the head of the if-body would stop the fall-through scan, same as the asm!

How to get a label at the head of the if-body in real C? A label is emitted for a `goto` target or a loop. If the if-body begins with a label that's the target of a goto... e.g.:

```
do {
    if (D_80115158[i].h != 0) {
        if (0) { goto body; }   // dead? no
        body:
        ot = call(...);
    }
    i++; w++;
} while (i < cnt);
```
Hmm, a label at the head of the if-body that nothing jumps to would be deleted. Need something to jump to it.

Alternative: use `do { ... } while(0)` where the do-body head is a loop label. But do-while(0) might be optimized away before reorg.

Another approach: invert the condition so the branch target is the if-body? No, then the if-body is the target, not the fall-through.

Hmm, what about using `while` loop shape? The outer loop already is do-while. What if I add an inner do-while(0) around the call:
```
if (h != 0) {
    do {
        ot = call(...);
    } while (0);
}
```
Does a do-while(0) leave a label? GCC's loop optimization for do-while(0) — the loop is a real loop at the tree/RTL level (NOTE_INSN_LOOP_BEG/END, CODE_LABEL at the end). Actually a do-while(0) executes the body once; gcc creates a loop with a label. The label would be at the END of the body (the loop latch/exit), not the head. So the head of the if-body would be the call, no label at the start. Hmm. But the label at the end (after the call) might affect the scan differently.

Alternatively:
```
do {
    ot = call(...);
} while (0);
```
The loop has a label after the call (the exit). The scan from the branch would hit the call (CALL_INSN, doesn't stop), then... the insn after the call. Hmm.

Actually, wait: the fall-through scan tries to find an insn to move into the delay slot. The first insn is `move a0,s0` (call arg setup). Without the barrier it moves that. With the barrier it doesn't. To stop it, I need a label or jump or asm as the FIRST insn of the fall-through.

What if the if-body starts with a nested `if` that creates a label? No.

What if I write the loop differently so that after the beqz, the first thing is a jump? E.g., the if-body is empty and the call is elsewhere:

```
do {
    if (D_80115158[i].h == 0) goto inc;
    ot = call(...);
inc:
    i++; w++;
} while (i < cnt);
```
Here the branch `if (h==0) goto inc` → beqz to inc (the target). The fall-through is `ot = call(...)`. The first fall-through insn is `move a0,s0`. Still no label.

What if:
```
do {
    if (D_80115158[i].h != 0) goto call_it;
    goto inc;
call_it:
    ot = call(...);
inc:
    i++; w++;
} while (i < cnt);
```
Now the if-branch is a bnez to call_it; the fall-through is `goto inc` (a jump!). A JUMP_INSN as the first fall-through insn → stop_search_p returns 1! That would stop the fall-through scan. But this changes the code shape (adds an extra jump and label). The target has beqz (branch when h==0), not bnez + jump. That would add insns.

Hmm, but maybe reorg/jump optimization would clean it up. Risky.

Alternative: a label that's genuinely at the head of the if-body. Use a `goto` from before:
```
i = 0;
if (n != 0) {
    cnt = n;
loop:
    if (D_80115158[i].h != 0) {
        ot = call(...);
    }
    i++; w++;
    if (i < cnt) goto loop;
}
```
Here `loop:` label is at the head of the loop body (before the if), not the if-body.

What about putting the label inside the if-body:
```
if (D_80115158[i].h != 0) {
    goto body;   // unconditional jump into body -> label
body:
    ot = call(...);
}
```
The `goto body; body:` is a no-op jump that gcc may delete. If not deleted, it adds a jump. Actually a forward goto to the immediately next statement is usually deleted.

Hmm. What about a `switch`? 

Let me reconsider. Maybe there's a simpler real-C move documented. Let me grep moves.md for "beqz" or "delay slot" filled from target. Also grep for "addiu.*delay" matches. And the cookbook for delay slot fill. Let me grep moves.md for "delay" broadly (I did some). Let me look at specific MATCH lines involving barrier → delay slot.

From the earlier grep:
- line 130: barrier | func_801812AC | MATCH: init at decl `s16 *s1 = 0;` (entry-block set; reorg puts it in the bnez slot, li v0,2 stays as load-delay fill) (G17)
- line 247: barrier | func_801876C4 | MATCH: `do { t = ...; sp10[4] = t; } while (0)` — the loop-shaped range keeps the u16 adds out of the t load delay slot (target nop) (G18)
- line 265: barrier | func_8014F74C | MATCH: invert the `!= 0x1D` guard so the two `return ret` collapse into one return block; jump_optimize then picks bne-to-return + move delay slot as the target
- line 260: barrier | func_8014A59C | WALL dbr-delay-fill — reorg eager fill moves li v0,128 into the bnez slot; stop_search_p stops only on asm/jump/label, li no trap and epilogue live-in is sp only

Line 260 is the key: "stop_search_p stops only on asm/jump/label". So a jump or label as the first fall-through insn works.

Let me think about a clean way to get a label or jump at the head of the if-body that produces the same instruction stream. 

Idea: use a nested do-while(0) whose latch label lands at the head? No.

Idea: The target already has a loop. What if the if-body contains a small `do { ... } while(0)` where the call is the body and the do-while exit label is right after? That doesn't put a label at the head.

Hmm, actually maybe I can get a label at the head by using `continue` in the outer do-while? `continue` jumps to the loop's latch/condition, creating a label there.

Let me reconsider the structure. The outer loop is:
```
i = 0;
if (n != 0) {
    cnt = n;
    do {
        if (h != 0) {
            call();
        }
        i++; w++;
    } while (i < cnt);
}
```
What if I write it as:
```
i = 0;
if (n != 0) {
    cnt = n;
    do {
        if (D_80115158[i].h == 0) {
            goto inc;
        }
        ot = call(...);
    inc:
        i++; w++;
    } while (i < cnt);
}
```
The `inc:` label is at the head of the else (after the if-body), which is the branch TARGET. For the fall-through scan (thread_if_true=0), the first insn is `move a0,s0` (call setup) — no label. So still fills from fall-through.

What if:
```
do {
    if (D_80115158[i].h != 0) {
        goto body;
    }
    goto inc;
body:
    ot = call(...);
inc:
    i++; w++;
} while (i < cnt);
```
The branch: `if (h != 0) goto body` → bnez to body (target). Fall-through: `goto inc` → JUMP_INSN. So the beqz/bnez fall-through scan hits a jump → stop. Then fills from target (body: the call). But the call is not eligible (CALL_INSN). Hmm, then it might scan further. This changes the branch direction (bnez vs target's beqz) and adds a goto/jump. The target has `beqz v0,ff8` (branch when h==0 to inc). My version would have `bnez v0, body` + `j inc`. Different insns. Likely worse.

Alternatively:
```
do {
    if (D_80115158[i].h == 0) {
        goto inc;
    }
    ot = call(...);
inc:
    i++; w++;
} while (i < cnt);
```
This is the natural inverted form producing `beqz v0, inc` (matching target!). The fall-through is the call. The label `inc:` is at the branch target. The delay slot: fall-through scan starts at `move a0,s0`, not stopped → steals it (wrong). Unless the label is considered...

Wait — but in this form, is there a difference from the original? The original has the barrier at the head of the if-body. This inverted form has no barrier, so the fall-through scan proceeds and steals `move a0,s0`. That's the "wrong" fill. So no.

Hmm. To stop the fall-through scan, the FIRST insn after the branch must be a jump/label/asm. The first insn after the branch (fall-through) is the call setup (`move a0,s0`). There's no way to put a label before the call setup in the fall-through unless the call is preceded by a label that's part of the fall-through.

Idea: make the fall-through begin with a label by having the call be a goto target from earlier:
```
do {
    if (D_80115158[i].h == 0) goto inc;
    goto body;      // this jump is the fall-through -> stops scan
body:
    ot = call(...);
inc:
    i++; w++;
} while (i < cnt);
```
Now: `if (h==0) goto inc` → beqz to inc. Fall-through: `goto body` (jump) → stops scan. Then target-thread fill: from inc (i++)... it might copy i+1. Hmm, but the jump `goto body` executes when h!=0, adding an extra jump. jump_optimize might turn `beqz inc; goto body; body:` into `bnez body` + fall-through to inc? Actually `goto body` where body is the next-next insn... The optimizer could simplify to `bnez v0, body; ...`. Hmm.

This is getting too speculative. Let me just TRY variants empirically. I have budget. Let me generate 6-8 variants and score them with sc.sh. Fast.

Actually, before that: the store-ordering diff (lever 6) and the n=3 diff (lever 3/4) also need solving. Let me try the struct trick for the store first since it's independent and plausible.

Let me design variants:

V_store: D_801151D0 as one-field struct.
```
extern struct { s32 v; } D_801151D0;
...
ot = (s32 *)func_80137D08(D_801151D0.v, ...);
...
D_801151D0.v = (s32)ot;
```
But anonymous struct type in an extern declaration inside a function — is it valid? `extern struct { s32 v; } D_801151D0;` Yes, C allows this; the type is unique.

But wait, MEM_IN_STRUCT_P: a store to `D_801151D0.v` — the field v is s32, address = D_801151D0 + 0. Does gcc mark MEM_IN_STRUCT_P for a struct member access? Yes, component refs get MEM_IN_STRUCT_P. The RMW store `((PTag*)...)->addr = (u32)ot` is also MEM_IN_STRUCT_P. So true_dependence would see them as possibly aliasing → keep order. 

But there's a risk: making D_801151D0 a struct might change the load at the top (func_80137D08(D_801151D0.v, ...)) — same lw. Fine.

Let me also consider: the header says "Re-declaring D_801151D0 as a one-field struct via a §37 asm-label alias works identically". The asm-label alias is because you might declare it as a differently-named struct var aliased to D_801151D0. But naming it D_801151D0 directly avoids the alias. Good.

V_n: try `s16 n` or a HImode temp.

V_delay: try variants.

Let me create these variants and score. But each variant is a full body copy. To reduce effort, I'll create a base and sed-edit? Let me just write a few files.

Actually, let me be smart: score one change at a time to isolate. Start with the store fix on top of nopin (V_store). If score drops from 9 to ~4, good.

Let me write nopin2.c = nopin with struct D_801151D0.

Wait, but the diff at the store was: mine has the store at 128-129, target at 134-135. That's 6 insns earlier, and the score contribution is likely small (the store move causes several branch-offset diffs? No, the offsets before the store are unaffected by the store position... actually the store move affects insn indices after 128, but the branch offsets are computed from addresses, and the branches are before the store, so no. The diff listed the store as delete mine[128:130] + insert mine[135:135] = a move; score counts as 2 hunks).

Let me just test.

Also, importantly: `n = 3` at insn 60 and the delay slot at 84 are the harder ones. Let me tackle them with variants.

Let me write V1 = nopin + struct D_801151D0, and V2 = V1 + s16 n, and V3 = V1 + inverted-goto loop. Score all with sc.sh.

Let me first write V1. I'll base it on nopin.c content.

Actually, let me create the variants programmatically via a small python script under the item dir, transforming nopin.c. That's cleaner than writing 4 full files. But edits are specific. Let me just use python to read nopin.c and do replacements, writing v1.c, v2.c, etc. Scripts under .run. Let me write a gen script.

Hmm, but "Scripts, not inline python -c". I'll write a .py file under the item dir.

Let me write gen.py that produces variants from nopin.c:
- v_store.c: replace `extern s32                 D_801151D0;` with `extern struct { s32 v; } D_801151D0;`, `D_801151D0,` → `D_801151D0.v,`, `D_801151D0 = (s32)ot;` → `D_801151D0.v = (s32)ot;`
- v_store_s16n.c: additionally `s32 n;` → `s16 n;`
- v_store_do.c: additionally wrap the if-body call in do{}while(0)
- v_store_inv.c: additionally invert the if to goto form

Let me be careful with the string replacements. Let me look at the exact nopin.c lines.

Actually, simpler: I'll write each variant file explicitly with the Write tool, since I need control. But that's a lot of tokens. Let me use a gen.py.

Let me write gen.py.

Plan for variants (all based on nopin):
1. v_store: struct D_801151D0.
2. v_store_s16: + `s16 n`.
3. v_store_u16: + `u16 n`? (n compared to i s16; u16 would change slt to sltu? target uses slt. So s16 better.)
4. v_store_do: + wrap call in `do { ... } while (0);`
5. v_store_goto: + inverted goto loop form.

Let me write the generator.

Wait, for the n=3 issue, another idea: use `n = (s16)3`? constant folds. What about `n = 3; ` but with `n` as volatile? volatile s32 n — would force a store/load, wrong.

Hmm. What about reading a value that the compiler knows is 3 but keeps as an opaque copy: `n = D_8011511A` in the inner-true? No.

Let me reconsider the target at insn 58-60 and 72:
- 58 li v0,3
- 59 bne v1,v0 (D_80115126 vs 3)
- 60 li v0,3 (delay; else arm n=3)
- ... if equal, 61 lui v0 (D_8011511A load) ...
- 64 bne v0,v1 (D_8011511A vs v1? v1 = D_80115126 = 3) — compares D_8011511A to 3
- 65 li v0,4 (delay; else arm n=4)
- ... if equal, 66-70 call, 71 move s0, 72 li v0,3 (inner n=3)

So the target loads li v0,3 at 58 (for the compare), then the else arm at 60 is another li v0,3 (redundant, but kept). Interesting: at 58 v0=3, bne v1,v0; delay slot 60 overwrites v0=3 again (redundant but harmless). So the else-arm assignment n=3 is emitted even though v0 already 3 — that's the opaque copy. Without it, deleted.

Now, at 72 the inner n=3 is after the call; v0 = return value, so n=3 must be loaded — it's not redundant there, so it stays. Indeed mine has li v0,3 at 72? Let me check: the diff didn't flag 72, so yes mine matches there. So only the else-arm (insn 60) needs the opaque copy.

So I need the else arm `n = 3` to not be deleted as redundant. Since v0 already holds 3, gcc deletes it. 

Real C ways to make it non-redundant:
- Assign a value that's 3 but not provably equal to the current v0. E.g., `n = D_80115126 - 3 + 3`? folds.
- Use a different pseudo for the compare constant: if the compare used v1 and a DIFFERENT register for 3, then v0 wouldn't be 3. E.g., make the condition `D_80115126 == 3` but ensure the 3 for n is loaded fresh. Hmm.
- Reorder: compute n=3 BEFORE the compare. E.g.:
```
n = 3;
if (D_80115126 == 3) {
    if (D_8011511A == 3) { call; n = 3; } else { n = 4; }
}
```
Then n=3 is before the branch; gcc emits li v0,3 then the compare uses it. But the else arm n=3 is gone (it's the initial). The target has li v0,3 at 58 (before bne) and 60 (delay slot). Hmm, if n=3 is before the branch, that's insn 58 (li v0,3), and the compare bne uses v1,v0; delay slot would be whatever. The target's 60 li v0,3 is the else arm. If we hoist n=3 before, then at 58 we have li v0,3 and the branch; delay slot might get something else. And the inner-true n=3 at 72 remains. Might be close! Let me try: `n = 3;` before the if, and remove the else `n=3`, keep inner `n=3` (after call) and `n=4` in inner else.

Wait, but the outer else arm is `n=3` (same as initial), so hoisting gives:
```
n = 3;
if (D_80115126 == 3) {
    if (D_8011511A == 3) { ot = call; n = 3; }
    else { n = 4; }
}
```
Hmm but now the outer else does nothing. The target's outer else does `n=3` in the delay slot. With hoisting, the delay slot of the outer bne would be... maybe the `n=3` load is before. Different.

Alternatively, keep the structure but make the else arm's 3 come from a different expression that gcc can't fold to the same v0. E.g., `n = D_8011511A & 3`? No, wrong value.

What about `n = 3 + (D_80115126 - D_80115126)`? folds.

Hmm. What if the compare is done differently so v0 isn't 3 at the branch? E.g., `if (D_80115126 != 3) { n = 3; } else { ... }` (inverted). Then the branch is `beq`/`bne` and the else arm (n=3) is the fall-through or target. The constant 3 for the compare would be in a register, and the else n=3 might still be redundant.

I think the HImode trick is the way: make `n` s16. When n is s16 and assigned 3, then used as cnt (s32) and compared with i (s16), the value flows through HImode. gcc might not delete the HImode assignment because it's a different mode. Let me just test.

Actually, moves.md line 202: `u16 i; u16 j` — the HImode copies of arg0/arg1 escape cse. So for the n=3: if I introduce an HImode copy `s16 k = 3;` and then `n = k;`, the HImode assignment `k=3` might be li v0,3 and the `n=k` a sign-extend... Let me test variants.

Let me just generate and score. I'll write a gen.py producing many small variants, then sc.sh them all. This is the efficient path.

Let me write gen.py that:
- reads nopin.c
- produces variants with labeled transformations.

Variants (transform from nopin):
A. store: struct D_801151D0.
B. store + s16n: also `s32 n;`→`s16 n;`
C. store + hitemp: add `s16 three = 3;` and use `n = three;` in both 3-assignments? But the inner n=3 (after call) also. Let me set both `n = 3;` → `n = three;`. And declare `s16 three = 3;` at top. Hmm, `three` is a local initialized to 3; gcc will keep it in a reg (li) or propagate.
D. store + hoist n=3 before if.
E. store + do-while around call.
F. store + inverted goto loop.

Let me implement A-E first, score, then iterate.

For the store transform, careful: the body has:
```
    extern s32                 D_801151D0;
...
    ot = (s32 *)func_80137D08(D_801151D0, (int)&D_800AE7B8[aD800B9A02], 2);
...
    D_801151D0 = (s32)ot;
```
Replace:
- `extern s32                 D_801151D0;` → `extern struct { s32 v; } D_801151D0;`
- `func_80137D08(D_801151D0,` → `func_80137D08(D_801151D0.v,`
- `D_801151D0 = (s32)ot;` → `D_801151D0.v = (s32)ot;`

Let me write the gen script and run it, then sc.sh all variants.

Let me do it.
