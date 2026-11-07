---
ts: 2026-11-06T14:32:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_khGw00HlhzYNXa5iT5uq
---
Baseline scores 0. Removing the keepalive gives score 4 (ORDER): the `lui a1,0x0; addiu a1,a1,0` (the address &D_8019DC34 loaded into a1) is placed later in mine (insns 31-32) vs target (insns 22-23). So the keepalive hoists the a1 address computation earlier. The target has a1 = &D_8019DC34 computed right after `a0 = s0` (before v0 = 0xFFF60000), while mine computes it later.

Let me see the full target and mine asm. Let me get the dt with more context. Actually, let me look at the target asm (from the baseline dump). Let me dump the baseline (orig) and the c1 to compare.

Actually, the diff says: target has `lui a1,0; addiu a1,a1,0` at position 22-23 (right after `a0 = s0`?), and mine has it at 31-32 (later). So the keepalive (which references a1) keeps a1 live/hoisted.

The fix: real C that makes the a1 address computation happen earlier. The source:
```
        func_8012B1B4(s0, (void *)&D_8019DC18);
        a0 = s0;
        a1 = (s32)&D_8019DC34;
        __asm__ __volatile__("" :: "r"(a1));  // keepalive
        v0 = 0xFFF60000;
        s0 = 4;
        ((Unkstruct_800B5CB8 *)a0)->unk14 = v0;
        ...
```

The target order:
```
lui a1,0x0; addiu a1,a1,0   # a1 = &D_8019DC34  (early)
v0 = 0xFFF60000
s0 = 4
...
```
Wait, let me get the actual target asm to see the order. Let me dump.

Actually, let me first try a simple real-C move: move the `a1 = (s32)&D_8019DC34;` assignment earlier (before `a0 = s0;` or before the func_8012B1B4 call?). Hmm, a1 is a local; moving the assignment earlier in the source would make the address computation earlier. But cse/sched1 might reorder.

The keepalive asm makes a1 a "used" value at that point, forcing the address computation to be scheduled there. Without it, sched1 sinks the address computation to the call site (where a1 is used as an argument).

The target wants the address computed early (at position 22-23) and then used later at the call. So the original source probably computed a1 early and used it later. Real C: if a1 is used early in some way... but it's only used at the call.

Hmm. Actually, maybe the target's order comes from the source order: `a1 = (s32)&D_8019DC34;` right after `a0 = s0;`, and the compiler (sched1) keeps it there because... without the keepalive, sched1 sinks it to the call. With the keepalive, it stays.

To keep it early in real C, I could move the assignment EARLIER, e.g., before `func_8012B1B4`? But then it might be scheduled even earlier.

Or use the value early in a real computation that folds. Hmm.

Wait — the target has a1 computed at insns 22-23. Let me see what's around there. Let me dump the baseline and look at the full asm. Let me dump c1 (or orig) to see the exact order.

Let me set up the dump for this TU. The TU is src/ov_SC04_004/ov_SC04_004_jr_8017AE2C.c. Let me use cc1_dumps_tu.

Actually, let me first look at the dt diff more fully (it only shows the diff). Let me get the target asm via a dump. But the dump is for the whole TU (~large). Let me just do it.

Alternatively, the diff tells me enough: I need the a1 address computation to be 9 instructions earlier.

Let me think about what real C would do. The a1 address `&D_8019DC34` is used as the 2nd arg to func_8012D5E4. The keepalive forces it early. 

Real-C levers:
1. Move `a1 = (s32)&D_8019DC34;` earlier in the source (e.g., right after `a0 = s0;` — it already is). Without the keepalive, sched1 sinks it.
2. Use a1 in an earlier real computation. E.g., `a1 = (s32)&D_8019DC34; ... v0 = 0xFFF60000 + (a1 - a1);`? folds.
3. Reorder the source so the address computation is before other statements that sched1 won't cross.

Hmm. Actually, the target's order suggests the address is computed right after a0=s0 and before v0=0xFFF60000. The keepalive is right after `a1 = ...`. So removing it lets sched1 sink a1.

What if I move `a1 = (s32)&D_8019DC34;` to BEFORE `a0 = s0;`? Then sched1 might keep it early (before a0=s0). But the target has a0=s0 before a1. Hmm, actually let me look at the exact target asm order.

Let me dump the TU (orig, score 0) and look at func_80183130's asm. Let me do it.

I need to recreate the _tu setup for ov_SC04_004. Let me create it and dump.

Actually, the TU may have different includes. Let me check the top of src/ov_SC04_004/ov_SC04_004_jr_8017AE2C.c.

Actually, for a quick look, I can dump the TU directly with cc1_dumps_tu.sh on the real src TU (it handles includes since it's a real TU). Let me do that: DUMP_ROOT=... bash tools/cc1_dumps_tu.sh src/ov_SC04_004/ov_SC04_004_jr_8017AE2C.c sc04.

Let me do it.
