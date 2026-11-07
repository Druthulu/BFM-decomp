---
ts: 2026-11-07T00:55:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9rTIF3NtVTEh1gQRWVE4
---
Good. Now let me get the approach note out and then start item 1.

Approach note (PA2 X1): 
- Item 1: strip the two launders and five pins; the plain-C body must reproduce 101 ins. The target register map (b=s0 c=s1 a=s2 p=s3) is set by global-alloc priority, where plain C gives p a priority far above a/b/c, so p takes $s0. I'll try real-C moves that raise b/c/a ref counts or shorten p's live range... hmm, actually to lower p's priority relative to b. Priority = refs*8/live. p has 11 refs/29 live = 3.03... hmm 11*8/29 = 3.03, but notes say 11379? That's a scaled priority (floor(floor(refs*8/live)*1000)?). global.c allocno_compare uses (floor(allocno->n_refs * 8 / (allocno->live + 1)))? Anyway.

Wait — but that note is from the prior attempt's analysis of the *unpinned* body: "plain C priority p(11 refs/29 live)=11379 >> b 3333 > a 1944 > c 1666". To get target b=s0 c=s1 a=s2 p=s3, p must rank lowest. Ref count on p is high (11 refs) because of all the p[] stores and p+=5. Hmm, p's live range 29.

Moves to lower p's priority: make p block-local? Split p into two vars? Use q for the first block too? Actually p is used for p[0..3], then p += 5, q = p. What if we write the first stores through a temp pointer and drop p usage... but p is a parameter, its allocno is the param pseudo. Hmm.

Alternatively raise a/b/c: b is incremented in the loop (b += 8), a <<= 4, c used in cs and q[2].

The target has b=s0 c=s1 a=s2 p=s3. The param regs in the target: incoming params are a0,a1,a2,a3 (p,a_,b_,c_). The target copies: b=a1? Let's actually look at the target dump. That would tell us what's happening. Let me get the target instructions for item 1.

Where are target dumps? T10 dir has tgt_ov_*.txt files. Let me look at the one for SC03_099.

Actually item 1's first includer is MAIN_012. The prior attempt instrumented ov_SC03_099. Hmm, the header is instantiated by 141 TUs. The target function in each includer's object is the same code but the surrounding/relocations differ? No — score compares function instructions with relocation masking, so all includers should have the same function bytes (except relocations). But prior note said "tree's own header scores 77 via first includer MAIN_012" — that was in T10 with an older tool version; now calibration gives 0. Good, the tool improved (S103 header shadow).

Let me look at the target dump to understand. .run/P40/T10/func_80177940/tgt_ov_SC03_099_jr_801734BC.txt. Is that over 20,000 chars? Probably small. Let me check size first.
