---
ts: 2026-11-06T16:29:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yrTAmVW2UmaTml3hCaxN
---
Very relevant: line 134-136: "pin | func_8018302C | WALL cse-copy-merge — target `move v1,v0` is `plus v,$0`: a hard-reg addend combine cannot fold, so cse keeps the copy; a C-level zero is a constant -> combine folds -> cse propagates (best 2)".

And line 217: "MATCH: copy hoisted above the branch via s16 temp (tmp=(s16)t; u=tmp) — HImode copy escapes cse equivalence class, so or v1,v0 survives in the bnez delay slot (RM1)". And 219: do-while(0) wrap.

Hmm, so for our case the target is `move v1,v0` = a copy of the call result. This is a cse-copy-merge class: cse merges the copy unless something keeps it.

But wait — our move v1,v0 is the call-result copy and the target also has v1 holding ret. In the natural compile the copy is *tied away* by local-alloc (not cse). So the question is allocation, not cse. Hmm, but maybe with a temp it becomes a cse issue.

Consider: `s32 t = func(...); s32 ret = t;` where ret is used twice. cse would propagate ret=t (copy), making the copy disappear and ret be the same as t. Then local-alloc ties t to v0.

Unless we prevent cse propagation by an HImode copy: `s16 tmp = t; ret = tmp;` Hmm.

But actually the target's andi reads v1 = ret. If the source had `m = ret & 0x8000` with ret an HImode copy... andi on HImode would need extension.

Let me think again about what natural C produces `move v1,v0; beqz v1; andi v0,v1,0x8000`.

Hmm! What if `ret` is declared `register`-free but the call result is assigned to `m` and ret separately? Like:

```c
m = func_801638A0(...);  // call result to m
ret = m;                  // ret copies
if (ret == 0) {}
else if ((m = ret & 0x8000) != 0) ...
```
Here m is reassigned; the call result copy to m ties v0. ret = m copy — if it survives cse, ret gets v1 (v0 taken by m). Then andi v0,v1 — but the andi writes m which is in v0... wait m is v0, and ret v1. `m = ret & 0x8000` → andi v0,v1,0x8000 (output m in v0, input ret in v1) — EXACTLY the target! And beqz v1 tests ret. 

So the target could come from: call result stored in a variable that is ALSO the andi destination (m), and ret is a separate variable holding the same value used in the test. But then what's the purpose of ret? In real C, maybe the source was:

```c
s32 ret = func_801638A0(...);
...
```
Hmm, but the two-variable version: `m = func(...); ret = m;`. cse would merge m and ret (copy). Unless... the copy is kept because m is used elsewhere. Hmm.

Actually wait, what if `ret` is used in the test and `m` is assigned from ret? That's the current form and natural allocation ties.

What if we reverse: `m` is assigned from the call, `ret` copies from m, and the test uses ret, and the andi uses ret into m. Then:
- call result pseudo c (the call's return move target) → m? Actually `m = func(...)` means m's pseudo is the call result → tied v0.
- `ret = m` copy → ret pref v0, but v0 taken by m (live until the andi's last use of ret? m dies at... m is used at `ret = m` and then redefined at the andi. So m's live range: born at call, dies at ret=m? If m is redefined later, the old m dies at ret=m. So ret's live range starts at ret=m and overlaps? ret=m is the copy; at that insn m is used and ret defined — tying could happen: ret could be tied to m's v0! The tying loop ties operand 0 (ret) with an operand that dies in this insn (m). So ret ties to v0 too, and the copy is deleted. Damn. Unless the copy can't be tied because m doesn't die there (m used later before redefinition).

Hmm, what if m is used later after the andi? no.

OK so tying kills simple copies.

The move v1,v0 must be a copy that cannot be tied, meaning the source value doesn't die at the copy. So the source must be live after. That's why the target has `ret` in v1 and the call result in v0, with the call result used *later*. What's the call result used later for? The andi! `andi v0,v1,0x8000` reads v1 not v0. Hmm.

Unless the source is: `ret = func(...)` where the call result pseudo (v0) is used in the andi (m = t & 0x8000) and `ret` is a copy of t that's live across... no wait, target's andi reads v1.

Let me reconsider: maybe the andi reads ret (v1) and the value in v0 is dead after the move. So the move's source dies at the move → tie should happen. Unless the move isn't a register copy but a `plus` with a hard-reg addend (per line 134): "target `move v1,v0` is `plus v,$0`: a hard-reg addend combine cannot fold". In that case the insn is `(set (reg v1) (plus (reg v0) (const_int 0)))` — an add of zero with a hard register operand, which local-alloc cannot tie (tying only for moves?). And combine can't fold because the addend is a hard reg.

So the source might be `ret = t + 0` where t is the call result! In C, `ret = func(...) + 0`? Hmm, that's weird but plausible in decompiled code, e.g. `ret = (s32)(func(...))`? No, a cast is not a plus.

Hmm, what about `ret = func(...)` and then the value used... Actually line 134 says a C-level zero is a constant → combine folds. So to keep `plus v,$0` you'd need a hard-reg addend, i.e. a pinned register. But we can't pin.

Wait, maybe that note is about the *pinned* build: with ret pinned $3, the copy from v0 to v1 became `plus v1,v0,$0` because... Hmm, the note says the target is plus with hard-reg addend, which combine cannot fold; a C-level zero gets folded. So that item was a WALL.

OK so for our function, let me look at the actual pinned build's insns to see whether the move v1,v0 is a plain move or a plus. The target.s shows `move v1,v0` = `addu v1,v0,zero` probably. Let me check the object dump of the pinned build to see the raw insn. Actually target.s was generated from the target object (ROM), showing `move`. And the pinned build scores 0, so the pinned build emits `move v1,v0` too. So in the pinned build, the call result copy to a $3-pinned pseudo is a plain move. Why isn't it tied? Because ret is a hard register — local-alloc doesn't tie hard regs.

So the question stands: how does plain C produce a non-tied copy from v0 to v1?

The trick from RM1: "copy hoisted above the branch via s16 temp (tmp=(s16)t; u=tmp) — HImode copy escapes cse equivalence class". That keeps a copy. But it's about `or v1,v0` surviving in a delay slot, i.e., a copy that cse would otherwise merge. The HImode copy is a real copy insn: `tmp = (s16)t` where t is s32 → this is a truncation, and `u = tmp` extends back. Hmm, in MIPS gcc 2.7.2, `(s16)t` to an s16 variable then used as s32... 

Let me look at the actual function func_80182ED4 or 8018302C in the repo to see the winning C. Actually they're src functions now banked. Let me look at func_80182ED4's body in src and its target shape. That could give the idiom. Let me find it.

Actually, time. Let me be strategic: item 1 is a pin item with target = pinned shape. Budget 20-30 min. Let me try a bunch of empirical candidates quickly.

Key insight attempt: the copy `move v1,v0` survives if the copy's source doesn't die (so no tie). In the pinned build the source is a hard reg. In plain C, we need a copy from a pseudo that is live afterward. So: make the call result live after the copy.

Source idea:
```c
s32 t = func_801638A0(...);
s32 ret = t;
if (ret == 0) {}
else if ((m = ret & 0x8000) != 0) {...}
```
If t is live after the copy, cse won't merge and tying won't happen. Make t live after: use t in the andi instead of ret? Then andi reads t (v0), not ret. But target andi reads v1.

Alternatively use t after the whole if (dead-ish but kept). Hmm, flow would delete if unused. Use t in a store? changes code.

Hmm what about this: the copy direction. `ret = t` where t is v0 and ret is v1: move v1,v0. For ret to get v1, t must be live. If t is used in the andi (m = t & 0x8000), then andi v0?,v0,0x8000... reads v0.

Target reads v1. So no.

Let me reconsider whether the target's andi really reads v1: `354: 30628000 andi v0,v1,0x8000`. Yes, `andi rt, rs, imm` → v0 = v1 & 0x8000. Reads v1 (ret).

So the andi reads ret, which is the copy destination. So the copy source (v0) is dead after the move. Then tying should occur... unless the copy insn isn't a plain move but something untieable, like a plus or a sign-extend (HImode copy).

HImode copy idea: `s16 tmp = t; ret = tmp;` — this would produce `sll/sra` or nothing? In MIPS gcc 2.7.2, a truncation to HImode followed by a use as s32 requires sign extension: `sll v1,v0,16; sra v1,v1,16`. That's 2 insns, not a move. Not our target.

Unless `ret` is u16 and compared as HImode: then the copy is a plain move (no extension needed) and the HImode pseudo... Let's think: `u16 ret = func(...)` → the call result (SImode) is truncated to HImode; gcc emits a move? Actually a HImode copy from a SImode value requires a truncation which on MIPS is just a move (low 16 bits are in the reg). So `move v1,v0` and the pseudo is HImode. Then `if (ret == 0)` → beqz v1. And `m = ret & 0x8000` — with ret HImode, `ret & 0x8000`: the andi operates on HImode; but then m's type? If m is s32, the HImode ret is extended (sll/sra) unless the andi masks. Hmm, actually gcc would promote: `ret & 0x8000` where ret is u16 → the result is int, so ret must be zero-extended first (andi v0,v1,0xFFFF) then andi 0x8000? That adds insns.

But if m is u16 too, `m = ret & 0x8000` → andi v0,v1,0x8000 (HImode andi works directly on the 16-bit reg? MIPS HImode in a register is in the low 16 bits, and andi 0x8000 works). Then `m != 0` → beqz/bnez on v0 (HImode test; needs no extension for a zero test since bits above 16 are unknown... hmm, HImode in a register: gcc requires the upper bits be sign/zero extended? For HImode pseudos, gcc 2.7.2 may treat them as having garbage upper bits, so a comparison to 0 would need sll/sra or sll. Actually for HImode compare against 0, `beqz` on the reg is valid only if the upper bits are known zero. Since `andi` with 0x8000 zeroes the upper bits, it's fine — andi writes a full SImode result in gcc's eyes? andi's mode is SImode with HImode operands... In gcc 2.7.2 mips.md, `andsi3` for HImode operands: if the operand is HImode, it might emit `andi` directly.

This is worth trying empirically.

Another idea: use `s32 m` but write `if ((m = ret & 0x8000) != 0)` where ret is HImode/u16.

Let me just generate a batch of ~12 candidates and score them.

Candidates (item 1):
c1: current win0 (8)
c2: decl order m first
c3: ret u16, m s32
c4: ret u16, m u16
c5: ret s16, m s16
c6: ret s16, m s32
c7: m u16, ret s32
c8: no m var (ret & 0x8000)
c9: t = call; ret = t; m = ret & 0x8000
c10: t = call; m = t; ret = m; ... 
c11: hoist: m = ret & 0x8000 before if, test m first? (order change)
c12: `if (ret) { if ((m = ret & 0x8000))...}` structure

Actually let me also reconsider: maybe the pins are both "not needed" in the sense that only ONE of them is the real problem and the other is redundant. Note W02: "pin redundant". Let me first test removing only $2, keeping $3; and removing only $3.

Test: keep ret $3 pin, remove m $2 pin → does it score 0? Then m naturally gets v0 (as the andi output). And keep m $2, remove ret $3 → ret naturally v0, no copy → likely not 0.

Let me batch these.

I'll write a script to generate the candidate files from orig.c with sed-like Python. Actually simpler: write each file with the Write tool? That's many calls. Better: a Python script under the shard dir that emits candidates, then sc.sh.

Let me write .run/P40/T11/W47x/gen1.py that writes candidate files.

Actually, given the many variations, a Python generator is efficient. Let me write it.

Let me define the body template with placeholders. I'll write explicit bodies.

Let me write gen1.py producing files w1_*.c.
