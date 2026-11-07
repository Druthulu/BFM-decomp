---
ts: 2026-11-06T08:33:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1OhWBnEIZv4mZGcYn6Zn
---
The build object is the *current* compiled src (score 0 anyway). The "target" is the original binary, disassembled from the ROM/asm in build/asm? Let me check build/asm. Actually the comparison target likely comes from the original executable disassembly, maybe `build/asm/...`. Let me check what delever_search uses — grep its source for "target". But source reading is allowed for tools? The rule says experts learn tools from --help; coders can read the source? Not forbidden, but let's avoid. Use `--keep`.

Let me run --keep with c1.c to get the scratch and see.
