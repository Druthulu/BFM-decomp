---
ts: 2026-11-06T15:39:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pDrjq39HrfgDWcPDonnn
---
All variants yield the sum in s0. This strongly suggests a wall: cse constant-address folding.

But wait — what if the original source used the *symbol through a pointer parameter*, e.g., the address is passed into the function? No, signature fixed.

Alternatively, what if the target's base is a *different expression*: maybe the original had a global `u8 *D_800AF630_p = &D_800AF630;`? Then target would load it (lw), not lui/addiu.

Or the original had `extern u8 D_800AF630[];` and used `D_800AF630 + 0x18` where D_800AF630 decays to a pointer. That's what we have.

Hmm, what about `(u8 *)&D_800AF630` where the *cast* goes through a struct? Let me test one more: a named derived pointer `u8 *mb = (u8 *)&D_800AF630;` then `mb = mb - 0x18;`?? No.

Let me reconsider the actual instruction counts: target 397, c1 397, score 6 with 6 replaced insns. So the only residual is these adds. The wall tag cse-const-addr exists exactly for this. Before declaring, I need ≥20 min and ≥30 scored tries on this item. I have ~15 tries so far (6+4+3+2 = 15). Let me continue with more ideas and reach 30, spending ~10 more minutes.

More ideas:
1. Use `(u8 *)((s32)&D_800AF630 + 0x18)` and `(u8 *)((u32)&D_800AF630 + 0x18)` for the two calls (different RTL types but fold same).
2. Use a `union` to get the address: `union { u8 *p; } u; u.p = &D_800AF630;` — a union member access is a memory op? GCC might keep in register.
3. Use a `struct` field pointer: `struct S { u8 pad[0x18]; }; func_8004914C(&((struct S *)&D_800AF630)->pad[0]);` same.
4. Compute the second call's arg from mb2 = mb + 0x18 where mb is a *parameter-derived* pointer? no.
5. Use a `long *` cast with an element index: `(long *)((u8*)&D_800AF630) + 6` → +24 constant.
6. Use `&D_800AF630[0x18]` where D_800AF630 declared as `u8[]` (p tested with &mb[0x18], not direct array). Try direct `func_8004914C(&D_800AF630[0x18])`.
7. Try `func_8004914C((u8 *)&D_800AF630 + sizeof(long) * 6)`? folds.
8. Try making mb `u32` and `(u8 *)(mb + 0x18)`.
9. Try a struct-typed pointer variable: `struct S18 *mp; mp = (struct S18*)&D_800AF630; func_8004914C(&mp->x);` where x at 0x18. Same constant.
10. Try `mb = (u8 *)(&D_800AF630);` with the address in a *static* local? static local initialization... no.

Hmm.

Actually — maybe a completely different angle: what if the launder isn't needed if we restructure the calls to use a *stack copy* of the pointer that is volatile-ish? no.

Let me look at how the *original binary* likely did this. This function is from a Square game; the source probably was something like:

```
SetRotMatrix(&D_800AF630);  // ?
```

Wait, func_8004914C and func_800491AC. Let me check the TU comments near 5995-6025 for hints about the intended original source.
