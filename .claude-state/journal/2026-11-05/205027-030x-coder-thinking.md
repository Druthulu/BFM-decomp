---
ts: 2026-11-06T03:50:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5zezF6yPWf8dfbzMuLSm
---
Same score 4, same diff. So the scheduler sinks the zero store regardless. The zero store ends up after the D0 load (position 54) in mine; target has it at 49.

Let me look at mine's stream for c2. Probably identical to c1.

How to force the zero store earlier? The zero store is independent; sched sinks it because... hmm, why would it sink? Let me think: sched1 schedules with priority; stores have low priority. The zero store gets deferred until... In target it's placed right after the C4 load. What real C makes that happen?

Perhaps the original had the zero store depend on the loaded value: `D_801269EA = 0;` might actually have been part of a compound assignment like `D_801269E8 = t, D_801269EA = 0;`? No.

Maybe the original used a temp for zero: `s16 z = 0; D_801269EA = z;`? A pseudo holding 0 could be scheduled.

Or perhaps the C was:
```
t = D_801864C4[idx];
D_801269E8 = t;
D_801269EA = 0;
```
and the target's order (EA before E8) is due to scheduler moving the zero store up. But mine (c1) had exactly that source and produced E8 then EA. Hmm.

Alternatively maybe the store order in target arises because EA and E8 are actually adjacent halfwords and the compiler combined them into one? No, target has two sh.

What if the zero is stored through a variable that also feeds the E8 store's address computation? No.

Wait — maybe the key is `D_801269EA = 0;` came BEFORE `t = D_801864C4[idx];` in the original and the scheduler hoisted the load above the store but kept the store before E8. c2 tested that and got the same output: the store still sank to 54. Let me actually check c2's stream — maybe identical. The diff is identical, so yes.

Hmm. Let's think about what determines this: the store `sh zero,EA` at 2a4c-2a50 in target. Mine has `lui at; sh zero,EA` at 54-56 i.e. after D0 load. The scheduler placed it there because of the `at` register: all these lui/addu use `at`. The zero store is `lui at; sh zero`. Since `at` is a scratch register used by every address computation, the scheduler may not move a lui at across other at uses? Actually each has its own at def; dependencies via at are WAR/WAW, which the scheduler respects! So the zero store's `lui at` can't be reordered across other `lui at` uses. Hmm, that constrains.

Target: lw C4 (lui at; addu at; lw) then lui at; sh zero (EA) then lui at; sh v0 (E8). Mine: lw C4; lui at; sh v0 (E8); lui at; addu; lw D0; lui at; sh zero (EA); ...

So in target the EA store came before E8. In mine E8 before EA.

To force EA before E8: make E8's value depend on EA's store? That's the dependency we need. Could we write:
```
D_801269EA = 0;
D_801269E8 = t + D_801269EA;
```
That would add a load of EA. No.

Alternative: make the EA store depend on t's load, so it stays right after the load, and make E8's store depend on EA's store? The latter impossible without reading.

Hmm, what about using a pointer to write both halfwords in one go? Like `*(s32*)(&D_801269EA) = ...`? Target has two separate sh (EA and E8 are 2 bytes apart: EA, then E8? 0xEA to 0xE8 is -2). Actually EA and E8 differ by 2; E8 is before EA. Two halves.

What if the source stored a struct: `*(s16*)(...)=0; *(s16*)(...)=t;` no.

Think differently: maybe the target's `sh zero,EA` is not `D_801269EA = 0` but the tail of a combined store: e.g., writing `D_801269E8 = t` where the struct copy... no.

Let me reconsider: perhaps the original source order was:
```
D_8012697C = D_801864AC[idx];
D_80126980[0] = D_801864B8[idx];
D_801269EA = 0;
D_801269E8 = D_801864C4[idx];
D_801A1274 = D_801864D0[idx];
```
and the sched1 of the real original gave the target order because of different register allocation. The difference between our build and the target: in our build with t reuse we forced the loads to serialize, but the zero store's placement differs.

What if we DON'T reuse t for the C4 load but instead write directly `D_801269E8 = D_801864C4[idx];`? Then the load is independent and sched could hoist it above the zero store; then the zero store would be... Let's test variants:

c3: no temp for C4: `D_801269EA = 0; D_801269E8 = D_801864C4[idx];` (keep t for AC/B8/D0).
Actually baseline nopin had `t = D_801864C4[idx]; D_801269EA=0; D_801269E8=t;` and produced EA after E8.

Try: `D_801269E8 = D_801864C4[idx];` after `D_801269EA = 0;`. Let me test a few.

Alternatively use a separate temp for the C4 value:
```
s32 u;
u = D_801864C4[idx];
D_801269EA = 0;
D_801269E8 = u;
```
Same as t but different pseudo — no anti-dep on t, so the load could hoist. Hmm.

Let me brute force a handful with sc.sh:
- c3: zero store before direct E8 assignment.
- c4: zero store after direct E8 assignment.
- c5: `t = D_801864C4[idx]; D_801269E8 = t; D_801269EA = 0;` (already c1).
- c6: separate temp u.

Let me create these and score in one sc.sh call.

Actually, maybe better: look at the original target more carefully. Maybe the zero store is scheduled between because sched1 in the original had the C4 load born from `D_801269E8 = D_801864C4[idx];` with the store order EA=0 then E8=load. Let me just test.

Let me generate variants via sed/awk. I'll write a small gen script under the item dir? Constraint says scripts under shard dir. Fine, use awk inline (allowed, it's a command not python -c). Let me produce c3..c6.

Base c1 lines:
40: t = D_801864B8[idx];
41: (D_80126980[0]) = t;
42: t = D_801864C4[idx];
43: D_801269EA = 0;
44: D_801269E8 = t;
45: t = D_801864D0[idx];

c3: replace 42-44 with:
    D_801269EA = 0;
    D_801269E8 = D_801864C4[idx];
c4: 
    D_801269E8 = D_801864C4[idx];
    D_801269EA = 0;
c5: separate temp u:
    u = D_801864C4[idx];
    D_801269EA = 0;
    D_801269E8 = u;
Need to add `s32 u;` decl. I can add it after `s32 t;` line 25.

Let me write these with awk. Simpler: use a gen.sh script under item dir that uses sed on c1.c. Let me just do it with awk one-liners per variant.
