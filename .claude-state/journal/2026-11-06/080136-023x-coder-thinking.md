---
ts: 2026-11-06T15:01:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QOwcu72ur2bcj8mujJ4r
---
--explain shows the residual. But for a candidate body we need disassembly. Let's use hdump.sh or cc1_dumps. Actually simpler: use the `--keep` option to get the object and objdump it. But scratch cleanup. Or use `.run/P40/T11/bin/dt.sh` which only gives diff.

Let me instead reason. The target: 
```
s0 = 0;
a0 = s0 << 10;   // = 0, target emits sll a0,s0,0xa (not folded!)
do {
   v0 = s0 << 1;
   ...
   a0 = 0x199;
   call
   a0 = s0 << 10;
} while (s0<4)
```

The launder forces s0 to be treated as an opaque value (asm), so gcc can't constant-propagate s0=0 into `a0 = s0 << 10`. Without it, `a0 = 0<<10` = 0 → `move a0,zero`.

Target wants `sll a0,s0,0xa` even though s0==0. Hmm but wait, is the target's index 8 sll? Target[9] is sll a0,s0,0xa. So target has TWO sll a0,s0,0xa? One before loop (index ~8) and one at loop end (index ~29). Mine without launder: move a0,zero before loop, and the end-of-loop `a0 = s0 << 10` after s0 increment — that one is sll a0,s0,0xa (since s0 is 1..4).

Actually wait, in the original with launder, the diff shows mine[8] = move a0,zero deleted and target[9] sll inserted. Hmm — maybe the launder was forcing a real def of s0 so the pre-loop shift... no.

Let me think about what the launder does: `__asm__("" : "=r"(s0) : "0"(s0))` — output tied to input. It means s0 is used and redefined. This blocks const propagation of s0 = 0 into the shift? Actually cse/combine: `a0 = s0 << 10` where s0 = 0 → constant 0. But with the asm, s0's value after asm is unknown (although tied), so it can't fold.

So the launder is load-bearing to keep `sll a0,s0,0xa` with s0=0 instead of `move a0,zero`.

Lever-free alternatives to get the same:
1. Make the shift expression non-foldable in plain C. E.g., make s0 a `volatile`? Not allowed (volatile is class C/D? Actually the census kinds: pin, launder, barrier, keepalive, instruction, gte-lever, asm-body. volatile might be a "barrier"? Hmm).
2. Reassign s0 in a way that its value isn't known to be 0? But s0 must be 0 at loop start.
3. Use a different spelling: `a0 = s0 << 10;` could be moved after? Or compute via a pointer? Hmm.

Wait — maybe simpler: if we reorder so that the pre-loop `a0 = s0 << 10` uses a different variable whose value is not known... but then register allocation changes.

Alternatively, make `s0 = 0` not a constant by reading it from something? No, must be 0.

Hmm, what about declaring s0 as `s16` or u8? `s0 = 0` then `s0 << 10` still folds.

What about the `do{}while(0)` trick? A `do { ... } while(0)` around the asm-free... C0535: do{}while(0) splits cse1 EBB, cracked a sched1-birth-order item. Here the issue is constant folding (combine/flow). Hmm.

Wait, maybe the launder isn't there for the pre-loop shift but for register allocation — to force s0 to be in a register from the start (li s0,0 before...). Let's look at the actual target assembly. Let me get the target function disassembly from build/. I can use tools/cc1_dumps_tu.sh? That's for TU dumps. hdump.sh is header pass dumps.

Alternative: objdump the built object. Find the object for this TU. Let me check what build/ contains and whether there's a script to dump a function. Let me look at .run/P40/T11/bin/b1_segs.txt maybe not.

Simplest: use delever_search --keep with a candidate, then objdump the scratch object and compare. But target object also needed. The target is in build/ — masked_diff compares with baseline object. Let me find the object path for ov_SC02_039.

Actually, tools/delever.py may have a --show/explain that dumps instructions. Let me check for a "disasm" helper: tools/cc1_dumps_tu.sh (TU dumps) and tools/alloc_table.py. Let me check the build layout.
