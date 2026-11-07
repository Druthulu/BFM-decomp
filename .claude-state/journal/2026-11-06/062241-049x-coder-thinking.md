---
ts: 2026-11-06T13:22:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FxwcIhtDLBypaboGyIBe
---
None cracked; do-while made it worse (4). Hmm. So the block split doesn't stop the sink (sched1 may schedule across? No, sched1 is per basic block... but maybe the do-while notes don't create a basic block boundary at that point, or the sched1 pass treats the loop notes differently).

Wait, v01 got score 4, worse than 2. Let me think differently.

The addiu a1,sp,16 is the address of `buf`. In the target it's emitted right after `addiu a0,s3,4` (the aa address). In mine it's sunk to just before the call.

What if `nn` were not a separate pinned variable but... nn is pinned to $5 (a1). The instruction `addiu a1,sp,16` is the *initialization* of nn from the address. Since nn is a hard-register variable (pinned), the compiler emits `addiu $5, sp, 16` directly? The disassembly shows a1 (=$5). Yes.

So the target order: a0 setup, a1 setup, then the s0 chain, then jal. Mine: a0 setup, s0 chain, a1 setup, jal.

sched1 decides. The barrier (memory clobber) prevented sinking of the addiu across it. Without it, sched1 sinks addiu a1.

Options:
1. Make the a1 setup depend on something computed early — no.
2. Make the s0 chain depend on a1 (so it can't move before the addiu) — e.g. use `nn` in the computation? Would add code.
3. Use a different C form for the call argument so the addiu is born earlier: e.g., pass `(s32 *)buf` directly in the call instead of `nn`: `func_80015978(aa, (s32 *)buf);` — then the address is computed at the call site (later). Worse.
4. Compute `nn` from something that forces scheduling: e.g. `nn = (s32)buf + 0;`? fold.
5. Use `buf` in a statement before the s0 chain, e.g. `d[2] = buf[0];`? changes code.
6. Reorder source: move `aa = (s32)(q+1); nn = (s32)buf;` AFTER the s0 chain but before the call — that's v09 (score 2, same).

Hmm, what about making the call's argument setup earlier by using the pinned var in a way that sched1 sees as high priority. In the target, the two addius are emitted right after the second rand's move. That suggests in the original source, `aa` and `nn` assignments came after `t = rand();` and before the s0 chain — exactly as now. The barrier kept them there.

What real-C construct orders them? A data dependency: if the s0 chain's first insn depends on the addiu a1... it doesn't.

What about making `t` and `s0` assignments be *conditionally* dependent on nn? no.

Alternative: use `s0 = rand(); t = rand();` — the two rand calls. Target: after the second rand, move s0,v0; addiu a0; addiu a1; andi s0... 

Hmm, what if we reorder the source so the aa/nn assignments are placed *before* the second rand? Then they'd be earlier than target. Not good.

The difference is only scheduling within the block. sched1 sinks addiu a1 because it's low priority and has no deps. What raises an insn's priority in sched1? The "birthing boost" (an insn that sets a pseudo used by many). addiu a1 sets a hard reg (pinned nn). Hmm, since nn is pinned to $5, the insn is `(set (reg $5) (plus sp 16))` — a hard-reg set. Birthing_insn_p checks if the dest is a pseudo born here... For a hard reg, maybe not.

Wait — maybe the pins are the problem! What if we drop the nn pin (a lever of another kind that "may stay", but we can also remove it — removing levers is allowed, we just can't add). The nn pin ($5) may be what makes sched1 sink the addiu: with a hard-reg destination, the insn has no "birth" boost. Without the pin, `nn` would be a pseudo, and the insn `(set (reg nn) (plus sp 16))` would get a birthing boost and be scheduled early!

That's promising. But then register allocation must still give nn = a1. The pins were "load-bearing" per the original notes ("every pin left here is load-bearing"). But we only need score 0; the original author said pins were needed, but maybe not all.

Actually careful: the brief says levers of other kinds the def already had may stay, never added. Removing them is fine (it's more lever-free). If dropping the nn pin fixes the order and the allocator still gives a1, score 0.

Let me test: variant dropping `register ... nn __asm__("$5")` → `s32 nn;`. And maybe also aa's pin. Let me try several combinations:
- v11: drop nn pin only.
- v12: drop aa pin only.
- v13: drop both aa and nn pins.
- v14: drop nn pin + do-while around s0 chain.

But wait: if we drop nn's pin, `nn = (s32)buf` might become a `addiu a1,sp,16` anyway via allocation. Let's test.

Also: the target has `addiu a0,s3,4` for aa — aa is $4. If we drop aa's pin, allocator might put it elsewhere. Test.

Let me generate these.
