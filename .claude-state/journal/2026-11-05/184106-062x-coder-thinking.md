---
ts: 2026-11-06T01:41:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aTkLBLbRStAS9JLoTyz7
---
The vA .jump dump function section is 895 lines; the tail at line ~740 shows no jump after 366. But the dump file is the whole TU; my extracted section may have been truncated at ";; Function" of next function. The jump at the end (return) is gone.

Hmm, maybe the return jump was deleted by `delete_jump` when redirect made it a RETURN and then... Actually maybe the RETURN insn was merged/deleted by the "return cross-jump" with another RETURN insn in the same function (cross_jump=0 though).

Let me look at the .rtl dump (after expansion) to see if the jump exists, and the .jump to see if it's replaced by something. It vanished. There's another possibility: `thread_jumps` ran before this (line 2859) — no, thread_jumps runs after this jump pass.

Wait, actually maybe the dump order: the .jump dump is written at line ~2840 right after the first jump_optimize. The vA .jump file section I extracted starts at line 7948 — but that's from the earlier grep for the *jump* file, which had line 7948 for nopin; for vA I grepped fresh. Fine.

Let me check whether the jump insn 368 exists in .rtl (yes) and whether the RETURN version exists anywhere. Maybe the dump prints `(jump_insn 368 366 0 (return))` — grep "return" found nothing. So it's deleted.

Who deletes? Possibly the "Delete insns following barriers, up to next label" (line 176) — no.

Hmm, maybe `redirect_jump(insn, NULL_RTX)` succeeded, then `delete_jump(insn)`? Let me look right after line 656.

Actually, let's look at lines 1000-1050 (a simplejump block) and 1039 `reallabelprev == temp`.

Better: use the debugger-free approach — check gcc source for where a jump to the end is deleted. Search "delete_jump (insn)" occurrences.
