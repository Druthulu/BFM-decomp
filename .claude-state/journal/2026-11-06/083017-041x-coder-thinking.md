---
ts: 2026-11-06T15:30:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dUYH0iH9TkjkINOqrEis
---
The function starts around line 2773 in the source file (the dump references line numbers). The TU line 2773... the function def in the TU. Let me find the function's start in the dump: cse dump prints ";; Function func_8017E178" maybe? Let me grep "Function func_8017E178" — it didn't match "func_8017E178" alone? The grep did match lines with the filename. Hmm, the function name may appear as a label. Let me grep "Function".

Actually, better approach: use the .lreg dump or .greg which has function headers. Or just look at the .s file, and work from the cse dump around the region. Let me find where the source line 2773 maps.

Actually the cse dump is in insn order; the function body is a contiguous region. The function is at source line 3156 in the original src but in the TU copy (a7_tu.c) line numbers differ. The dump line 5448 references 2760 — that's the TU line? No, 2760 is an insn uid probably.

Let me search for ";; Function" in the dump.
