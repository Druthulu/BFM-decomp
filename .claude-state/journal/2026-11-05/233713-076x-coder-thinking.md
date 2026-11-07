---
ts: 2026-11-06T06:37:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_R7bYGPwbus9Lsre04WgA
---
Now the target asm is clear:

```
subu sp,-32
move $5,$4          ; a1 = a0
sw $31,24(sp)
lh $2,252($5)       ; t = unkFC
beq $2,$0,L270
move $3,$2          ; (delay slot) v1 = t
lw $4,32($5)
addu $2,$3,-1
sh $2,252($5)
...
L270:
lh $2,10($5)        ; t = unkA
lh $3,D_80126B62
addu $2,$2,-48
slt $3,$3,$2
la $2,D_801D093C
beq $3,$0,L273
li $3,0x40000000
la $2,D_801D094C
L273:
or $2,$2,$3
li $3,0x20000000
or $2,$2,$3
sw $2,88($5)
lhu $2,2($5)        ; t = unk2
#APP #NO_APP
sll $2,$2,2
lw $2,D_801D0A3C($2)
jal $31,$2
move $4,$5
```

So in the target, t is v0 throughout, and a0 is copied to a1 ($5) at the start (because $4 is used as a scratch for unk20).

My candidate (mine):
```
14  lh	v1,10(a1)     ; t = unkA in v1
15  lui	v0,0x0
16  lh	v0,0(v0)
17  addiu	v1,v1,-48
18  slt	v0,v0,v1
...
```
So mine uses v1 for t and v0 for the compare temp.

Interesting: in the target, `lh $2,10($5)` (t in v0), `lh $3,D_80126B62` (compare value in v1), `addu $2,$2,-48`, `slt $3,$3,$2`.

In mine: `lh v1,10(a1)`, `lui v0; lh v0,0(v0)`, `addiu v1,v1,-48`, `slt v0,v0,v1`.

So the difference is which of the two gets $2. The compare value (D_80126B62 load, block-local) vs t (global).

In the target, t = $2 (pinned) and the local temp gets $3.
In mine, the local temp (r76? 2 refs live 2 ST_REGS) gets... hmm, the order says r73 (t) first → $2. But the final shows t in v1.

Unless r73 is NOT t. Let me re-examine: r73 has 13 refs, 14 insns, live at the start of block 4. Hmm, "Registers live at start: 29 30 72 73" in block 4.

Hold on: t = unkA (block 2), and in block 4, t = unk2. If t is one pseudo, it's live across blocks 2→4. The middle value (unk58 = t) is dead after the store. So t's live ranges: block 2 (set + uses), then block 4 (set + use). Since it's the same pseudo, its "live" count is the sum.

13 refs over 14 insns — that's t: t=unkA (1), t-=0x30 (2), cmp (1), t=D_801D094C (1) or t=D_801D093C (1), t|=0x40000000 (2), t|=0x20000000 (2), unk58=t (1), t=unk2 (1), t used in index (1)... ≈ 12-13. Yes, r73 = t.

So r73 is FIRST in the allocation order and conflicts only with v0 and sp. So it should get $2 unless it conflicts with $2 — and it DOES conflict with v0. So it takes $3.

Why does t conflict with v0? Because at the indirect call, t is live (the call target) and v0 is live (call-clobbered). In the target, t IS v0 — the same register, so the "conflict" is between t and v0 but since t is a hard-reg variable, gcc allocates the hard reg anyway (hard-reg variables bypass allocation).

Hmm, so plain C: t can never be in $2 because it conflicts with $2. Unless t is not live at the call.

Wait, in the target's asm, `lhu $2,2($5)` then `sll $2,$2,2` then `lw $2,D_801D0A3C($2)` then `jal $31,$2`. t is consumed into $2 before the jal; the jal's target is $2. t is dead after the lw. So t is NOT live across the call.

Then why does flow say r73 conflicts with v0? Maybe because of the OTHER call... there's only one call. Hmm.

Or maybe the conflict comes from the `beq` at the top: `lh $2,252($5)` — no.

Hmm, "conflicts v0,sp" for r73. Let me look at where. Maybe cse created a pseudo for the call address that's live at the call... 

Alternatively, the conflict arises from the call insn's `(use (reg/i:SI 2 v0))` or the return value. In the RTL, the call `(call (mem (reg 73)) ...)` — hmm.

Wait, maybe r73 is not t. Let me check the actual assignment: in the target's alloc table (with the pin), what does r73 correspond to? Let me dump the target's alloc table.

Let me do that — quick.
