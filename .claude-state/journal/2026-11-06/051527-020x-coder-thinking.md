---
ts: 2026-11-06T12:15:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5PUvPrQpPH2WNEIR4kn7
---
I can run mipsel-linux-gnu-objdump -drz on the build object and on the candidate object. But is objdump on PATH? Let me check by running it. It's a toolchain command; presumably allowed (bin/sc.sh runs gcc from same dir). Let me try.

Actually simpler: dump both to files under the item dir and read them.
