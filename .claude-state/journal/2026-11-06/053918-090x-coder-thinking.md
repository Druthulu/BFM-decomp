---
ts: 2026-11-06T12:39:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ngmdt1DdLs2ciUiLunk2
---
x1 = 5 (launder-as-plain-assign + keepalive removed). So the best lever-free (all three removed) is v0 = 13; but a 2-kind-removed body = 5.

For the WALL row: best = lowest score of a lever-free body = 13. Hmm, but x1 (5) still keeps the barriers. "best = lowest score of a lever-free body" — lever-free means all row kinds gone. So 13.

Tries: 4 + 4 + 8 + 6 + 6 + 3 = 31. Good.

Let me write notes, results row, moves line. Then the log file and finish.

Wall tag for item 4: the barrier is jump2-crossjump-arms (existing tag!). The launder/keepalive are register steers (global-pri-bank-order / lreg-*). Since the dominant is the barrier (12), and there's a fitting tag `jump2-crossjump-arms`, I'll use that.

Hmm, but the row's wall column takes one tag. The mechanism in evidence mentions all three. Let me use `jump2-crossjump-arms`.

Actually — the launder at 2 is a register steer: `global-pri-bank-order`? or `lreg-*`. And the keepalive at 3: the value coalesces with pos (lreg-copy-pref-dying-base?). I'll cite jump2-crossjump-arms as the main tag and mention the others in evidence.

Time: ~07:50. Now write everything up: notes.md, results row, moves.md line, then the log phase-ends/current/logs/T11.cG31.md.

Wait — the LOG path is `phase-ends/current/logs/T11.cG31.md`. Is that allowed? The brief says LOG: phase-ends/current/logs/T11.cG31.md. The general instruction says "never read phase-ends/*/logs/" but writing my own log is required. OK.

Also cleanup: remove --keep scratch (I used --keep twice: .run/P36/engine/score/main__func_8001EFE0/p3 and ov_SC01_005__func_8017EFA8/p3, and ov_MAIN_012__func_80136824/p3). The brief says "`--keep` scratch is removed after use". Those are under .run/P36 (not my shard) but they're the tool's scratch dirs I created. Let me remove them.

Also disk: my shard dir size — lots of .c files, small. Fine.

Let me write the notes for item 4.
