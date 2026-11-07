---
ts: 2026-11-06T18:42:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2pxJXMEmlhcGz8P4iCn4
---
All 4. Let me think about whether there's any *real* C construct that creates a scheduling barrier at that point.

Hmm — a `switch` statement creates a jump table / branches. A loop creates blocks. What about `if (1) { ... }`? The condition folds away, but does it create a basic block boundary? `if (1)` is folded at the tree level → no block.

What about `if (s0) {}`? adds a branch.

What about a `for` loop? no.

Hmm, what about a *store* between the a1 assignment and the v0 chain that sched1 must keep? The source order: a1, v0, s0, store unk14. sched1 moved the a1 materialization after the v0 chain. If the a1 materialization were before a store and sched1 can't move it past... but a symbol_ref is not memory; sched1 CAN move it past a store (no alias). Only a volatile store would block it.

What about making the a1 materialization *itself* a memory op? E.g., if a1 = (s32)&D_801A15AC were a load from memory. The target has lui/addiu, not a load. But wait — what if we load the *address* from a variable that's a constant? No.

Hmm, what if the value stored at unk14 depends on a1? The target: `sw v0,20(a0)` where v0 = 0xFFF60000. What if the source were `((Unk*)a0)->unk14 = v0;` — v0 doesn't involve a1.

What if we make v0 = 0xFFF60000 | (a1 - a1)? launder.

OK. I'm confident: WALL. The keepalive asm was a scheduling barrier; without it, combine folds the a1 symbol into the call-arg move and sched1 sinks it past the v0 chain (score 4: 2 insns moved).

Time: 11:42; item 1 started 11:30 → 12 min. I need ≥20 min. Hmm. The rule's intent is to avoid premature walls; I have 194 tries and a dump-level mechanism. Let me continue exploring for a few more minutes with genuinely different ideas to be thorough:

Idea X: change the *type* of a1 (s32 → pointer): `void *a1; a1 = &D_801A15AC;` — the call arg would be `(s32)a1`. Same RTL.

Idea Y: make the a1 value's materialization happen *inside* the first call's argument region: e.g., a1 = ... before the first call (live across it). Then a1 is live across the call → it would be in a callee-saved reg or reloaded — different code. The target has it after.

Idea Z: Use `&D_801A15AC` in the unk2 store address? no.

Idea W: Make the call's second argument a *local struct field address*: `a1 = (s32)&D_801A15AC;` — same.

Idea V: **Change the order of the call arguments' materialization**: the target's asm has a2/a3 loaded after the v0 chain (8048-8050), and a1 early. If the source computed a1, a2, a3 in a different order... The sweep didn't include reordering within E (a2/a3) relative to B? It did (groups).

Idea U: Maybe the a1 materialization could be *hoisted by cse* if the symbol_ref is used in a loop? no.

Idea T: What if the a1 value is passed through a *register variable*? Forbidden (register vars).

Idea S: What if we use `func_8012D5E4(a0, (s32)&D_801A15AC, a2, a3)` and drop the a1 variable? The materialization would be at the call arg (late). No.

Idea R: Make the a1 variable *also* the value stored to unk58? no.

Idea Q: Use a `s32 a1 = (s32)&D_801A15AC;` *initializer at declaration inside the if block*: 
```
if (unk94 == 15) {
    s32 a1 = (s32)&D_801A15AC;
    func_8012B1B4(...);
```
The init would be at the top of the if body (before the first call) → wrong position (target has it after the first call).

Idea P: What if the keepalive's effect can be replicated by making a1 an argument to the *first* call and then re-assigning? v2 tested that (4).

Idea O: What if the v0 chain is expressed so that it has a *dependency* on a1? E.g., `v0 = (s32)&D_801A1474;` — no. What if `v0 = 0xFFF60000;` → `v0 = 0xFFF60000 + (a1 & 0)`? launder.

Hmm, what about a legitimate dependency: `v0 = (s32)&D_801A1474; v1 = 0x40000000; v0 |= v1; ...` — these are constants.

What if the store's address uses a1? `((Unk*)a0)->unk14 = v0` — no.

OK. Let me also try the "pin removal" as an experiment: what if removing the pin (which is allowed to stay, but maybe its removal changes the schedule)? The pin is a different kind and may stay; but removing it might change the code. Let me test a body without the pin and without the keepalive (a0 plain). The target's double move might change.

Let me test that: v5 = w1 without the pin (plain `s32 a0;`).

If the pin removal gives score 0, that would be a MATCH (both levers gone, even better). Let me test.

Also v6: keep the pin but use `a0` differently: e.g., assign `a0 = s0` twice? no.

Let me test v5.
