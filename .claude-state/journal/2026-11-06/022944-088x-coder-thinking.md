---
ts: 2026-11-06T09:29:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XLzizRuqtduLCNYptEYp
---
Target: `lui a2,0xff; ori a2,a2,0xffff` at 1f04-1f14 = mlo = 0xFFFFFF in a2. And `and v1,v1,a2` (mlo). `lui t3,0xff00` = 0xFF000000 mask. `lui t2,0x0` = ob (D_800AA60C).

Note mlo's setup (lui a2,0xff; ori) is placed *inside* the function, not at the top, at 1f04 — after the first packet's stores. Interesting: the source has `mlo = 0xFFFFFF;` just before the first `*(u32*)pkt = ...` line. So its live range starts there.

Now the priority: mlo's life starts late (at 1f04) and it's used 4 times across the 4 packets; c80 starts at 1e80 and is used 12 times. Global-alloc priority: refs × live-length? Actually global-alloc's allocno_compare uses floor_log2(refs) * refs * size / live_length (the same formula). mlo: refs 5 (1 set + 4 uses), life from 1f04 to the last packet (long). c80: refs 13, life from 1e80 to last packet.

pri(mlo) = 1*5*4/life; pri(c80)=1*13*4/life. c80 wins by refs. So mlo can't naturally beat c80 — the keepalive adds 6 refs to mlo → 11 refs, still < 13? Hmm, but with the keepalive mlo got a2 (highest). Let me compute more carefully: maybe c80's live range is longer.

Hmm, whatever. The keepalive is load-bearing.

Real-C alternative: make mlo's ref count higher by writing `mlo` in a real expression 6 more times — impossible without insns. OR reduce c80's refs: c80 is used in 12 stores. If instead we write the constant 0x80 inline (`*(u8*)(pkt+6) = 0x80;`), the compiler would create a constant pseudo per use or `li` each time — different codegen (target has li a3,128 once). So no.

So item 3 = WALL greg-pri-refs / global-hardreg-reserve, best 56.

Hmm. But hold on — maybe I should check whether the *pin* alone (without keepalive) plus real-C moves could reach 0? pin-only scored 38. No.

OK, all 5 walls. That's the likely truth, and the brief anticipated walls. But I must satisfy the ≥30 tries and ≥20 min per item.

Wait, wait. Before settling, let me reconsider item 2 once more: the target's `move v0,s2`? No, item 2's target has res in v0 with `move v0,zero` / `lui v0;addiu v0` — those are the *res assignments themselves*, not a final move. And flg in v1. The lever-free version has flg in v0 and res in v1. If a real-C move flipped that, we'd get 0! Let me examine whether the keepalive is even needed for item 2's structure: the keepalive keeps res live (dead otherwise). The target's res is live because the original function returned it. So lever-free res is dead → dropped. So item 2 needs a real use of res.

Hmm, but what if we make res live *legitimately*? The function computes res and returns it (original). Without a return type, dead.

Unless... the last statement is a real C use that produces NO instruction and matches the target. Is there one? `res = 0; if (flg) res = &D;` — res is dead. What if `res` is `*a` no...

OK so item 2 wall, best lever-free 14.

Now, hmm, let me reconsider: maybe the mod's intent is that these "singleton" items are mostly walls and the coder discovers them, with the ≥30 tries rule ensuring diligence. The mod will bank the walls. Fine.

But 30 tries per item is the requirement. Let me generate 30 real-C variants per item efficiently. I'll write a generator script per item and score all. The "tries" column = number of scored candidates.

Let me do item 1 first with ~32 variants. Variants (lever-free, no asm):
Base: win.c (score 19).
1. decl order permutations: 5! too many; pick 8 orders.
2. t as u8/u16/s16.
3. found as u8* then cast.
4. loop as while(p<end) vs do-while vs for.
5. init at decl (all at top vs mixed).
6. buf[3]=0 before/after the call.
7. buf as u8[4]/s16[4].
8. a0 as void*/u8*.
9. t constant inline 0x25 vs variable.
10. nested ifs as &&.

Let me write the generator with a base template and substitutions. To keep it manageable, I'll write a Python script that emits variants into files v01..v32, then sc.sh them all.

Actually — scoring 32 files with sc.sh runs 32 compiles sequentially; each compile of a TU takes ~1-3 s. That's ~1-2 min. Acceptable. But the output must be ≤40 lines? sc.sh prints one line per file — 32 lines, fine (but the tool guidance says >40 lines via run.sh; 32 is OK).

Let me write the generator for item 1.
