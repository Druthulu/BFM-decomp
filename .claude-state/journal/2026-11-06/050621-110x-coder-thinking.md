---
ts: 2026-11-06T12:06:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FeXNCtAPuMRGKRGiXZog
---
Removing the launder drops to score 10, 163 insns (2 missing: the sll/sra).

Now I need to keep the `sll v0,a3,0x10; sra v0,v0,0x10` without the launder. The launder makes nx opaque so `nx * 0x10000 >> 0x10` isn't simplified.

Real C ways to keep a 16-bit sign extension:
- Declare nx as `int` and use `(short)nx`? The compiler might still simplify.
- Make the expression `nx * 0x10000 >> 0x10` where nx's range is unknown.

What if `nx` is declared `uint` and the comparison is `(int)(nx << 16) >> 16 < 3`? Hmm.

Let me look at the target's exact sequence:
```
addiu v0,a3,1
move a3,v0
sll v0,v0,0x10
sra v0,v0,0x10
slti v0,v0,3
```
So nx (v0) = iVar4+1; iVar4 = nx; then nx<<16>>16 < 3. The sll/sra is the 16-bit truncation.

Without the launder, mine:
```
addiu v0,a3,1
move a3,v0
sll v0,v0,0x10
sra v0,v0,0x10
slti v0,v0,3
```
Wait, in w2 (launder kept, keepalive removed) the tail was:
```
addiu v0,a3,1
move a3,v0
sll v0,v0,0x10
sra v0,v0,0x10
```
That's with the launder. In w8 (launder removed), the diff earlier (w1) showed:
```
lui v0,0x1
addu a3,a3,v0
sra v0,a3,0x10
```
So the compiler transformed the loop: it keeps `a3` as iVar4*0x10000? Let me look at w8's tail.

Hmm. The compiler knows nx = iVar4+1 and the loop bound, so it optimizes.

To keep the sll/sra, I need to make the value opaque. Without an asm launder, the classic real-C trick is to pass through a **memory variable** (store + reload) — but that adds lw/sw.

Or use a `volatile` — lever.

Or make the expression involve a value the compiler can't range-analyze. For example, `nx = iVar4 + 1;` where iVar4 is `int` — the compiler can analyze.

What if iVar4 is `uint` and nx is `int`? `(short)iVar4 == two` comparisons. Hmm.

What if I change the loop to `while ((short)(iVar4 + 1) < 3)`? Same.

Hmm, what if the loop condition is `while (nx * 0x10000 >> 0x10 < 3)` and nx is `uint`? `(uint)nx * 0x10000 >> 0x10` would be a logical shift → different code (srl). Target uses sra (arithmetic), so nx is signed.

What if nx is `short`? Then `nx * 0x10000` promotes to int; `>> 0x10` → sra. And the compiler knows nx is short, so the sll/sra is the conversion from int to short... Hmm, if nx is `short`, assigning `nx = iVar4 + 1` truncates to short; the comparison `nx * 0x10000 >> 0x10 < 3` would be `(int)nx`. The compiler would sign-extend nx (sll/sra) when loading it? If nx is a short variable in a register, the compiler might keep it sign-extended and skip the sll/sra.

Let me try: declare nx as `short` and `iVar4` as `int`, with `nx = iVar4 + 1; iVar4 = nx;`.

Actually, the target's `move a3,v0` suggests iVar4 = nx (a3 = v0). And then `sll v0,v0,0x10; sra`. If nx were short, `iVar4 = nx` would sign-extend.

Let me just experiment with nx's type and the loop condition form.

Variants:
- nx as short
- nx as uint
- condition `(short)nx < 3`
- condition `(int)(short)nx < 3`
- `while ((nx << 16) >> 16 < 3)`

Let me generate a batch on top of w7 (keepalive already cracked) with the launder removed.

Let me write gen.py.

Also, another idea: use the do-while to split and keep the sll/sra? No, the simplification is by combine/flow, not scheduling.

Let me test the type variants.
