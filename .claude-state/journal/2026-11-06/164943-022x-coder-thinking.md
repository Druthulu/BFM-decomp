---
ts: 2026-11-06T23:49:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4KpC7ZgmhhRYY5piJLcg
---
Useful. Note the last line: "Refused as closes: ... a dead store kept only to steer a pass, a pointer alias invented only to dodge cse." Hmm — so a pointer alias invented only to dodge cse is refused. But the dead-reset C0414 is a documented technique that "cracked 3 launders in G16x" per the brief's MOVES+.

OK. So the dead-reset is legitimate. But does it help here? The mechanism here is the copy.

Let me think again about what makes the copy appear. In target:
- q_old = &D_800C7C60 (address computed somewhere)
- asm: q_new = q_old
- p = q_new

Hmm wait, maybe the address is computed directly into q_new, and q_old is eliminated. So effectively: q_new = &D_800C7C60 (v0); p = q_new (a3).

For C: `q = &D_800C7C60; p = q;` — the question is why cse merges. cse merges because p and q are copies. To prevent, q must have 2+ sets so cse's qty for q is invalidated... no, make_regs_eqv works on the *qty* of the source at that point.

Hmm, actually let's read cse_insn's handling of copies: it calls make_regs_eqv only when the source is a register with a valid qty and... let me look. Actually the key question: after `q = &sym`, q has a qty (the address constant). Then `p = q`: cse makes p eqv q (canonical). Then p's uses become q. So p disappears. The address lives in one reg.

For target, p survives. Why? Because cse's table is *cleared* at the asm (an asm invalidates the table: `if (insn_invalidates ...) `). After the clear, q_new has NO qty. Then `p = q_new`: make_regs_eqv requires REGNO_QTY_VALID_P(old) → q_new has no qty → so it does NOT equate; instead it creates a new qty for p? Then p and q_new are different. Hence the copy survives!

So the requirement: at the point of `p = q`, q must have NO valid cse qty (i.e., cse's table must have been invalidated between the address set and the copy).

A C construct that invalidates cse's table between the address computation and the copy: a function CALL! (cse clears the table at calls? Actually cse handles calls specially — it invalidates memory but keeps regs... hmm, calls clobber caller-saved registers but cse's table for pseudos may survive).

What else invalidates: a label/jump target? A `setjmp`? Actually cse.c: `if (GET_CODE (insn) == CALL_INSN ...)` it invalidates things.

Hmm, but here between q = &sym and p = q there's nothing in the target (the asm is the barrier). 

Alternative: make q's value come from a *different* cse qty so that the copy isn't merged. E.g., q = something the compiler can't fold into a constant. But it must be &D_800C7C60.

What if q is a *parameter*? No.

What if q is loaded from memory? e.g. `s32 *q = *(&some_ptr)` — adds a load.

Hmm, what about a statement that invalidates cse between the two: `func_8002F658()` is called right before! Look:
```
if (func_8002F658() != val || mode >= 0) {
    s32 *q = &D_800C7C60;
    __asm__("" : "=r"(q) : "0"(q));
    p = q;
    *p = val;
    D_800C7C64 = &D_800A2E20;
}
```
The call is before the block. The address is computed after the call.

What if we compute q BEFORE the call? Then the call invalidates cse, and `p = q` after the call can't be merged! That's a real C move: hoist the address computation above the `if (func_8002F658() != val || mode >= 0)`.

But careful: the block is conditional; hoisting q = &D_800C7C60 out of the block would add insns on the else path... but the compiler might sink it. Hmm, but it's a constant address, so it's cheap and might be sunk by sched1.

Hmm, wait. Actually if q is computed before the call and used after, cse's qty for q at the copy point: the call invalidates q's qty? cse invalidates memory at calls and caller-saved hard regs, but pseudos are not invalidated (they're not in the table's invalid set... actually cse marks all pseudos as invalid if the call can clobber them? Pseudos live across calls are not clobbered). Hmm, the address in q would still be known.

Hmm, but there's `cse_basic_block` boundaries. 

OK let me stop theorizing and just try candidates. Empirical is faster. Let me write several and score them in one sc.sh call.

Candidates for item 1:
A. hoist address above the if:
```
s32 *q = &D_800C7C60;
if (func_8002F658() != val || mode >= 0) {
    p = q;
    *p = val;
    D_800C7C64 = &D_800A2E20;
} else {
    p = 0;
}
```
B. dead-reset after store:
```
s32 *q = &D_800C7C60;
p = q;
*p = val;
q = 0;
D_800C7C64 = &D_800A2E20;
```
C. dead-reset on the address temp:
```
s32 *q = &D_800C7C60;
p = q;
q = 0;
*p = val;
D_800C7C64 = &D_800A2E20;
```
D. two-step through u32:
```
u32 a = (u32)&D_800C7C60;
s32 *q = (s32 *)a;
p = q;
```
E. `p = &D_800C7C60; q = p; *q = val;` (reverse roles)
F. q used after the copy: 
```
s32 *q = &D_800C7C60;
p = q;
*p = val;
D_800C7C64 = q;  // wrong value, no
```
no.

Let me also consider that maybe the correct approach is different: perhaps make `p`'s register a3 by making p used elsewhere, and get the address into v0 via a call... 

Let me just test A-E quickly.

I'll generate them with a script (Write tool for a script? The brief says scripts, not inline python -c). I can use sed/awk in bash though — that's a command, not inline python. Let me write a small shell script via Write under the item dir. Actually simpler: create the candidate files with the Write tool directly (they're small). Let me do that.

Actually the whole body is 85 lines; writing 5 full files is verbose. Better: use sed on orig.c to produce variants. Let me do it with a bash script written to the item dir.

Plan: write a script `gen.sh` in the item dir that takes orig.c and applies transformations. Hmm, easier: use sed with line-specific edits. The block is lines 1000-1008 in orig.c terms... In orig.c (which starts at line 936), the block is at relative lines 65-73 (1000-936+1=65). Let me verify: orig.c line 65 = `if (func_8002F658() != val || mode >= 0) {`.

Let me write the variants using a python script (a real script file, not -c).
