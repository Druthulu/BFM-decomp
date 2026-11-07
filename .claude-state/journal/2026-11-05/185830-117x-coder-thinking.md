---
ts: 2026-11-06T01:58:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AWjfolSIh3gw552RmfNn
---
gdb says "No symbol table is loaded". Maybe the binary's symbols are present but gdb needs `file`. Let me try `gdb -q -batch tools/bin/.../cc1 -ex "break delete_insn" -ex run ...`. Hmm, the issue: I passed `tools/bin/gcc-2.7.2-psx/cc1` then `--args`; maybe `--args` after the file resets. Use: `gdb -q -batch -x script --args tools/bin/.../cc1 -quiet ...`. Earlier that gave the same error. Perhaps gdb can't read the 32-bit static binary's symbols? Let me test `gdb -q -batch -ex "info functions delete_insn" tools/bin/gcc-2.7.2-psx/cc1`.
