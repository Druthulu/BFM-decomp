---
ts: 2026-11-06T20:20:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Dh4j2YKqVahjM5KZsd6m
---
Baseline score 10, 54 insns both. Two residual clusters:

1. The barrier: target has `bnez v1,...; nop` (delay slot nop), mine has `bnez v0,...; xori v0,v0,0x1` (reorg filled the delay slot with the xori). The barrier prevented reorg from copying the xori into the bnez delay slot. This is the "dbr-delay-fill" wall family: "delayed-branch fill takes a fall-through insn the target leaves out of the slot (G18x)". 

2. The launder: mine has `jal; lui a1,...` (the constant materialized AFTER the jal in the delay slot? Actually mine: `jal ...; lui a1,0xfff8` — the lui is in the jal's delay slot; target: `lui a1,0xfff8` BEFORE the jal, and the delay slot holds `sh v0,2(s0)`). Let me look: target around 21bc-21c8:
```
21b8: move a0,s0
21bc: lui a1,0xfff8
21c0: li v0,7
21c4: jal func_8012B178
21c8: sh v0,2(s0)      <- delay slot
```
mine: 
```
move a0,s0
li v0,7
jal
lui a1,0xfff8   <- delay slot
...
sh v0,2(s0) later?
```
So the launder's effect: without it, `r = 0xFFF80000` is rematerialized as `lui a1,0xfff8` in the jal's delay slot; with it, the constant is materialized earlier (at its source position) and the store goes into the delay slot.

The launder `asm("" : "=r"(r) : "0"(r))` makes r a "2-set" value (zero-byte re-tie) so combine/sched can't rematerialize the constant at the call.

Real-C replacement: give r a real second set so the constant isn't rematerialized. Like item 2: split a real operation.

`r = 0xFFF80000;` then `func_8012B178(q, r);`. The launder re-ties r to its input (same reg). What real C can prevent rematerialization? Rematerialization happens because the constant is cheap (lui) and used once; combine replaces the arg with a fresh lui at the call. If r were computed with an operation that can't be rematerialized (e.g., `r = 0xFFF80000 | something`), it stays.

Look at the target: `lui a1,0xfff8` — the constant is materialized before the jal, not rematerialized into the delay slot. So in the target the constant insn sits at its source position and reorg doesn't move it into the delay slot (instead the `sh` goes there).

Without the launder, the constant gets rematerialized into the delay slot.

Real-C ideas:
a. `r = (s32)0xFFF80000;` — same.
b. `r = 0xFFF80000 + 0;` — folded.
c. `r = -0x80000;` — same constant (0xFFF80000 = -524288).
d. Make r a `u32`? `u32 r = 0xFFF80000;` — same.
e. Compute r from another variable: `r = s0 & 0xFFF80000;`? Different semantics (the function gets r as an argument; the target passes the constant regardless). Actually what does func_8012B178(q, r) do? The value 0xFFF80000 is the second arg. Changing it changes semantics. But maybe `r = (s32)0xFFF80000u;`.
f. Use a volatile? `volatile s32 r = 0xFFF80000;` would put it on the stack — changes code.
g. Assign r twice: `r = 0xFFF80000; r = r;`? self-copy deleted.
h. `r = 0xFFF80000; r += 0;` — folded.
i. `r = 0x100000 * ...`? For 0x100000 (the other arm) = 1<<20; `r2 = 1 << 20;` — constant folded to 0x100000.
j. The C0414 dead-reset: after the call, `r = 0;`? That gives a 2nd set of r but AFTER the use — does it prevent rematerialization? The launder is a re-tie of r to itself (`"=r"(r) : "0"(r)`), which makes r have 2 sets at the same point (input and output). Hmm, actually the launder's output is a new value in the same reg; it's placed BEFORE the store/call? The launder line is right after `s32 r = 0xFFF80000;` and before the store and call. So r's value after the asm is unknown to the compiler, but constrained to the same register ("0" ties input to output). So the constant is still 0xFFF80000 but the compiler can't rematerialize it (the asm is opaque). It emits the lui at r's definition.

A real-C way to make a value non-rematerializable: make it depend on a non-constant. E.g., `r = (s32)((u32)s0 & 0) | 0xFFF80000;` — identity launder, banned.

Hmm. But maybe we can split a real operation: `r = 0xFFF80000; r |= 0x0;` — identity.

What about making r's value computed from the constant in a way that is a real operation but still yields the same value: e.g., `r = 0xFFF80000 ^ 0;` identity.

Alternatively, prevent rematerialization by making r live longer / used twice: use r twice? e.g., after the call, `if (r) ...`? adds code.

Hmm. Let me think about what actually happens. The launder is a 2-set on r (same reg). What if we give r a real 2nd set that is dead but survives (hard reg? no, r is not pinned). A dead `r = 0;` after the call would be deleted by delete_dead_from_cse (pseudo, dead).

What about the C0414 "dead-reset" trick on a *derived* value: e.g., `r = 0xFFF80000; ... call(q, r); r = 0;` — deleted.

Hmm, but wait: for item 2 the crack was splitting a real operation. Here, maybe we can rewrite the constant as a real computation that the compiler keeps as a distinct insn: `r = 0xFFF80000;` is a single `lui`. What if we write `r = (s32)0x80000; r = -r;`? That's `li r,0x80000` (lui) then `neg r,r` (subu). Target has only `lui a1,0xfff8` (one insn). No.

What if we use `r = 0xFFF80000 >> 1;`? Folds to 0x7FFC0000 — wrong value.

What about `r = 0xFFF80000;` but make the *variable* `r` have 2 sets by also assigning it in the other arm? No, separate scopes.

Alternative approach: maybe the rematerialization is done by combine because r is a constant in a pseudo with a REG_EQUAL note. If we prevent the REG_EQUAL note (e.g., by making the constant not a simple move), combine can't rematerialize. E.g., `r = (s32)(0xFFF80000u + 0);` folded.

Hmm. What about making r's type `u32` and the constant a hex `0xFFF80000u`? Same.

Let me look at what exactly differs: mine has `jal; lui a1,0xfff8` (lui in delay slot) and the sh later; target has `lui a1,0xfff8; li v0,7; jal; sh v0,2(s0)` (sh in delay slot).

So in mine, the constant was rematerialized at the call (in the delay slot) and the store moved after. In target, the constant is at its source position and the store is in the delay slot.

The launder prevented rematerialization. How to do that in real C? Make r's value not a compile-time constant known to combine: e.g., compute it from a global? That changes code (a load).

What if r is assigned from a *volatile*? no.

Wait — maybe we can get the same final code a different way: make the store's scheduling put the sh in the delay slot. The store `((Unk*)s0)->unk2 = 7;` is `li v0,7; sh v0,2(s0)`. Target's delay slot has `sh v0,2(s0)` and the `li v0,7` is before the jal. Mine: `li v0,7; jal; lui a1,...` — wait, mine's listing: let me get the full mine disassembly to see exactly.

From the diff:
```
insert mine[33] target[33:34]: -- | lui a1,0xfff8
insert mine[34] target[35:36]: -- | jal
delete mine[35:37] target[37]: jal | --
                                 lui a1,0xfff8 | --
```
So mine[33] is something else, mine[35]=jal, mine[36]=lui a1, target[33]=lui a1, target[35]=jal. Hmm, target[34] would be `li v0,7`? and mine[34]=? Confusing. Let me get the full disassembly via --keep.

Actually easier: run dt.sh with a big tail and look at the whole mine/target listing. The diff only shows mismatches. Let me get mine's disassembly from --keep.

Let me do that.
