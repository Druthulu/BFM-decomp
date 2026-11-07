---
ts: 2026-11-06T15:32:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EZLxyUswSOrHPj2ZJ1Tu
---
The cse dump's function header at 10511, but the rtl dump's header at 11317 — different line bases because each dump file has different content. In the cse dump, the asm should be there. grep -c "asm" = 151 occurrences in the whole file (other functions). Let me grep for asm within the function region of the cse dump more carefully — maybe the asm is printed as `(insn ... (set (reg/v:SI 74) (asm_operands...)))`. My sed range 10511-12151 found none. Weird. Maybe cse replaced the asm with a plain set? Or the function header in cse at 10511 but the function body is elsewhere?

Hold on: the cse dump prints each function's blocks then the insns. The function func_8017E178 in the cse dump is at 10511 and the next function at 12152. The grep for "asm" in that range found nothing. But the asm must be in the RTL. Unless the asm was deleted because its output is a tie (a no-op)? cse's delete_trivially_dead_insns? No.

Wait, maybe the orig cse dump I generated is from the TU where the function body was NOT replaced with orig.c? I passed orig.c to --try, which splices it. Should be right.

Hmm, let me look at the .rtl dump (before passes) at 11317 to see the asm.
