---
ts: 2026-11-06T11:35:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IUxu9GQlBmiJoCdGrxUZ
---
It needs a work dir with <fn>/t.c — from rtu_match. Hmm. Alternatively I can produce a scratch spliced TU from the --try scratch (with --keep) — but the scratch dir is removed unless --keep. I can run with --keep and then feed that .c to cc1_dumps_tu.sh with DUMP_ROOT under my item dir.

But dumps are heavy; disk capped. Do it only when unsure.

Let me first reason about the code. Target (from the diff positions, target indices):

Around 50: `li v1,8; sb v1,3(v0); li v1,56; move v1,s2;` ... so target does:
- p[3]=8 store early (right after p+=8)
- li v1,56 -> p[7]=0x38 store (56=0x38)
- then move v1,s2? (s2 = y?)
- sh a0,8(v0); sh v1,10(v0) — stores vx,vy
- lw t1,16(sp) — hmm 16(sp) is w_? Actually args: x,y,w_,h_ in a0,a1,a2,a3, then c1..c6 on stack at 16,20,24,28,32,36. Wait `lw t1,16(sp)` = c1. and `addu s1,s1,t1` = x += w_? No: x += w_ means x is s1? Hmm addu s1,s1,t1 where t1 = lw 16(sp) = c1. That doesn't fit x += w_ (w_ = a2). Hmm.

Actually maybe s1 = x and t1 loaded from stack is... the params after 4 registers are c1..c6 at 16(sp)... yes c1 at 16(sp). So `addu s1,s1,t1` = x += c1? No wait. Let me re-read the source: `x += w_;`. Hmm.

Hold on: maybe the compiler didn't inline x/y as s1/s2? Let me get the actual full target listing. Use --keep and dump candidate object, plus find baseline object. Actually dt.sh output only diffs. Let me write a small script under G30 that prints the full target and mine disassembly? There may be a helper: .run/P40/T11/bin/sc.sh scores candidates only.

Simplest: run dt.sh with a body that is orig.c (score 0) — diff empty. Not helpful.

Alternative: objdump the baseline object for func_80015B6C. Need the object. Let me find which build object contains the symbol: grep the .o files? `nm build/src/*.o | grep func_80015B6C`. Let me do it with a loop, output small.
