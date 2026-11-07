---
ts: 2026-11-06T06:37:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vNsZvSk1P5wYkSUPiHES
---
In the target (pin present), there's no r73 as a global allocno — t is a hard reg so it's not in the alloc order. The order is 76 72 74.

So in the target, the compare temp and the others get v1 etc.

Now, in my candidate, r73 = t is a global allocno with 13 refs/14 live → pri 27857, conflicting with v0.

The question: why does t conflict with v0 in my candidate but not in the target? Because in the target t is a hard reg, so flow... hmm, flow's conflict recording is independent of whether it's a hard reg. The conflicts are computed on the RTL.

OH WAIT. I see it: in the target, the launder is present. The launder `asm("" : "=r"(t) : "0"(t))` — hmm.

Hmm, but the conflict is about t being live across the call. In the target, t is the *call target*: the RTL is `(call (mem (reg 73)))` — if t is still live at the call insn (as the target register), flow marks it live at the call → conflict with call-clobbered v0.

In the target's RTL, is t still live at the call? The launder puts a set of t before the call. Hmm.

Actually, let me look at the .flow dump of my candidate for the conflicts. Hmm, that's not in the dumps.

Alternative explanation: in the target, the call target computation is `lw $2,D_801D0A3C($2)` — the loaded function pointer in $2, then `jal $31,$2`. So the CALL's target is the *loaded value* (a new pseudo), not t. t (the index) dies at the load. So t doesn't conflict with v0.

In my candidate, is the same structure? Mine's tail from the diff at 29-32:
```
29  lhu	v1,2(a1)     | 29 lhu v0,2(a1)
...
31  ...
```
Let me see mine's full tail. From the earlier diff:
```
29  lhu	v1,2(a1)     | lhu v0,2(a1)
replace mine[31:32]
```
Let me print the full diff tail.

Hmm, let me instead reason about the alloc order: my r73 (t) has 13 refs and conflicts v0. Since it's first in the order, if it can't take $2 it takes $3 (v1). Then the rest follow.

So the crux: t conflicts with v0 in my build. If I can make t NOT conflict with v0, it takes $2 (first in order) and everything else follows → likely score 0.

Why does t conflict with v0? Let me find out by checking the RTL. In my .lreg dump, the function's block 4 RTL. Let me print it properly (lines 20545+ up to the next function header).

Let me find the next ";; Function" after 20545 in c.i.lreg.

Actually, from the "Registers live at start: 29 30 72 73" for block 4, t (73) is live at the start of block 4. And the call is in block 4. So t is live across the call → conflicts with v0.

But in the target, t is ALSO live across the call in the same source... unless the launder changes it.

AH WAIT. The launder! `t = unk2; __asm__("" : "=r"(t) : "0"(t)); D_801D0A3C[t](a0);`

The asm sets t from t. In RTL: `(set (reg 73) (asm_operands ...))`. This makes t live *into* the asm and out of it. Hmm, that doesn't change liveness at the call.

Hmm. But maybe with the asm, the call target computation differs: the asm forces t into a register at that point, so `(mem (plus (reg t) ...))`.

Let me look at the actual RTL difference. Let me print my function's block-4 RTL and the target's.

I'm spending a lot on item 3. Let me try quick variants instead:
V1: split t into t (middle) and t2 (tail) — then t (middle) is dead before the call and t2 is local to block 4.
V2: reorder so the tail uses a direct expression.
V3: make the middle t a different type (s16/u16).

Let me generate ~8 variants and score. That's efficient.

Actually, thinking about it more: the simplest fix for "t conflicts with v0" is to make t's live range end before the call. If the tail is `t = unk2; D_801D0A3C[t](a0);` and t is the same variable as the middle, then t's live range... the middle t dies at `unk58 = t` (block 2). The tail t starts fresh in block 4. So t is not live ACROSS blocks 2→4 (it's dead after the store and redefined).

Hmm, but the dump said "Registers live at start: 29 30 72 73" for block 4 — so t IS live at the start of block 4. That means the middle value is still live into block 4?? That can't be right unless the store `unk58 = t` happens in block 4.

Let me look: the CFG blocks:
- block 0: entry, the unkFC test
- block 1: unkFC != 0 body
- block 2: the t = unkA ... unk58 = t part
- block 3: ? 
- block 4: the tail (t = unk2; call)

And "block 4: Registers live at start: 29 30 72 73" — hmm, t live at the start of block 4 means the value from block 2/3 flows into block 4. That would be the case if the store `unk58 = t` is in block 4... 

Wait, actually: maybe block 4 is the join after the if/else (blocks 2 and 3 are the two arms t = D_801D094C / D_801D093C), and then `t |= ...; unk58 = t;` is in block 4. Then the tail's `t = unk2` is also in block 4. So t is live at the start of block 4 (from the arms) — correct.

Then t is redefined in block 4 (t = unk2) and used at the call. So t is live at the call only briefly (the index).

But the conflict with v0 comes from the point where t is live *across* the call? Hmm, t dies at the call target computation.

Hmm, unless the RTL keeps t live until after the call. In the target's asm, `lw $2,D_801D0A3C($2)` then `jal $31,$2`. t ($2) is dead after the lw.

So why "conflicts v0"? Because at the `jal` insn, v0 is live (call-clobbered) and... t is not live.

Hmm, unless the conflict is recorded at the *load* insn: `lw $2,0($2)` — t (r73) is the address base and v0 is... the destination? If the destination is v0 and the base is t, then t and v0 conflict at that insn! Yes! `(set (reg 2) (mem (plus (reg 73) ...)))` — the destination hard reg $2 is live-out, the source reg 73 is used. They conflict at the same insn (both live at the same point).

In the target, t IS $2 and the load is `lw $2,D_801D0A3C($2)` — the same register used as base and destination! That's a valid MIPS insn (read the base, write the dest in one cycle). But gcc's allocator would consider it a conflict... unless t is a hard-reg variable (then no allocation needed).

So in plain C, `t = unk2; ... D_801D0A3C[t](a0)` where the loaded function pointer goes into a pseudo that ends up in $2 → t conflicts with $2.

To avoid: make the loaded function pointer not be $2... but the target has it in $2.

Hmm, in the target's RTL, the table load's destination pseudo would be allocated to $2 (a local pseudo, block 4). And t is a hard reg $2. They coexist in the same insn (base = $2, dest = $2). That's legal for the target's compiler because t is a hard-reg variable — the conflict is not checked for hard-reg variables.

Plain C cannot express that. This is a real wall: "lreg-v0-local-first" or similar. Hmm, but maybe there's a C spelling where the load's base isn't t...

What if the call is written as `D_801D0A3C[((Unkstruct*)a0)->unk2](a0);` (no t)? Then the load is `lhu v0,2(a1); sll; lw v0,...` — the index is a temp. That's different from the target (`lhu $2,2($5)` — same as t's value).

Hmm. Actually the target's `lhu $2,2($5)` loads t (the index) into $2, then `sll $2,$2,2`, then `lw $2,D_801D0A3C($2)`. So t is a single value flowing through $2.

In plain C with t as a pseudo, the sequence would be the same insns but t in some reg and the final load's dest in v0 (since it's the call target). If t were in v0, the base and dest would collide.

So the target's code REQUIRES t in $2 with the dest also $2 — only a hard-reg variable does that.

Hmm, unless... the load's destination pseudo gets a different reg and then `jal $31,$2`? No, the target has `lw $2,...` then `jal $31,$2`.

So: wall. Tag: `lreg-v0-local-first`? Not exactly. Better: a new tag `hardreg-base-dest` or use "cse-copy-merge"? Let me define: `lreg-index-v0-dest` — "the index pseudo must be $2 while the table-load dest is also $2; plain C makes them conflict, so the index takes $3".

Hmm, but wait. Let me reconsider: maybe with a slightly different spelling, the loaded value goes into a different pseudo that gets $2, and t gets... no, we need t in $2.

Actually hold on. What if `t` is made a *local* variable in block 4 with a very short life, and the middle value is a different variable? Then t2 (the index) is block-local; local-alloc gives it $2 first? Then the load dest would conflict with $2... same problem.

Unless local-alloc assigns the index to $2 and the load dest to $3, then the call is `jal $31,$3`? The target has `jal $31,$2`.

So no. WALL.

Hmm, but hold on — is it really true that the target's `lw $2,D_801D0A3C($2)` has the same reg as base and dest? Yes: `lw $2,D_801D0A3C($2)`.

In gcc's RTL: `(set (reg 2) (mem (plus (reg 73) (symbol_ref D_801D0A3C))))` where reg 73 = t pinned to $2. Global/local alloc would record a conflict between the pseudo (r73) and $2 (dest). Since r73 IS $2 (hard reg variable), the conflict is vacuous/ignored.

Plain C: the index pseudo and the dest pseudo are different pseudos; both want $2; the conflict forces one to $3.

Could we make the dest NOT want $2? The dest is the call target — gcc's `call_value`/`call` uses a register; the destination of the table load would prefer... it's just a pseudo that must be in a register for `jal`. It gets $2 by local-alloc (first choice).

What if the table load's result were used in another way first... no, it's the call target.

OK: WALL for item 3, with best = 17 (my lever-free body). But I need ≥30 tries and ≥20 min for a WALL. I have ~4 tries so far. Let me generate a batch of ~26 variants to reach 30.

Let me write the generator with plausible moves:
- split t into t and t2
- direct call expression without t
- different widths (s16, u16 for t)
- reorder statements
- declaration order
- make t u32
- combine the two `t |=` into one statement
- write unk58 = t | 0x60000000
- etc.

Let me do it.
