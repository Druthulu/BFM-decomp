---
ts: 2026-11-06T16:34:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_R2OXpBnJLieNhrHYtmBK
---
The tie at the andi requires the input operand to die. In the natural build, insn 61 has REG_DEAD 74, so it ties. For the target, no tie happened. Why? Because in the target's build, the andi's input was NOT ret-74? It reads v1. Hmm, if the input pseudo had a REG_DEAD too, it'd tie.

Unless the tie was *blocked* because the input reg's qty had a copy preference already and... no, tie is independent.

Wait, actually the tie in block_alloc: `combine_regs` ties q1 and q2 only if their live ranges don't conflict. At insn 61, 74 dies (last use) and 75 is born — they don't conflict, so tie. So m always ties to ret. Then how can the target have them in different regs?!

Unless the andi's input is a DIFFERENT pseudo than the one in the branch. In target: branch tests v1, andi reads v1. If both read the same pseudo, tie would put m in the same reg as that pseudo. But m is v0 ≠ v1. So the andi's input must be a different pseudo than the branch's operand!

Hmm! Let's re-read: `350: beqz v1,384` tests v1. `354: andi v0,v1,0x8000` reads v1. If the C were `if (ret == 0) else if ((m = ret & 0x8000))`, both read ret — tie would apply.

Unless the tie is blocked because ret is live ACROSS the andi (not dying). Then m can't tie. If ret were used after the andi, ret wouldn't die at 61, so no tie, and m gets its own reg (v0), ret stays v1. But in the target, after the andi, ret isn't used (v1 dies). Unless ret is used in the else arm! In the else arm (block 4/5), is v1 used? Let me check the target: at 360-374 the else arm: move a0,s0; jal func_80146E90; li a1,32; ... no v1. And the ret==0 path at 384: no v1.

So ret isn't used after.

Hmm, so how can m avoid tying? The tie happens at insn 61 only if reg 74 dies at insn 61. If the andi's input were a *different* pseudo t that doesn't die at 61 (used later), then m doesn't tie with t. And the branch tests a pseudo also v1... 

Consider source:
```c
s32 t = func(...);
s32 ret = t;
if (ret == 0) {}
else if ((m = t & 0x8000) != 0) ...
```
- t = v0 (call result).
- ret = t: copy; t is live after (used at andi) → copy survives → ret gets v1. 
- branch tests ret (v1).
- andi: m = t & 0x8000, input t dies at the andi → m ties with t → m = v0! andi v0,v0,0x8000.
But target andi reads v1, not v0. Damn. Unless t = v1 and ret = v0? The branch tests v1...

Hmm, wait: what if the copy is `ret = t` and t is v1, ret is v0? Then branch tests ret=v0, andi reads t=v1. Target branch tests v1. So no.

What if the branch tests t and the andi uses ret? Target: both v1.

OK so both the branch and the andi read the same register v1. If they read the same pseudo, tie applies and m shares. Therefore in the target they must read *different pseudos that happen to be allocated the same register v1* — impossible (two live pseudos can't share; but if one dies before the other is born they can share the same reg). Ah, that's possible: the branch reads pseudo A (v1), A dies at the branch; then the andi reads pseudo B (also v1, since A's reg was freed). B dies at the andi, so m could tie with B → m = v1. But target m = v0. Hmm.

Unless B doesn't die at the andi (live later) → no tie → m gets v0. And B is in v1 because A's reg... 

Let's construct: 
```c
s32 a = func(...);      // a = v0
s32 b = a;              // b = v1 (copy survives because a live later)
if (b == 0) {}          // tests v1
else if ((m = a & 0x8000) != 0) ...   // andi reads a (v0) -> andi v0,v0
```
No.

```c
if (a == 0) {} else if ((m = b & 0x8000) != 0)   // branch v0, andi v1
```
No.

Hmm, target: beqz v1; andi v0,v1. Same reg.

What if the andi's input is a subreg of the same pseudo? E.g., `(subreg:SI (reg:HI ret))`. The tie loop handles SUBREG: `if (GET_CODE (r0) == REG || GET_CODE (r0) == SUBREG)`, and r1 similarly. Tying a subreg to a reg? combine_regs with a SUBREG... Let me think: if the andi input is `(subreg:SI (reg:HI 74))`, then r1 is a SUBREG, and combine_regs may tie them (same reg) — but the mode differs (HImode). Hmm, that's exactly the HImode case! In w1_r16, ret is u16 (HImode). The andi `m = ret & 0x8000` with m u16 → the RTL would be `(set (reg:HI 75) (and:HI (reg:HI 74) 0x8000))` — both HImode, tie allowed. But w1_r16 gave `andi v0,v1,0x8000` — wait, w1_r16 DID give andi v0,v1,0x8000! And move v1,v0! So in w1_r16 the tie did NOT happen (m=v0, ret=v1). Why? Because... hmm interesting. Let me look at w1_r16's lreg dump. Maybe the HImode andi's constraint made tying invalid, or the andi pattern is different.

In w1_r16, ret was `u16` assigned directly from the call: `ret = func(...)`. So RTL: (set (reg:HI 74) (subreg:HI (reg:SI 2 v0))). The copy from v0 to a HImode pseudo → not tieable (mode mismatch / subreg) → the move survives, ret gets a reg. Then the andi on HImode didn't tie. So ret=v1, m=v0, andi v0,v1 — perfect. Only the zero-test added `andi v0,v1,0xffff`.

So the HImode route nails the copy and the andi. The only problem is the branch's zero-extension.

Can we make the zero-test use `beqz v1` directly? In gcc, comparing HImode to 0 uses `andi 0xffff` because upper bits unknown. What if the comparison is done in a context where gcc knows ret's upper bits? If ret's producer is a zero-extending operation, gcc knows. The producer here is a subreg of v0 (unknown).

Hmm, what if we test `if ((u32)ret == 0)` — same.

What if ret is declared `u16` but we compare `if (ret < 1)`? same.

What if we compare `if (!ret)` — same.

What if the test is `if ((s32)ret == 0)` — sign extension → sll/sra.

What if we make ret HImode but the comparison uses `ret & 0xFFFF`? That's an andi... 

Hmm, what if the test is on a SImode value that's a copy of the call result, and the andi uses a HImode copy? Like:

```c
s32 t;
u16 h;
t = func(...);       // t = v0
h = (u16)t;          // HImode copy -> move v1,v0? then t live?
if (t == 0) ...      // tests v0, not v1
```
No.

We need: branch tests v1, andi reads v1, move v1,v0, andi output v0, and no extension insn.

The extension insn arises only if the branch operand is HImode. If the branch operand is SImode, no extension. But then the andi must be HImode? No, the andi can be SImode with SImode operands.

So: branch operand SImode = v1; andi SImode reads v1. And the move v1,v0 is HImode? The move is the *definition* of ret. If ret is SImode, the copy from v0 (SImode) is tieable. Hmm, but what if ret is defined via a HImode intermediate and then... that adds an extension.

Wait, what about the *tie* being blocked by a REG_DEAD absence: the andi's input not dying. If ret is SImode and used after the andi, no tie. But then m gets v0, ret v1... but ret would need to be live after the andi, adding uses. The target has no such uses. Unless the use is in the else arm but flow/cse removed it? 

Hmm, hold on. What if the tie is blocked because `combine_regs` refuses when the qty already has a hard reg preference? No.

Let me look at why w1_r16's andi didn't tie: read its lreg dump. Let me dump w1_r16.

Actually, let me first consider another way to kill the extension: make the branch test use a value that gcc knows is zero-extended. What if ret is u16 and the test is `if ((u32)ret == 0)` — gcc knows (u32)u16 is zero-extended, so it emits `andi v0,v1,0xffff` then beqz — same. Hmm, that IS the zero-extension.

What if we write the test as `if (ret == 0 && 1)`? no.

What if we make ret `s32` but produce it via a zero-extending HImode copy that gcc folds into a plain move? E.g. `ret = (u16)t;` where ret is s32: gcc emits `andi ret,t,0xffff` (an explicit andi!). That's an extra insn, but maybe cse/combine could... no.

Hmm, wait. Actually maybe the target's `move v1,v0` is a HImode copy but the branch is on a SImode copy of the same? Let's re-read target:
```
34c: move v1,v0
350: beqz v1,384
354: andi v0,v1,0x8000
```
If ret were HImode, the branch would need the extension. Unless the branch tests a *different* SImode value in v1 that was set by the same move... no, one move.

So target ret is SImode. The copy v1←v0 for SImode survives only if untieable. Untieable reasons: (a) the source doesn't die (live after), (b) the destination has a hard reg (pinned), (c) mode mismatch.

Since no pin, (a) or (c).

For (c): the destination or source is a SUBREG with a different mode. E.g., the copy is `(set (reg:SI 74) (subreg:SI (reg:DI ...)))` no.

Hmm, what about a copy through a *different mode* value: `ret = (s32)(u16)t` where t is SImode and ret is SImode: gcc generates `andi` (zero-extend) not a move.

What about `ret = (s32)(s16)t`? `sll v1,v0,16; sra v1,v1,16` — 2 insns.

So (c) gives extra insns.

Therefore (a): the source must be live after the copy. Then the source pseudo is a different value than ret, and it must be used later. What could use it later with no extra visible instruction? If the later use is *dead code that flow doesn't delete*... e.g., a use in a branch that gets folded? Hmm.

Wait — what if the later use IS the andi, and the branch uses ret? Let's see:
```c
t = func(...);        // t v0
ret = t;              // copy survives (t live at andi) -> ret v1
if (ret == 0) {}      // beqz v1
else if ((m = t & 0x8000) != 0) ...   // andi v0,v0,0x8000
```
The andi would read v0. Target reads v1. So no.

Unless the andi reads ret AND t is live after for another reason. What other reason could there be with zero insns? REG_DEAD notes are the only thing that matters for the tie. If t is live out of the block (used in another block), then at the andi t doesn't die. But the target has no use of t later... unless the later use is in a block that the target's code doesn't show because it was optimized... 

Hmm, hold on, what about the possibility that the copy `ret = t` is kept not by liveness but by **cse/copy-prop being unable to merge** because t is used in a *different* basic block? If `ret = t` is in block 2 and t is live out... same thing.

OK let me look at w1_r16's dump to understand why the tie didn't happen there, then maybe find a variant that keeps the HImode copy but tests in SImode.

Idea: make TWO variables: a HImode copy for the andi and a SImode copy for the branch? Then two moves. No.

Idea: what if the branch tests a SImode `ret`, and the andi reads `ret` (SImode), but the copy v1←v0 is HImode because... no, ret is SImode.

Hmm, let me reconsider (a) with the tie: if the andi's input is ret and ret is live after the andi, then no tie → m gets v0, ret keeps v1. So we need ret live after the andi with ZERO extra instructions. Is there a construct where a variable is "live" but not used? A `(use)`? That'd be an instruction.

What about the REG_DEAD note being absent because of an intervening block boundary: if the andi is in a different basic block than... no.

Wait, actually — what about the branch being BEFORE the andi in a different block? In the target, `beqz v1` and `andi v0,v1` are in the same block (delay slot). ret dies at the andi.

Hmm OK. Let me look at w1_r16's lreg to see the RTL. Maybe the HImode andi's REG_DEAD is absent for a subtle reason (subreg). Then the trick is: get the andi to not tie while keeping the branch SImode.

Let me dump w1_r16.
