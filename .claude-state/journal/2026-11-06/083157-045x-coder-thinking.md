---
ts: 2026-11-06T15:31:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ugEmt52ifAQHNHzC4JfQ
---
No asm in the cse dump — because the asm is deleted/expanded earlier? The asm is an RTL insn with asm_operands; it should appear. Hmm, maybe cse's dump shows it as `(insn ... (asm_operands ...))`. Let me grep the whole orig cse dump for asm.

Actually the grep above was restricted to lines 10511-12151 and found nothing. Maybe the asm insn was converted to something. Let me grep the whole file.
