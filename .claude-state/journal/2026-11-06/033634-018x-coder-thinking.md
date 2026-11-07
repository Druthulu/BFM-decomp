---
ts: 2026-11-06T10:36:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NeYSjhRxTqz52AZSvEn9
---
Interesting. Removing the pins causes:
1. `s1` is now used as the copy of a0 instead of `s0` — because the target's pinned s0 ($16) forces s0. The target has `move s0,a0` and sw s0,16(sp), and only 24-byte frame (s0 only, no s1). Ours uses s1 and s0 (two callee-saved) → frame 32.
2. The t = unkC4 load into v1 instead of v0: target loads `lw v0,196(s0)` then `lui v1/addiu v1/sw v1,88(s0)` then `ori v0,v0,0x2; sw v0,196(s0)`. Ours loads v1 then uses v0 for the address (because v0 is used by the pin... hmm).

Wait in target: the load result t goes to v0, and the &D_801907C4 address constant goes to v1. In ours: t→v1, address→v0. That's a local-alloc priority/order issue.

So two problems: (a) the a0 copy register (s0 vs s1) due to pin; (b) v0/v1 swap for t vs address.

For (a): why does a plain `void *s0 = a0;` get s1? Because global-alloc assigns based on priority. Target: s0=$16 for the pointer. Hmm.

Wait, in the target, the frame is 0x18 and only s0 is saved. Ours has s1 and s0 saved (frame 0x20). So lever-free makes two callee-saved pseudos where target has one. That means the `s0 = a0` copy is the pinned pseudo $16 in target; lever-free, the copy becomes a separate pseudo that gets $s1, and then the dereference base is... Actually mine: `move s1,a0` (s1 = copy), `sw s0,16(sp)` and `move s0,s1` — so there's a second copy s0 = s1. That's because `((Unkstruct*)s0)` where s0 is a local; the compiler copies a0 into s1 (the local), then... `move s0,s1`? Hmm why two? Perhaps because the function uses s0 elsewhere via the struct pointers? Wait, the `((Unkstruct_800B5CB8 *)s0)` — and later `*(s32*)((s32)s0+0x20)`.

Actually maybe the extra `move s0,s1` is the copy for the `func_8012CAE4(s0)` call in the if branch... no.

Hmm, the mine order:
```
0 addiu sp,-32
1 sw s1,20(sp)
2 move s1,a0
3 sw ra,24(sp)
5 sw s0,16(sp)
6 move s0,s1
```
So there are two pseudos: one (s1) = a0, another (s0) = s1 copy. Why would C create two? Because `s0` declared as `register void *s0 __asm__("$16")` pinned — removed now. In orig, `s0 = a0` with s0 pinned to $16 → `move s0,a0` only. Without the pin, gcc's expand of `s0 = a0;` then uses of s0... only one pseudo. Unless... hmm, the `register` qualifier removal changed something else. Let me check: maybe `void *s0;` declared at top and assigned `s0 = a0;` — that's one pseudo. The second move suggests a copy into the parameter's pseudo? Hmm, `move s1,a0` is the store of a0 into local s0-pseudo; `move s0,s1`? That would be a copy of that pseudo into another pseudo used as a base.

Ah — maybe because the local `s0` is assigned to a0 and then the local variable is used, gcc creates the pseudo for the local, but the incoming argument a0 pseudo (REG 4) needs to be moved to the local's hard reg. That's one move. Then the local's pseudo is also used as a base in address computations requiring a hard register... no, same pseudo.

Wait, maybe the two moves come from `v0 = ((s32(*)(void))func_8012C1B8)();` ... no.

Hmm, actually the mine instructions 2 `move s1,a0` and 6 `move s0,s1`. Maybe s1 is the local variable `s0` and s0 is... the pseudo that got allocated to $16 anyway by global? Then `move s0,s1` is a leftover copy inserted by reload because some use required a hard reg $16? Not likely.

Hold on — maybe the struct type's member access `((Unkstruct_800B5CB8 *)s0)->unk20 = v0;` uses the local pseudo, and the call `func_8012CAE4(s0)` too. But `func_8012A828((s32)s0, ...)`. Hmm.

Let me instead test simply: does declaring `void *s0;` as a parameter (i.e., renaming) change? Or maybe use `register void *s0;` without asm? That's not a pin per se (no register-asm), but the constraint says no `register` vars at all.

Alternative: the second copy could be because `s0` is a "used in both branches" pseudo and global-alloc splits... no.

Let me look at the orig's compiled output to compare. Actually let me test: with pins removed but barrier kept = 22. Let me also test barrier removed only (pins kept) to see.

Also let me check: maybe the a0 copy issue is because in orig the pin forced s0 for the *variable*, and the extra move in nopin is from the pinned removal making the parameter's pseudo and local's pseudo distinct: in orig `register void *s0 __asm__("$16")` means the local is hard reg 16, and `s0 = a0` is a move from a0 to $16. In nopin, local is a pseudo; the parameter a0 pseudo dies after the copy, so it should coalesce.

Actually wait — maybe gcc copies the parameter to the local for the branch structure: `if (v0 == 0) func_8012CAE4(s0);` — the s0 pseudo is live across the call, so it must be callee-saved (s1). And separately, maybe... no second pseudo.

Let me just try variations empirically. First, a variant where the local is initialized at declaration: `void *s0 = a0;`. Also one where uses are direct on `a0`? Can't — call clobbers.

Hmm, what about the second `move s0,s1` — it appears AFTER `sw s0,16(sp)` (save of s0) at position 6, i.e., in the prologue. So gcc saves both s0 and s1 and then copies s1→s0 in the prologue. That's a global-alloc artifact: two pseudos that must be in different regs? Or... Actually if both pseudos were the same value, global-alloc could have coalesced. The reason: one pseudo is the local `s0`, the other might be the result of `((Unkstruct_800B5CB8 *)*(s32 *)((s32)s0 + 0x20))`? No, that's later.

Wait, maybe it's the *incoming argument* a0 which is live until the end? `move s1,a0` puts a0 into s1; then `move s0,s1` — could be the copy for the local variable used as the base in `sw v0,32(s1)` at 8: `sw v0,32(s1)`. Hmm at index 8 mine has `sw v0,32(s1)` — using s1. So s1 is used for the store. So s1 = the local? Then s0 is used for `lw v1,196(s0)` etc. Both used.

OK so there genuinely are two pseudos holding the pointer. Why? Because the local `s0` is copied... Let me look at the C again: `s0 = a0;` then uses. One pseudo. Unless the compiler treats the `if (v0 == 0)` branch as... hmm.

OH WAIT. Look at orig: `register void *s0 __asm__("$16")`. The `register ... __asm__` is a local register variable. In nopin I replaced with `void *s0;`. But maybe the orig also relied on the fact that... hmm.

Let me test a minimal hypothesis by scoring a variant where the local is a plain variable named differently and the parameter used directly: keep `void *s0 = a0;` at declaration.

Let me create several variants and score with sc.sh (one line each).

Variants:
- v1: `void *s0 = a0;` at declaration (remove separate assignment), pins removed, barrier kept.
- v2: no local at all — replace s0 with a0 everywhere? a0 is a parameter, but after the call func_8012C1B8, a0 is dead? Actually a0 is used after the call, so it must be saved. In target, s0 holds it. Hmm.
- v3: keep barrier.

Also the v0/v1 swap: target wants t load into v0 and address into v1. That's local-alloc. The barrier's removal changes ordering (the memory barrier prevented reordering: with barrier, `t = unkC4` load happens before `unk58 = &D_801907C4` store). In target, `lw v0,196(s0)` comes first, then lui/addiu v1 (address), sw v1,88(s0), then ori v0,v0,2, sw v0,196(s0). So the load and the address computation are interleaved: load first, then address. Without the barrier, the compiler may sink the load after the address computation (which is fine — target has load first!). Hmm mine has `lw v1,196(s0)` then `lui v0/addiu v0/sw v0,88` then `ori v1,v1,2; sw v1,196`. Same order as target, just v0/v1 swapped! And mine 66 ins vs 63: the extra is the `li v1,16384` placement: target has `li v1,16384` at 35 then presumably `sw v1,0x18(...)` twice and `sh`; mine has `ori v1,v1,2; sw v1,196` then `li v1,16384` — i.e., the address constant load (lui v0, addiu v0) is at 31-32 and the 16384 load at 39. Wait target: `lw v0,196`, `lui v1,0`, `addiu v1,v1,0`, `sw v1,88(s0)`, `ori v0,v0,2`, `sw v0,196`, `li v1,16384` at 35.

Mine: `lw v1,196`, `lui v0`, `addiu v0`, `sw v0,88`, [missing ori v0,2; sw v0,196], then delete block 37-40 mine has `ori v1,v1,2; sw v1,196; li v1,16384`. So basically identical modulo v0/v1 swap, plus an extra `sw v0,196(s0)`? No: mine 37-40 has ori v1,v1,2; sw v1,196; li v1,16384 (3 insns), target 34-35 has ori v0,0x2; sw v0,196; li v1,16384 (3). So the sequence is same. The diff is just register naming v0↔v1. That's 6 insns swapped = 12 score, plus the prologue 10 = 22.

So the v0/v1 issue: in target, the loaded t is in v0 and the address constant in v1. In mine, t in v1, address in v0. This is local-alloc. The pin `register s32 t __asm__("$2")` forced v0 for t. So we need a real-C way to get t into v0.

Hmm. Local-alloc gives v0 to the pseudo with higher qty priority (more refs/live length). The address constant pseudo (from `&D_801907C4`) is used once. t is used twice (load + ori). Hmm, but t is defined once and used once in `t | 0x2`? Actually `t` is used once in `t | 0x2`. And the address `&D_801907C4` used once in a store.

Wait, maybe there's a `t | 0x2` in-place: `unkC4 |= 0x2` would be different. Target does `lw v0,196(s0); ...; ori v0,v0,2; sw v0,196(s0)` — that's `|= 0x2` in place, with the load result kept in v0. The C currently uses t to avoid... Let's think: if we write `((Unkstruct*)s0)->unkC4 |= 0x2;` directly, then the load-use-store is one pseudo and the compiler may schedule it around the unk58 store differently. The orig used `t` explicitly. Perhaps the original author needed t to prevent the load from being sunk? Let me test.

Actually since we must find a lever-free body, let's explore. Key: what does the barrier do? It prevented the load `t = unkC4` from moving past `unk58 = &D_801907C4` store (aliasing). Without the barrier, in mine the load is still before the store (lw at 30, sw at 33). Good — so ordering is fine. The barrier only mattered for the v0/v1 allocation? No, barriers don't affect allocation.

Wait, the score with pins removed but barrier kept was 22. Let me also score barrier removed, pins kept. That tells which diff is due to which lever.

Let me create nobar.c and win0.c.

win0: pins removed + barrier removed. Score it.

Let me do these with python/sed and sc.sh. Note sc.sh takes itemdir files.
