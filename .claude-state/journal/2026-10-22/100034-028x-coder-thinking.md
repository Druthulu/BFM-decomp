---
ts: 2026-10-22T16:00:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7OzKcUOh1KMlSzkvz3u6
---
Now I see it clearly: at cse2 (actually before cse2 — this is the input to cse2? no, the dump is *after* the pass), insn 21 sets `reg:SI 80 = fp+16` — a pseudo holding &m. Then insn 33 sets a1 = reg80 with REG_EQUAL (plus fp 16). So cse created reg 80 for the address (plus fp 16) because it appears in the block move's dest and in the calls.

Interesting: the block move is `movstrsi_internal` (a movstr pattern) with dest `(mem:BLK (plus fp 16))` and source `(mem:BLK (reg 81))`. So expand_block_move uses the movstrsi_internal pattern with a *register* source (reg 81 = symbol). And the address of the dest is `(plus fp 16)`.

Then cse created reg 80 = fp+16 to hold the address. Why? Because `find_best_addr` decides an address is worth a register when it's used in multiple MEMs and... Hmm, actually insn 21 appears at cse2 — maybe cse2 created it. Let me check .cse (first cse) — insn 21 may not be there. And check .rtl (before passes).

Actually the key: cse's find_best_addr: for `(plus fp 16)`, it computes the address cost; if the address is not "cheap" (e.g., contains a pseudo that isn't constant), it creates a reg. Here fp+16 IS a valid base+offset, so it should be cheap. But `find_best_addr` in cse.c: if `addr_affects_sp_p` or if the address is used in multiple places with REG_EQUAL... Hmm.

Wait — maybe cse created reg 80 not for the MEM address but because of the *REG_EQUAL note* on the a1 copy: cse propagates `(plus fp 16)` into a1's REG_EQUAL and then... no, insn 21 is a separate set.

Let me check .cse (first pass) to see whether insn 21 is created there, and .rtl.

Actually, the important thing: how does the *target* avoid it? In the target, the same C shape (if it were a block move) would produce the same cse behavior — unless the target's C did NOT have a block move, but 8 element stores. With 8 element stores `m[0]=t0; m[1]=t1; ...`, each dest is `(plus fp 16+k)` with distinct offsets → cse's find_best_addr may still create a reg for `fp+16` as the common base? In the w1 version (element stores, no struct copy) the diff showed self in s1 and no &m reg → so cse did NOT create reg 80 there. Good.

So: element stores (m[i]=t) don't trigger the address reg; the block move (movstrsi_internal) does. Why? Because the movstr dest `(mem:BLK (plus fp 16))` is a single MEM with that address, and cse's find_best_addr for a MEM in a movstr... plus the calls. Hmm, in w1 the address `(plus fp 16)` also appears in the calls (3 uses) but not in a store MEM. Maybe cse only creates an address reg when the address appears in a *store* MEM (find_best_addr is called for stores?) Actually cse's find_best_addr is called on addresses of MEMs in *loads* and stores. Hmm.

Wait, in w1, the stores are `m[0] = t0` → dest MEM `(plus fp 16)` too! Same address, 8 times + 3 calls = 11 uses. And cse did NOT create a reg. Hmm, contradiction.

Unless in w1 the stores were `(plus fp 16)`, `(plus fp 20)`, ... and cse's fold... the address `(plus fp 16)` appears once as a store dest and 3 times in calls. In c_struct, the block move dest is `(plus fp 16)` once + 3 calls. Similar. Hmm.

Wait, maybe the difference is that the movstr insn's dest MEM is BLK and cse treats it differently.

Let me check the .cse (first cse) dump for c_struct: is insn 21 there? If insn 21 exists already before cse (from expand), then it's not cse's doing — it's expand_block_move itself! Look: `movstrsi_internal` uses the dest `(mem:BLK (plus fp 16))` — that's not reg 80. So reg 80 is separate. In insn 33 (a1 = reg80) the REG_EQUAL says (plus fp 16). If expand had created reg80 for the calls, it'd be before the block move. Insn 21 comes right after the branch — before the block move (insn 24). Hmm.

Let me check .rtl and .cse.
