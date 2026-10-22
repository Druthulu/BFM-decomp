---
ts: 2026-10-22T00:26:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_p24jGZkSL1TLEhA6a5Bu
---
Item 7: func_8017E780 has ONE launder:
```
            s32 t;
            t = ((Unkstruct_80126B58 *)p)->unk20;
            __asm__ __volatile__("" : "=r"(t) : "0"(t));
            func_8001D0E8(t, 0x140, 0xF0);
```
The re-tie on t: the load of unk20 (t) is followed by a call. The re-tie gives t's reg a 2nd set → the load isn't boosted → it stays at its source position (right before the call). Without it, the load is boosted → sinks to its consumer (the call's argument setup) — which is the same place, hmm.

The difference: the "call arg setup" — sched1 (per the doc §8) moves a call + its immediately-preceding "USE argreg" insns as a unit (SCHED_GROUP_P). The load t is the call's first argument → the arg setup. With the re-tie, the load stays as a separate insn before the arg setup.

Let me test: extract the function, remove the launder, score.

Let me find the function's end. The function starts at 4711. Let me look for the end.

Actually, let me use a trick: the list.tsv says lines=58 for func_8017E780. Hmm, that's the item's "lines" field: 58. Hmm, but the function looks longer than 58 lines. Let me check: list.tsv row: "func_8017E780__ov_SC03_092_jr_8017AE2C	src/ov_SC03_092/ov_SC03_092_jr_8017AE2C.c	func_8017E780	launder	58" → the last column is 58 = the number of lines of the def? The def is ~58 lines (4711-4768?). Let me find the end.

Let me grep for the next function after 4711.
