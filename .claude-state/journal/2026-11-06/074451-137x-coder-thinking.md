---
ts: 2026-11-06T14:44:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iVgfg3bbBMeJmpSwkGaT
---
Now I see the target code for case 5:
```
$L67:
	sll	$2,$17,16
	sra	$16,$2,16        # t = (s16)a1  (t in $16/s0)
	bne	$16,$0,$L68      # if (t != 0) goto L68
	li	$3,3             # delay slot: v1 = 3
	la	$2,D_8018C4FC
	j	$L60
$L68:
	beq	$16,$3,$L70      # if (t == 3) goto L70
	li	$2,5             # delay slot: v0 = 5
	bne	$16,$2,$L71      # if (t != 5) goto L71
 #APP
 #NO_APP                  # launder
	bne	$16,$3,$L73      # if (t != 3) goto L73
$L70:
	la	$2,D_8018C520
	j	$L60
$L73:
	...
$L71:
	lbu	$4,D_801802E4($16)
	...
```

So the launder (empty asm) sits between `bne $16,$2,$L71` and `bne $16,$3,$L73`. It's an empty asm with t as input/output. It emits nothing but forces t to stay in $16 (s0) and creates a scheduling barrier.

Without the launder (c1), the diff says:
- mine[90] `li v0,3` vs target `li v1,3`
- mine[95] `beq s0,v0` vs target `beq s0,v1`
- mine[97] `beq s0,v0` vs target `bne s0,v0`
- mine[99] `j` vs target `bne s0,v1`

So without the launder, the compiler:
1. Puts the constant 3 in v0 instead of v1.
2. Changes the branch structure: mine has `beq s0,v0` twice (for t==3 and t==5?) and a `j`, while target has `beq s0,v1; bne s0,v0; bne s0,v1`.

Hmm, let me look at mine's asm (c1). Let me dump c1's TU. Let me set up the scratch TU for ov_SC01_004.

Actually, the diff shows the region around insns 90-100. Let me look at mine's asm for the same region. Let me dump c1.

Let me set up the scratch TU (ov_SC01_004) and dump c1.

Actually, I can reason: without the launder, the compiler does:
```
$L67:
	sra $16,$2,16
	bne $16,$0,$L68
	li $3,3
	la $2,D_8018C4FC
	j $L60
$L68:
	beq $16,$3,$L70
	li $2,5
	beq $16,$2,...  ??? 
```
Hmm, the diff says mine[97] `beq s0,v0` where target has `bne s0,v0`. And mine[99] `j` where target has `bne s0,v1`.

So mine's structure is different: `beq s0,v0` (if t==5 goto ...) then `j ...` (goto L70?). Target: `bne s0,v0` (if t!=5 goto L71) then `bne s0,v1` (if t!=3 goto L73).

So the difference is in how the `if (t == 5) { ... }` and the `goto sel_054` are compiled.

The C:
```
if (t == 3) { goto sel_054; }
if (t == 5) {
    __asm__(...);
    if (t != 3) { goto sel_094; }
sel_054:
    sel = &D_8018C520;
    goto set_sel;
sel_094:
    ...
}
```

The target compiles this as:
```
beq t,3,$L70       # t==3 -> sel_054
li v0,5
bne t,5,$L71       # t!=5 -> the code after the if
bne t,3,$L73       # t!=3 -> sel_094
$L70: sel = &D_8018C520; goto set_sel
$L73: ...
$L71: ... (the code after the if: func_800291B4(D_801802E4[t])...)
```

Without the launder, the compiler reorganizes:
```
beq t,3,$L70
li v0,5
beq t,5,...   # t==5 -> ?
j ...         # 
```
Hmm, mine has `beq s0,v0` at 97 and `j` at 99. Let me look at mine's actual asm.

Let me dump c1. I need the scratch TU. Let me set it up.

The TU includes? Let me check.
