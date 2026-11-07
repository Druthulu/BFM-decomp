---
ts: 2026-11-07T00:59:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZML8b8JJbcEphdAh4Vdn
---
Interesting: in w02, p=q got eliminated (p is dead after p=q then p=0 → both stores removed) and the tail uses a3 (=q? no). Wait mine[83]: `lhu v0,-32(a3)` — a3 is the q pointer. So p=q and p=0 both vanished; the tail uses q directly. So the dead reset caused the *copy* p=q to be removed entirely, not the p=0. Because p=0 after p=q: dead store elimination removed p=0 AND then p=q is also dead (p unused) → removed. So the tail uses q. That's actually what we want structurally? Target: `move s3,a0` (p=q) and `move v0,s3` (r=p). Mine has neither.

Hmm, so the dead reset approach removed the p=q assignment. Bad.

But interesting: w02's mine is 97 ins and the regs differ more.

OK. So the two artifacts (p=q and r=p) are hard to materialize lever-free. In the target they exist because pins/launders force them.

Now, what would a MATCH even look like? The target has:
- move s3,a0 (p=q)
- move v0,s3 (r=p)

Both are copies that cse/flow remove in plain C. So lever-free MATCH requires forcing both copies to survive AND the register permutation. This is essentially impossible without a lever.

Conclusion: WALL. Tag: "callee-saved-order" (existing tag from the T10 notes) or check walls.txt. Let me read walls.txt for an appropriate tag.

But I still need ≥30 tries and ≥20 min. I have 23 scored candidates (base w0 + 22). Plus the calibration (not a try). Let me add ~10 more variants quickly (batch 3) to reach 30+, spanning C0505 moves: widths, loop shape, decl order, statement order, &&/|| folds, init at decl.

Batch 3 candidates:
- b/w: `i` as u32; `i` as int; do-while loop; while loop; reordered stores; `cs` temp; `flag` set via both branches; `t` via `(n << 3) + 8`; `col` as u16? no.
- Also: use `u32 *q = p + 5;` (no p += 5) — w20 scored 72.
- `p[2]` using `cs` temp.
- `(b + 0xf)` vs `(b + 15)`.

Let me add a batch of 12 via a second generator that does string replacements on w00.

Actually, simpler: write a small script that reads w00.c and applies textual substitutions for each variant. Let me write gen2.py.

Variants (from w00 text):
1. `s16 i;` → `u32 i;`
2. `s16 i;` → `int i;`
3. `for (i = 0; i < 4; i++)` → `for (i = 0; i != 4; i++)`
4. for → do-while:
```
  i = 0;
  do
  {
    ...
    i++;
  } while (i < 4);
```
Need // !FAKE: do-while comment.
5. while loop: `i = 0; while (i < 4) { ... i++; }`
6. store order: p[1] before p[2].
7. cs temp: `u32 cs; ... cs = c << 16;` and use cs.
8. flag: `flag = 0;` in the if and `flag = 0x1000000;` before? The target has lui t0,0x100 then move t0,zero (flag=0) in the branch. Actually target: `lui t0,0x100` then `move a3,zero`... wait `move a3,zero` is i=0; `move t0,zero` is flag=0. Yes.
9. t: `t = ((n << 3) + 8) | 0x4000;`
10. `(b + 0xf)` → `(b + 15)`
11. `n * 8 + 8` → `(n * 8) + 8` (same)
12. init at decl: `u32 flag = 0x1000000;` (remove the assignment).

Let me write gen2.py with these substitutions.

Also, I realize I should double-check the launder-kinds: the win.c must have no asm at all. All candidates are asm-free. Good.

Let me write gen2.py.
