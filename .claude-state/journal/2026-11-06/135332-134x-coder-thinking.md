---
ts: 2026-11-06T20:53:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0JW03JAyWTCiH9p9f0o5
---
The initial RTL for vAQ:
- 95: reg90 = v[0] ^ v[1]? Wait: `(xor (subreg:SI (reg:HI 88)) (subreg:SI (reg:HI 89)))` — reg 88 is v[0] (loaded at insn 94? no, 94 loads into 89). Hmm, two different loads: reg88 and reg89.
- 97: reg91 = subreg of 90
- 98: reg92 = reg91 & 1
- 99: reg93 = zero_extend(reg92)
- 101: ent = a0 + reg93

So the expression `v[0] ^ v[0]` was NOT recognized as x^x at the tree level (it loads v[0] twice into reg88 and reg89!). Later cse folds the two loads (same address, no intervening store) and then `x^x` = 0, `& 1` = 0, and the add becomes `a0 + 0`. The temp regs are pseudos; the +8 frame is odd though (pseudos don't use stack unless spilled).

Hmm, the +8 frame: maybe one of the temps got spilled. But the final code has no extra insns... The frame size is computed from the max stack slot usage; a spilled temp would add insns. Hmm.

Wait — maybe the frame grew because of the *stack temp* used for the `subreg` HI temporaries: gcc sometimes uses a stack slot for subreg operations (`reg:HI` from memory). The insn 94 loads `(mem/s:HI (reg:SI 69))` into a HI reg — that's v[0]. And insn 95 xors two HI subregs. gcc might use a stack slot for the HI temporaries.

Anyway, the net effect: +8 frame, same insns.

Can I avoid the temp? What if I use a *s32 local* instead of the array element, so no HI subregs:
```
s32 z = v0 ^ v0;
ent = a0 + (z & 1);
```
But v0 is dead... hmm, v0 (the local) is the first call's result; at the copy point it's dead but still in a register? It's not live, so the compiler would have to keep it → extends the live range across calls → callee-saved reg, frame change.

What about `v1 ^ v1`? v1 is live at the copy point (set to unk20). `v1 ^ v1` = 0. The compiler would fold it? Maybe not (x^x not folded). And no stack temp (v1 is SI in a register). Let me try:
`ent = (s32)a0 + ((v1 ^ v1) & 1);`

If the xor is not folded at the tree level and uses v1 (SI), the RTL would be: reg = v1 ^ v1; reg &= 1; ent = a0 + reg. Then cse folds v1^v1 = 0? cse's fold_rtx does simplify `(xor x x)` to 0? If cse folds it, we get a0 + 0 → the add survives as a distinct pseudo → MATCH (and no stack temp).

But wait: would cse fold the whole thing to a copy? cse's fold_rtx would simplify `(and (xor x x) 1)` → `(and 0 1)` → 0, so `ent = a0 + 0` → fold_rtx might simplify the plus to just a0 → the pseudo becomes a copy → propagated. Hmm.

But in vAQ, the same happened and the add SURVIVED (the copy `move a0,s0` exists). So combine/cse did NOT simplify `(plus reg 0)` to a copy. Interesting: gcc's combine keeps `(plus reg 0)` as an addsi3 with 0, which emits `addu rd,rs,$0`.

So the plan: use a subexpression that cse folds to 0, producing `(plus a0 0)` with a distinct dest.

vAQ's problem was only the frame. Let me try `v1 ^ v1` and other scalar variants.

Actually, wait: in vAQ, did cse fold the whole thing? The final code has `move a0,s0` and no xor/and insns, so yes.

Let me try variants:
vAY: `ent = (s32)a0 + ((v1 ^ v1) & 1);`
vAZ: `ent = (s32)a0 + ((v0 ^ v0) & 1);` (v0 dead → risky)
vBA: `ent = (s32)a0 + ((s32)(v[0] ^ v[0]) & 1);` — same as vAQ.
vBB: `ent = (s32)a0 + ((v[1] ^ v[1]) & 1);`

Let me test vAY and vBB.

Hmm, but v1 is used later (`v1 = unk20` is set before the copy; is v1 still live after the copy? The code: `v1 = unk20; ((Unk*)v1)->unk2C |= 0x10;` then v1 is dead. So v1 is dead at the copy point. Using v1 in `v1 ^ v1` would make it live → the compiler would keep it across the two calls (func_8004914C/AC) → it's already dead before those calls. Extending v1's live range across the calls would force a callee-saved register and change the code.

Hmm. What about v[1]? v[1] is loaded at ed54 (`lhu v0,18(sp)`) — inside the block. The copy is before it.

What about a *new* local scalar declared in the block, e.g., `s32 z;` used as `z ^ z`? Uninitialized → undefined behavior, and the compiler might not fold it (two reads of an uninitialized variable). That would emit a real xor of garbage → changes semantics (ent would be wrong).

Hmm. What about a *constant* expression that isn't folded by the front end? E.g., `(0 ^ 0) & 1` → folded immediately.

What about `(v[0] ^ v[0]) & 1` but with `out[0]` instead (a different array)? Same temp issue maybe.

What about using the array element in a way that avoids HI subregs: `v[0]` is u16 (HI). The subreg machinery caused the temp. What if we use an s32 lvalue: e.g., `v0` (s32 local) — but liveness.

Hmm, what about `((s32)v[0] ^ (s32)v[0]) & 1`? The casts to s32 might avoid the HI subreg temps. Let me try:
`ent = (s32)a0 + (((s32)v[0] ^ (s32)v[0]) & 1);`

Let me test these.

Actually, hold on. The +8 frame might be acceptable if... no, the target's frame is 40.

Let me test a batch:
vAY: `(s32)a0 + (((s32)v[0] ^ (s32)v[0]) & 1)`
vAZ: `(s32)a0 + ((v[0] ^ v[0]) & 1)` (vAQ, 48)
vBA: `(s32)a0 + ((v[1] ^ v[1]) & 1)`
vBB: `(s32)a0 + ((out[0] ^ out[0]) & 1)`
vBC: `(s32)a0 + ((v[2] ^ v[2]) & 1)`

Let me score them.
