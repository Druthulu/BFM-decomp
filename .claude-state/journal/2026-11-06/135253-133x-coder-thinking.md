---
ts: 2026-11-06T20:52:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Ag7vjee49mWGBi2VFQyp
---
vAQ (with `& 1`) = 6 with 69 insns; vAU (`^` only) = 6 with 73 insns (extra insns). vAT (subtract) = 7.

Hmm, vAQ's `(v[0] ^ v[0]) & 1` gave the right copy but +8 frame. vAU's `v[0] ^ v[0]` gave +4 insns.

Interesting. So `(v[0]^v[0])&1` was folded to 0 at some point but caused a stack temp.

Let me think: why would `& 1` cause a stack temp? Maybe the expression is evaluated as: t = v[0]^v[0]; t &= 1; then a0 + t. The `& 1` ensures the value is 0/1 and the compiler can't prove it's 0? If it can't prove, it would emit insns (but the count is 69, so it did fold).

Hmm, the frame +8: maybe a temp for the `& 1` operation.

Let me look for an expression that produces a real PLUS that folds to 0 without a stack temp. 

What about using a *parameter or local scalar* rather than an array element: e.g., `v1 - v1` (v1 is a local s32). At the copy point, v1 is set later (v1 = unk20 after func_8001C214). Hmm, v1 is assigned before the copy? Let me check the source order:

```
v0 = func_8012C1B8();
unk20 = v0;
if (v0 == 0) {...}
func_8001C214(v0, &D_801E81A4);
v1 = unk20;
((Unk*)v1)->unk2C |= 0x10;
func_8004914C(...);
func_800491AC(...);
RotTransSV(...);
unk6 = v[0];
{
    ent = a0 + zr;
```
So v1 is live at the copy point (set earlier). `v1 - v1` would use v1's register; the compiler might fold it to 0 (no insn) and not need a temp. But would it be a real PLUS at expand? `x - x` — gcc's fold() might simplify to 0 at the tree level. vAT used `v[0] - v[0]` and got 7 (folded to a copy). Hmm, so `v[0]-v[0]` folded to a copy but `v[0]^v[0]` did not. Interesting: fold() doesn't simplify x^x (only x-x). So `x ^ x` stays as an expression.

vAU (`v[0]^v[0]`) gave 73 insns (4 extra): so it emitted the xor (2 loads? + xor + add). Hmm, but it scored 6.

vAQ added `& 1`: 69 insns (no extra!) but +8 frame. So `(x^x)&1` was optimized: maybe gcc's `fold` turns `(x^x)&1` into 0? If so, the add would be a0+0 → a real PLUS with a constant 0 (not folded by the front end!) → combine later simplifies to a move but keeps the pseudo. And the stack temp... hmm.

Wait, if `(x^x)&1` folded to 0 at the tree level, then the expression is `(s32)a0 + 0` — a real PLUS with const 0. gcc's expand would emit `addsi3` with 0. Then combine simplifies `(plus reg (const 0))` to a move (addu with $0). The pseudo ent is the add's dest, distinct from a0 → no copy propagation. That explains the copy surviving.

But then why +8 frame? Maybe because `(v[0]^v[0])&1` was NOT folded at the tree level but during RTL expansion, and a temp was allocated. Hmm.

Actually, the key insight: a real `(plus reg (const_int 0))` in RTL survives cse/combine as a distinct pseudo, and local-alloc emits `addu a0,s0,$0`. That's exactly the target!

So I need a C expression that produces `a0 + 0` in RTL without a stack temp. 

If I write `ent = (s32)a0 + 0;` the front end folds it to a copy. But if the 0 comes from a subexpression that gcc folds LATE (during expansion or combine), the add might survive.

What subexpressions fold to 0 late but don't allocate a temp? `(v[0] ^ v[0]) & 1` allocated 8 bytes. What about `(v0 ^ v0) & 1` using a local scalar v0? v0 is dead at that point (used at the top); using it would extend its live range across the calls → a callee-saved reg, changing the frame.

What about `(v[0] ^ v[0])` alone (vAU)? 73 insns — not folded late enough.

Hmm, vAQ's `& 1` made it fold (to 0?) and kept 69 insns. The +8 frame is the only issue.

Where does the +8 come from? Maybe the compiler allocated a temp for the `^` expression because `& 1` forced a specific evaluation. Or maybe the frame grew because of an extra register save? The diff showed:
```
0 addiu sp,sp,-48 vs -40
1 sw s0,40(sp) vs 32(sp)
2 sw ra,44(sp) vs 36(sp)
```
Only the frame and the saved-reg offsets. So the extra 8 bytes are unused stack (a temp slot).

What allocates a temp slot? During expand, `expand_expr` for a complex expression may allocate a temporary via `assign_temp` (a stack slot). `(v[0]^v[0])&1` — the compiler might have used a temp for the XOR result? But the final code has no XOR insn... so the temp was used then optimized away.

If the temp is a compiler temp (not a declared local), the frame grows. To avoid it, I need an expression that doesn't need a temp.

Idea: use a *register* variable for the subexpression: e.g., `s32 z = v[0] ^ v[0]; ent = a0 + (z & 1);` — z is a declared local → it would be optimized to 0 and might not need a stack temp. Let me try.

Actually, if `z` is a declared local, it gets a pseudo, and `z & 1` folds to 0 → `a0 + 0` → the add survives! And no stack temp (z is in a register). Let me test:
```
s32 z = v[0] ^ v[0];
s32 ent = (s32)a0 + (z & 1);
```
Hmm, but the declaration order: z must be declared with the others. The compiler might fold `z = v[0]^v[0]` to 0 and `z&1` to 0 at the tree level, then `a0 + 0` folds to a copy. Hmm.

Let me test a few:
vAX: `s32 ent = (s32)a0 + (s32)((v[0] ^ v[0]) & 1);` — same as vAQ (frame 48).
vAY: `s32 ent = (s32)a0 + (s32)(v[0] != v[0]);` — hmm, `!=` yields 0/1; x != x is 0; maybe not folded, and the result is an int. vAR tested `v[0] != v[0]` and got 7 (folded to a copy). So `!=` folds.

vAQ's `(x^x)&1` is special: it seems gcc's fold does NOT simplify `x^x` but does simplify `(x^x)&1`? That seems odd. Maybe the `& 1` makes it a "boolean" and some pass simplifies.

Let me look at the vAQ initial RTL to see what expression was emitted. That will tell me where the temp comes from. Let me dump vAQ.

Actually, let me first try simpler variants that might avoid the temp:
- `(s32)a0 + (s32)((v[0] ^ v[0]) & 0x1)` — same.
- `(s32)a0 + (s32)((v[0] ^ v[0]) & 3)`.
- `(s32)a0 + (s32)((v[0] ^ v[0]) >> 31)`.

Hmm.

Better: understand the temp. Let me dump vAQ's initial RTL around the copy. That's the fastest way.

Let me splice vAQ and dump .rtl.
