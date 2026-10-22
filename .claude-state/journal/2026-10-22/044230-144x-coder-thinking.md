---
ts: 2026-10-22T10:42:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_1gpw3Pl5wMzfBe6q3hWq
---
The `set -- $spec` inside the loop: $1 = the src path, $2 = the func name — but `ls -d $R/${1}__*` used ${1} = the src path. I need the item dir name derived from the func name. Let me fix: the item dir = the dir whose name starts with the func name.

Let me redo with a pythonscript.
