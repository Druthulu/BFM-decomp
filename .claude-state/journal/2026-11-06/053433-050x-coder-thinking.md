---
ts: 2026-11-06T12:34:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xh2BmJ6D5jni22cs88xo
---
There's `hard_reg_preferences[allocno]` — the allocator prefers registers that the pseudo already uses (from `REG_PREFERENCES`), i.e. `reg_preferred_class`. Also `preferences` come from local-alloc (`local_reg_n_refs`)? Actually `hard_reg_preferences` is set in global.c from `reg_pref` / `PREFERRED_RELOAD_CLASS`? Let me look at how hard_reg_preferences is computed. In gcc 2.7.2 global.c: `hard_reg_preferences` is filled from `regs_live_bits`? Hmm.

Actually — the key: in gcc 2.7.2, global-alloc gives preference to the register the pseudo got in local-alloc (`reg_renumber` from local-alloc / `local_reg_n_refs`), i.e. `best_reg` from preferences where `TEST_HARD_REG_BIT(hard_reg_preferences[allocno], i)` — hard_reg_preferences comes from `reg_pref[regno].prefclass` (REG_PREFERRED_CLASS / PREFERRED_RELOAD_CLASS).

For a pseudo used in a `return` (set v0 = pseudo) — hmm, does gcc mark v0 as preferred for pseudos that feed a return? There is `REG_PREFERRED_CLASS` computed in local-alloc... 

Let me take an empirical approach instead: try C variants and look at where ret lands.

Variant A: put the store and return in a different order:
```
STORE:
    ((Unkstruct_800B5CB8 *)param_1)->unk2 = ret;
    return ret;
```
already.

Variant B: `return ((Unkstruct_800B5CB8 *)param_1)->unk2;` after the store (reload). Extra insn.

Variant C: make the arms assign to the struct field directly AND ret:
```
((...)->unk2 = ret = 7; goto STORE;
```
Hmm.

Variant D: declare ret as the last variable / different decl order — affects nothing for allocno.

Variant E: eliminate `ret` entirely: arms do `((...)->unk2 = 7; return 7;` — duplicated store+return per arm, no.

Hmm wait. Actually, maybe I should reconsider: what if the target's C keeps `ret` in v0 because `ret` is *also* used as the return value of the early returns (the uninitialized use), and the pin... 

Let me test whether the early `return ret;` with ret getting a0 (c1: ret in s0) vs c2 (ret in a0): both without pin. Interesting: in c1 ret→s0; in c2 ret→a0. So removing the entry-live-range changed the class from saved to call-clobbered, but it picked a0 rather than v0.

So the question: how to make it pick v0 over a0. In find_reg, the order of trying registers is by `reg_alloc_order` (REG_ALLOC_ORDER) unless there are preferences. Let me look at the earlier part of find_reg (lines 904-1040) to see the ordering.
