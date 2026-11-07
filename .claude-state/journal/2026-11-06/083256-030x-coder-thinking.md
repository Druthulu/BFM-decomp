---
ts: 2026-11-06T15:32:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0PibMSh42HCG4tVZeWTZ
---
Item 2: func_8018AD9C, 3 identical launder sites. The launder breaks cse's unification of `mb + 0x18` across the call. Target keeps two separate adds (two `addiu a0, mb, 24` off a base). Without launder, cse unifies so only one add.

Approach: C0414 dead reset: `mb = 0;` after the first call? But the sequence is:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
<launder>
func_800491AC(mb + 0x18);
```
The launder's purpose: cse unifies the second `mb + 0x18` via the constant class of `(const (plus D_800AF630 24))`. If we add a dead reset of mb between the calls: `mb = 0;` then `func_800491AC(mb + 0x18)` would compute 0x18, wrong. Can't set mb to 0 before its use.

Alternative: use two different variables, e.g. `mb` for the first and `mb2` for the second:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
func_800491AC(mb2 + 0x18);  // mb2 = &D_800AF630
```
Hmm but cse still unifies the addresses since both are the same constant expression. Unless we make the second one differ: e.g. reuse mb with a second set:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = (u8 *)&D_800AF630;   /* re-set: cse invalidates the class, then re-adds */
func_800491AC(mb + 0x18);
```
But cse would still recognize `(plus D_800AF630 24)` as the same expression and CSE it — unless the re-set breaks it. Actually cse processes: after the call, `mb = &D_800AF630` set; then `mb+0x18` — cse has hash entry for `(plus (symbol_ref D_800AF630) 24)`? The issue is cse's constant-address handling: it records the address expression in a register. If mb is re-set to the same value, cse would recompute but may reuse the old register if still valid... The old register across the call isn't valid (call clobbers? but it's a constant address, cse may keep it in a callee-saved reg).

Hmm. Let me think about the mechanism. The orig (with launder) scores 0 — target has two adds. Actually wait, let me confirm orig scores 0 and see what the target looks like. Let me extract orig and score, then disassemble.

Note this function has THREE launder sites; all identical. The FRESH step: no orig.c exists. Extract lines 6026-6172.

Let me do that.
