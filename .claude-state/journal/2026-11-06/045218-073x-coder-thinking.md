---
ts: 2026-11-06T11:52:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_spZfWwsSncPiIsvPzJFx
---
Very informative. The target has `nop` in load-delay slots throughout (after each lhu, and after some lw). The compiler emitted nops rather than filling them. In mine, sched1 filled them.

Wait, but sched1 runs on all code. Why would the target leave nops? Because the barriers prevented the scheduler from moving insns into the delay slots? Actually the nops are in the *target* binary — that's the original compiler output. The project's build (from current source with barriers) reproduces them.

Key: the target uses `v0` for the loaded global values, and after each `lhu v0` there's a nop, then negu/srl. The load-delay slot is unfilled because the only available insn (negu v0,v0) depends on the load. In mine, the scheduler put *other* insns in the delay slots (from the next group), i.e. it hoisted the next group's lui/lhu into the delay slot — which requires the barriers gone... wait no, mine has no barriers, so sched1 merged more and filled the slots.

Hmm, in the target, the barrier at line 23 (after sh 0x10/0x08) prevents moving the next `lui v0` (for xr) above. So the nop after lhu remains.

Actually the target's first group:
```
lui v0 (D_800AF7BC); lhu v0; nop; negu v0,v0; srl v1,v0,31; addu v0,v0,v1; srl v0,v0,1; sh v0,16(t1); sh v0,8(t1);
[lui v0; lhu v0; nop; srl v0,v0,1; sh 20; sh 12]   <- xr
[lui v0; lhu v0; nop; negu...; sh 14; sh 10]        <- yl
[lui v0; lhu; ...; sh 22; sh 18]                     <- yr
```
Wait, where are the barriers? The source has barriers only after xl's stores (line 23) and after yl's stores (line 30). But the target's disassembly shows nops after EVERY lhu, including xr's and yr's.

Interesting: the barrier after xl prevents the xr load from filling xl's delay slot. But xr's lhu nop: the next insn is srl v0,v0,1 (dependent). Why is there a nop and not the yl load? Because the yl group comes after the barrier at line 30... no wait, order: xl group, barrier, xr group, yl group, barrier, yr group.

The nop after xr's lhu: the delay slot could be filled by `lui v0` for yl's load? No — both use v0, an anti-dependence (yl's lui writes v0) — anti-dep cost 0, so it could be scheduled in the delay slot. Hmm, but it isn't.

Actually, hmm: maybe sched1 doesn't fill delay slots at all here; the nops are inserted by the assembler/`dbr` (delayed branch) pass? No — load delay nops are inserted by the assembler (gas) when a load's result is used in the next instruction. So these nops are NOT from the compiler's scheduling: they're inserted by gas because the compiler emitted `lhu v0` immediately followed by an insn using v0.

Wait, but sched1 would have tried to fill the slot. The fact that nops remain means sched1 did not fill them (nothing available or not worth it). In mine, sched1 filled them by hoisting the next group's loads.

OK. So the barriers restrict the scheduler to a small EBB, where the delay slot has nothing to fill.

Now for a lever-free MATCH, I need real C that (a) keeps the groups in order and (b) prevents delay-slot filling. Hmm.

Let me look at the p1 (barriers kept, launder gone) diff — 13. And p2 (launders kept, barriers gone) — 22.

p1 is close: with barriers kept, only the launder removal hurts. The launder `__asm__ __volatile__("" : "=r"(pv));` in the else branch: it forces pv into a register and prevents the compiler from reusing it. Let me see p1's diff.
