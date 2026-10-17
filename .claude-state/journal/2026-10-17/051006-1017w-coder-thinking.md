---
ts: 2026-10-17T11:10:06.721Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
I'm wondering whether CSE could fail to recognize pd as constant if it's loaded from memory rather than set directly—checking if the equivalence table would still catch that case, since that affects whether this extra instruction actually matters.

Looking at the target's layout, I'm trying to match it against possible source constructs like `if (pad != 0) {...} else {...}` versus `if (pad == 0) goto else`, since gcc 2.7.2 tends to lay out blocks in source order and that constrains which C form produced this control flow. Tracing through the EBB that cse1 would follow—BB0 into BB1 via fallthrough, then the bne path into the store block—the join label with multiple uses would terminate that extended block, which matters for figuring out whether the pd[2] read gets folded consistently across both passes.

For the read to stay register-relative in both cse passes, pd can't carry a qty_const at that point in either pass, which seems hard to arrange if pd is just a simple constant-valued pseudo. I'm wondering if pd's value instead comes from something like `(set pd (plus Y K))` where Y isn't a known constant, or if there's some invalidation happening when pd gets set a second time within the EBB. I'm also considering whether cse_follow_jumps' path rescanning interacts with invalidate_skipped_block in a way that breaks the constant tracking, or whether this is really about reload/regclass introducing a REG_EQUAL note when the address is used elsewhere as a value.

Even so, fold_rtx would still fold the PLUS regardless, giving a constant address, and then find_best_addr's CONSTANT_ADDRESS_P check would just return early without substituting a register -- so the memory address stays constant. I'm trying to trace whether validate_change then replaces that constant address and whether lookup() on it hits that same early-return path.

Maybe the class also contains `(plus pd 4)` itself, if an earlier insn set rX to that expression — cse would fold the equivalence and group rX, (plus pd 4), and the constant together, then pick whichever has lowest address cost and best rtx_cost.

If cost ties favor the folded constant, only that constant gets re-inserted into the equivalence class, meaning a later MEM address lookup would resolve to a different register entirely than our target—so that path doesn't explain the (plus a1 4) case. I need to figure out specifically when the raw (plus pd 4) expression itself gets inserted into the table as a MEM address, since that's the key to reaching our target form.

Checking cse_insn more carefully, it inserts the folded MEM source itself, not the inner address expression separately—so insertion of (plus pd 4) must happen through a different mechanism. This pushes me to compare rtx_cost for CONST versus the plus expression under MIPS's cost model, since that tie-break determines which form survives into the table.
