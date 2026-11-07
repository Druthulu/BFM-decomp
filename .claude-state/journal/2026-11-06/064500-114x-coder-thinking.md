---
ts: 2026-11-06T13:45:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7sK5s39V4lypM5bqBHyP
---
None better than 2. v6 (swap ww/hh order) also 2. Hmm.

The barrier-free A gives score 2 with the lbu sunk by 2. Need to prevent that sink.

Ideas:
- The lbu loads `h` from the stack (parameter). The use of hh is later. sched1 sinks it.
- In the target, the lbu is early. The barrier prevented the sink.

What if we make hh used earlier? The first use of hh is `pkt->v2 = pkt->v0 + hh;` much later. No.

What if we change the *parameter* handling: h is a u8 K&R param. `hh = h;` is a load. Could we avoid the load by using h directly? Then the load would happen at the use site (later) — worse.

What if we make hh's assignment depend on something that's scheduled early? E.g., `hh = h; ww = w;` (v6) still 2.

Hmm. What about the *order of the loads*: target has lbu t6 (w) then lbu t7 (h) adjacent, then the D_800A5E60 lui/lw. Mine has lbu t6, then lui/lw t0, then lbu t7.

sched1 placed the lui/lw between the two lbu's. Why? The lui/lw is the D_800A5E60 load; it's used by `pkt = D_800A5E60; D_800A5E60 += 0x28;` — the store back to D_800A5E60 depends on it. 

To keep lbu h before the lui/lw, hh's insn must have higher priority. Since it's a leaf (no successors except the distant use), it's low priority.

What if `hh = h;` is written as `hh = h + 0;`? fold. `hh = (u8)h;`? h is u8 already.

What if we use hh in an expression right after that folds but creates a dependency... e.g. `rgb = rgb + hh - hh;`? fold.

Hmm, what about making the lbu *part of a chain* with ww? e.g. `ww = w; hh = h; rgb = 0x808080;` — reorder so hh is earlier in source? v6 put hh before ww and still 2.

What if we move the hh assignment AFTER the pkt lines but before the gte macros? Target has it early, so no.

Hmm, what if the lbu is made non-sinkable by a *dependence on the stack pointer adjustment*? No.

Let me look at the actual sched: maybe the lbu is placed in the load-delay slot of the D_800A5E60 lw. The target leaves a nop there (no, target has lui after lbu t7).

Alternatively: make the D_800A5E60 load come *earlier* than the lbu? Target has the lbu first.

OK, what about the `hh = h;` assignment being moved into the `pkt` statement? e.g., `pkt->v2 = pkt->v0 + hh` uses hh later.

Time check: 06:44. Item5 started 06:42. Let me try a few more ideas for A, but also consider that maybe barrier A is genuinely hard (2 off). But B and C are bigger. Let me look at B and C first — maybe cracking them makes the combined body closer or reveals a global approach.

Actually, wait: the individual scores: A alone 2, B alone 30, C alone 8. The combined is 40. If I fix A (do-while) but leave B and C, then fix B and C... Let me first crack A with more tries, then B, then C.

For A, one more idea: the pins. hh is NOT pinned. ww/hh are plain s32 locals. What if hh's load is scheduled late because the pseudo's live range is long? 

What if we add a *use* of hh early that's dead: e.g. `if (hh == 0xFFFF) { }`? A compare + branch, code changes.

What about `hh = h; ... pkt->code = 0x2C;` — hmm.

What if we write `hh = h;` as `hh = *(u8 *)((char *)&h);`? Same load.

What if the assignment order is: rgb, cyy, zf, tpp, ww, hh — and the D_800A5E60 lines follow. The scheduler interleaves. If we make the pkt lines *depend* on hh, the lbu must come first! E.g., `pkt = (FT4_801857A4 *)D_800A5E60; ... pkt->v2 = pkt->v0 + hh;` — the v2 assignment is later. 

What if we move `pkt->v2 = pkt->v0 + hh;` earlier? It's at the end of the block; moving it changes the order of stores (target has v0/v1/v2/v3 in a specific order).

Hmm.

What if we use hh in the address computation of pkt? No.

OK, alternative: maybe the answer for A is a *different* real-C that changes the register/scheduling such that the target's order is reproduced by chance. v6 gave 2 (same). Let me look at v6's diff — is it the same lbu issue?

Let me check a couple of other shapes:
- Assign hh from a temp: `s32 t = h; hh = t;` — adds a move, no.
- Put `hh = h;` inside the same statement as something else: `rgb = 0x808080, hh = h;`? comma expression — same insns.

Hmm.

Actually! What about making the *D_800A5E60 load* later by splitting its group? In mine, the lui/lw of D_800A5E60 is placed between the lbu's. If the pkt group were in a do-while block, maybe the lbu's stay together. v5 (do-while around pkt lines) gave 8 with 150 ins (worse). v4 14/150.

What about a do-while around the gte macros? no.

Let me try: do-while around the `ot = ...` line or the whole pkt+ot+code group; and reordering the pkt group after the rgb stores.

Actually, maybe simpler: in the target, the order is lbu t6; lbu t7; lui t0; lw t0. In mine: lbu t6; lui t0; lw t0; lbu t7. The scheduler interleaved. What if I reorder the source so that the `pkt` lines come BEFORE `ww = w; hh = h;`? Then the lbu's would be after the pkt load — but the target has them before. No.

What if the source assigns hh and ww *after* rgb/cyy/zf/tpp but the D_800A5E60 code comes later in source — it already does.

Hmm, what if we make hh a pinned register? That would add a lever of another kind (not allowed to add pins). No.

Let me move on to B and C and come back to A if time permits.

Barrier B (line 68): after `tpage = ...` before the getClut. Removing gives 30.
Barrier C (line 75): after `uu = ...` before `vv = sv;`. Removing gives 8.

Let me look at C first (score 8).
