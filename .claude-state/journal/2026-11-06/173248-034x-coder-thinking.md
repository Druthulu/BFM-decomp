---
ts: 2026-11-07T00:32:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_S2uYgtCMxVcqYnpIq95H
---
So the pointer load happens once (a2 at 2d9c/2da0) and is reused at 2ddc. The sb didn't invalidate at cse time — because the sb was moved? No, the sb is at 2dd8 right before the lhu at 2ddc. So at cse time the sb was between and it still didn't invalidate.

Hmm, wait: maybe the sb was NOT before the second load at cse time — sched1 could have moved the sb up/down. But the second load uses a2 which is only set once, so the load was NOT re-issued by cse. So cse really did keep the entry.

So my reading of note_mem_written must be off. Maybe the store insn at cse time is `(set (mem:QI (reg pseudo)) 0)` where the address is a bare REG (because the stack slot's address was computed as a pseudo reg? No, stack slots are (plus reg const)).

Alternatively — maybe writes_memory.all was set, but `invalidate_from_clobbers` is called... wait, look at the order in cse_insn: `invalidate_from_clobbers(&writes_memory, x)` at line 7236. And `invalidate_memory` removes entries with `p->in_memory`. Maybe our symbol load entry is NOT `in_memory`?! 

Hmm: `in_memory` is set when the expression is a MEM. Look at insert: `new->in_memory = (GET_CODE(exp) == MEM)`. Our entry exp = the MEM expression → in_memory = 1.

Unless the entry was created not for the MEM but... Let me test empirically with a simple check: does the sb actually reach cse? Maybe the front end folds `*(u8*)&svec_in = 0` — hmm, but the sb IS emitted, so it exists.

Unless the sb was inserted AFTER cse by... no, it's in the source.

Wait — maybe the sb appears in the output because it's still in the RTL at the end, but cse1's invalidation happened and the second load was NOT re-issued because cse's `cse_insn` re-inserts... no.

Hmm, let me reconsider: is the second `lhu v0,18(a2)` using a2 because cse replaced the *pointer load* with a copy from a2's pseudo? a2 is the allocated reg for the pseudo holding the pointer. Yes.

Unless... the sb was moved below by cse? No.

Let me do a controlled experiment: write a tiny test? That costs time. Alternative: maybe the invalidation IS happening, but cse2 re-merges because by cse2 time the sb is gone? No, sb is in the final output.

Hmm, hold on: maybe `writes_memory.all` is set, `invalidate_memory` removes all in_memory entries — but then cse's `cse_insn` for the sb also does `invalidate(dest)` etc. Then for the *second load* insn, cse processes `(set (reg v0) (mem:SI (symbol_ref)))` — it looks up the expression: not in the table (removed), so it inserts it and emits the load. So we'd see a second load. We don't.

So the invalidation did NOT happen. Which means note_mem_written didn't set all. Which means... the store's mode isn't QI at that point? `*(u8 *)&svec_in = 0;` — maybe the front end turned it into `(set (mem:QI ...) (const_int 0))`; mode QI. Hmm.

OR: the store was *deleted before cse1*. What deletes it? cse1 itself runs `delete_dead_from_cse`... but the sb is in the output! Unless the sb in the output is a *different* sb — no, sb zero,16(sp) is exactly it.

Hmm, is it possible that cse1 is run BEFORE jump_optimize... and the store got moved? Let me check the pass order and, more importantly, let me verify the invalidation empirically with a simpler experiment: put the dead byte store BEFORE the first use (i.e., right after the call) and see if the first pointer load is also re-issued... that doesn't distinguish.

Better: check whether `writes_ptr->var` is set — `invalidate_from_clobbers` only calls invalidate_memory if `w->var`. note_mem_written sets `writes_ptr->var = 1` at the end (unconditionally for a MEM). OK.

Hmm, what if the store is not a plain SET but combined with the `sb` being represented as `(set (mem:QI (plus (reg) (16))) (const_int 0))` and `MEM_IN_STRUCT_P` true and mode QI → all=1. Should be.

Wait... unless the cse pass that matters is cse1 and at cse1 time the insn stream has the store as part of a different block? No.

Let me look at this from a different angle — maybe the a2 reuse comes not from cse but from *local-alloc/global-alloc* choosing a2 for a pseudo that was already holding the value. No: the value is in a2 because a single load fed both uses.

Hmm, unless combine merged two loads! combine could merge `lui a2; lw a2; ... lhu v0,18(a2)` twice? No.

OK, let me test whether the sb is before or after in the RTL by checking if cse re-issued the load for a *bigger* invalidation: use a BLKmode store (struct assignment) instead of a byte store. E.g., `svec_in = svec_in;`? That's a self-assignment which might be optimized away. 

Alternatively a call: no.

Actually — maybe the simplest: the dead byte store didn't work because cse's *first* pass (cse1) sees the store and invalidates, but then the second use's load is re-inserted and the second load IS emitted... but the assembly shows only one load. Contradiction. So no.

Let me verify my understanding of the compiled RTL by dumping cc1 RTL for the candidate. tools/cc1_dumps_tu.sh + hdump.sh. The brief says hdump.sh (header pass dumps) and cc1_dumps_tu.sh (TU dumps). Dumps must go under my item dir and be deleted after.

Time check: ~17:45; started 17:24 → 21 min. I need to wrap this item soon. Let me consider the budget: "Budget 20-30 min wall per item". I'm at 21 min with 4 tries. A WALL needs ≥20 min AND ≥30 scored tries. So I need 26 more tries quickly, or crack it.

Let me think harder — a smarter approach might beat brute force.

Key question: what invalidates cse's memory table entry for a symbol load in real C? Options: a call, an asm, a QImode/BLK/SCRATCH store. My QImode test failed. Let me verify with a quick experiment whether QImode invalidation works at all — maybe I mis-set the store.

Hmm wait! Maybe the issue: `*(u8 *)&svec_in = 0;` — since svec_in is passed by address to a call, the store is to a stack object whose address escaped. cse's `invalidate_memory` removes entries with `p->in_memory && (all || ...)`. all=1 → removes ALL in_memory entries. Fine.

Unless cse1 did remove and re-insert, but the *second* load was folded back by combine? No.

Let me actually check the RTL dumps. Use tools/cc1_dumps_tu.sh. Let me read its usage.
