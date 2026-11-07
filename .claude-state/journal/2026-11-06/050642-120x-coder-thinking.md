---
ts: 2026-11-06T12:06:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MTLNlwzKNqgO3OTqVvg4
---
The volatile load forces the address into a register (v0/v1) instead of `at`, adding 1 insn (addiu v0,v0,0).

Hmm. Both volatile variants cost 1 insn.

What if the volatile load's address is a single symbol + index (no addiu)? The extra insn comes from `lui v0; addiu v0,0` (the symbol address) vs `lui at,0`. A volatile MEM needs a real register for the address, so the `at` trick isn't used.

Idea: use a *single* volatile load of `D_8018DB2C[idx]` but... hmm.

OK, let me consider the launder side once more. In w1 (base = assignment) we got +3 (rematerialization). What if I combine: keep the launder's effect with a dead reset:
```
base = (u8 *)&D_8011F7F0;
arr = base - 0x48;
```
Hmm.

What if I write `base = (u8 *)&D_8011F7F0; arr = base - 0x48;` and then use `arr` for the later accesses instead of `base`? The later uses are `*(u16*)(base - 0x34)` = `*(u16*)(arr + 0x14)`. That's real C (using a different but equivalent expression). Would the compiler keep arr in a register? arr is used for slot too. Hmm, arr = base-0x48; slot = param_1*4 + arr.

Let me try: replace `*(u16 *)(base - 0x34)` with `*(u16 *)(arr + 0x14)` and `*(u16 *)(base - 0x32)` with `*(u16 *)(arr + 0x16)`.

The target uses `lhu a3,-52(s2)` where s2 = base. If we use arr (s4), the offsets would be different registers. Hmm, might not match.

Let me just try it and a couple of others.

Actually, let me reconsider the whole item: maybe the launder can be replaced by making base a *parameter-derived* value. Hmm.

Time check: item 4 started at 05:02. Let me check the time now. I've done ~10 tries on item 4.

Let me try a few more then decide. The best lever-free so far is w3 = 38.

Let me try:
- z1: use arr for the later base accesses.
- z2: `base = (u8*)&D_8011F7F0;` + `arr = base - 0x48;` + `base = arr + 0x48;` (re-tie via arr).
- z3: declare base as `u8 *volatile`? no.

And barrier:
- z4: `D_8011F83A = idx;` → `D_8011F83A = (u8)idx;` (cast, no change).
- z5: move the store earlier/later in C.

Let me test z1, z2.
