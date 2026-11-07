---
ts: 2026-11-06T04:55:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QlZzmidCvHPQlh7cTtEu
---
All 12 (45 ins vs 47). The missing 2 insns are the two reloads? Target has 47, mine 45. Wait earlier the diff said mine 45, target 47. The barrier removal loses 2 insns: one `lw` (call arg reload) and one...? Target has `lw v1,0(v1)` for the sh base and `lw a0,0(a0)` for the call arg. Mine has one reload for the sh base (v1) and no call-arg reload → 1 insn missing, plus maybe a `nop`? Actually target 47 vs mine 45 = 2 missing: maybe target has `lw a0,0(a0)` and a `nop` (load delay) = 2.

So we need the call-arg reload to survive. The load `*p` for the call arg gets forwarded/coalesced to the register holding the stored value.

Key: cse replaces the load with the stored value if it can. Even across blocks? cse1 works on EBBs. The store is before the if-branch... Hmm, but maybe the branch is not between: let me check the RTL order. Source:
```
*p = v0;
if (v0 != 0) {
    sh;
    call(*p);
}
```
The conditional jump on v0 is before the if body. The store is before the jump. So the load is in a different basic block. cse1's EBB: after the conditional jump, a new EBB starts. cse1 won't forward across.

Unless the compiler transformed `if (v0 != 0)` differently: maybe flow inverted and the store ended up in the same block? Or maybe it's not cse but *global-alloc coalescing*: the call arg load result and the stored value could be coalesced because the load is a copy of the same register? No, a load isn't a copy.

Let me actually check the RTL. Let me use cc1 dumps for this function. There's .run/P40/T10/hdump.sh for header pass dumps. Let me check its usage.
