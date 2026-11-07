---
ts: 2026-11-06T11:38:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9bXZ1a5wLqvyXlCnepDq
---
All 6. The value is always computed directly into s1.

Hmm, let me reconsider: what if the pinned variable tmp is used in a way that requires it to hold a value across the switch? E.g., if `tmp` itself were used after the switch. In the target, the value used in the 0x53 arm comes from s1. If tmp (a1) were the one used across... no, a1 is clobbered.

What if we make sVar3 and tmp both live: `sVar3 = tmp;` where tmp is used later in a no-op way.

Actually here's an idea: the target's `andi a1,v0,0xfff` writes a1 (tmp). What if we DON'T pin tmp but instead make the *expression* land in a1 naturally? The register allocator chose s1. Can't control.

What about the reverse: pin sVar3 to s1 and let tmp be... then `andi` might write s1 directly again.

Hmm, wait. Let's look at v2 (barrier removed, launder kept): score 0, and the pins are all there. The launder is what keeps the copy. So the launder is genuinely load-bearing.

Is there any real-C way to make a value be "materialized" in a hard reg and copied? The pin forces the reg; the launder forces the materialization. Without an asm, the compiler is free to compute directly into the final reg.

What if we split the computation: `tmp = ratan2(...) - 0x400;` then `sVar3 = tmp & 0xFFF;` — the andi is on sVar3. Target has the andi on a1 (tmp). Try it: with tmp pinned a1:
```
register s32 tmp __asm__("$5") = ratan2(...) - 0x400;
s32 sVar3 = tmp & 0xFFF;
```
Then andi goes into s1 → `andi s1,...` still no copy. Hmm.

What about: `register s32 tmp __asm__("$5") = ratan2(...); ... sVar3 = (tmp - 0x400) & 0xFFF;` then addiu/andi into s1. no.

I think the fundamental issue: without an asm, gcc will always fold a copy whose source is only used there. Actually no! A copy from a hard register *cannot* be folded in general — the destination is a different reg, and if the hard reg is live... but here tmp is dead after the copy, so the compiler can retarget the definition.

To prevent retargeting, tmp must be live after the copy. What if tmp is used AFTER the switch? E.g. add a use that's dead in the final code? Any real use adds code.

Unless... the use is in a branch that flow deletes? Hmm.

What if we exploit the case 0x41 arm: the target's 0x41 arm returns `D_80188614[...](a0) & 0xFF`. If tmp were used in that arm's expression in a way that cancels: e.g. `(ret + (tmp - tmp)) & 0xFF`? folds.

What about the switch's default (no default) — falls to the end, returns garbage. The target has no code after the switch (j to epilogue). So no.

I'll consider this a WALL: combine-copy-merge (the copy the target keeps). But wait — is the residual really a combine merge? Let me check: `andi s1,v0,0xfff` vs `andi a1,...; move s1,a1`. The copy `sVar3=tmp` was folded into the computation. In gcc terms, cse's `cse_insn` for the copy: it records sVar3 as equivalent to a1, then replaces uses of sVar3 with a1... but a1 is clobbered by the call. Hmm, then regmove or local-alloc coalesces. The tag "cse-copy-merge" (cse merges a copy the target keeps in its own reg) or "combine-copy-merge" fits.

But before declaring a wall I need 30 tries and 20 min. Let me look at the clock. I started around now. Let me check date at start — I didn't record it. Let me note the current time and continue with more variants to reach 30.

Actually, wait. Let me reconsider the problem once more. The target's `move s1,a1` is in the *delay slot* of `beq v1,v0` (case 0x53). This is a sched1/reorg placement. Maybe the copy is a real copy in the source placed there? No, the source has `sVar3 = tmp;` before the switch.

Alternatively, maybe the original C is different: what if the target's `tmp`/`sVar3` split comes from a *function argument* or a cast? Hmm.

What if the C uses the value in a comparison before the switch? e.g. `if (sVar3 ...)`. no.

Let me try: use tmp in a `&&`/`||` fold with bVar1? e.g. `switch (bVar1 | (tmp >> 31 & 0))`? folds.

OK. Another idea: use a *different variable type* so that the copy needs a real move: e.g., sVar3 is `u16` — then `sVar3 = tmp` truncates to 16 bits → `andi`? adds.

What about making sVar3 a pointer type? `void *sVar3 = (void*)tmp;` then use `(s32)sVar3 + sVar4`. Pointers are 32-bit, no conversion insn, and the copy... probably still folds.

Let me try a pointer variant and a few more, then accept the wall.

Actually, hold on! Let me reconsider the "launder" removal from a different angle: what if the launder is replaced by the *pin itself* being used differently. The kinds are barrier,launder. The pin is a different kind (allowed to stay). The launder line is `__asm__("" : "=r"(tmp) : "0"(tmp));`. What if I keep an asm but of the *pin* kind? No — the asm itself is the launder. Any asm = lever? The constraint says pins (register-asm) are allowed as a different kind... but the launder is an asm.

Hmm, tricky: "levers of other kinds the def already had (pins under other causes) may stay". The launder is listed in the row kinds, so it must go. The pins may stay.

Could I *convert* the launder into a pin? e.g. `register s32 tmp2 __asm__("$5") = tmp;`? That's a new pin — "never added" (new lever of another kind). No.

OK, so I need real C.

One more idea: the launder forces tmp to be *both* defined and used by the asm, so its value is live at that point and can't be folded into the expression. Real C equivalent: make the value pass through a function that the compiler can't see... no.

Real C equivalent that's not a lever: an *array store/load*? e.g. a local array on the stack — adds sw/lw.

Hmm what about: `sVar3 = tmp;` where sVar3 is declared `volatile`? Lever.

Let me try the pointer variant and a couple of others; then wall.

Actually, wait! Maybe the trick is the opposite: instead of keeping tmp alive, change which pseudo is used so the andi writes a1 and the copy appears from a *different* source: the `sVar4 + sVar3` addition. Target: `addu v1,s1,v0` — uses s1. If the compiler computes the andi into a1 and then... 

Hmm, what if the value's live range is such that global-alloc must use a caller-saved reg across the switch? The 0x41 arm's indirect call clobbers a1..a3, t0..t9, v0,v1. If the value is live across that call (it isn't used after, but if the C forced liveness), it must be in s-regs. But the target has it in a1 across the dispatch and copies to s1 on the 0x53 path only.

Honestly, the target's structure is: value in a1 (pin), copy to s1 placed in the beq delay slot (because on the 0x53 path the value is live across the ratan2 call, so it needs s1; on the 0x41 path it's dead).

To replicate without asm: I'd need the value's liveness to start in a caller-saved reg... 

Hmm, what if we write:
```
s32 tmp = ...;        // (no pin)
...
case 0x53:
  sVar3 = tmp;        // inside the arm
```
Then the copy is inside the arm after the dispatch, not in the delay slot. But sched1/reorg might fill the delay slot with it! Actually if the copy is the first statement of the arm and the beq targets the arm, the delay slot is filled from the arm's first insn if safe. Let me try: move `sVar3 = tmp;` into the case arm. The compiler would compute tmp... where? tmp's only use is in the arm; the compiler would sink the computation into the arm → andi into s1 inside the arm. Hmm, but maybe not.

Let me try it anyway. Also try making tmp's computation stay in the switch prologue by using it in both arms.

Let me batch: 
- c1: sVar3=tmp inside the case arm (before bb load).
- c2: pointer type.
- c3: use tmp in both case labels via a label-less approach? no.
- c4: `sVar3 = tmp;` before switch, and also `case 0x41: ... ; break;`? no.

Let me do c1, c2, plus a few type variants (u16, s16).

Actually, let me count tries so far: v1, v2, v3, v4, a1, a2, a3, a4(err), a5, a6, b1, b3(err), b4, b5 = 14 scored (12 scored + 2 compile errors). Need 30. Let me do a bigger batch.

Let me write a generator producing ~20 variants. Variants to try (all removing launder):
- c1: copy inside case arm
- c2: `void *sVar3`
- c3: sVar3 as u16
- c4: sVar3 as s16
- c5: tmp declared `volatile`? (lever — skip)
- c6: `sVar3 = tmp + 0x0;`
- c7: reorder declarations (sVar3 before tmp)
- c8: `sVar3 = (s32)tmp;`
- c9: `sVar3 = tmp;` then `bVar1` load, then switch; already base.
- c10: move `iVar5` load after the switch? changes sched
- c11: move bVar1 load to decl (init at decl)
- c12: combine bVar1 decl with the switch
- c13: split the expression: `s32 tmp = ratan2(...); tmp -= 0x400; tmp &= 0xFFF;`
- c14: `sVar3 = tmp;` with sVar3 used via `& 0xFFF` at the store: `(sVar3 + sVar4) & 0xFFF` unchanged.

Hmm, most will give 6. But that's fine — they count as tries toward the 30, and one might hit.

Let me also try a fundamentally different idea: what if the copy is produced by *not* pinning tmp but pinning sVar3? `register s32 sVar3 __asm__("$17")` (s1=$17). Then the computation andi would write... maybe a1 then move to s1! Because the destination is a hard reg, the compiler might compute in a temp (v0→a1?) and move. Let's test: pin sVar3 to $17 and remove the launder (tmp unpinned). The andi result must go to $17, so it computes `andi s1,v0,0xfff` directly probably. Hmm, but worth a try. Actually maybe combine needs a move because the expression result comes in v0 and the andi... no, andi can write s1.

But that's adding a pin — allowed? Pins already in the def may stay, never added. Adding a pin is adding a lever of another kind → prohibited. So no.

OK let me do the batch of real-C variants.
