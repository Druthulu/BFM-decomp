---
ts: 2026-10-22T20:38:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rX3fu85Pq8UrzOQwveVB
---
Score 4, 52 ins. The diff:
- mine: `lui a1,0x0; addiu a1,a1,25996` (= 0x658C) then `nop` at 24; target: `lui v1,0x0; addiu v1,v1,0` (D_80120194 low = 0? hmm) then `addiu a1,v1,25996`.
So the target computes `it` in v1 and `p = it + 0x658C` in a1. Mine computes `p` directly in a1 (it's dead in mine). So in mine, `it` is dead after computing p — because cse folded `it + 0x658C` into `lui/addiu a1, 0x658C`... no wait, mine: `lui a1,0x0; addiu a1,a1,25996` — that's the full address D_80120194+0x658C in a1, meaning gcc folded the addition (it is a constant address!) into one lui/addiu pair with the symbol. The target keeps `it = D_80120194` in v1 and then `addiu a1,v1,0x658C` — two-step, because it needs `it` later (for the `copy: p = it;` path).

Wait, in mine, is `it` used later? The `copy:` label uses `it`. But that's in the *other* branch (else) — no, `copy:` is inside the else branch. Let me look: the else branch has:
```
it = (s32)D_80120194;
p = it + 0x658C;
goto test;
copy:
p = it;
goto found;
test:
it = (s32)D_801202A0;   // it reassigned!
...
```
So `it` is reassigned at `test:` before `copy:` is reached. Therefore the first `it` value is dead at `copy:` — so gcc folded `it + 0x658C` into a constant. But the target keeps `it` in v1 and adds! Why? Because in the target's source, `it` is *not* dead — or the target's `it` is used before being reassigned.

Hmm, the target: `lui v1; addiu v1,v1,0` (D_80120194 = 0x80120194? the low 16 bits = 0x0194... the addiu shows 0 in the diff because of relocation). Then `addiu a1,v1,25996` (0x658C). So target computes it=v1, p=a1=it+0x658C.

If `it` were dead, gcc would fold. So in the target's source, `it` IS live across to the `copy:` block? Let's see the target's flow: `test: it = D_801202A0; if (it == p) goto zero; body: if (*(u16*)it == 0) goto copy; it += 0x10C; ...` — `it` is reassigned at test. So the first it is dead.

Unless the target's source doesn't reassign `it` at test but uses a *different* variable, e.g. `it` and a separate loop pointer. Then `copy: p = it;` would use the original it.

Hmm, but the loop body uses `it` (the second value). If the source used two variables, say `it` (base) and `q` (scan pointer), then:
```
it = D_80120194;
p = it + 0x658C;
goto test;
copy: p = it; goto found;
test: q = D_801202A0; if (q == p) goto zero;
body: if (*(u16*)q == 0) goto copy; q += 0x10C; if (q != p) goto body;
```
Then `it` stays live (used at copy), so gcc keeps it in a register (v1) and computes p = it + 0x658C. That matches the target! And the register allocation a1->v1 x4 suggests the two-variable split.

Wait, but the target's `copy: p = it` — hmm, with it live, the compiler must keep it. Let me check the target's disassembly to confirm the loop uses v1 and the copy path.

Let me dump the target for func_8012C750.
