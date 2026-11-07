---
ts: 2026-11-06T13:38:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UZDYJEtJRQJQLKOHNhtB
---
Source:
```
aa = t * m;
bb = aa >> 12;
cc = bb + 8;
[barrier]
d = cc * (D_80126950 + 500);
d = d / (ret * 4);
```

Target: mult v0,s2 (aa = t*m); mflo t0; sra v0,t0,0xc (bb); addiu a2,v0,8 (cc); lui v0; lw v0; nop; addiu v0,500; mult a2,v0; mflo v0 (d); sll a2,s0,2 (ret*4); div...

Mine: mult v0,s2; lui v1; lw v1; nop; addiu v1,500; mflo t0; sra; addiu a2; mult a2,v1; ...

So sched1 hoisted the load chain above mflo (filling the mult latency). Target keeps it after.

The barrier sits exactly between cc and the d statement. So the barrier prevents the load from moving above the cc computation.

Real-C: make the load depend on cc. Since it's a global load, we could use cc in the address in a way that folds away... e.g. `D_80126950` via an array index `((s32*)&D_80126950)[cc & 0]`? folds.

What about using `cc` in a comparison that guards the load but always true... adds branch.

Hmm, what about reordering the source so that the load statement comes after something that creates a dependence: e.g., `d = cc * (D_80126950 + 500);` where we first compute `cc = bb + 8;` then `d = ...`. Already.

What if the load is written as `d = cc * (*(s32 *)((u8 *)&D_80126950 + (cc - cc)) + 500);`? gcc folds cc-cc to 0? Probably.

What if we use a struct member access on D_80126950 that makes it a nonscalar MEM? Then sched's dependency might differ, but the position...

OK, what about the C0535 do-while trick: wrap `cc = bb + 8;` in a do-while so that cse1's EBB splits? That wouldn't affect sched1.

Hmm, but wait: maybe the relevant pass is not sched1 but the *first* cse/combine moving the load? No, the load is a MEM; only scheduling moves it.

Let me test whether sched1 is responsible via a dump. The cc1 dump would tell. But time.

Alternative idea: what if we make the load's address computation use a register that's produced late — e.g., use the `gp` (global pointer) base? D_80126950 is accessed via lui/lw. 

What if we access it via a *different* symbol that is already in a register? No.

Let me think about the target: `lui v0; lw v0; nop; addiu v0,500`. The `nop` after lw is the load delay. In mine the same but placed earlier with v1.

Sched1's behavior: it fills the mult latency with the independent load chain. The target doesn't. The barrier prevented it.

Real-C constructs that make the load non-hoistable across the mult:
- A memory dependence: if the mult's operands came from memory... no.
- Volatile: a volatile load can't be moved across other volatile ops, but can be hoisted past the mult.

Hmm, actually! sched1 might refuse to move a load above a *store* to a potentially-aliasing address. There's no store here.

What about making the load and the mflo related? mflo t0 reads the HI register. If the load were in the HI/Lo... no.

OK, let me consider that the difference might be sched2 (post-reload), not sched1. sched2 runs after register allocation. The barrier asm at post-reload: `__asm__ __volatile__("")` — after reload, the asm becomes... it's still an asm insn, and sched2 also treats it as a barrier. So both.

At sched2, the registers are already allocated (v1 vs v0 in mine vs target — but wait, register allocation happens before sched2, so the v0/v1 difference comes from sched1/alloc, not sched2).

Hmm, in mine the load used v1; in target v0. That's a register allocation difference caused by the different scheduling/positions? No — local-alloc/global-alloc happen after sched1 and before sched2. The RTL at alloc time has pseudos; the schedule determines live ranges, which affect allocation. So the whole difference could originate at sched1.

Let me do the dump to confirm and see what's around. Actually, let me first try the cheap source variants (10 min max), then dump if needed.

Variants:
1. do-while around `cc = bb + 8;`
2. do-while around `d = cc * (...)` line
3. temp for the load: `{ s32 g = D_80126950; d = cc * (g + 500); }`
4. pointer: `{ s32 *g = &D_80126950; d = cc * (*g + 500); }`
5. reorder: `d = (D_80126950 + 500) * cc;`
6. `d = cc * 500 + cc * D_80126950;` (no)
7. do-while around both cc and d
8. `cc = bb + 8; d = cc * (D_80126950 + 500);` with cc computed inline: `d = (bb + 8) * (D_80126950 + 500);` — hmm, this removes cc's intermediate? cc is used later? Let me check: cc is only used here (cc = bb+8). Pinned $6. Actually if cc is only used here, we could inline it: `d = (bb + 8) * (D_80126950 + 500);` — then the addiu a2 might be born later (at the mult), which is the same as target? Target has addiu a2,v0,8 then the load then mult a2,v0. Inline would give the same order probably. Worth a try.

Let me write these.
