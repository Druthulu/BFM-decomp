---
ts: 2026-11-06T04:53:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Os3b7G4CoDLs57Iw7t19
---
Removing the barrier changes register allocation significantly (v0/a0 swapped) and the schedule. The target: after `*p = v0` (sw v0,0(a0) with a0 = &D_80127524), then `sh v0,26(v1)` (store to D_80127524+0x1A via v1), then `lw a0,0(a0)` (reload *p for the call arg), then call.

Without barrier, mine: `sw a0,0(v1)` (p in v1), `sh v0,26(v1)`, then the call arg load? Let me see the full mine asm.

The barrier forces the load of *p (call arg) to happen after the store, in the same order as target. Without it, the load moves earlier (before the store), changing allocation.

Let me see the full diff and asm. First, get mine and target asm.

Actually let me get the target disassembly for func_8013A2BC from a build object. Which build? ov_MAIN_012/ov_MAIN_012_jr_801380E0.o.

Let me dump both. For the candidate, use --keep via tryinc? tryinc passes args through; --keep would work if delever_search accepts it. Let me run with --keep.
