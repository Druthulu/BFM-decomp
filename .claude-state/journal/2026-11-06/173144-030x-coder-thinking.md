---
ts: 2026-11-07T00:31:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cjZ3TxD0VniUenKsGI3Z
---
Interesting! The sb survived to codegen (68 ins total though — the score is 10 and the insn count matches, but the sb is in the stream replacing... hmm, mine has sb at 33 and target has lui/lw; and mine has 68 ins but with the sb; so somewhere mine is missing an insn the target has... Let's see: mine 68, target 68, but mine has sb + 1 fewer pointer load pair? Hmm.

Also note mine still caches the pointer in a2 (18-19) and uses a2 at 28 and 34! So the sb did NOT break cse here?! Wait, the second use still reads a2 (lhu v0,18(a2)) — so cse still forwarded. And the sb is still in the output.

Hmm, so the byte store did not invalidate. Why? Maybe the dead store was removed... no, it's in the output. But cse's invalidation happens at cse1 — wait, maybe the store's address `(mem:QI (plus (fp) (16)))` — hmm, at cse1 time the frame pointer isn't fp yet, it's a pseudo (virtual stack slot reg?). In gcc 2.7.2, stack slots are `(mem (plus (reg virtual-stack-vars) (const)))`. GET_CODE(addr) == PLUS and mode QI → the condition `!((in_struct||PLUS) && mode != QI)` → since mode == QI, `(true && false)` = false → `!false` = true → all=1. Should work!

Unless... the store was reordered by cse? No.

Wait, maybe the sb is NOT a QI store at cse1 time... it is.

Hmm, but hold on: maybe cse1 did invalidate, and cse2 re-merged them! cse2 runs after loop. Yes! cse2 runs later and would re-CSE the two loads — unless the store is still there at cse2. It is (sb is in the output). Hmm, so cse2 should also invalidate.

Unless cse2's `cse_insn` handles the sb differently... same code.

Hmm, wait. Look again at mine[33:35]: sb zero,16(sp); lhu v0,18(a2). So mine loads the pointer ONCE (a2) and the sb is between the store and the second use. So cse1/cse2 both forwarded.

Why? Maybe because the sb's destination at RTL is `(mem:QI (reg virtual-stack-vars))` with a *constant* offset folded into... no, offsets are explicit.

OR: the store insn's pattern at cse time is `(set (mem:QI (plus (reg) (const))) (const_int 0))` — note_mem_written is called with the *written* expression. Let me check where note_mem_written is called with the destination: line 7981 `invalidate_memory(&writes_memory)` in cse_insn. Let me look at how writes_memory is computed for a store.

Hmm, maybe the issue is that `sb zero,16(sp)` — the value is a constant, and cse may handle constant stores... no.

Let me test more directly: does cse invalidate for a byte store at all? Consider that maybe my read of the flow is wrong: the invalidation might occur but then cse2 re-merges because... cse2's table is fresh and the sb is between. Same invalidation.

Unless the sb was moved *below* the second use by cse's own reordering? The listing shows sb before the lhu.

Hmm, so why doesn't it invalidate? Let me look at cse_insn's store handling around line 7900-7990.
