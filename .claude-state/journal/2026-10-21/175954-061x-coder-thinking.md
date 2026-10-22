---
ts: 2026-10-21T23:59:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_GyY57WgEsUnXkeNsIKpA
---
The target for 8017EEB0: the value stored (`sh v0,2(s0)`) is in v0 ($2) — the pinned register held the *stored* value (0xF/8/4/2), and the first call's result (func_8012BCCC) is compared directly in v0 (the call's return reg) — `slti v0,v0,25600` uses v0 = the call result, and `slt v1,v1,v0`.

So the pin `register s32 v0 __asm__("$2")` was applied to the *stored value* variable, not the call result. In the current src, the same variable `v0` is used for BOTH the call results and the stored value (the pin forces it into $2).

The win.c splits them: `w` = the first call's result (used twice: `w > 0xFFFFF` and `w < 0x6400`), and `v0` = the second call's result / the stored value.

Mechanism: the pinned $2 must hold the value that is stored (the 0xF/8/4/2 constant) and the second call's result. Splitting the first call's result into its own variable `w` (2 uses) leaves `v0` (the value stored) as the allocno that wins $2 — because the stored value's live range is short (set → store) while the first call's result (w) is live across two compares.

Good. Now, the evidence: "gcc local-alloc: splitting the 1st call's result into w (2 uses) leaves the stored value as the short-range allocno, so it wins $2; the pin is gone".

Now let me write the notes and results. Let me do it efficiently.

First, count the candidates per item for the "tries" column.
