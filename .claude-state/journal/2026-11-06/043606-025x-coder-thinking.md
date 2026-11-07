---
ts: 2026-11-06T11:36:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KOcQscWVOStQu9uQWOc0
---
Now I understand the target fully. Let me map insn numbers (delever_search uses 0-based insn index). Target function has 144 insns (0..143).

Let me count from e90:
0 e90 addiu sp
1 e94 sw s2
2 e98 lui s2
3 e9c lw s2
4 ea0 lui v0
5 ea4 lhu v0
6 ea8 lui a0
7 eac lw a0
8 eb0 li a2,2
9 eb4 sw ra
10 eb8 sw s3
11 ebc sw s1
12 ec0 sw s0
13 ec4 sll a1
14 ec8 addu a1
15 ecc sll a1
16 ed0 lui v0
17 ed4 addiu v0
18 ed8 jal
19 edc addu a1 (delay)
20 ee0 move s0
21 ee4 lui v1
22 ee8 lh v1
23 eec li v0,3
24 ef0 beq v1,v0
25 ef4 li v0,7 (delay)
26 ef8 bne v1,v0
27 efc li a0,2 (delay)
28 f00 sw zero,16(sp)
29 f04 li a0,2
30 f08 lui a2
31 f0c addiu a2
32 f10 j f28
33 f14 move a1,s0 (delay)
34 f18 sw zero,16(sp)
35 f1c move a1,s0
36 f20 lui a2
37 f24 addiu a2
38 f28 jal
39 f2c li a3,1 (delay)
40 f30 move s0
41 f34 move a0,s0
42 f38 lui v1
43 f3c lhu v1
44 f40 lui a2
45 f44 addiu a2
46 f48 sll v0
47 f4c addu v0
48 f50 sll v0
49 f54 lui at
50 f58 addu at
51 f5c lw a1
52 f60 move a3,zero
53 f64 jal
54 f68 addiu a1,a1,8 (delay)
55 f6c move s0
56 f70 lui v1
57 f74 lh v1
58 f78 li v0,3
59 f7c bne v1,v0
60 f80 li v0,3 (delay)   <-- TARGET[60] li v0,3; mine[60] nop
61 f84 lui v0
62 f88 lhu v0
63 f8c nop
64 f90 bne v0,v1
65 f94 li v0,4 (delay)
66 f98 move a0,s0
67 f9c lui a1
68 fa0 addiu a1
69 fa4 jal
70 fa8 li a2,3 (delay)
71 fac move s0
72 fb0 li v0,3
73 fb4 beqz v0,1010   <-- TARGET[73]
74 fb8 move s1,zero (delay)
75 fbc move s3,v0
76 fc0 sll v0,s1
77 fc4 sra a2,v0
78 fc8 sll v0,a2
79 fcc lui at
80 fd0 addu at
81 fd4 lh v0
82 fd8 nop
83 fdc beqz v0,ff8   <-- TARGET[83]
84 fe0 addiu v0,s1,1 (delay)  <-- TARGET[84] addiu v0,s1,1
85 fe4 move a0,s0
86 fe8 jal
87 fec move a1,s2 (delay)
88 ff0 move s0
89 ff4 addiu v0,s1,1
90 ff8 move s1,v0
91 ffc sll v0
92 1000 sra v0
93 1004 slt v0,v0,s3
94 1008 bnez v0,fc0   <-- TARGET[94]
95 100c addiu s2,s2,32 (delay)
96 1010 move a0,s0
97 1014 move a1,zero
98 1018 move a2,zero
99 101c li a3,21
100 1020 jal
101 1024 sw zero,16(sp) (delay)
102 1028 lui a1,0x200
103 102c lui a2
104 1030 addiu a2
105 1034 sw a1,0(s0)
106 1038 lhu v1,0(a2)
107 103c nop
108 1040 sll v0,v1
109 1044 addu v0
110 1048 sll v0
111 104c lui at
112 1050 addu at
113 1054 lw v0
114 1058 lui a0,0xff
115 105c lw v0,8(v0)
116 1060 ori a0
117 1064 and v0,v0,a0
118 1068 or v0,v0,a1
119 106c sw v0,0(s0)
120 1070 lhu v1,0(a2)
121 1074 and a0,s0,a0
122 1078 sll v0
123 107c addu v0
124 1080 sll v0
125 1084 lui at
126 1088 addu at
127 108c lw a1
128 1090 addiu s0,s0,40
129 1094 lw v0,8(a1)
130 1098 lui v1,0xff00
131 109c and v0,v0,v1
132 10a0 or v0,v0,a0
133 10a4 sw v0,8(a1)
134 10a8 lui at,0x0
135 10ac sw s0,0(at)      <-- TARGET[134:136] lui at + sw s0
136 10b0 lw ra
...

So target insns 134-135 are `lui at,0x0; sw s0,0(at)` — the D_801151D0 store, at the very end. Mine has it at 128-129 (before `addiu s0,s0,40` etc). So sched hoisted it.

Now the three diffs:
1. insn 60: target `li v0,3` in the delay slot of bne at 59. This is the outer `n = 3` copy. In source: 
```
if (D_80115126 == 3) {       // bne v1,3
    if (D_8011511A == 3) {   // bne v0,v1
        ot = call; n = 3;
    } else { n = 4; }
} else { n = 3; }
```
Target insn 58-60: `li v0,3; bne v1,v0; li v0,3(delay)`. So the `li v0,3` at 60 is the delay slot of the outer bne — it's the `n=3` from the else arm (or the shared). And insn 72 `li v0,3` is the inner n=3 after the call. So both arms have n=3. The outer bne at 59 is `D_80115126 == 3`; if not equal, else arm sets n=3 (insn 60 in delay slot). If equal, goes to inner check; inner true does call then n=3 (72); inner false n=4 (65 delay slot of bne at 64).

Wait, insn 60 `li v0,3` is in the delay slot of the outer `bne v1,v0` at 59. The outer bne jumps to fb4 (1010? no). Let me recheck: f7c `bne v1,v0,fb4` — if D_80115126 != 3, jump to fb4 (the loop guard, with v0 = 3 from the delay slot at f80). So the else arm `n=3` is exactly `li v0,3` placed in the delay slot. And if equal (fall through), continue to inner check at f84-f90.

So without the opaque `+zr`, the else arm `n=3` is deleted because v0 already = 3? No wait — v1 = D_80115126, v0 = 3 (loaded at f78). The compare bne v1,v0. In the else arm, n=3 means v0=3, which it already is. So the assignment `n=3` is a no-op move and gets deleted; the delay slot becomes nop. With `3+zr`, it's an opaque `addiu v0,zero,3` that isn't recognized as redundant, so it survives and reorg puts it in the delay slot.

To reproduce with real C: need the else-arm value to be a non-obvious 3. Options:
- Read it from a variable that's 3: e.g. `n = D_8011511A;`? No, D_8011511A is compared to 3 in the inner. In the else arm (D_80115126 != 3), we can't assume D_8011511A == 3.
- Use a temp `s32 k = 3;` set at top, then `n = k`? Then k is a register pseudo; `n = k` is a move. But k=3 would be loaded once. Hmm, but then the delay slot would be `move v0,k` not `li v0,3`. Unless k is constant-propagated.

Hmm. What about `n = (s16)3`? A cast of a constant folds.

What about using a bitfield or a different-width assignment that survives? The target needs a plain `li v0,3` (addiu v0,zero,3). 

Alternative: restructure the control flow so the constant load isn't redundant. E.g., instead of loading v0=3 for the compare and reusing, use a different register. But that changes the compare.

Idea: make `n` an s16. Then `n = 3` involves a sign-extension (sll/sra) or the compiler may still li. Actually storing to an s16 local doesn't sign-extend on assignment; it just uses the value. Hmm.

Idea: The HImode-copy trick from moves.md: `u16 i; u16 j` made copies escape cse. For n: `s16 n;` and compare `i < cnt` where cnt is s32... Let me just try declaring n as s16 and see.

Actually wait: the target's `n` is in v0 (word). The loop: `cnt = n;` (s3 = v0), `i` is s16 in s1, comparison `slt v0,v0,s3` — signed compare, s3 is word. If n were s16, cnt would still be word. Let me just test.

2. insn 84: `addiu v0,s1,1` in the delay slot of `beqz v0,ff8` at 83. The beqz is `D_80115158[i].h != 0` (lh v0; beqz). If h==0, branch to ff8 (skip call). The delay slot has `addiu v0,s1,1` = i+1. Then after the call, insn 89 `addiu v0,s1,1` again, 90 `move s1,v0`. So i++ computed twice. The first (delay slot) is a copy reorg inserted from the branch target region (the i++ at ff4/ff8? Actually i++ is `addiu v0,s1,1; move s1,v0` at ff4-ff8 which is the branch target). So reorg copied `addiu v0,s1,1` from the target into the delay slot (speculative, safe because it's just computing i+1). 

Without the barrier, reorg fills the delay slot from the fall-through instead: the fall-through after beqz is `move a0,s0` (call arg setup). Hmm, the comment says it steals `addu a0,s0,zero` from the fall-through. In my version, mine[83] beqz, mine[84] would be `move a0,s0` moved into delay? The diff said mine[83:84] vs target[83:85] — mine has 1 insn, target has 2. So mine's delay slot is a nop? Or mine moved something else. Actually the count difference: mine 143 vs target 144, and target has the extra `addiu v0,s1,1` at 84. So mine lacks that insn entirely; reorg didn't duplicate it.

How to make reorg duplicate i+1 into the delay slot without asm? fill_simple_delay_slots: for a branch, it calls fill_slots_from_thread for the fall-through thread (with opposite flag) and then for the taken thread. It tries to fill from the fall-through first; if that fails, from the target. stop_search_p stops the search on asm/jump/label.

The barrier `__asm__("")` is the first thing in the if-body (fall-through after beqz). So the forward scan from the branch immediately hits the asm and stops (can't fill from fall-through). Then it scans the taken thread (branch target ff8) and finds `addiu v0,s1,1` safe → copies it in.

Real-C way to make stop_search_p true at the fall-through start: put a `goto` or a label there. E.g.:
```
do {
    if (D_80115158[i].h == 0) goto next;
    ot = call(...);
next:
    i++;
    w++;
} while (i < cnt);
```
Here the branch is `if (h==0) goto next`. The fall-through is the call. The branch target is `next:` (label + i++). Reorg would scan fall-through: first insn is `move a0,s0` (call arg setup) — is that safe to move into the delay slot? Moving a call-arg setup into the delay slot is unsafe because the call follows? Actually reorg's `stop_search_p` doesn't stop on a move; it may consider it. Hmm.

Actually the barrier stopped the scan; a label in the fall-through also stops it (stop_search_p returns 1 on CODE_LABEL). So if I put a label right after the branch in the fall-through... but the fall-through must be the call. Could do:
```
if (h != 0) {
    goto do_call;
}
next:
    i++; w++;
    continue;   // or restructure
do_call:
    ot = call(...);
    goto next;
```
That's convoluted and would add a jump.

Alternatively use `do{}while(0)` per C0535 to create a label? A do-while(0) block creates a CODE_LABEL at the end maybe. Hmm.

Let me reconsider: maybe a cleaner real-C approach for the whole loop. The target loop shape:
```
i = 0;
if (n != 0) {
    cnt = n;
    do {
        if (D_80115158[i].h != 0) {
            ot = call(ot, w, i);
        }
        i++;
        w++;
    } while (i < cnt);
}
```
The barrier is inside the if-body head. What if we reorder so that the if-body starts with a `do{}while(0)` wrapper? That creates a label/insn boundary that stops the scan.

C0535: "do{}while(0) around two copies splits cse1's EBB so sched1 keeps their birth order". Maybe a `do { } while(0);` at the head of the if-body acts as a barrier-like boundary for reorg? stop_search_p stops on... let me check reorg.c stop_search_p.

Let me look at reorg.c stop_search_p.
