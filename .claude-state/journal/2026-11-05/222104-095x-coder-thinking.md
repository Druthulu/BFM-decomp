---
ts: 2026-11-06T05:21:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kTCCv11qnQqV0palmx8U
---
The counts are the same in flow and cse (299), so the dump files may be the *input* to each pass or something. The dump naming: `v1.i.flow` is the dump after flow? Or the RTL at that point.

This is getting expensive. Let me take a different approach: find which pass removes the stores by looking at the *insn sequence* in each dump. Let me extract the `(set (mem:HI ...24...))` occurrences in order from the flow and cse dumps.

Hmm, the dumps are big (106k lines). Let me grep with context for `(mem:HI` near const_int 24.

Actually, maybe simpler: the source has 6 stores to b[0]/b[2]. In the target object there are 6 sh to 24/28. In v1's object there are 3. Which pass? Let me test with `-fno-...`? Can't change flags.

Let me think about the mechanism instead. GCC 2.7.2's `cse.c` has this in `cse_insn`:

```
  /* If this is a store into a memory location, and we know the location
     is dead, ... */
```

Actually I recall in cse.c there's the "n_sets == 1 && SET_DEST is MEM" case with `cse_insn` recording `reg_eqv`... The dead store elimination for memory is in `flow.c`? Hmm.

Let me grep cse.c for "dead" and for deleting stores.
