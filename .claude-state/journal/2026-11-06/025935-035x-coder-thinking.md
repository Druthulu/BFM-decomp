---
ts: 2026-11-06T09:59:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_D5wRMe6w8DefpaRuBxEp
---
Confirmed: mine's final call at 91c has delay slot nop and NO `move a0,s0` anywhere. That means in mine, the arg is passed in a0 but a0 was clobbered... unless the compiler thinks the value is still in a0. Wait — the source `((void (*)(s32))func_80146C3C)(s0)`. In mine's lever-free body, `s0` is a plain `s32` variable. The call needs a0 = s0. But the generated code has no move.

Unless... `s0` in the lever-free body got allocated to $4 (a0)! Let's check: line 2 in the mine dump: `move s0,a0` — hmm, that's at 8 insns into the function. Let me look at the actual prologue of func_800CD314 in the object.

Wait, the dump showed index 0 addiu sp,-24, 1 sw s0,16(sp), 2 move s0,a0, 3 sw ra,20(sp). That's `s0 = (s32)arg0`. If the variable `s0` were allocated to $16, this is `move $16,$4`. Fine.

But then the arg to the last call must be $16. There's no move. That's a compiler bug? No...

OH. I bet the last call in the *source* is `((void (*)(s32))func_80146C3C)(s0);` and GCC's `s0` variable is dead after? No, it's used as the arg.

Hold on — maybe the disassembly line at 91c `jal func_80146C3C` and the delay slot `nop`: the `move a0,s0` might have been moved BEFORE the jal by sched/reorg, i.e., at 918? No, 918 is `sw v0,28(s0)` (delay slot of j at 914).

Wait, actually maybe the target's `move a0,s0` IS in the delay slot, and mine has `nop` because the move was *hoisted above the jal* and then the jal's delay slot can't be filled... but there's no move above either.

Hmm, unless the variable `s0` is in $4! Let me verify by looking at whether $16 is used as `s0` at all: prologue `sw s0,16(sp)` saves $16; `move s0,a0` sets $16. Epilogue restores. So $16 = the s0 variable. So the call arg must be moved.

Unless... the arg passed is NOT s0 but `arg0` and the compiler kept arg0 in... no, arg0 was moved to $16.

This is bizarre. Let me look at the full disassembly of func_800CD314 in the candidate to see if there's a `move a0,s0` I missed. Let me grep.
