---
ts: 2026-11-06T05:12:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DuGcyfjWkvf9wWML9Flr
---
C0473: "`sb` ALIASES SCALAR GLOBALS WHILE `sh`/`sw` STRUCT STORES DO NOT" — that's about mem_in_struct_p alias behavior. Interesting: MEM_IN_STRUCT_P affects aliasing. And C0381/§340: "sched.c's ALIAS ORACLE emitting a FALSE true-dependence".

So alias behavior via C types IS a recognized real-C lever in this project (§425, §469 MEM_IN_STRUCT_P).

The cast `*(s16 *)&D_80078EA6` — does it set MEM_IN_STRUCT_P? No, it's a scalar cast. Hmm.

Let me read §425 (C0473) — it might tell me how to make the EA4 store alias the EA6 load with a struct store. Actually, the target's *store* is `sw v0,0(at)` — a scalar store. If I make it a struct store (e.g., via a struct-typed lvalue), the alias behavior changes (struct stores don't alias scalars per §425). That's the opposite direction.

Hmm, what makes a scalar store alias a scalar load? Per §425, `sb` aliases scalar globals while `sh`/`sw` struct stores do not. Our store is `sw` (scalar) — does it alias scalar loads? Apparently not (the compiler reused the load).

Wait, in the target, the reload happens because of the asm clobber. In real C, the scalar sw store doesn't alias the scalar lh load (different symbols).

So to force the reload, I need the load or store to be in a different alias class such that they conflict. The cast does that (it changed the MEM's alias set).

Let me look at §425 to understand the alias rules. Let me read C0473.
