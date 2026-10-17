---
ts: 2026-10-17T13:58:40.347Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I'm noticing that in case 0, the known value being 0 means val+1 would be 1, but the compiler doesn't propagate that constant through the switch since the target still loads the value directly. I'm trying to figure out the scheduling order by working backward from the load and the li instruction at the top, considering whether aliasing could explain it.

I'm comparing exact instruction placement between my attempt and the target: the target loads right after a function call, before any stores, while mine delays the load past several symbol stores. I suspect a volatile asm barrier is fencing the load before it, and I'm wondering if rearranging the statement order in the original source — like moving the pointer store earlier — would shift the scheduler's placement of the load.

To force the load to stay before the stores, I need anti_dependence between them to hold true, so I'm digging into how memrefs_conflict_p in 2.7 handles distinct fixed SYMBOL_REFs — recalling whether different symbol addresses are treated as non-conflicting or whether the PLUS/rtx_equal checks change that.

So symbol references avoid dependency conflicts since they're resolved via assembler macros, while register-based memory accesses can still conflict — that's why the scheduler could freely move the load past the symbol stores in the target but not in the pinned original with its barrier. I'm now trying to brute-force the statement reordering, testing candidate positions for the value read and the literal assignment to see which permutation the scheduler would actually produce.

Before brute-forcing all 720 permutations, I should actually time a single compile to see if this is feasible.

The `+1` spelling doesn't affect where the load sinks—it always lands just before the `*p` store, its only possible alias. I'll apply catalog move R42 to permute the independent statements and time that version first.
