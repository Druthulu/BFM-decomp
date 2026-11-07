---
ts: 2026-11-06T22:42:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_22ayajsz7cUXcwpXzy5Y
---
This only handles direct reg copies. So r78's a1 preference must come from an insn where r78 is set from a reg (a copy). Hmm, insn 90/100: `r78 = r76 - ...`. Not a copy.

Wait, maybe the "prefers a1" in the alloc_table is derived differently by the tool (tools/alloc_table.py). Let me check what the tool reports. It might report the *preference set* including full_preferences. Hmm.

Actually, maybe the tool's "prefers" column comes from the greg dump's "N preferences: M" lines, which are `hard_reg_preferences`. And those come from set_preference during the conflict scan. For r78, the preference a1 means some insn sets r78 from a reg... Hmm, but there's no such insn.

Wait — maybe r78's number in the .greg dump is not iVar4. Let me re-check: the lreg dump says insn 81 sets r78 = minus(r76, ...). But the greg dump's "78" might be a different pseudo after the register allocation? No, the numbers are stable.

Hmm, but the "78 preferences: 5" line — maybe the preference comes from an insn where r78 is an *operand* with a hard reg. Let me look at mark_reg_set/mark_reg_clobber... Actually set_preference is called only from mark_reg_set with SET_SRC.

Unless there's another call site. grep showed only 1348 and 1535. So set_preference is called when a reg is set.

Hmm, so which insn sets r78 from a reg? Maybe after reload/combine there's a `r78 = r76` copy somewhere. In the greg dump, let me search for insns setting r78.

Let me look at the w0 greg dump for "reg/v:SI 78" lines.
