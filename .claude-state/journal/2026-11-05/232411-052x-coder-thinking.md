---
ts: 2026-11-06T06:24:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UwIiT4c3JhLUZ77qGCmN
---
Now I have the target asm. Key facts:

- The target uses `sll $2,$19,2; $L201: lw $2,D_8018E894($2)` — the array base is a *symbol* load with an indexed offset, NOT a hoisted pointer. So loop.c did NOT strength-reduce here (no loop notes? or it did but...). Actually `lw $2,D_8018E894($2)` uses a %lo relocation on the symbol with the index in $2. That's the "constant address" folding.

- The magic 0x55550000/0x5556 is materialized inside the inner loop (per iteration), after the call.

- Registers: $23=s7 = arg0, $22=s6 = base, $18=s2 = mod, $20=s4 = half, $21=s5 = sign, $16=s0 = tmp, $17=s1 = j, $19=s3 = i.

Interesting: target's `sign` is in s5 ($21) and `hh` in $16 (s0). Mine: `sra a1,a1,0x1f` vs target `sra s5,s4,0x1f`.

Now: mine hoists the array base into s5 and the magic into s8. Both are loop.c optimizations (GIV strength reduction + const hoisting). The target has neither, meaning the target's loops had NO loop notes... but the target was compiled from the src WITH the pin/launder. The src has `for (i = 0; i < 6; i++)` — a normal for loop with LOOP notes. Yet no strength reduction?!

Wait, look again: target `lw $2,D_8018E894($2)` where $2 = i*4. That's NOT strength-reduced, and it's not hoisted. With loop notes, loop.c's strength reduction (giv) should convert D_8018E894[i] into a pointer increment. Why didn't it in the target?

Because... the `$2` is reused for many things? Hmm. Or because loop.c's `strength_reduce` requires the loop to be "simple". 

OH WAIT. I bet the reason is the `jal rand` calls and the register pressure... no, loop.c doesn't know about regs.

Hmm, actually: maybe loop.c DID run but `D_8018E894[i]` — the address is a SYMBOL (constant), and gcc's loop.c only strength-reduces `base + offset` where base is a register or a pseudo... For a symbol address, `find_and_verify_loops`... Actually loop.c's `strength_reduce` works on givs: a giv is an insn that adds a constant to a register each iteration. `D_8018E894[i]` with i incremented → the address is a GIV with base = symbol address and increment 4. loop.c's `combine_givs`/`strength_reduce` can create a new pseudo initialized to the symbol address and incremented by 4 — that's what mine did (s5).

So why not in the target? Because in the target the loops have LOOP notes too... unless the notes were absent. The target src is the current src: `for (i = 0; i < 6; i++)` — definitely has loop notes.

Hmm, unless the *pin* `register s32 tmp __asm__("$2")` affects it? No, loop.c runs before global-alloc but after... hmm, actually loop.c runs BEFORE local-alloc and global-alloc. The hard-reg variable creates a hard-reg reference in the RTL. Hmm, could a hard-reg variable in the loop body prevent strength reduction? loop.c's `strength_reduce` checks `loop_regs_scan`, and for the GIV it needs `benefit > 0`. 

Alternatively, the launder asm (an insn with no pattern) inside the loop might block loop.c's optimizations. But we removed it in win.c and mine still hoists... wait, mine hoists MORE than the target (the target with levers does NOT hoist). So the levers (pin/launder/asm) are what *prevent* the hoisting in the target!

Hmm, that's backwards from usual: the asm launder (a volatile-ish insn with a REG_UNSET... ) could inhibit loop.c's move_movables. Actually, loop.c's `find_mem_givs`/`record_givs`... an asm insn in the loop might make loop.c bail out? In loop.c, `loop_optimize` calls `find_and_verify_loops`; if the loop contains an asm (`#APP`) it doesn't bail. But `strength_reduce` is called; hmm.

Alternatively: the hard-reg pin `$2` might make loop.c's `strength_reduce` skip because the GIV's benefit is negative when the register is a hard reg? 

Whatever the mechanism, empirically: mine (lever-free) hoists; the target (with levers) doesn't. So we need a plain-C way to stop loop.c's strength reduction and const hoisting.

Known move: `for -> goto loop (no LOOP notes)` — kills all loop.c opts. That would produce exactly the target shape: index scaling sll, symbol loads, magic materialized per iteration.

But careful: converting to goto also changes the branch layout. The target's layout:
```
move $19,$0        ; i = 0
sh $0,34; sh $0,36
sll $2,$19,2       ; (before L201! computed before the label)
$L201:
lw $2,D_8018E894($2)
...
$L197:
jal rand
...
slt $2,$17,4
bne $2,$0,$L197
addu $19,$19,1
slt $2,$19,6
bne $2,$0,$L201
sll $2,$19,2       ; in the delay slot
```

So the outer loop: label L201 at the top, test at the bottom (`slt $2,$19,6; bne $2,$0,$L201` with the delay slot doing `sll $2,$19,2` for the next iteration). That's the classic for-loop rotation (test at bottom), and the entry test is `sll $2,$19,2` + fall into L201 — with i=0, the entry is unconditional! Indeed: `move $19,$0; sh...; sll $2,$19,2; $L201: lw ...`. There's NO entry test for the outer loop — gcc knows i=0 < 6 so the first iteration is unconditional (it's a do-while rotation of a for loop where the initial test is provably true... actually gcc's loop.c "loop inversion" doesn't do this; the front end emits `for` as: init; test; body; incr; test...). 

Hmm, with `for (i = 0; i < 6; i++)`, gcc 2.7.2 expands to:
```
i = 0;
goto test;
top:
body
i++;
test: if (i < 6) goto top;
```
And `jump_optimize` (jump.c) can delete the initial jump if the test is provably true (i=0 < 6 constant-folded). Yes! jump.c's `jump_optimize` folds `if (0 < 6)`. So the entry test disappears.

If I write a goto loop:
```c
i = 0;
L201:
    ...body...
    i++;
    if (i < 6) goto L201;
```
That gives exactly the same shape (no entry test) but no LOOP notes. 

Similarly the inner loop:
```c
j = 0;
L197:
    ...
    j++;
    if (j < 4) goto L197;
```

Hmm, but the target's inner loop entry: after the setup, falls into L197 with j=0 (no test). Same.

So the goto conversion preserves the target's CFG shape exactly. 

But wait: does the absence of LOOP notes change the *scheduling* or other things? The known move says it's fine and it's the documented way.

Now: the target's loop body order. Let me write the goto version and score.

Current source:
```c
    if ((D_800B99DA & 7) == 0) {
        pos[1] = 0;
        pos[2] = 0;
        for (i = 0; i < 6; i++) {
            u = D_8018E894[i];
            tmp = u * 0x600 + 0x2000;
            base = tmp;
            mod = (tmp << 16) >> 18;
            step = u * 6 + 0x12;
            half = step * 2;
            pos[0] = step;
            pos[1] -= 0x24;
            for (j = 0; j < 4; j++) {
                sign = half >> 31;
                obj = func_801850D8(...);
                if (obj != 0) {
                    *(s32 *)(obj + 0x20) |= 0x800000;
                }
                hh = half;
                pos[0] -= hh / 3;
            }
        }
    }
```

Goto version:
```c
    if ((D_800B99DA & 7) == 0) {
        pos[1] = 0;
        pos[2] = 0;
        i = 0;
    L201:
        u = D_8018E894[i];
        ...
        j = 0;
    L197:
        sign = half >> 31;
        ...
        pos[0] -= hh / 3;
        j++;
        if (j < 4) goto L197;
        i++;
        if (i < 6) goto L201;
    }
```

Careful: the original `for` has the body inside braces; the increment `i++` comes after the inner loop. Yes.

Let me write this. Also note the target has `move $19,$0` (i=0) then `sh $0,34; sh $0,36` then `sll $2,$19,2` — wait, pos[1]=0 and pos[2]=0 are the `sh` and then sll. The order: i=0 is set BEFORE the two stores in the target? `move $19,$0; sh $0,34($sp); sh $0,36($sp); sll $2,$19,2`. Interesting: i=0 first. In the source, pos[1]=0; pos[2]=0 come before the for. sched1 reordered. Fine.

Let me write win.c with goto loops.

Also I should double check: the launder deletion — does the target need the `base = tmp` copy? In the target: `move $22,$2` (base = tmp) then `#APP #NO_APP` then `sll $2,$2,16`. Hmm: the target's asm has `move $22,$2; #APP #NO_APP; sll $2,$2,16`. So base=tmp (s6=$22) is set BEFORE the launder, and mod = (tmp<<16)>>18 after. In my win.c, `base = tmp;` then `mod = (tmp<<16)>>18;` — the asm removed. Does the copy survive? Since base is used later (addu $16,$22,$16), yes.

Hmm, but in the target, `#APP #NO_APP` sits between `move $22,$2` and `sll $2,$2,16`. In my candidate, without the asm, those might be scheduled differently. We'll see.

Let me write the goto version.
