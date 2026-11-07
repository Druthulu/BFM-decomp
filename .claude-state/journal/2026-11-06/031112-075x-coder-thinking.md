---
ts: 2026-11-06T10:11:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_axoHaT5ZJlYEePKkTxtc
---
No change. The local-alloc assignment is robust.

Let me now seriously consider: the target's s1ang in s1 requires s0 to be taken at local-alloc time. The only candidate is d, which is global. So maybe in the ORIGINAL, d was local!

How can d be local? If d is defined and used within ONE basic block. The divisions are in blocks 6,7,9. But wait — maybe the original source did NOT have the `if (iVar4 >= 0)` split into two division sites. Let me re-examine the target: the two divs are at 394c and 398c, in the two arms of `if (iVar4 >= 0)`. So d is used in 2 blocks.

Hmm, unless the original computed the division ONCE and the compiler duplicated it? No.

Wait, maybe I'm wrong that d is global. Let me check the nopin alloc table: r74 "dies in 3 places; crosses 1 call" — "dies in 3 places" means it has 3 death points (the 2 divs + ?). And it's global (blk None). So yes.

OK, let me look at whether the *target* could have d in s0 via a different route: maybe d is local-alloc'd in the original because the sign-extension `d = (s16)d` creates a NEW pseudo, and the *sign-extended* d is used in the divisions (blocks 6,7,9 → global), while the original d (from arg1) dies at the sign-extension (insn 55, block 0) → local!

OH WAIT. That's exactly it! In the nopin RTL, insn 55 is `(set (reg/v:SI 74) (sign_extend (subreg (reg/v:SI 74))))` — the SAME pseudo r74 is both source and dest (a self-set). So r74 is one pseudo: defined at insn 6, redefined at insn 55, used in the divs. It's global.

But if gcc had created a NEW pseudo for the sign-extended value (e.g., `s32 d2 = (s16)d;` with d2 used in the divs), then:
- d (from arg1) dies at insn 55 (block 0) → local!
- d2 is global.

Then local-alloc: d is local, crossing the call, refs 2 (set + use at sign-ext), live ~49 (from insn 6 to 55). Priority = 1*2/49 = 0.04 → 408. Hmm, low. And s1ang: refs 2, live 7 → 2857. s1ang has HIGHER priority → gets s0 first. Then d (local, 408) gets... s1? Then the target would have d=s1. No.

Hmm, unless d's live range is short. If `d = (s16)d` is right after `d = arg1` (both in the prologue), then d (the arg1 value) dies immediately → live ~2 → priority 1*2/2 = 1 → 10000 > s1ang 2857 → d gets s0! And s1ang gets s1! TARGET!

But then the sign-extension instruction would be in the prologue, not at position 19. The target has `sll s0,s0,0x10` at position 19 (after the call). Hmm.

Unless... the sign-extension of d happens at the prologue in the RTL but sched1 moves it later? No, sched1 could move it later (it's independent). The target has it after the call. Hmm, sched1 moved it later? Sched1 typically hoists, not sinks. Hmm.

Wait, actually, let me reconsider. In the target, `move s0,a1` (d=arg1) is at position 3. Then `sll s0,s0,0x10` at 19. If the source had `d = arg1; d = (s16)d;` both at the top, the RTL would have move + sll + sra in the prologue. Sched1 might sink them? Unlikely.

Hmm, but what if the source had:
```
d = arg1;
...
s1ang = ...;
u5 = ...;
d = (s16)d;
```
That's our current source, and RTL insn 55 is the sign-extend. If gcc created a NEW pseudo for the result (not a self-set), then d's live range would be from insn 6 to insn 55 (long) → local with low priority (408). Not good.

Unless the assignment `d = (s16)d` reuses the same pseudo (self-set), which is what happens. Then r74 is global.

Hmm. So how to get a short-lived local d that takes s0?

What if we use a separate variable:
```
s32 d;      // from arg1, dies early
s32 dd;     // sign-extended, used in divs
d = arg1;
...
dd = (s16)d;   // after u5
...
q = iVar4 / dd;
```
Then d is local, live from insn 6 to the sign-ext at position ~19 → live ~15, refs 2 → pri = 1*2/15 = 0.133 → 1333. s1ang: 2857. s1ang higher → s0. d lower → s1. Still wrong.

Hmm. Unless d's live range is shorter (2) → 10000. That requires d = arg1 and d = (s16)d adjacent at the top. But then the sign-ext is in the prologue.

Hmm, what if we write:
```
s32 d = (s16)arg1;   // sign-extend at decl
```
Then there's only ONE variable d, defined at the prologue with the sign-extension. The RTL: `(set (reg d) (sign_extend (subreg (reg a1))))`. That's move + sll + sra in the prologue. Target has sll/sra at position 19, not the prologue. Hmm, but wait — maybe sched1/dbr moves the sll/sra later? Let me test w4 (which did `d = (s16)arg1` at top): it scored 40 (74 ins). So no.

Hmm, the target's sll/sra at position 19 suggests the sign-extension is genuinely later in the source.

OK so d is global. Then s1ang gets s0. Contradiction with the target. Unless the original had a THIRD local-crossing variable.

Hmm, wait — what about the `(s16)` cast of arg1: `d = (s16)d` creates a sign-extension. In RTL, insn 55 sets r74 from a sign_extend of r74. But actually, look at insn 55's REG_EQUAL: `(sign_extend:SI (subreg:HI (reg/v:SI 74) 0))`. So it's a self-set.

Hmm, let me look at the target's sll/sra: `sll s0,s0,0x10; sra s0,s0,0x10`. This is the sign-extension of a 32-bit value's low 16 bits.

What if the ORIGINAL source computed the sign-extension via a *different variable* used only in the divs, and that variable is global (gets s1 or s0)? Let's think: if dd (sign-extended) is global with refs 3 (def + 2 uses), live from position 19 to the divs (~30) → pri = 1*3/30 = 0.1 → 1000. d (local, dies at sign-ext) — if d's live is short... 

Hmm, but the target only has 2 callee-saved regs used (s0, s1). So there are at most 2 callee-saved variables. They are d and s1ang/u6. So d is global (or the sign-extended dd is global) and s1ang is local or global.

If dd is global and d is local-short: local-alloc would give d s0 (if d's priority > s1ang's) or s1. Then the divs use dd in... no, the divs use s0 in the target. So the variable in s0 is the divisor (sign-extended). If dd is in s0, then dd is global and d (local) must have gotten... hmm, if d is local and gets s0 first, then dd (global) can't use s0. So d must get s1 and dd s0. For d (local) to get s1, s1ang must get s0 (higher priority). Then dd (global, after s1ang and d) gets... only callee-saved regs s0 (s1ang), s1 (d) taken → s2. Not target.

This is getting complicated. Let me try the "separate dd variable" idea empirically:
```
s32 d;
s32 dd;
d = arg1;
s1ang = ...;
u5 = ...;
dd = (s16)d;
...
q = iVar4 / dd;
```
Let me test it.

Also test: 
```
s16 d;  // s16 variable
d = arg1;
...
q = iVar4 / d;  // sign-extend at each use
```
v3 scored 25 with pin removed.

Let me test the dd variant.
