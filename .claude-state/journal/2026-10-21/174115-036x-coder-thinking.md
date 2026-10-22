---
ts: 2026-10-21T23:41:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_U2kAgdlSTQx8r96pmENX
---
The ov TUs are split into "tail" objects. The function func_8014C308 is in one of them. objdump them and find the function. Let me check if objdump is available and works. The tool uses `objdump -drz`.

Let me find which object contains func_8014C308: grep -l over the .o files (binary) with -a.

Then objdump -dr that object and extract the function.

Note disk: objdump output is small; fine.

Let me doit.
