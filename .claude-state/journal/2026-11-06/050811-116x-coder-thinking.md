---
ts: 2026-11-06T12:08:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DYcL0L5G1DU10USeHbyD
---
Mine (v_s8_both_dw) tail:
29 sw v0,16(s0)     (0x10 store) — matches target 29!
30 lui v0,0x20      (unk14 value) — target 30 is li a0
31 li a0,2432       — target 30
32 sw v0,20(s0)     (unk14) — target 32
33 lui v0,0x2
...

Target:
29 sw v0,16(s0)
30 li a0,2432
31 lui v0,0x20
32 sw v0,20(s0)
33 lui v0,0x2
...

So mine has `lui v0,0x20` at 30 and li a0 at 31; target has li a0 at 30 and lui v0,0x20 at 31. It's a swap of `lui v0,0x20` and `li a0,2432`.

So now the issue is: mine orders lui v0,0x20 (unk14 value) before li a0; target orders li a0 before lui v0,0x20.

This is a sched2 ordering of two independent insns. The target: li a0 (for the call) then lui v0 (for unk14). Mine: lui v0 then li a0.

Hmm. So with the do-while around the store, the store is fixed but the li/lui order flipped.

Let me try to fix this. The `lui v0,0x20` is the value for unk14 = 0x200000. The `li a0,2432` is the call arg. 

If I reorder the source tail: `unk14 = 0x200000` comes before the call (source). The li a0 is generated at the call. sched interleaves.

To get li a0 before lui v0,0x20... hmm. The target has li a0 at 30, then lui v0,0x20 at 31, then sw unk14 at 32. So the li a0 is scheduled before the unk14 value computation.

Mine: lui v0,0x20 (30), li a0 (31), sw unk14 (32). So the unk14 value is computed before the li.

This is a sched priority. To flip, maybe reorder the source tail so the call comes before the unk14 store? But the target has the call LAST. 

Alternatively, maybe using a different width for unk14 changes the priority. unk14 is s32 (0x14). The store `((...)a0)->unk14 = 0x200000` is a s32 store (`sw`). The value 0x200000 = lui v0,0x20. 

What if I use `CAST_WIDTH(s32, (u8*)a0, 0x14) = 0x200000;` (different spelling)? Maybe changes scheduling. Let me try.

Also, what if I reorder the tail statements slightly? The target source order is unk14, 0x18, unk48, unk1C, call. The sched interleaves. 

Let me try:
- v_both_cast14: use CAST_WIDTH for unk14.
- v_both_tail_perm: different tail orders.
- v_both_call_early: move the call's arg computation? 

Actually, the `li a0,2432` is the call's first arg. If I compute it earlier via a variable... tested (v_call_var = 2 with the wrong base). Let me try v_call_var on top of v_s8_both_dw.

Let me test a batch on top of v_s8_both_dw:
- v_both_callvar: `s32 c = 0x980; func_8002D4C8(c, 0);`
- v_both_cast14: CAST_WIDTH for unk14.
- v_both_perm1: swap unk14 and 0x18.
- v_both_perm2: ...

Let me test.

This is promising! We're at score 2 with only a li/lui swap. Let me push.

Time: 05:08. Item 4 ~12 min. Good, let me keep going.
