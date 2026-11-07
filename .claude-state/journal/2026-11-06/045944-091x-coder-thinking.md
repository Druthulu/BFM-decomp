---
ts: 2026-11-06T11:59:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SeXCKZtBvdTvQVlonNUh
---
v_two_s8: 
- Mine has `li v1,2` at insn 3 (early), target at insn 5 (after the lw). So the `li v1,2` is scheduled earlier in mine.
- The store `sw v0,16(s0)` at 30 vs target 29 (still one slot off).

So the register swap is fixed (p=v0, two=v1), but the `li v1,2` is now scheduled at insn 3 instead of 5, and the store is still one off.

Interesting. With s8 two, the li v1,2 is hoisted to insn 3 (right after sw ra). Target has it at insn 5 (after lw v0,32). 

Hmm. So the s8 version reordered the li earlier. 

Let me think: target order:
0 addiu sp
1 sw s0,16
2 move s0,a0
3 sw ra,20
4 lw v0,32(s0)
5 li v1,2
6 sh v1,2(s0)
7 sh zero,52(s0)
8 sh zero,20(v0)
9 sh zero,18(v0)
10 jal (delay sh zero,16(v0))

Mine (v_two_s8):
0 addiu
1 sw s0
2 move s0
3 li v1,2   <- early
4 sw ra,20  ?
...

Wait, the diff says delete mine[3] li v1,2 (target has nothing at 3), insert mine[6] target[5:6] li v1,2. So mine's li v1,2 is at 3 and target's at 5. Mine's sw ra is at ? Let me disassemble v_two_s8.

Actually, the s8 assignment might have changed the scheduling. Let me dump v_two_s8.

Let me get the full disassembly.
