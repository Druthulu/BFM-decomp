---
ts: 2026-11-06T15:11:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8V5jbk54qTm7VEqINF3a
---
Hmm, the instruction indices in the diff are per-function counting from the start. Let me get the exact region: diff said mine[90] ↔ li v0,3. Let me print with line numbers. The objdump addresses: function starts at 0x5c8? Let me find. Actually easier: dump all and use awk with a counter.

Let me dump both and number instructions 0..N-1.

I'll write a small helper? Or use objdump + grep. Let me just extract the function region and number.

Actually, the diff already tells me enough:
- mine[90]: li v0,3 ; target[90]: li v1,3
- mine[95]: beq s0,v0,70c ; target: beq s0,v1,70c
- mine[97]: beq s0,v0,71c ; target: bne s0,v0,740
- mine[99]: j 740 ; target: bne s0,v1,71c

So the target has an extra comparison sequence: beq s0,v1(t==3) → 70c; bne s0,v0(t!=3) → 740; bne s0,v1 ... hmm.

Wait, with the launder, t is opaque; the source is:
```
if (t == 3) goto sel_054;      // compare 1
if (t == 5) {                  // compare 2
    launder(t);
    if (t != 3) goto sel_094;  // compare 3
sel_054: ...
```
Target code likely:
- li v1,3
- beq s0,v1,sel_054
- li v0,5
- bne s0,v0,sel_094 (if t != 5 skip to after the if)
- bne s0,v1,sel_094  ← the launder's test (t != 3)
- sel_054: ...

Mine without launder:
- li v0,3 (target li v1,3)
- beq s0,v0,sel_054
- li v0,5
- beq s0,v0,... then within the if: t is known 5, so `if (t != 3)` folds to always true → j sel_094. And since the fall-through into sel_054 is dead... hmm mine has `beq s0,v0,71c` and `j 740`.

So the launder is load-bearing to keep the `if (t != 3)` test as a real compare, even though t==5 is known.

To crack: plain C must keep a real `t != 3` test after `t == 5` is known. That's the "flow-known-value" wall (moves line: func_8018656C "flow: the empty asm is a USE of diff ..."). Hmm.

But note the score is only 4 — the register pair v0/v1 swap plus the branch shape. So it's close.

Idea: restructure so the `t != 3` test isn't provably dead. E.g., replace the launder with a real 2nd set of t that is value-preserving but opaque... 

Actually, maybe simpler: reorganize the if-chain so that the `t != 3` test compares a *different* variable whose value is not known. E.g., use `sel` or another variable.

Think about what the code means:
```
t = (s16)a1;
if (t == 0) { sel = &D_801C3C70; goto set_sel; }
if (t == 3) goto sel_054;
if (t == 5) {
    launder(t);
    if (t != 3) goto sel_094;
sel_054: sel = &D_801C3C94; goto set_sel;
sel_094: if ((func_800291B4(0x40) & 0xFF) == 0) goto call_45F;
    sel = &D_801C3CD4; goto set_sel;
}
...
```
At runtime with t==5: the launder test is true → goto sel_094. sel_054 is only reached from t==3. So this is equivalent to:
```
if (t == 3) { sel = &D_801C3C94; goto set_sel; }
if (t == 5) {
    if (t != 3) goto sel_094;   // always true
    ...
}
```
But the compiler with the launder keeps the test.

To keep a `t != 3` test in plain C after `t == 5`, we need the compiler to not know t. Options:
- Reassign t to something opaque (but value-preserving).

What plain-C value is opaque and equals 5? Hmm.

Alternatively, restructure the control flow to naturally produce the same branches. The target has:
```
li v1,3
beq s0,v1,sel_054      # t==3
li v0,5
bne s0,v0,<after if>   # t!=5
bne s0,v1,sel_094      # t!=3
```
The last `bne s0,v1,sel_094` is the launder's test. Since t==5 known, this is always taken; the fall-through goes to sel_054 (dead).

Can we write plain C that generates `bne t,3,sel_094` naturally? If the source has `if (t != 3) goto sel_094;` and the compiler doesn't know t==5. What if we *reorder* the tests: check `t == 5` before `t == 3`? Then:

```
if (t == 0) ...
if (t == 5) {
    if (t != 3) goto sel_094;
sel_054: ...
} else if (t == 3) goto sel_054;
```
Hmm, then the compiler knows t==5 inside and still folds t!=3.

What if we merge the two tests so the same variable is tested but the compiler loses track? The compiler's knowledge comes from the branch `t == 5` dominating. If we use a *copy* of t made before the branch, the copy is known too (cse).

What if the `t != 3` test is on a *different variable* that also holds 5 but whose value the compiler can't prove? E.g., `s16 u = (s16)a1;` then compare u. But cse knows u == t.

Hmm.

What about making the t==5 test not dominate — e.g., use a switch/if structure where the `t != 3` test is in a block reached from multiple paths, one of which doesn't know t. In the target, sel_094 is a shared label? Let's look: sel_094 is reached from the launder test AND from... only within the if. Hmm.

Alternatively: what if the `if (t != 3)` is placed in a block that's also reachable via the `t==3` path? Then the compiler couldn't know t==5 there.

Look at the original source structure: 
```
if (t == 3) goto sel_054;
if (t == 5) {
    if (t != 3) goto sel_094;
sel_054:
    sel = &D_801C3C94;
    goto set_sel;
sel_094:
    ...
}
```
Since sel_054 is inside the t==5 block but jumped to from outside (goto), the label is shared. The launder's test controls the fall-through into sel_054.

Equivalent plain C restructure: maybe write it as a switch with fallthrough? Or:

```
if (t == 3) {
    sel = &D_801C3C94;
    goto set_sel;
}
if (t == 5) {
    ... sel_094 body ...
}
```
This removes the `t != 3` test entirely (2 fewer branches) — different code.

Hmm. To keep the test, the C must contain a comparison that the compiler can't fold. 

What about comparing against a variable that the compiler doesn't know? The target's `bne s0,v1` where v1 = 3 (li v1,3). If we compare t against a variable `c = 3` that cse doesn't fold... The moves catalog line 134 says a hard-reg addend can't be folded. But comparing against a variable c=3 — cse would know c=3 and fold the compare to a constant compare... it might still emit `bne s0,v1` with li v1,3 if it doesn't substitute constants into compares? Hmm, in the target, li v1,3 then beq s0,v1 — that's a compare against a constant loaded in a register. gcc's mips.md has `beq` with a register operand.

Hold on — the target uses v1 for the constant 3 in beq s0,v1, while mine uses v0. That's a register allocation difference (v0->v1 x2). The main issue is the branch structure.

Let me think about the C source that produces target's code. Target:
```
li v1,3
beq s0,v1,L70c      # if (t == 3) goto sel_054
li v0,5             (probably at 96)
bne s0,v0,L740      # if (t != 5) goto <after>
bne s0,v1,L71c      # if (t != 3) goto sel_094
L70c: (sel_054) sel = &D_801C3C94; goto set_sel
L71c: (sel_094) ...
```
Wait the target diff: mine[97] beq s0,v0,71c ↔ target bne s0,v0,740; mine[99] j 740 ↔ target bne s0,v1,71c.

So target has at 97: `bne s0,v0,740` and at 99: `bne s0,v1,71c`. Hmm, indices: target[97]=bne s0,v0,740; target[98]=? (mine[98] matched something); target[99]=bne s0,v1,71c.

So target:
- 95: beq s0,v1,70c   (t==3 → sel_054)
- 96: li v0,5
- 97: bne s0,v0,740   (t!=5 → skip the whole if)
- 98: (delay slot? something)
- 99: bne s0,v1,71c   (t!=3 → sel_094)
- 100: (fall through to 70c sel_054)

That matches: `if (t == 5) { if (t != 3) goto sel_094; /* fall to sel_054 */ }`.

And mine:
- 95: beq s0,v0,70c
- 97: beq s0,v0,71c  (t==5 → 71c?) hmm mine's structure differs: because t==5 known, `if (t != 3)` folded to true, so it becomes `goto sel_094`, i.e., `j 740`? and the t==5 test... 

Mine at 97 is `beq s0,v0,71c` and 99 `j 740`. So mine does: if (t==5) goto 71c (sel_094), then j 740. Hmm, meaning the t==5 body was inverted.

Anyway, to match we need the extra `bne t,3` test to survive.

Plain-C ideas:
1. Use a `switch(t)` with cases 3 and 5 and fallthrough? Switch might generate a jump table (bad).
2. Make the compiler lose knowledge of t between the `t==5` test and the `t!=3` test by introducing a function call? A call would clobber... but t is a local (callee-saved). cse/flow: after a call, the compiler still knows t? t is in a register; if it's a local pseudo, the call doesn't change it (saved across calls). flow's constant tracking: `s0 = t` in a register; the call doesn't clobber callee-saved regs, but flow doesn't track constants through calls? Actually the value is known because t==5 from the branch; a call doesn't invalidate that. And adding a call changes codegen anyway.
3. Use `volatile`? lever.
4. The "flow-known-value" wall (moves line 273): "flow knows cc==1 on the fall-through so the 2nd if(cc==one) folds (89 ins); real 2nd sets fold; a (cc&0xFFFF) mask keeps it but costs 1 andi (best 10)". Hmm, `(cc&0xFFFF)` mask keeps the test but costs an andi. Here maybe `(t & 0xFFFF) != 3`? t is s16 promoted; t & 0xFFFF = 5, the compiler knows. Hmm, but the mask might prevent the known-value propagation? In that wall it "keeps it but costs 1 andi".

5. Reassign t before the test in a value-preserving way: `t = (s16)a1;` again — cse knows.
6. Use `t = t;` — no-op, likely removed. But flow's constant tracking: `t = t` might create a set that invalidates? Actually combine's get_last_value for the compare follows LOG_LINKS to `t = t` which is a copy... it would then follow further. cse might delete it.

Hmm, what about a real 2nd set that is value-preserving and opaque to the compiler: e.g., `t = (s16)(u16)t;`? The compiler knows t=5 → folds to 5. 

What about making t a `s16` and reading it through a union/memory? e.g. `t = *(s16 *)&t;` — address-taken → memory, changes allocation.

Hmm. What about this: the launder is inside `if (t == 5)`. What if we restructure so the `t != 3` test is on a value that comes from a *different* source: e.g. compare `a1 != 3` instead of t. `a1` is the original argument; the compiler knows a1's low 16 bits == t. But does it? `t = (s16)a1`, and `t == 5` implies (s16)a1 == 5, so a1's low bits are 5. Would the compiler derive `(s16)a1 != 3`? cse's fold might not relate a1 and t if there's a truncation. Actually `t = (s16)a1` is a sign-extension of a HImode value; comparing a1 (s32) to 3 is a different comparison. The compiler might not know a1's value (it only knows t=5). So `if ((s16)a1 != 3) goto sel_094;` — the compiler might not fold, emitting a real compare of a1 against 3. But then the register would be a1's, not t's — could differ.

Hmm wait: but at the point `t == 5` is known, the compiler knows `(s16)a1 == 5` if it tracks that t is derived from a1... cse records the equivalence `t == (s16)a1`? Possibly.

Let me look at the actual source context more: the case 5 block also uses `t` later (`func_800291B4(D_80183478[t])`, `t == 0xC`, etc.). 

Alternative idea: change the structure to use a `goto` label ordering that makes the `t != 3` test's block reachable from the t==3 path too. E.g., make sel_054 fall into the test:

Actually, here's a thought: what if we put the `if (t != 3)` test BEFORE the `if (t == 5)` test, but structured so the target's branch order is preserved? No.

Let's think about what determines the target's code: the source probably is exactly the orig.c with the launder. We need a lever-free equivalent. The wall tag candidates: flow-known-value.

Idea from moves line 273: a `(cc & 0xFFFF)` mask keeps the test but costs an andi. Here: `if ((t & 0xFFFF) != 3)`. Hmm, but t is s16; `t & 0xFFFF` yields an int; the compiler knows t=5, so 5&0xFFFF=5, still folds. The wall said the mask "keeps it but costs 1 andi" — maybe because the mask forces a real AND instruction whose result isn't tracked. But then we'd have an extra andi (279+1 ins). Not matching.

Hmm. Let me look at the score-4 diff more carefully: only 5 instructions differ, and it's a MIXED class. Maybe a different restructure gives the exact branches.

Let me look at the target's full case-5 region vs mine to understand exactly. Let me dump both with numbered instructions. I'll write a script to print numbered insns for a function from an object.

Actually simpler: objdump the target and candidate objects and extract the region. Let me get the target region addresses. Function start? Let me grep the symbol.
