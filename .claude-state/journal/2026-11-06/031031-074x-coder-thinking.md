---
ts: 2026-11-06T10:10:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_k4inSn3VYu9g3zO45XoT
---
Line 141 is interesting: "pin | func_8012EF34 | MATCH — the game's real prototype is s32, not void: the s32 return keeps $v0 live across the gte_stsz asm, so local-alloc gives the &sp10/load temp $v1 ($3) instead of $v0 ($2) (141/141 includers 0) (G07)". So for void functions with pins, sometimes the real prototype is different but... we can't change the prototype.

Line 284: "keepalive | func_800CB458 | MATCH: pass arg0 to func_800CAF84 (cast call) — keeps $4 live across the Struct16 copies so local-alloc gives the temps a1-a3 as target; the pin+keepalive had faked that liveness (G24)". So real C liveness can substitute for a keepalive.

Line 285: "keepalive | func_800CB900 | WALL lreg-copy-pref-dying-base — w3c load keeps dying base $s5 copy pref; target $a0 needs twicep live across w3c range (keepalive faked it); no real C use after the load (G24)".

OK. Our case: the pin forces d to $s0. Lever-free, s1ang takes s0.

Hmm, let me reconsider: maybe there's a way to make d take s0 by making s1ang NOT need a callee-saved reg at all — i.e., make s1ang NOT cross the call. The target's s1ang crosses the call, so no.

OR: make s1ang a GLOBAL allocno. My g1 attempt changed the RTL (lost an instruction). Let me try a cleaner way to make s1ang global without changing the RTL: add a *use* of s1ang in a later block that cse/dead-code won't remove but that doesn't emit code. Impossible without asm (launder).

Hmm. What about making the load's result flow to a later block via a copy that's needed? E.g., the target has u6 = s1ang & 0xFFF used later. If we make the *load* pseudo itself used later... 

Actually, wait: what if we DON'T mask into a separate u6, but write:
```
u6 = s1ang & 0xFFF;
```
where `s1ang` is a *s16* variable? Then s1ang's load is `lh` and `s1ang & 0xFFF`... hmm.

Let me reconsider g1's instruction loss: the u5 andi disappeared. Why? Because `if (s1ang == u5)` where s1ang = s1ang & 0xFFF and u5 = (...) & 0xFFF. Maybe gcc's cse/combine saw `(a & 0xFFF) == (b & 0xFFF)` and... no, it can't remove u5's mask. Unless `combine` merged the andi into the subu? `subu a0,a2,v0; andi a0,a0,0xfff` — could combine into... no MIPS instruction does subu+andi.

Hmm, actually maybe the missing instruction is elsewhere. Let me count: mine 74, target 75. The diff showed mine[14:18] deleted (4 lines) vs target[17:17] (0). So mine has 4 insns where target has 0 at that point, but the insert at mine[1:1] target[1:5] shows mine missing 4. Net 0? Hmm, confusing. The score 33 with 74 vs 75 means one insn fewer overall.

Let me not chase g1. Let me try a variant of g1 that keeps u6 but ALSO uses s1ang later: e.g.
```
u6 = s1ang & 0xFFF;
...
iVar4 = u5 - u6;
if (iVar4 > 0x800) { t = (u6 = s1ang & 0xFFF) ... }
```
no.

OK, alternative idea: make the *load* pseudo global by loading s1ang into a variable that's used later *as s1ang* while also masking into u6:
```
s1ang = *(...);       // load
...
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
iVar4 = u5 - u6;
if (iVar4 > 0x800) { t = u6 + 0x1000; iVar4 = u5 - t; }
if (iVar4 < -0x800) { t = u6 - 0x1000; iVar4 = u5 - t; }
...
q = iVar4 / d;   // and somewhere use s1ang?
```
No.

Hmm, what if `d` is used in a way that makes it local? 

Let me reconsider: the target's d is in s0. What if the ORIGINAL source had the divisor as a `register` variable? K&R `register` decls: in gcc, `register` locals are marked `DECL_REGISTER` and might get better allocation? Let me check: in local-alloc, `reg_preferred_class` might be affected? Hmm, actually gcc's `-ffixed`/register vars: `REG_NO_CONFLICT`? No.

Let me test `register s32 d;` (no asm) and `register s32 s1ang;`.

Also test `s32 d` declared inside... hmm.

Let me batch a few more:
- r1: `register s32 d;` (no asm)
- r2: `register s32 s1ang;`
- r3: both register
- r4: d declared as `s32 d = arg1;` AND `s1ang` declared after d? (decl order)
- r5: swap declaration order (s1ang before d)
- r6: s1ang assigned before d=arg1
- r7: d = (s16)arg1 at top with pin removed and `s16 d` — already v3/w4.

Let me try these. Also:
- r8: `u6` computed as `s1ang & 0xFFF` but s1ang declared `volatile`? no.

Let me test r1-r6.
