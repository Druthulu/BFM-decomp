---
ts: 2026-10-22T12:46:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_OauiypRSWs95YCJxLcwp
---
cse.c has "quantity numbers" for pseudo registers. The reload pass then uses `reg_equiv` / `quantity` info. Let me look at reload.c's handling of a pseudo whose quantity is 1 (single set) — `reload` marks `reg_equiv` when the pseudo is set once from a constant.

Let's grep reload.c for reg_equiv_contain_p and the "quantity" mechanism.

Actually, the more relevant mechanism might be in reload.c: `reload_reg` → for each reload, if the value is a constant, it may "rematerialize". In GCC 2.7's reload.c, there's a function `reload_reg` that decides whether to rematerialize: it checks `reg_equiv_contain_p` and `cost` heuristics.

But we also know from moves.md: "cse-copy-merge", "reload-rematerialise" walls exist.

Rather than deep-diving GCC internals, let me EXPERIMENT. Each test is ~1 second. Let me create a batch of candidate bodies for item 2 and score them all.

Candidates (all keeping the launders removed):

w2: dead reset before:
```c
    it = 0;
    it = (s32)D_80120194;
    p = it + 0x658C;
```
Hmm, but `it = 0;` then `it = (s32)D_80120194;` — the front end stores 0 to the slot then the address. cse might eliminate the first store as dead (cse removes a set of a pseudo whose value is never used? For a pseudo with quantity 2, cse keeps both).

w3: dead reset after the use:
```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    it = 0;
```
But careful: `it` is later reassigned to D_801202A0, so `it = 0;` is dead (overwritten before use). But it does add a set to the pseudo.

Hmm, but wait: does the dead store even reach RTL? The front end expands `it = 0` as a store to the frame slot; then `it = (s32)D_80120194` stores the address; then `it = 0` stores 0 again. Since `it` is a local variable in memory, the front end emits 3 stores + 1 load. Then cse: the loads get merged with the preceding store. The pseudo for the load after the first store has quantity... hmm, cse's quantity numbers: each pseudo gets a quantity = number of sets. With 3 stores, the "load pseudo" after store 1 has quantity 3 → not "quantity 1" → reload keeps it in a register!

That's the classic GCC 2.x mechanism: `reload` only rematerializes a pseudo if it has a single set (quantity 1). So giving the variable 2+ sets forces a register. THIS is exactly the "real 2nd set" trick in the project's cookbook.

But: for the front end, the local variable `it` is in memory (frame slot) — the stores are real memory stores, and the load is a MEM load; reload would then see the load as a "reload" of the frame slot... hmm, but GCC's cse in the RTL phase merges the store/load pairs (cse_basic_block → the load of a pseudo-equivalent...). Hmm, in GCC 2.x, locals are memory, and there's no "promotion to register" pass except... hmm! But we observed no stack traffic in the compiled code, so promotion happened. Where?

GCC 2.7.2: `expand_start_function` allocates the frame; local vars are MEMs. The RTL passes: cse, jump, loop, flow, combine, regmove, reload, expand, ... The "reload" pass is what turns MEM references into registers. For a local variable that's only stored and loaded in a simple pattern, GCC 2.x's cse pass (which works on RTL, including the frame slot MEMs) can eliminate the redundant loads/stores: cse_basic_block has a "case SET" / "case MEM" handling that removes a load that follows a store to the same address (that's the "cse" of memory). Yes, cse.c handles MEM: it tracks the last value stored to each memory location and removes redundant loads.

Then the load becomes a pseudo with a constant value → then reload's reg_equiv → rematerialize.

So with an extra dead store, the load pseudo's quantity becomes 2 → not rematerializable → kept in a register.

Let me test empirically! Let me write w2 and w3.

Actually, note: the compiler in the pipeline is `cc1 -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker`. GCC 2.7.2.

Let's do it.

Also for the second launder in C2D0 (`it = (s32)D_801202A0;`): in the target, that one is materialized plainly (lui v1; addiu v1) because it's used as a MEM base (lhu v0,0(v1)) — so no launder needed there anyway (my candidate w1 already had it correct). Only the FIRST launder matters.

Let me create the candidates and score.
