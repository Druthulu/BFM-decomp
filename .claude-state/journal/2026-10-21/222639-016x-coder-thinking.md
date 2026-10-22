---
ts: 2026-10-22T04:26:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_9sgmdwpLC8U2hM5C7s82
---
The target comes from the tree's own baseline object (the ROM build) — `oracle.baseline_path`. So the target listing can be produced by objdump of the baseline object. I can produce the target listing myself by objdump-ing the baseline .o for the function, to see the whole 40 insn target.

Which TU? `src/shared/ov/func_8014FD54.h` is a header included in many TUs. The target baseline is the same bytes for all (ROM). Let me find the baseline obj path.

Let me find the ROM baseline object: probably build/*.o or build/ov_*/... Let me check what oracle.baseline_path does — grep in tools/oracle orsimilar.
