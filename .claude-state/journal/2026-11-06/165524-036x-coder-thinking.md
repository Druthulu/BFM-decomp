---
ts: 2026-11-06T23:55:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KlLLgHlCtFFtPoD6skiA
---
So r72 = base: 8 refs, 158 insns. r73 = mode: 5 refs, 83 insns.

To flip: need mode pri > base pri. pri = floor_log2(refs)*refs/live*10000.

base: 3*8/158 = 1518
mode: 2*5/83 = 1204

If mode live were 78: 2*5/78 = 1282 — still < 1518. Need ≤65 for 1538.

Hmm, 83→65 is 18 insns. Hard.

Alternatively, base live 158→? To get below 1204: 24/live < 0.1204 → live > 199. Impossible.

Or base refs 7: 2*7/158=886 ✓ (mode 1204 > 886).
Or base refs 6: 2*6/158=759.

So dropping ONE base reference flips it! base has 8 refs (7 uses + 1 set). If I can drop one use...

Hmm, the 5 `unkA3D8` reads. What if one of them is read from a different expression that doesn't count as a base ref? E.g., if the last if used `D_800AF630` directly (a fresh symbol reference) instead of `base`... that would add an address computation (lui/addiu) — extra insns.

Hmm, what if base's SET is eliminated? If `base` were a function parameter... no.

Wait — what about `base` being assigned once and the compiler keeping it in a reg. What if I declare `base` as `u8 *base = D_800AF630;` at declaration (init at decl)? Same.

Hmm, what if I use `base` in one place where the value is already in another register? no.

OK, alternative: increase mode refs from 5 to 7 (2 more). Adding 2 refs. What C constructs add a ref without an insn? 

Hmm, actually here's one: in `CdReadRequest(&cdFileLocTable[file], D_80072C74, mode, p)`, mode is passed. What if I pass `mode` twice? changes args.

What about `mode = -1;` → could be `mode = -1, mode = -1;`? dead set deleted.

Hmm, what about making the comparison `if (mode == 0 && ...)` into `if (mode == 0 && mode >= 0 && ...)`? Adds a ref but combine folds it.

Hmm.

OK, so the register order seems genuinely hard. Let me now check: is there a way to avoid needing mode in s3 at all? What if the two levers interact: maybe with a DIFFERENT launder replacement, the allocno set changes so that base's refs drop?

The launder `q` is a separate allocno r79 (p) and maybe r76? Hmm.

Hmm, let me look at the original (pinned) allocno table for comparison. Actually, the pinned version scores 0, so its allocno table is the target's.

Let me think about the "real source" once more. The decompiler author added the pin because lever-free the body didn't match. So the original source's C is unknown to us; the pin approximates it. In this crack shard, we need to find a lever-free body that matches. It may be that the original source used a different structure that naturally gives mode s3.

Key: in the target, base=s4, mode=s3. Since s0,s1,s2 = cnt,file,val, the allocation order is file, val, [base or mode]. For base to get s4 and mode s3, mode must be allocated before base. So the original source's allocno priorities had mode > base.

What if in the original, `base` had refs 7 (e.g., it wasn't used in one of the places we use it)? No — the target code uses base in all those places.

What if the original used `mode` more often? The target code refs mode 5 times.

Hmm, unless live lengths differ. In the original source, the RTL live lengths could differ from our reconstruction if the statement order differs! For example, if `mode = -1;` is placed EARLIER in the source but the code still emits it at the same place after scheduling... no, live_length is pre-scheduling.

Wait: live_length is computed by flow on the RTL. If the C has `mode = -1;` early but sched moves it later, the live length is still large. Conversely if the C has it late...

Hmm, what if the original's `mode = -1;` is not a separate statement but part of an expression, making the RTL order different?

Let me look at what would shorten mode's live to ≤65: the set would have to move ~18 insns later. The if is at RTL position ~34 (insn index). 18 later = position 52, which is past the cnt call and 2 ifs. Not possible.

Unless the LIVE range is measured from the first *use* (not set)? In gcc's flow.c, `reg_live_length` counts instructions between the first and last *reference* (including sets). The set at position 34.

Hmm, what if `mode`'s set `mode = -1` is moved to just before the `if (func_8002F658()...)`? It already is.

OK. What if the original used a completely different variable structure, e.g., mode is not a variable but the result of a comparison... 

Hmm, let me look at the assembly: `li s3,-1`, `move s3,zero`, `bltz s3`, `move a2,s3`, `bnez s3`. It's clearly one variable holding -1/0.

I think this is genuinely a global-pri-bank-order wall. But let me try a couple of experiments to confirm:
1. Drop one base reference by restructuring (won't match code, but see if the regs flip → confirms the mechanism).
2. Add mode refs.

Actually, a cheap diagnostic: make a body that changes base's ref count (e.g., add an unused read of base) and see if the regs flip. If they do, the mechanism is confirmed, and I record the WALL with evidence.

Let me do the diagnostic: add `if (base[0] == 0xFF) { }`? That adds code. Instead, `if (base != 0) {}` — a ref to base that flow might keep (base is a pointer, the test is always true but the compiler doesn't know). That adds an insn (bne) but flips refs to 9 → pri 3*9/158 = 1708, higher — wrong direction. I want refs 7, i.e., remove one.

Let me instead add a ref to mode: `if (mode != -2) {}` — always true, adds an insn, refs 6 → 1445 (still below). Two refs: `if (mode != -2 && mode != -3) {}` → refs 7 → 1686 > 1518 ✓. This diagnostic tells me if flipping the order fixes the regs.

Let me do that as a diagnostic only (won't be a crack since it adds code).

Actually, better diagnostic: temporarily change the *variable* structure to see if the reg assignment follows priority. Let me just do the mode-refs-7 experiment and check whether mode→s3, base→s4.

Let me write it.
