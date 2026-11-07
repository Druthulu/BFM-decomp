---
ts: 2026-11-06T15:01:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tKLYXC9JfngnrLUG9okj
---
Baseline works. Now, my task is to remove the levers and still score 0.

Item 1: func_8017DE00. Kinds: launder. But orig.c has register pins too ($4,$5) — pins are a different kind than the row kind (launder). Constraint says: "levers of other kinds the def already had (pins under other causes) may stay, never added". So pins may stay; launder must go.

The launder at line 3237: `__asm__ __volatile__("" : "=r"(s0) : "0"(s0));  // !FAKE: launder`. Also `a0 = s0 << 10;` etc. Let me understand the function.

Body:
```c
void func_8017DE00(a0p)
s32 a0p;
{
    s32 s0, s1, s2, v0, v1;
    register s32 a0 __asm__("$4");
    register s32 a1 __asm__("$5");
    s32 a2;

    s1 = a0p;
    s0 = 0;
    s2 = (s32)D_8019B538;
    __asm__ __volatile__("" : "=r"(s0) : "0"(s0));  // launder
    a0 = s0 << 10;
    do {
        v0 = s0 << 1;
        v1 = ((Unkstruct_800B5CB8 *)s1)->unk70;
        s0 = s0 + 1;
        v1 = (v1 << 3) + s2;
        v0 = v0 + v1;
        a1 = *(u16 *)v0;
        a2 = s1;
        a1 = a1 + a0;
        a1 = a1 << 16;
        a0 = 0x199;
        func_8012C658(a0, a1 >> 16, a2);
        a0 = s0 << 10;
    } while (s0 < 4);
}
```

The launder is on s0. It's a tied output — effectively opaque, so s0's initial 0 is a real assignment that can't be folded. Hmm, but s0 = 0 then asm on s0. Actually `__asm__ __volatile__("" : "=r"(s0) : "0"(s0))` reads s0 and writes s0 — a use+def. It forces s0 to be materialized? Actually since it's empty asm with tied operands, s0 is unchanged. Its effect: creates a barrier so s0=0 is not propagated into first use? And it might force s0 into a register at that point.

The target presumably has li s0,0 then... Let's get the target disassembly to understand. We can use dt.sh with tail or hdump. Better: look at the diff with a candidate. Let's first try removing the launder and score.

Let me create a working copy and test. Candidate: replace the asm with nothing.
