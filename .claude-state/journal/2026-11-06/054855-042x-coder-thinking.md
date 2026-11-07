---
ts: 2026-11-06T12:48:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_frWfzBCARdHonkWrh3FR
---
e2 (swapped arms, if(!tc) first):
```
ba78 andi v0,a1,0x10
ba7c bnez v0, ba8c      ; if tc goto ba8c (the tc arm)
ba80 andi v1,t0,0xffff  ; delay slot
ba84 j ba90
ba88 move a0,v1         ; else: ua = ub  (delay slot of j)
ba8c addiu a0,v1,-256   ; tc arm
ba90 join
```
Target (from diff):
```
andi v0,a1,0x10
beqz v0, ba8c
<delay slot>
j ba90
addiu a0,v1,-256
ba8c: move a0,v1
ba90: join
```
So target has the *else* block (move a0,v1) at ba8c, and the *tc* arm fall-through with j+addiu. Mine has them swapped: tc arm at ba8c, else fall-through with j+move.

So target = `if (tc) {ua = ub-0x100;} else {ua = ub;}` laid out as: beqz → else; fall-through tc arm; j; else block. Mine (f1, same source) = beqz → join, delay-slot move, addiu. Different dbr choice.

And e2 (if(!tc) first) = bnez → tc arm at ba8c; fall-through else with j+move.

So target = "if (tc) first" source with dbr NOT threading, and e2 = "if (!tc) first" with dbr threading the else.

Hmm: in target, the branch `beqz v0, ba8c` targets the else block which is at ba8c; the fall-through is the tc arm (addiu) with a `j` to join. That's the *default* layout when dbr does not thread.

So I need dbr to not thread. In e2, dbr threaded by moving the else's single insn into... wait e2 also has a j and the move in the j's delay slot. So e2 is actually the *same* structure but with the arms swapped: branch to the tc arm at ba8c; else fall-through = j ba90; move a0,v1 in the j delay slot.

Target: branch to else at ba8c; tc fall-through = j ba90; addiu in j delay slot.

So both have: branch to one arm, other arm = j + delay. The difference is WHICH arm is out-of-line. Target puts the *else* (move) out-of-line; e2 puts the *tc* arm out-of-line.

For f1 (if tc first), mine put the else's move in the beqz delay slot — a different, more aggressive fill.

So: to match target, I need the tc arm as fall-through (with j+addiu) and the else out-of-line at ba8c — exactly f1's *source*, but f1's dbr chose the eager fill.

The difference between target and f1 must come from the barrier in the else making the else block 2 insns (asm + move), so dbr couldn't thread it into the delay slot, and instead used the j layout.

Real-C way to make the else block 2 insns: hmm.

What if the else arm contains a real second statement that is needed? e.g. `ua = ub; tc = 0;`? Dead.

What if I use `ub = ub;`? dead.

What about making the else arm assign to a volatile-ish? No.

Alternative: what if the *condition* is computed in a way that makes the branch's delay slot unavailable? Hmm.

Alternative approach: use `&&`/`||` folds or a different control shape that yields the same 8 insns. For instance:

```
if (!tc) {
    ua = ub;
} else {
    ua = ub - 0x100;
}
```
= e2 (score 3, but arms swapped).

What about `if (tc == 0) ua = ub; else ua = ub - 0x100;`? Same as e2.

What about the whole thing as:
```
ua = ub;
if (tc) {
    ua = ub - 0x100;
}
```
f2 = 10.

Hmm, what about making the branch condition `tc != 0` with a temp:
```
s32 dv = 0;
if (tc) dv = 0x100;
ua = ub - dv;
```
That's 2 branches/insns. Target has one branch. No.

Let me look at this from a different angle: is the difference maybe in `if (id & 0x100)` blocks? No.

Given time (~35 min already on item 1), let me consider: the best lever-free score so far is 3 (e2). That's a WALL if I keep a barrier... but e2 has NO barriers and scores 3. So it's a lever-free body with score 3 → WALL (since not 0). The rule: "WALL (best = lowest score of a lever-free body)". So item 1 could be WALL with best 3, if I can't crack it.

But wait — I have budget. Let me try a few more ideas for barrier 3, then decide.

Idea: make the else arm's move come from a different pseudo so dbr can't thread. E.g., `ua = ub;` where ub is assigned right before... 

Idea: use a `do {} while (0)` with the *if* inside but with the else containing two statements:
```
if (tc) {
    ua = ub - 0x100;
} else {
    ua = ub;
    ua = ua;
}
```
g4 = 10 (folded).

Idea: what if the else arm writes a *different* variable that's then copied? e.g.
```
if (tc) {
    ua = ub - 0x100;
} else {
    ua = ub;
}
```
→
```
if (tc) {
    ua = ub - 0x100;
} else {
    ua = ub;
}
ub = ua + rec->h - 1;
```
already.

Idea: increase the register pressure in the else so dbr can't thread: no.

Idea: since dbr's eager fill requires the insn to be in the "thread" (the fall-through target), maybe making the branch target the else and the fall-through the tc arm with an explicit j is what happens when the else block has >1 insn. Let me check if adding a genuinely needed second insn to the else arm is possible: e.g., the else could compute `tc = 0;`? Dead. Or `ub = ub;`? Dead.

Hmm — what about making the else arm do `ua = ub` where ua is declared as a different type... 

Different idea: maybe use the *original* barrier-3 position but with a real statement that gcc cannot delete: a *store* to a memory location that's then overwritten? Not semantics-preserving.

OK — alternative: change the branch so it's a `beqz` on a *different* expression whose delay slot is naturally filled by something else. E.g.:
```
tc = tpage & 0x10;
ub = sy;
ua = ub;
if (tc) ua -= 0x100;
```
f2 = 10.

Let me try: `if ((tpage & 0x10) != 0) { ua = ub - 0x100; } else { ua = ub; }` — the andi may be folded differently.

And: `if (tpage & 0x10) ...` directly without the tc var (but tc is used? only here). Target has `andi v0,a1,0x10` and uses tc nowhere else? Let me check: `tc = tpage & 0x10;` used only in `if (tc)`. So removing the tc variable → `if (tpage & 0x10)`. Try it.

Also try: put the `ub = sy;` assignment after the branch:
```
tc = tpage & 0x10;
if (tc) {
    ub = sy;
    ua = ub - 0x100;
} else {
    ub = sy;
    ua = ub;
}
```
g3 was similar (with ub=sy inside) = 10.

Let me try the direct condition and a couple of shapes, then stop on item 1 with best 3 as WALL if nothing works. Actually — wait. Let me reconsider the possibility that the target's layout comes from the *asm barrier* being in the else, and the real-C equivalent is a statement that survives into RTL in the else: a `do{}while(0)` around the else body survived (g1) but still 10.

Hmm, g1 had `else { do { ua = ub; } while (0); }` = 10. So dbr still threaded. Meaning the do-while didn't create an extra insn.

What about `else { if (1) ua = ub; }`? The constant-if is folded.

What about `else { ua = ub; if (0) tc = 0; }`? folded.

Let me try the direct-condition variant and one with the arms as a ternary assigned to ua:
```
ua = tc ? ub - 0x100 : ub;
```
f3 was `ua = ub - (tc ? 0x100 : 0)` = 10. Let me try `ua = tc ? ub - 0x100 : ub;`.

Let me run these three.
