---
ts: 2026-11-06T10:08:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RjxtF1S0U6GCWcxD58ir
---
v2 is worse. So the source order (load before call) is correct.

Let me reconsider. In v2, s1ang got s1? "mine[15:16] sll v1,s1,0x10; sra s1,v1,0x10" — hmm, that's a sign extension of s1 (which in v2 is... d? since mine[2] move s0,a0?? confusing).

OK let me go back to nopin and think about the register flip.

Key fact: s1ang is LOCAL (block 0), the only local-crossing qty → gets s0.

For the target, s1ang must be in s1. Since the target's s1ang is also local (def+use in block 0), the only way is that s0 was unavailable. 

Hmm, wait — unless in the target, s0 was assigned to *d* by local-alloc because d was local. Let me reconsider d: `d = arg1` at the top (block 0), sign-extended at insn 55 (block 0!), used in the divs (blocks 6,7,9). So d spans blocks → global. Unless... the sign-extension at insn 55 creates a NEW value; the original d (r74) after insn 55 is dead except for the divs.

Hmm, what if the ORIGINAL source assigned the divisor inside each block? No.

OK, let me try yet another idea: what if we make s1ang's use be in a different block by moving `u6 = s1ang & 0xFFF;` AFTER the `if (u6 == u5) return 0;`? No, u6 is needed for the if.

What if we compute `if (s1ang == u5) return 0;` without the & 0xFFF? No, wrong semantics and code.

Hmm, let me look at the problem from the C source reconstruction angle. The target's `andi s1,s1,0xfff` means s1ang is masked. What if the original variable was `u6` directly:
```
u6 = (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12)) & 0xFFF;
```
Then there's no s1ang variable; the load's result is a temp used immediately in the andi. The temp would be local (block 0) and the andi result (u6) global. The temp (load result) crosses the call? The load is before the call, the andi after → the temp is live across the call → local qty crossing the call → gets s0! Then u6 prefers s0. Same problem.

Unless the load's temp is used AFTER the call, so it crosses → s0. Same.

Hmm.

Wait, maybe the key is that in the target, the *load temp* is not live across the call because the andi happens right after the call and the load is... no.

Let me reconsider: maybe the target's local-alloc DID give s1ang s0, but then *global-alloc* reassigned? No, local-alloc's assignments are final.

Hmm, hold on. Let me re-read the target's prologue order:
```
addiu sp,-32
move v0,a0        # arg0 → v0
sw s0,16(sp)      # save s0
move s0,a1        # d = arg1
sw ra,24(sp)
sw s1,20(sp)      # save s1
```
The save of s0 happens BEFORE `move s0,a1`. And the save of s1 is after. This order comes from the prologue's register-save ordering. Not informative.

Let me look at the nopin prologue:
```
move s1,a1       # d = arg1 → s1
sw ra,24(sp)
sw s0,16(sp)
```
(from the --explain diff: mine[3:6] = move s1,a1; sw ra; sw s0). And target[2:5] = sw s0; move s0,a1; sw ra.

Hmm.

OK, let me try to make s1ang global by adding a *real* use in a later block that doesn't change the instruction count. Is there such a use? For example, the source could compute `iVar4 = u5 - u6` and use u6 later. u6 is already global. s1ang is not.

What if we write the divisions as `q = iVar4 / d` but ALSO use s1ang somewhere in a later block in a way that's redundant? Redundant uses usually get eliminated by cse/flow.

Alternatively, what if we *don't* have a u6 variable and use `s1ang & 0xFFF` directly in all the places u6 is used? Then s1ang is used in blocks 1,2,3 → global. And cse might hoist the `& 0xFFF` to block 0, keeping the andi there. Let's think: 
```
if ((s1ang & 0xFFF) == u5) return 0;
iVar4 = u5 - (s1ang & 0xFFF);
if (iVar4 > 0x800) { t = (s1ang & 0xFFF) + 0x1000; ... }
...
```
CSE would compute `s1ang & 0xFFF` once in block 0 and reuse it. The CSE temp would be global (used in multiple blocks). s1ang itself: used in block 0 (the andi) only → local. Hmm, same as before.

Unless cse puts the andi in block 0 and s1ang is local → gets s0. Then the cse temp (u6) prefers s0. Same.

Hmm.

OK, let me try a completely different tack: maybe use `register` declaration without asm. In gcc, `register` variables might be treated as "not addressable" and get better allocation. But `register s32 s1ang;` — does it change anything? Probably not, but let me test. Also `register s32 d;`.

Actually — there's `-ffixed`... no.

Hmm, what about declaring s1ang as `volatile`? That would force memory. No.

What about making s1ang a *parameter*? No.

Let me look at this from the alloc-table arithmetic angle suggested by the tool doc: "agent a4 flipped a 34-instruction residual to zero by moving one allocno's priority 6524 → 6808 past another's 6666". That's about GLOBAL allocnos. Here the conflict is local vs global.

Hmm, what if we can make d's priority HIGHER so that... no, d is allocated last regardless (it's last in the global order because low pri). Wait, the global order is 78 80 79 77 76 74. If d's priority were HIGHER, it would move earlier in the order, but s0 is taken by s1ang (local) already. So no.

The ONLY fix is s1ang not taking s0.

Hmm, unless we can make d a local qty. Let me reconsider: what if the divisions use a *different* variable that is set inside each block? E.g.:
```
if (iVar4 >= 0) { q = iVar4 / (s16)d_local1; ... }
```
No.

What if `d` is read from the stack? No.

Wait — what if we make the function use `d` only in ONE block by restructuring the divisions? The target has 2 divisions in 2 blocks. Hmm.

OK, let me consider: maybe the target's s1ang was allocated s1 because in the original, there was ANOTHER local-crossing-call qty with higher priority. What could it be? The `*(s32 *)(arg0 + 0x20)` value (loaded at 38e0 `lw v0,32(v0)`)! That value is used at 38f0 `lh s1,18(v0)` — before the call. Not across.

What about `D_80126B66` / `D_80126B5E` loads? They're before the call and used in the call args.

Hmm, what about the call's arguments `a0`, `a1` computed before the call? Not across.

What about `u5`? Born at the call.

So no.

Let me reconsider whether the target's s1ang is actually local. In the target RTL, the def `lh s1,18(v0)` and use `andi s1,s1` — are they in the same block? Yes (block 0, before the bne). So local.

Given all this, maybe the original compiler's REG_ALLOC_ORDER differs (e.g., the actual build uses a different mips.h with s1 before s0). But the project's toolchain is pinned and reproduces the target for the pinned source. The pinned source forces s0 via the asm pin. So we don't know if the toolchain would naturally pick s1.

Hmm, but the project's toolchain compiles the src to byte-identical target. If the original (Square) source compiled with the same toolchain, then the same local-alloc would apply. So the original must have had a different RTL that made s1ang get s1.

Let me try: what if s1ang's *definition* is a `(set (reg) (sign_extend (mem:HI ...)))` where the dest is a NEW pseudo, and the value is copied? Hmm.

Actually — WAIT. What if in the original, `s1ang` was assigned to a *variable that is used before the call too*? No.

Let me try a fundamentally different structure: what if the original source was:
```
s32 s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
```
with init at decl. Same RTL.

Hmm.

Let me try making s1ang GLOBAL by having its load happen inside a conditional that is always... no.

You know what, let me look at the actual score if I use `register` and a few other things. But time is passing. Let me check the clock.

Actually, let me reconsider the possibility that this item is a WALL. moves.md has similar walls:
- line 178: `pin | func_801415C0 | WALL lreg-qty-order — locals c,d take $s0/$s1 before globals a,b,e; the target has a=$s0,b=$s1 and no plain-C spelling flips the order (G07)`
- line 165: `WALL global-alloc-nrefs-prio`
- line 162/163: `WALL greg-alloc-order`

Our situation: a local qty (s1ang) takes s0 before the global d. The target has d=s0, s1ang=s1. This is exactly "lreg-qty-order" or "greg-alloc-order".

But before declaring WALL, the brief requires 30 scored tries. I have ~12 so far. Let me do a broader batch of ~15 more variants quickly, then decide.

Actually, wait. Let me reconsider one more idea: the `keepalive` on u5 might be doing double duty — maybe removing it changes the block structure! The keepalive `__asm__ __volatile__("" : : "r"(u5))` creates a use of u5. Without it, maybe u5's computation is merged. Hmm.

Actually, let me reconsider the problem: maybe the *keepalive removal* is what causes the register flip, not the pin. Let me test: keep the pin, remove the keepalive → score? And remove pin, keep keepalive → score?

This isolates. Let me do it.
