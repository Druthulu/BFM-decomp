---
ts: 2026-11-06T09:18:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4exyZc3Kmsxjg4fmykLb
---
Item 4: only differences: `e` = base+4. Target computes `addiu s0,s1,4` once (s0 = base+4, the element pointer) and uses offsets relative to e; mine computes `move s0,s1` (s0 = base) and uses offsets +4. So target's `e` pointer is the one in s0, mine keeps `base` in s0 and uses e = base+4 folded.

This is a real-C move: make `e` the primary pointer. E.g.:

```c
base = D_801DA130;
for (i = 0; i < 0x40; i++) {
    e = (Sub_80180A54 *)(base + 4);
    ...
    base += 0x18;
}
```
The target has s0 = e = base+4 (addiu s0,s1,4) and uses e->flag at 2(s0)? Wait target `lh v0,2(s0)` and mine `lh v0,6(s0)`. e->flag: e = base+4, flag at offset 2 → base+6. Target: s0 = base+4 (e), lh 2(s0) = base+6. Yes. Mine: s0 = base, lh 6(s0).

So target's loop keeps `e` in s0 and base in s1. Also `func_80016714(base, 0x18)` uses s1 (base). So target: s1 = base, s0 = e = base+4. Mine: s1 = base too? mine s0=base, and base in s1 as well? `move s0,s1` means s0=base (s1=base). Then `move v0,s0` at end = v0=base. Target `move v0,s1` = v0=base.

So the only change: target computes e = base+4 into s0 at loop top (addiu), mine does move s0,s1 then uses base-relative offsets. Why? Because in my code `e = (Sub_80180A54 *)(base + 4);` — the compiler folded e's offset into the accesses (e->flag → base+6). Target kept e as a separate pointer. The difference: target's `e` is a pointer variable that survives (maybe because of `func_80016714(base, 0x18)` and the loop). Hmm, both are the same source. The pin affects allocation: with the pin, v0=$2; without, v0 is a normal pseudo whose allocation changes... but the e pointer folding is a *combine* decision, not alloc. Hmm, actually mine shows `move s0,s1` then uses offsets +6 etc. — so the compiler DID keep a separate pseudo s0 for e but then realized e == base (coalesced them, since e = base+4 then folded offsets). Wait no: `move s0,s1` means s0=base; if e were a separate pseudo = base+4, it would be addiu. So combine/cse folded e back into base+4 and used offsets.

Target: addiu s0,s1,4 = e kept as base+4 pointer.

This is a "cse-const-addr" / pointer-arithmetic canonicalization difference driven by... hmm, what makes the target keep e? Possibly because `e` is used many times (7 field accesses) and cse decides to keep the base+4 address in a register (a cse-reg). In mine, cse didn't. The pin changes reg allocation; cse's decision to register-ize a constant address depends on register pressure (cse's `cse_reg` heuristics: it won't register an address if regs are tight). With the pin occupying $2, more pressure → register the address; without, less pressure → fold.

Hmm, that's a real "lever-free" difference. A real-C move to force e to be a real pointer: use e in a way that prevents folding, e.g. make e a different type or use `e` as the base for the call: `func_80016714((u8*)e - 4, 0x18)`. That's a real C change (pointer arithmetic), though maybe it'd fold back.

Alternatively restructure the loop to iterate with e:
```c
base = D_801DA130;
e = (Sub_80180A54 *)(base + 4);
for (i = 0; i < 0x40; i++) {
    if (e->flag == 0) { ... func_80016714(base,0x18) ... }
    base += 0x18;
    e = (Sub_80180A54 *)(base + 4);
}
```
Hmm, that changes loop codegen.

Or simply: declare `u8 *eb = base + 4;` and use `e = (Sub_80180A54 *)eb;`?

Let me try the simplest: reorder so `e` is assigned before `i` loop... Actually maybe the issue is that `e` is a local assigned inside the loop and cse folds `base+4` into the accesses because e is a single-use-per-iteration pseudo. If we make `e` also used as an argument: `func_80016714((u8 *)e - 4, 0x18);` then e must be computed (addiu). Let's try that: replace `func_80016714(base, 0x18);` with `func_80016714((u8 *)e - 4, 0x18);`. That's real C and should force e = base+4 in a reg. But will the target's codegen match? Target at the call: let me look at target's call region.

Let me dump target around the call.
