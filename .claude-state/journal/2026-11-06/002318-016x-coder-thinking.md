---
ts: 2026-11-06T07:23:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LuspL8Y6YelcXN7RebUQ
---
Now let's plan per item.

Item 1: func_800CB458. Original:
```
void func_800CB458(s32 arg0) {
    extern void func_800CAF84(void);
    extern s32 func_80146A6C(...);
    register s32 keep_a0 __asm__("$4");  // pin
    s32 s0 = arg0;
    s32 s1;
    s32 v0;
    s32 id;

    keep_a0 = arg0;
    s1 = ((Unkstruct_800CB458 *)s0)->unk34;
    v0 = *(s32 *)(s1 + 0x20);

    *(Struct16 *)(s0 + 0x38) = *(Struct16 *)(v0 + 0x34);
    *(Struct16 *)(s0 + 0x48) = *(Struct16 *)(v0 + 0x44);
    __asm__ __volatile__("" :: "r"(keep_a0));  // keepalive

    func_800CAF84();
    ...
}
```
The kinds is keepalive only. The pin is under another cause (maybe "arg-copy"?). So I need to remove the keepalive asm, keeping the pin. Wait — but "Lever-free = none of the row kinds in <dir>/kinds remain: no pin ...". Hmm, row kind is only keepalive. So keepalive must go. The pin may stay.

But wait, can win.c keep a pin? The constraint: "levers of other kinds the def already had (pins under other causes) may stay, never added". Yes.

So for item 1, I need to remove the keepalive asm line while keeping register allocation the same. The keepalive forces keep_a0 to be live at that point (a use of $4). Removing it means keep_a0 has no use, so the `keep_a0 = arg0` assignment might be deleted entirely (dead store), and arg0's copy into $4 is gone. The pin itself: `register s32 keep_a0 __asm__("$4")` and `keep_a0 = arg0;` — if no use, flow deletes the assignment. But then the pin is gone effectively. Hmm, but the pin is there to make arg0 live in $4? Let's think about what the target does.

Target: function takes arg0 in $4. `s0 = arg0` (move $16? no). Actually the target presumably moves a0 into s0 (callee-saved $16) and $4 stays? Let's check the target disassembly. Let me use dt.sh output only score; need disassembly. There's bin/dt.sh gives score+diff tail. Maybe bin/sc.sh. Let me see .run/P40/T10/dis.sh, df.sh etc. But we're in G24 shard; tools are at .run/P40/T11/bin/. Only dt.sh and sc.sh. We can use tools/delever_search.py --explain? Or use the diff output from dt.sh with tail. Let me run dt.sh with a bigger tail on orig to see if it prints diff (it says score + diff tail). With score 0 there is no diff. Let me instead look at the target asm via `tools/cc1_dumps_tu.sh`? That's for TU dumps of our build.

Actually the target is in build/ presumably. delever_search compares "the function in build/". Let me look at how to get disassembly of target and mine. Maybe `--keep` prints candidate object path. There's .run/P40/T10/objfn.sh. But our shard only has dt.sh/sc.sh. Hmm. We can use objdump directly? Toolchain is reached through bin/sc.sh, bin/dt.sh, tools/cc1_dumps_tu.sh. Maybe objdump isn't allowed. Let me check tools/delever_search.py for a diff print mode that shows the differing insns. dt.sh passes `[tail]` to tail, and delever_search --try prints a score line plus maybe a diff. With score 0 no diff. For non-zero we'll see diffs.

Let me test removing the keepalive line from item 1 orig and score. That's the simplest first try.

Let me create w1.c as orig minus keepalive asm.
