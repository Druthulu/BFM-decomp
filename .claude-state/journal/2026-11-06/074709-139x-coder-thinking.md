---
ts: 2026-11-06T14:47:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6vwvk1KNGPDEaFpkO76k
---
Only one, and it's a WALL. So this class is known hard. But maybe there's a crack. Let me look at the exact wall: "flow knows cc==1 on the fall-through so the 2nd if(cc==one) folds (89 ins); real 2nd sets fold; a (cc&0xFFFF) mask keeps it but costs 1 andi (best 10)".

So the wall is that the second test folds. Our case is the same: the second `if (t != 3)` folds because flow knows t==5.

But wait — the target KEEPS the test because the launder makes t opaque. Without the launder, the test folds. So the WALL.

But maybe there's a real-C crack: a real operation that makes t opaque without extra code. The wall note says "a (cc&0xFFFF) mask keeps it but costs 1 andi (best 10)". So a mask works but adds an instruction.

For our case, could I use a mask that folds to nothing? `t = t & 0xFFFF` where t is s16 — the mask might fold (since t is s16, t & 0xFFFF != t in general because t is sign-extended; but the compiler might emit andi). Hmm.

Actually, our `t` is `s32 t; t = (s16)a1;`. So t is a sign-extended s16. `t & 0xFFFF` would change the value if t < 0 (e.g., t=-1 -> 0xFFFF). So it's not a no-op. But in the target, t==5 (positive), so the mask is harmless for this path. But the code must be correct in general.

Wait — the target code only enters the `if (t == 5)` block when t==5. Inside, `if (t != 3)` — with t==5, t!=3 is true. So the check is redundant. If I replace t with `(t & 0xFFFF)` inside the block, since t==5, `t & 0xFFFF == 5`, so `(t & 0xFFFF) != 3` is true — same behavior. And it costs an `andi`. But the target has no andi. So it would differ.

Unless the andi is optimized away... The compiler might fold `(t & 0xFFFF) != 3` given t==5? If it knows t==5, it folds to true (removing the check) — back to square one. If it doesn't know, it emits andi+compare. Either way, not the target.

Hmm.

Let me reconsider the target's branch structure. Maybe I'm misreading the C. Let me re-read the case 5 C:
```
    case 5:
        t = (s16)a1;
        if (t == 0) {
            sel = (u32)&D_8018C4FC;
            goto set_sel;
        }
        if (t == 3) {
            goto sel_054;
        }
        if (t == 5) {
            __asm__ ("" : "=r"(t) : "0"(t));
            if (t != 3) {
                goto sel_094;
            }
        sel_054:
            sel = (u32)&D_8018C520;
            goto set_sel;
        sel_094:
            if ((func_800291B4(0x40) & 0xFF) == 0) {
                goto call_45F;
            }
            sel = (u32)&D_8018C560;
            goto set_sel;
        }
        if ((func_800291B4(D_801802E4[t]) & 0xFF) == 0) {
            goto call_45F;
        }
        ...
```

Wait — `sel_054` is a label INSIDE the `if (t == 5)` block, but the `if (t == 3) goto sel_054;` jumps into it from outside. So if t==3, jump into the middle of the t==5 block (skipping the t==5 check), execute sel_054, then `goto set_sel`. So the control flow is:
- t==3 -> sel_054 (sel = &D_8018C520)
- t==5 -> (launder) if t!=3 -> sel_094 (the func_800291B4(0x40) path); else sel_054.
  Since t==5, t!=3 is true, so -> sel_094.
- else (t not 0,3,5) -> the code after the if (func_800291B4(D_801802E4[t])...).

So the target's branches:
- beq t,3,L70 (sel_054)
- bne t,5,L71 (after the if)
- bne t,3,L73 (sel_094)
- L70: sel_054

Without the launder, the compiler folds: t==5 => t!=3, so the `bne t,3,L73` is removed, and the structure becomes:
- beq t,3,L70
- beq t,5,L73  (if t==5, go to sel_094)
- j L71
- L70: ...

Hmm, that's mine.

So the target keeps a redundant check. This is a jump/fold wall.

Is there ANY real C that produces the target's branch structure? The target structure has 3 conditional branches: `beq t,3`, `bne t,5`, `bne t,3`. The last one is redundant. For the compiler to emit it, it must not know t==5 at that point. 

What if the code is structured so that the `bne t,3` is on a DIFFERENT basic block reached from multiple paths? In the target, after `bne t,5,L71`, the fall-through is t==5. The `bne t,3,L73` follows. Jump.c's threading knows t==5.

What if I restructure so the `bne t,3` is shared by the t==3 path and the t==5 path? Hmm.

Actually, wait. Let me reconsider: maybe the target's `bne t,3,L73` is NOT redundant in the target's C. Let me re-read: the `sel_054:` label is inside the t==5 block. If t==5, we enter, launder, then `if (t != 3) goto sel_094;`. Then `sel_054:`. So the `bne t,3` checks the (possibly laundered) t. The launder could change t! So the check is real. Without the launder, t is unchanged (5), so the check is redundant.

So the launder is load-bearing. To remove it, I need another way to make t "potentially changed" between the `t==5` check and the `t!=3` check.

Real C options:
1. A function call between them (the compiler assumes globals may change, but t is a local — a call doesn't change a local unless its address is taken). Hmm, t is a local; a call can't change it. So the compiler still knows t==5.
2. Take the address of t and pass it to a function? That would force t to memory (extra code).
3. A volatile read? extra code.

Hmm. What if t is a GLOBAL? No, t is a local.

Wait — what if the launder's effect is only needed because t is a local. If t were loaded from a global or recomputed after a call, it'd be opaque. But that changes the code.

Let me reconsider: maybe the crack is to restructure the C so the target's branch structure arises naturally. The target has:
```
if (t == 3) goto sel_054;
if (t == 5) { if (t != 3) goto sel_094; sel_054: ... }
```
What if I write it as:
```
if (t == 3) goto sel_054;
if (t != 5) goto after;
if (t == 3) goto sel_054;   // redundant but written explicitly
goto sel_094;
sel_054: ...
after: ...
```
The compiler would fold `t==5 && t==3` to false. Hmm.

What if I write:
```
if (t == 3) goto sel_054;
if (t == 5) {
    if (t == 3) goto sel_054;
    goto sel_094;
}
sel_054: ...
```
Same fold.

The compiler's jump.c threads: at the `if (t==3)` inside, it knows t==5 (from the outer), so it folds.

Hmm.

What if I use a value that the compiler can't prove: e.g., `t` is recomputed as `(s16)a1` after a memory barrier? No.

What if I make `t` a `s16` (not s32)? The C has `s32 t; t = (s16)a1;`. If t were s16, the comparisons would be on HImode and the code would differ.

Hmm. Let me look at the wall entry again: "a (cc&0xFFFF) mask keeps it but costs 1 andi (best 10)". So the mask trick works to keep the check but adds an instruction. For us, the mask `t & 0xFFFF` would add an andi. The target has no andi. So best would be higher than 0.

Wait — unless the mask is applied to a DIFFERENT variable that's already masked. Hmm.

Let me reconsider the exact target branch structure. Maybe there's a C formulation with a `switch` or a different nesting that naturally emits the redundant check because the compiler doesn't thread it. For example, if the second check is in a block that has another predecessor:

```
if (t == 3) goto sel_054;
if (t == 5) goto in5;
goto after;
in5:
    // t==5 here
    if (t != 3) goto sel_094;   // jump.c knows t==5 from the bne above?
    sel_054: ...
```
With explicit gotos, the block `in5` has a single predecessor (the `if t==5` fall-through or branch). Jump.c might still know t==5.

What if the second check's block has TWO predecessors: one from t==5 and one from elsewhere? Then jump.c can't assume t==5. For example:
```
if (t == 3) goto check3;      // t==3 path goes to check3
if (t == 5) goto check3;      // t==5 path goes to check3
goto after;
check3:
    if (t != 3) goto sel_094;
sel_054: ...
```
Wait, but the t==3 path should go to sel_054, not sel_094. Hmm. Let me think: if t==3, we want sel_054 (skip the check). If t==5, we want the check (which is true -> sel_094).

So the check block `if (t != 3) goto sel_094` is reached only from t==5. So a single predecessor.

Unless I restructure to make t==3 also go through a check. Hmm:
```
if (t == 0) { sel = &D_8018C4FC; goto set_sel; }
if (t == 3) goto sel_054;
if (t == 5) {
    if (t != 3) goto sel_094;
sel_054:
    sel = &D_8018C520;
    goto set_sel;
sel_094:
    ...
}
after: ...
```
The target. The `sel_054` label is reached from two places (t==3 jump and the t==5 fall-through). But the `if (t != 3)` check is reached only from t==5.

Hmm. What if I move the `if (t != 3)` check BEFORE the `if (t == 5)`? No, semantics.

I think this is a genuine WALL (flow-known-value). The launder's opacity is essential.

But let me try a few real-C ideas:
1. Replace the launder with a real store/load of t through a volatile? Extra code.
2. Use a `switch (t)` for the inner check.
3. Use `if (t == 3) goto sel_054; else if (t == 5) { if (t == 3) goto sel_054; goto sel_094; }` — the compiler folds.
4. Recompute t from a1 with a cast that the compiler can't fold? `t = (s16)(a1 & 0xFFFF);`? a1 is s32; (s16)(a1 & 0xFFFF) = (s16)a1 for the low bits... the compiler might fold or emit andi+sll+sra. Hmm.

Let me look at the moves.md for "launder" cracks that involve jump/fold. Maybe there's a technique: "launder->real 2nd set" etc. Those are cse, not jump.

Let me try a few variants:
- v1: remove the launder (c1) — 4.
- v2: replace with `t = (s16)t;` — might emit sll/sra (extra code) or fold.
- v3: restructure the inner if as `switch`.
- v4: use a do-while(0) around the inner check? That might create a block boundary that prevents jump threading. Let me try: `do { if (t != 3) goto sel_094; } while (0);`.
- v5: `if (t != 3 && t == 5)`? no.

Let me test v4 (do-while(0)) — the C0535 EBB split might prevent jump.c from threading. Actually, jump.c threading is CFG-based, not EBB. But the do-while(0) creates a NOTE_INSN_BLOCK, not a basic block. Hmm.

Let me also try: reorder the checks so the compiler doesn't thread. E.g., put the `if (t != 3)` check first inside the block:
```
if (t == 5) {
    if (t != 3) goto sel_094;
sel_054: ...
}
```
That's the same.

What if I write the whole case 5 differently:
```
t = (s16)a1;
switch (t) {
case 0: sel = &D_8018C4FC; goto set_sel;
case 3: sel = &D_8018C520; goto set_sel;
case 5:
    if (func_800291B4(0x40) & 0xFF) { sel = &D_8018C560; goto set_sel; }
    func_8002D4C8(0x45F,0); return 0;
default: break;
}
...
```
This restructures the control flow. The target's code has the check `if (t != 3)` which is redundant for t==5. In a switch-based formulation, the compiler might emit different code. Let me not guess; let me test.

Actually, the target's code structure strongly suggests the original C was exactly the current form (with the launder). The launder was added because the compiler folds. So a real-C crack must prevent the fold.

Let me look at whether the fold is done by jump.c's thread_jumps or by the front-end. If it's jump.c, maybe a `goto`-based structure prevents it.

Let me try the explicit-goto structure:
```
if (t == 3) goto sel_054;
if (t == 5) goto in5;
goto after;
in5:
    if (t != 3) goto sel_094;
sel_054:
    sel = &D_8018C520;
    goto set_sel;
sel_094:
    ...
after:
    ...
```
Hmm, but the label `sel_054` must be reachable from the t==3 path. With explicit gotos, the compiler's CFG is the same as the if/else, so jump.c would thread the same.

Let me test a few variants and see.

Actually, let me reconsider the problem. The score 4 diff shows:
- mine: `beq s0,v0` (t==5 -> L73) and `j L71`
- target: `bne s0,v0` (t!=5 -> L71) and `bne s0,v1` (t!=3 -> L73)

The target's structure is `if (t!=5) goto after; if (t!=3) goto sel_094;` — i.e., the compiler kept the second check. Mine merged them into `if (t==5) goto sel_094; else goto after;`.

Wait — actually, mine's `beq t,5,L73; j L71` is the result of the compiler deciding: at the point after `beq t,3,L70`, if t==5 go to L73 (sel_094), else L71 (after). This is the folded version.

For the target, the compiler did NOT fold. 

Let me try to prevent the fold by making the second check's value come from a computation that's opaque. Since the launder is forbidden, maybe I can use a REAL computation that the compiler can't fold but that produces no code. Hmm.

What about `t = t ^ 0`? folds.

What about using `a1` directly in the second check: `if ((s16)a1 != 3)`? The compiler knows (s16)a1 == t, folds.

What if a1 is modified between? No.

Hmm. What if I make `t` and the second check use a value that's the result of a function that's already called? No call there.

Wait — maybe I can restructure so the second check is on `t` after a REAL operation that changes t but keeps it != 3 for t==5. For example, `t = t - 5 + 5;`? folds. `t = t * 1`? folds. `t = t | 0`? folds. `t = t & -1`? folds.

What about `t = t + (D_8011515A - D_8011515A);`? That's a global read (extra code) and folds? The compiler can't fold two reads of a volatile global, but D_8011515A is not volatile. It might fold (same value). And it adds a load.

What about `t = t + (a1 & 0);`? folds.

Hmm.

Let me look at the wall entry again: "a (cc&0xFFFF) mask keeps it but costs 1 andi (best 10)". So the mask prevents the fold (because the compiler doesn't know cc&0xFFFF == cc unless cc is known to fit). For our t, `t & 0xFFFF` — the compiler knows t = (s16)a1, and t==5 in the branch. So `t & 0xFFFF` given t==5 is 5 — the compiler folds. Hmm, but if the compiler doesn't propagate the t==5 knowledge to the mask... Actually, the compiler (jump.c) knows t==5 on the fall-through of `bne t,5,L71`. So `t & 0xFFFF` = 5, and `!= 3` is true. It might fold the whole thing to `goto sel_094`, removing the branch. But the target has a branch.

Hmm, but the wall note says the mask keeps the check. Maybe the mask is applied BEFORE the branch so the compiler can't propagate. Let me think: if I write:
```
if (t == 5) {
    s32 u = t & 0xFFFF;
    if (u != 3) goto sel_094;
    ...
}
```
The compiler knows t==5 -> u = 5, so u != 3 is true. It folds. Unless the compiler doesn't propagate through the `&` for the branch... It should.

Hmm, maybe the mask is applied to the CONDITION variable in a way that the compiler treats as a new value: `if ((t & 0xFFFF) != 3)` where the compiler knows t==5 -> (5 & 0xFFFF) = 5 != 3 -> true. Folds.

So the mask wouldn't help here either. Unless the compiler doesn't do the constant propagation in jump.c for the masked expression.

Let me just test: v2: `if ((t & 0xFFFF) != 3)`. And v3: `t = t & 0xFFFF;` before the check (but that changes t and adds code).

Actually, let me first test the simplest restructurings and see the scores. Let me test:
- v1: c1 (4)
- v2: `if ((t & 0xFFFF) != 3)`
- v3: `if ((s16)a1 != 3)`
- v4: `do { if (t != 3) goto sel_094; } while (0);`
- v5: switch-based restructure.

Let me generate and score.

Actually, wait. Let me reconsider the target's branch structure once more. The target:
```
beq t,3,L70       # if t==3 -> L70 (sel_054)
li v0,5
bne t,5,L71       # if t!=5 -> L71 (after)
#APP #NO_APP
bne t,3,L73       # if t!=3 -> L73 (sel_094)
L70: sel_054
```
Hmm, so the fall-through after `bne t,5,L71` is t==5. Then `bne t,3,L73` — since t==5, t!=3 is true, so it always jumps to L73. So the `bne t,3,L73` is effectively an unconditional jump to L73! But the compiler emitted it as a conditional branch (not a `j`). That's the "redundant test on a known value" that the launder prevented folding.

Without the launder, the compiler replaces `bne t,3,L73` with `j L73` (or merges it). Mine: `beq t,5,L73; j L71` — hmm, that's different: mine merged the `bne t,5,L71` and `bne t,3,L73` into `beq t,5,L73; j L71`. So mine effectively does: if t==5 goto L73 else goto L71. Which is the folded form.

So to match, I need the compiler to NOT merge. 

Is there a real-C formulation that produces `bne t,5,L71; bne t,3,L73`? Only if the compiler doesn't know t==5 at the second branch. 

Hmm, what if the second check is in a block that's also reachable from the t==3 path? Let me design:
```
if (t == 3) goto sel_054;
if (t == 5) goto check;
goto after;
check:
    if (t != 3) goto sel_094;
sel_054: ...
```
The `check` block has one predecessor (the t==5 branch). Jump.c knows t==5. Threads.

What if `check` is also reachable from somewhere with a different t? Like from the `t==3` path (but then t==3, and the check would be false, going to sel_054). Hmm, but that changes the semantics: if t==3, we want to go to sel_054 without the check. If I route t==3 through the check, the check `t!=3` is false, so it falls to sel_054. Same result! So:
```
if (t == 3) goto check;
if (t == 5) goto check;
goto after;
check:
    if (t != 3) goto sel_094;
sel_054: ...
```
Now `check` has TWO predecessors: t==3 and t==5. Jump.c can't assume t==5. The check `t != 3` is real (for t==3 it's false, for t==5 it's true). The emitted code: `beq t,3,check; bne t,5,after; check: bne t,3,sel_094; sel_054: ...`. 

Target: `beq t,3,L70; bne t,5,L71; bne t,3,L73; L70: sel_054`. 

Hmm, in the target, `beq t,3,L70` goes to L70 (sel_054), NOT to the check. And `bne t,3,L73` is the check. So the target's t==3 path skips the check. My restructure routes t==3 through the check (which is false -> falls to sel_054). The emitted code would be `beq t,3,check` where check is `bne t,3,sel_094`. So t==3 -> check -> bne (false) -> sel_054. The code: `beq t,3,L_check; bne t,5,L_after; L_check: bne t,3,L_sel094; L_sel054: ...`. That's `beq t,3,L_check; bne t,5,L_after; L_check: bne t,3,L_sel094`. 

But the target has `beq t,3,L70` where L70 is sel_054 directly, and then `bne t,5,L71; bne t,3,L73`. So the target's structure is different: the t==3 path goes directly to sel_054, and the check block has only the t==5 predecessor.

Hmm. So my restructure would produce `beq t,3,check; bne t,5,after; check: bne t,3,sel094; sel054:` — which is logically the same but the branch target differs (check vs L70). The emitted code might be:
```
beq t,3,Lcheck
bne t,5,Lafter
Lcheck:
bne t,3,Lsel094
Lsel054:
...
```
vs target:
```
beq t,3,L70
bne t,5,L71
bne t,3,L73
L70:
...
```
These differ in the branch target (Lcheck vs L70) and the layout. But maybe the compiler lays it out such that Lcheck == L70? If sel_054 immediately follows the check, then `beq t,3,Lcheck` and Lcheck is the `bne t,3,...` insn. So the t==3 path would execute the `bne t,3` (false) then fall to sel_054. That's an extra branch executed (but no extra insn in the code). The target's t==3 path jumps directly to sel_054 (skipping the bne). So the target's layout has sel_054 before the check? Let me look at the target layout:
```
$L68:
	beq	$16,$3,$L70
	li	$2,5
	bne	$16,$2,$L71
 #APP
 #NO_APP
	bne	$16,$3,$L73
$L70:
	la	$2,D_8018C520
	j	$L60
$L73:
	...
$L71:
	...
```
So L70 (sel_054) is right after the check, and the t==3 branch targets L70 (skipping the check). So the t==3 path skips the check.

In my restructure, the t==3 path goes THROUGH the check (executing the bne, which is false). That's a different control flow but same result. The emitted branch target would be the check, not sel_054. Hmm.

But maybe the compiler would still emit the target's code? Unlikely.

Let me just TEST the restructure and see. Let me create v5 with the shared-check restructure.

Also, let me test v2/v3/v4.

Let me generate:
- v2: `if ((t & 0xFFFF) != 3)` 
- v3: `if ((s16)a1 != 3)`
- v4: `do { if (t != 3) goto sel_094; } while (0);`
- v5: shared-check restructure (explicit gotos)
- v6: switch restructure

Let me write v5 carefully. The original:
```
        if (t == 3) {
            goto sel_054;
        }
        if (t == 5) {
            __asm__ (...);
            if (t != 3) {
                goto sel_094;
            }
        sel_054:
            sel = (u32)&D_8018C520;
            goto set_sel;
        sel_094:
            ...
        }
        if ((func_800291B4(D_801802E4[t]) & 0xFF) == 0) {
```
v5: replace the t==3 goto and the t==5 block with a shared check:
```
        if (t == 3) {
            goto sel_054;
        }
        if (t == 5) {
            goto sel_054_chk;   // hmm
        }
```
Hmm, this is getting complicated. Let me just test v2/v3/v4 first, and if they fail, consider v5.

Actually, let me reconsider. The simplest real-C idea: since the `if (t != 3)` is redundant when t==5, the compiler folds it. What if I make the inner check depend on a value that's NOT t, but a copy that the compiler can't equate? For example, a value loaded from a global that I set to t earlier? That adds code.

What if the inner check uses `a1` cast differently: `if ((s32)(s16)a1 != 3)` — the compiler knows (s32)(s16)a1 == t. Folds.

What if `t` is `volatile`? extra code.

Hmm.

Let me look at the wall entry for flow-known-value (G22) — it says "a (cc&0xFFFF) mask keeps it but costs 1 andi (best 10)". So the mask prevents the fold in that case. Let me test the mask here: `if ((t & 0xFFFF) != 3)`. If the compiler folds (t==5 -> 5 != 3 true), it removes the branch. If it doesn't, it emits andi + compare. The target has just `bne t,3`. So the mask would add an andi (not matching). Unless the andi is folded away but the branch kept? Unlikely.

Let me just test.

Actually, wait — maybe there's a subtlety: the target's `bne t,3,L73` compares t (in $16) with 3 (in $3). If I write `(t & 0xFFFF) != 3`, the compiler would compute t&0xFFFF into a temp and compare. That's an extra andi. Not matching.

Hmm.

Let me test v2/v3/v4 and see.

Actually, let me reconsider the whole thing: maybe the crack is to remove the redundancy differently. The target's `bne t,3,L73` is redundant (t==5). But the C has `if (t != 3) goto sel_094;` inside the t==5 block. What if I restructure the C so that this check is NOT redundant — i.e., the t==5 block is reached with t possibly != 5? 

Hmm, the block is only reached when t==5. 

What if I merge the t==3 and t==5 handling:
```
if (t == 3 || t == 5) {
    if (t != 3) goto sel_094;
sel_054: ...
}
```
Then the block is reached when t==3 or t==5. The check `t != 3` is real (t==3 -> false, t==5 -> true). The compiler can't fold! Let me check the emitted code:
```
if (t == 3 || t == 5) { if (t != 3) goto sel_094; sel_054: ... }
```
The compiler would emit: `beq t,3,enter; bne t,5,after; enter: bne t,3,sel094; sel054: ...`. Hmm, that's `beq t,3,enter` then `bne t,5,after`. The target has `beq t,3,L70` (L70=sel054) then `bne t,5,L71` then `bne t,3,L73`. 

In my merged version, the t==3 path goes to `enter` (the check), which is `bne t,3,...` (false) then falls to sel054. The target's t==3 path goes directly to sel054 (skipping the check). So the branch targets differ.

BUT — maybe the compiler would lay it out so that `enter` == the check and the t==3 branch targets the check. That's `beq t,3,Lcheck; bne t,5,Lafter; Lcheck: bne t,3,Lsel094; Lsel054:`. That's 3 branches, same as target but with different targets: target has `beq t,3,L70` (sel054) and `bne t,3,L73`. Mine would have `beq t,3,Lcheck` (the bne insn) and `bne t,3,Lsel094`. 

The difference: target's first branch targets sel054 (after the check); mine targets the check. Since t==3 makes the check false, both reach sel054, but the branch target differs, producing different machine code (different offsets). So it wouldn't match byte-for-byte.

Hmm. Unless the layout coincidentally matches. Let me just test it.

Actually, the target's structure is: `beq t,3,L70` where L70 is sel054 (the instruction after the check). And `bne t,5,L71` where L71 is after. And `bne t,3,L73` where L73 is sel094. So the t==3 path skips the check. This is the natural compilation of the ORIGINAL if-structure with the launder.

The `t==3 || t==5` restructure would make the t==3 path go through the check. Different.

Let me test it anyway (v6) — maybe the compiler reorders/lays out to match.

Let me also test v2/v3/v4.

Let me generate and score.
