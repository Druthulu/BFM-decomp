---
ts: 2026-11-06T08:41:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_M8okI611ira4YPYFWj9S
---
c1 mine: missing the `nop` at position after lw v1 (target insn 25). Target has an extra nop between `lw v1,0(at)` (t4 load) and `sw v1,32(sp)`. Mine has no nop there — i.e., a delay-slot nop that the target has. This nop is probably a load-delay nop (load in a delay slot or scheduling artifact). Actually the nop at target 25 comes from sched1 not filling? Hmm, it's the nop after a load in a "load-delay" slot.

In w1 (score 9), we had 47 insns and that nop was present:
w1 listing line 36 `nop` after lw v0,0(at) then sw v0,32(sp). Yes w1 has the nop. So c1's reordering removed it.

OK so reordering t3's store doesn't work.

Let me think again about what real C can lengthen t3's live range by 1 insn slot without changing emitted insns. The live length counted in the .lreg dump is "across 5 insns" for r77 in w1 (insn 39 to 51 = 12 in insn numbers but 5 actual insns). The count is the number of insns between first and last use inclusive? insn 39 (lw), 42,45,48 (sw at 51) — from 39 to 51 inclusive, insns: 39,42,45,48,51 = 5. Yes, counts non-note insns.

To make it 6 without adding an instruction or changing order, t3 must be used in one more existing insn before its store. What if the store `sp10[3] = t3;` is written as something else that uses t3 twice? No, count is insn span, not uses.

Alternatively make t3's load later in the stream: if t3's load (insn 39) moved later (after t4's load?) then the span from load to store shrinks... we want to shrink t3's priority below 3703, i.e. increase span. Actually live 6 gives 3333 < 3703. So the span must grow by one insn. The only insns between t3's load and store are sw t0, sw t1, sw t2 (3 insns). To add one, an instruction must be between. In target there isn't.

Alternatively reduce t3's refs? no.

So lowering t3's priority needs a different structure.

What about raising the a0-copy's priority? refs 5→6: 2*6/27 = 4444 > 4000. A 6th use of the a0 copy that doesn't add an instruction... Hmm, but if a use is folded into an existing insn, refs counts the pseudo occurrences in RTL. E.g., use a0 twice in one expression: `h[0] = h[0] + ((Unkstruct*)a0)->unk6;` — could write `h[0] = h[0] + ((Unkstruct*)a0)->unk6 + 0;` no.

Or use the pointer copy in the store address of the call: `func_8012C51C(sp10, (s32)a0);` is one. What about `func_8012C51C(sp10, (s32)(a0));` same.

Could we make the a0 copy local instead of global? Hmm.

Different idea: maybe change the live length of the a0 copy by moving the call earlier? No.

Alternative real-C route: make the a0 copy die and be re-created? No, target uses a2 throughout.

What if we don't use a copy at all, and instead cast a0 directly each time (no local var)? The param pseudo r4 would be used 5 times; but gcc creates a copy at function entry (move a2,a0) anyway, and the pseudo lives 27.

Hmm, what determines whether the a0 copy is global? "crosses 3 calls" is weird. Let me look at w1's global dump (the .greg file) for the function section.
