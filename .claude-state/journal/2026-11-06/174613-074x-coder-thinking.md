---
ts: 2026-11-07T00:46:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DlWb8QcB1J9J7RSMxFZY
---
There are blank lines between the do-while and *p = 0. Let me fix the patterns to include the blank line. Simplest: change ST3 and TAIL definitions to match exactly: ST3 ends with "            } while (0);\n\n" and TAIL starts with "            *p = 0;\n".

Let me update gen2.py: add "\n" after the do-while close, and for ST3P add a blank line after.
