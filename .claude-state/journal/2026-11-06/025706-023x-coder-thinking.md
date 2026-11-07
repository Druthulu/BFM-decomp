---
ts: 2026-11-06T09:57:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7F86OlbwhG6AgzJlEWMU
---
Diff is small: 7 mismatches.
- lines 52-55: mine loads unk4C into v1, unk54 into v0; target reverse: unk4C into v0, unk54 into v1. Wait target line52 lw v0,76(s0) = unk4C; line53 lw v1,84(s0)=unk54. Mine line52 lw v1,76 = unk4C, line53 lw v0,84 = unk54. So mine has t in v1, tb in v0; target has t in v0, tb in v1. And the store order: mine sh v1,6(s0) then... target sh v0,6(s0). And line 55: mine lw v1,80(s0) [unk50] vs target lw v0,80. Hmm, so target reuses v0 for unk50 after storing v0 at unk6.
- line 58: mine sh v0,14(s0) [unkE] vs target sh v1,14. Because mine's tb is v0, target's tb is v1.
- line 59: addiu v0,v1,-8 vs addiu v0,v0,-8 (t-8; mine t in v1, target t in v0).
- line 75: mine nop vs target move a0,s0 — the call setup `((void (*)(s32))func_80146C3C)(s0)` in the target has `move a0,s0` in the delay slot; mine has nop. That's the a0-clobber barrier's job! The barrier `__asm__ __volatile__("" ::: "a0")` made a0 free so the call could move a0,s0 into the delay slot. Hmm, actually mine has nop in the delay slot and target has move a0,s0.

So 3 issues:
1. v0/v1 assignment for t and tb.
2. delay slot fill: move a0,s0 vs nop.

For #2: target's delay slot has `move a0,s0`, meaning the arg setup was scheduled into the delay slot (reorg). Mine emits nop. Why? Because a0 is already live/used? The barrier clobbered a0 making it dead at that point, enabling reorg to fill. Without barrier, maybe s0 is in a0? No, s0 is a separate pseudo.

Hmm wait, actually without the barrier, maybe the call arg is set earlier and reorg doesn't fill. Let me think: target: `move a0,s0` in delay slot. Mine: nop, so the move a0,s0 is before the jal (not in delay slot), or... let me look at the instructions around 70-78 in both.

Let me get the full instruction listing. I can use the cc1 dump / objdump. Let me check tools. There's `bin/dt.sh` output diff only. To see full listing, maybe there's a helper. Let me look at .run/P40/T10/func_80181F4C for tools used, or check for a script that dumps the candidate object.

Actually delever_search has internals; maybe I can add a scratch script that prints both streams. But I shouldn't modify shared tools. I can write a scratch script under my shard dir that imports delever_search and prints.

Let me look at delever_search --try implementation to see if it can print full listing. Search for "def cmd_try" or similar.
