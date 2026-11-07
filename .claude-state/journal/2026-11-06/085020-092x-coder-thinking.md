---
ts: 2026-11-06T15:50:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_F7IaQawXRxZnJdsdsDQZ
---
Line 69: "keepalive | func_80182424 | WALL combine-argcopy-sink — combine folds 1-use a1 pseudo into call-arg set at the call, sched1 keeps la a1 late; keepalive 2nd use blocks merge (best 4) (WH1)". A keepalive is a lever kind (not allowed). But it says "keepalive 2nd use blocks merge" — a second use of the pseudo blocks combine's merge. So if arg has a second use, the merge is blocked and the la stays early!

What second use can we add at zero cost? A *dead* second use that flow deletes before sched1. But if flow deletes it, the merge... The keepalive is presumably a macro with a real use. Hmm.

But maybe the second use can be a store that's dead? "A dead store kept only to steer a pass" is refused as a close per C0505. Hmm.

What about using arg in a statement that's part of the real logic? The function calls func_80052E38(arg) once. Is there another natural use? Maybe the original code passed arg to another call or used it. Let me look at the target: is `a0` reloaded later? The target's la a0 at the top is the only materialization? Let me grep orig.dis for D_800AF648.
