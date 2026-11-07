---
ts: 2026-11-06T23:54:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0JTSB2pgZXW1Umg3rgpP
---
The .greg order line: 144 79 76 78 74 75 72 73 77.

So the allocation order (highest priority first):
r144 (pri 6000, refs 3, live 5, prefers v1)
r79 (pri 5333, refs 4, live 15, prefers a3, pointer)
r76 (5000)
r78 (5000)
r74 (3692, refs 8 live 65, conflicts s0)
r75 (2413, refs 7 live 58)
r72 (1518, refs 8 live 158, pointer)  ← this is likely base
r73 (1204, refs 5 live 83)           ← likely mode
r77 (1111, refs 3 live 27)

Hmm, but s0 is already assigned to r84 (local-alloc). So global-alloc allocates these 9 allocnos.

Wait, the table shows r72 conflicts s0 → so r72 can't get s0. r72 is the pointer with live 158 (the whole function) = base. r73 live 83 = mode? refs 5.

Order: 144, 79, 76, 78, 74, 75, 72, 73, 77. So r72 (base) is allocated before r73 (mode). r72 gets the lowest free callee-saved... 

Hmm, but which regs are available? s0 is taken by r84 (local-alloc). v0,v1,a0..a3 are call-clobbered; these allocnos cross calls so they need callee-saved. Actually r144 (live 5, refs 3) doesn't cross calls maybe. Hmm.

But in the final code: cnt=s0 (r84 is s0), file=s1, val=s2, mode=s3, base=s4. Which allocnos are file, val, mode, base?
- r84 = s0 (local-alloc) = cnt? It has live 13, refs 3, crosses 1 call. cnt = func_80029504() then used twice. Yes, r84 = cnt.
- r72 (refs 8, live 158, pointer, conflicts v0,v1,a0,a1,a2,a3,s0) = base (longest live, pointer).
- r73 (refs 5, live 83) = mode?
- r74 (refs 8, live 65) = val? val is set 3-4 times, used in compares. Hmm.
- r75 (refs 7, live 58) = file?
- r76 (refs 3, live 6, prefers v0) = st?
- r78 (refs 4, live 16, crosses 1 call) = ?
- r79 (refs 4, live 15, prefers a3, pointer) = p!
- r77 (refs 3, live 27) = res? (res set in both arms, live 27)

Hmm, so the order: r74 (val), r75 (file), r72 (base), r73 (mode), r77 (res).

Available callee-saved: s0 taken by r84. So the first global allocno that needs a callee-saved reg gets s1, then s2, etc.

r74 (val): crosses calls → needs callee-saved → gets s1? But target has val=s2 and file=s1. Hmm.

Wait, order is 144,79,76,78,74,75,72,73,77. r144 (live 5, refs 3, prefers v1) — probably doesn't cross calls, gets v1 or v0. r79 (p, pointer, prefers a3) — gets a3! Yes, p=a3 in target. r76 (prefers v0) → v0. r78 (live 16, crosses 1 call) → needs callee-saved → s1? Hmm, but file=s1.

Hmm, wait: r78 crosses 1 call. r74 crosses 6 calls. Both need callee-saved. r78 is allocated before r74 (order). So r78 gets s1, r74 gets s2, r75 gets s3, r72 gets s4, r73 gets s5?? That contradicts.

Unless "crosses 1 call" means it can be call-clobbered if it doesn't cross... Actually allocno_calls_crossed==0 means it can use call-clobbered regs. r78 crosses 1 call → must be callee-saved.

Hmm, my mapping is off. Let me get the actual assignment from the .lreg dump or the final code. In the target (pinned), the assignment: s0=cnt, s1=file, s2=val, s3=mode(pinned), s4=base.

In G_nopin: s0=cnt, s1=file, s2=val, s3=base, s4=mode.

So base and mode swapped: in nopin, base=s3, mode=s4. With pin, s3 reserved → base=s4, mode fixed s3.

So the allocno order must be such that base comes before mode, and they get the next two free callee-saved regs after s0,s1,s2.

Wait: s0=cnt (r84, local-alloc). Then global allocnos take s1, s2, s3, s4 in order. The order must be: file, val, base, mode (or similar). From the order line: 74, 75, 72, 73. If 74=file, 75=val, 72=base, 73=mode → s1=file, s2=val, s3=base, s4=mode. That matches G_nopin exactly!

And with the pin, mode is not in the order (it's a hard reg), so 74,75,72 → s1,s2,s4? No: with s3 reserved, 74→s1, 75→s2, 72→s4. Yes! base→s4. Matches.

So: r74 = file (refs 8, live 65), r75 = val (refs 7, live 58), r72 = base (refs 8, live 158), r73 = mode (refs 5, live 83).

To flip base and mode: make r73 (mode) come BEFORE r72 (base) in the order. Order is by pri:
r72 pri = 1518 (refs 8, live 158): floor_log2(8)=3, 3*8/158*10000 = 24/158*10000 = 1518. ✓
r73 pri = 1204 (refs 5, live 83): floor_log2(5)=2, 2*5/83*10000 = 10/83*10000 = 1204. ✓

To flip, need pri_mode > 1518. Options:
- refs_mode 6: floor_log2(6)=2, 2*6/83 = 1445. Still < 1518.
- refs_mode 7: floor_log2(7)=2, 2*7/83=1686 > 1518 ✓ (live 83)
- or refs 6 with live 78: 2*6/78=1538 > 1518 ✓
- or reduce live: refs 5, live 65: 2*5/65=1538 ✓

Hmm, so I need to change mode's refs/live. But those come from the RTL, which must match the target. Any change would alter the code.

UNLESS: the target's own RTL has different refs/live for mode! Wait — the target was compiled from the *original* source with the pin. With the pin, mode is a hard register, so no allocno. So the target's allocno table has no mode allocno. The target's base got s4 because s3 was reserved.

Lever-free, we can't reserve s3. So we need mode to outrank base... but that changes nothing in the target's code.

Hmm, wait. Is there a C spelling that changes the allocno *structure* without changing the emitted instructions? For instance, if `mode` were not a global allocno but assigned by local-alloc... no.

What if `mode` is split into two variables? E.g., mode is set to -1 and 0 in different places and used later. If we use two variables... no, changes code.

What if base is made to conflict with s3 somehow? No.

Hmm, what about making base NOT an allocno crossing calls — no.

Alternatively: reduce base's priority. base: refs 8, live 158, pri 1518. If live were 200: 24/200=1200 < 1204 → then mode (1204) outranks base! base's live is 158 already nearly the whole function (161 insns). To get 200 we'd need... no.

Or increase base's refs? refs 9: floor_log2(9)=3, 3*9/158=1708 — still > mode but higher. Wrong direction.

Or reduce base's refs to 7: floor_log2(7)=2, 2*7/158=886 < 1204 ✓! So if base had 7 refs instead of 8, mode would outrank it.

Hmm, can I reduce base's ref count by 1 without changing the code? base's refs: it's used in the 5 if-conditions (5 uses) + at the end (1) + ... Let's count: `((Unkstruct_80010178 *)base)->unkA3D8` appears 5 times, `((Unkstruct_80010178 *)base)->unkA3DE` once, and at the end `((Unkstruct_80010178 *)base)->unkA3D8` once. So 7 uses + 1 set = 8 refs.

Could I combine two uses into one C expression without changing code? E.g., in the first if: `if (X == 0x300B && Y != 0)` uses base twice (unkA3D8 and unkA3DE). That's 2 refs in one expression. Can't reduce.

Hmm, but what if base's *set* doesn't count as a ref? It does.

What about making `base` an alias of another allocno? E.g. compute `((Unkstruct*)D_800AF630)` directly instead of via base — that would remove the base variable entirely and change code (recompute address each time). No.

OK. Different angle: what if we make `mode` have 7 refs by adding a use that produces no extra instruction? For example, change `if (mode == 0 && (res & 1))` to `if (!mode && (res & 1))` — same refs. Hmm.

What about `mode >= 0` → the allocno refs count is per-insn references. Hmm.

Alternatively, extend mode's live range SHORTER. mode's live = 83. First use... let me check the .lreg dump for r73 to see where its live starts/ends.

Actually, here's a thought: what if I declare `mode` inside the if-block scope or initialize it differently so its live range starts later? mode is set by `mode = -1;` before the if. What if instead I write the code so mode's first set happens later? But the target has `li s3,-1` before the if (in the delay slot). That's sched1 hoisting. The RTL order could still be different.

Hmm! Key insight: live_length is computed on the RTL *before* scheduling. If I move `mode = -1;` later in the C source (e.g., into the if), the RTL order changes and live shrinks. But the target's code has `li s3,-1` scheduled before. sched1 could hoist it.

Currently `mode = -1;` is at C line 970, before `if (st != ...)`. The first use of mode is `mode >= 0` at line 1000 — but wait, there's `cnt = func_80029504();` and 5 ifs between (lines 978-998). So mode's RTL live from set to first use spans the cnt call and 5 ifs = ~40 insns, plus to the last use = 83.

If I move `mode = -1;` down to just before line 1000 (after the 5 ifs), the live length would drop by ~40 → ~43. Then pri = 2*5/43 = 2325 > 1518 ✓. But would the emitted code change? `li s3,-1` would move later in the RTL, and sched1 might place it differently → different bytes. Risky, but sched1 has freedom.

Hmm, but wait: the if at line 971 sets `mode = 0` conditionally:
```
mode = -1;
if (st != (...)) {
    mode = 0;
    if (st != 0) func_8002F620();
}
```
So mode=-1 must be before that if. Can't move it after.

Hmm. What about the ORDER: mode=-1 is right before the if. So its live starts there.

OK, let me reconsider. Maybe instead of flipping priorities, I can make `mode` conflict-free with s3 differently... 

Actually, WAIT. Let me reconsider the problem. Maybe the target's original C doesn't have `mode` as a separate variable at all — maybe the pin was "NEEDED DIFFERS" meaning the pinned register IS what the target has, and the original source had a variable that naturally landed in s3. The pin was added by the decomp author to force s3. So lever-free, we need a different C that naturally puts mode in s3.

Since the target code is fixed, the only freedom is the allocno structure. To get mode→s3 lever-free, mode must outrank base.

Options to raise mode's pri above 1518 (keeping emitted code identical):
- refs 6, live ≤ 78 → 2*6/78*10000 = 1538 ✓
- refs 5, live ≤ 65 → 2*5/65*10000 = 1538 ✓

Can I shorten mode's live by 5 (83→78) without changing code? If the last use of mode moves earlier... The last use is `if (mode == 0 && (res & 1))`. Hmm.

Or the FIRST use moves later.

Hmm, live_length in gcc is `reg_live_length` computed by flow: it's the number of insns between first and last use (weighted by loop depth). For a straight-line function it's basically last_uid - first_uid.

If I move `mode = -1;` to just AFTER the `st = func_8002F648()` call... it's already there. Hmm.

Actually here's a cleaner idea: what if `mode`'s first set is moved INTO the if, e.g.:
```
if (st != ...) {
    mode = 0;
    ...
} else {
    mode = -1;
}
```
Then mode has 2 sets, in different blocks, and the live range... The target code has `li s3,-1` at 10ec (before the branch) and `move s3,zero` at 10f4. Both before/at the branch. If the else-arm sets -1, the code would be: beq → then-arm; else: li s3,-1. But the target has li s3,-1 in the delay slot of the beq, which is the *fall-through*... hmm, actually 10e8 beq v0,v1,1100; 10ec li s3,-1 (delay slot). The delay slot always executes. So mode=-1 is set unconditionally before the branch — consistent with `mode = -1;` before the if. If it were in the else arm, the compiler would put it after the branch in the else block, not in the delay slot.

So the C order is fixed: mode=-1 before the if.

Hmm OK. What about reducing base's pri? base refs 8, live 158. If live were 165: 24/165=1454 < 1518? No, 1454 < 1518 means base pri drops below... wait we want base pri < mode pri. mode pri = 1204. base pri needs < 1204: 24/live < 0.1204 → live > 199. Not possible.

Or base refs 7: 2*7/158 = 886 < 1204 ✓. Can I make base have 7 refs instead of 8? base refs = 8 (1 set + 7 uses). If one use could be folded... 

Idea: combine two base uses into one via a common subexpression the compiler can share? E.g., `unkA3D8` is read in 5 consecutive ifs. In C, could I read it once into a variable? That would change the code (one lh instead of 5). No.

Hmm. What about making `base` not a pointer variable but... 

Alternatively, make mode an allocno with refs 7 by adding a zero-cost ref. Is there a C construct that adds a register reference without emitting an instruction? For example, a use in a context that's folded at RTL: `mode += 0;` → combine folds add 0 (but it's an insn in the RTL before combine; global-alloc runs after combine? Order: cse, loop, cse2, flow, combine, sched, local-alloc, global-alloc. Actually global-alloc runs after local-alloc which runs after... let me recall the pass order: ... combine → sched → local-alloc → global-alloc → ... Hmm, in gcc 2.7.2: cse, loop, cse2, flow, combine, sched, local-alloc, global-alloc, reload, ...

So `mode += 0` would be folded by combine (before global-alloc), so no extra ref.

What about `mode = mode;`? Deleted by flow (dead).

What about a use that's deleted after global-alloc? No, everything before.

Hmm.

Let me reconsider: maybe the live_length can be shortened. live for r73 = 83. The function is 161 insns. mode is first set at insn ~34 and last used at ~139. 139-34 = 105, but live_length counts only "live" insns (reg_live_length is computed differently — it's the number of instructions in the live range, maybe excluding... ). Anyway.

If the FIRST set moved later by 5+ insns → live 78 → pri 1538 > 1518 ✓.

Where's the first set? `mode = -1;` right before the if. The if is at 10e8. The preceding code: `st = func_8002F648()` at 10b0. Between them: 10b4-10e4 (~13 insns) compute file/val.

Hmm! What if I move `mode = -1;` AFTER the file/val computations but before the if? In C, those computations are lines 966-967:
```
file = D_800D34AC[...] & 0xFFF;
val = D_800D34AE[...];
st = func_8002F648();
mode = -1;
if (...)
```
mode=-1 is already right before the if. Can't move later.

What if mode's first *use* moves later? First use is `mode >= 0` in the if at line 1000. Hmm.

What if the last use moves earlier? `if (mode == 0 && (res & 1))` at line 1016. Fixed.

Hmm, hold on. What if I make mode's live range start later by declaring and initializing it at its first use point... no, it's used in the if.

OK, alternative: what if I give mode refs=6 with the SAME code? refs is the count of references in the RTL. `mode = -1` (1), `mode = 0` (1), `mode >= 0` (1), CdReadRequest(..., mode, ...) (1), `mode == 0` (1) = 5. To get 6 I'd need one more reference. But any extra reference = extra insn or deleted.

Unless: `mode = -1;` could be spelled as an expression that references mode twice? Like `mode = (mode = -1);`? The frontend would emit one set. Hmm, maybe two? `mode = mode = -1` — the inner set is to a temp maybe. Ugly.

Or: `if ((mode = -1) >= 0)`? no.

Hmm. What about using mode in the `||` condition differently: `if (func_8002F658() != val || mode >= 0)` — mode is referenced once.

What if: `if (func_8002F658() != val || !(mode < 0))` — same refs.

Hmm.

OK, let me step back. Maybe the live_length can be reduced by REORDERING statements so that the RTL first-set is later. Actually the first set's RTL position is fixed (right before the if) but the *live length* is measured by reg_live_length which counts instructions between the first and last reference. Hmm.

Wait, actually maybe I should reconsider: is live_length 83 for mode? r73: refs 5, live 83, pri 1204. Let me verify: floor_log2(5)=2, 2*5/83*10000 = 1204.8 → 1204. Yes.

And r72: refs 8, live 158 → 3*8/158*10000 = 1518.9 → 1518. Yes.

Hmm, what if I could make base's live_length grow to 199+? Not possible in a 161-insn function... unless loop-weighted. No.

What if base's refs drop to 7 → 886. Then order: ... 74(5000? no, 74 is 3692), 75(2413), 73(1204), 72(886). Then mode before base ✓. But how to drop a base ref?

Base refs = 8. The uses: 
1. `((Unkstruct_80010178 *)base)->unkA3D8` (if 1)
2. `((Unkstruct_80010178 *)base)->unkA3DE` (if 1)
3. unkA3D8 (if 2)
4. unkA3D8 (if 3)
5. unkA3D8 (if 4)
6. unkA3D8 (if 5)
7. unkA3D8 (end)
+ set = 8 refs.

Could one of these be folded into another register? No.

Hmm what if `base` is `D_800AF630` used as a u8* — what if instead I use a *different* base for the last if (e.g. recompute `D_800AF630` there)? That would change code.

OK, I'm stuck on the reg order via C semantics. Let me look at the walls.txt for "global-pri-bank-order" — it's a known wall. But this task is a "singleton crack shard" where I'm supposed to crack them or record a WALL.

Hold on, let me reconsider whether the reg swap is really unavoidable. What if the extra `move` (launder) changes the allocno structure? When I fix the launder (add the copy), maybe base's refs change? No.

Hmm, but wait: maybe there's a different assignment of variables to allocnos. What if I change `file`/`val`'s allocnos such that s1/s2/s3 assignments shift? No, base and mode are r72/r73 with fixed priorities.

What if I make base and file/val share? Hmm.

Let me reconsider: maybe I can make mode's refs 6 via a genuine extra use that costs no bytes because it's in a delay slot or merged. E.g., `mode = -1;` and then... 

Actually! What about `mode` used in the CdReadRequest call AND in the condition — could I write `CdReadRequest(..., mode ? mode : p)` no.

Hmm, what about this: the `p` variable. In the target, p is a3 (r79). p = 0 in the else. What if the C writes `p = mode >= 0 ? q : 0`? That adds a mode ref and changes code.

OK. Let me look at the problem from the "real source" angle again. Perhaps the original source declared `mode` with a different type or used it differently. But the target's code is what it is.

Let me now consider: maybe the reg order can flip if `base` is not the same allocno. What if `base` is declared `u8 *base` but used via a struct pointer `Unkstruct_80010178 *b = (void*)base;`? Then b might be a separate allocno... but the address computation is `lui s4; addiu s4` then `addu at,s4,at` — one base register. If we had two variables, there'd be a copy.

Hmm.

OK let me look at the walls file for global-pri-bank-order to see if there's a documented lever.
