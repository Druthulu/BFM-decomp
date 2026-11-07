---
ts: 2026-11-06T01:44:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_M5NSOGIseSCUHehUvDVQ
---
So .jump = after first jump pass, .rtl = after RTL generation (line 2702). Good.

So vA's .jump2 shows merge. Let me re-examine vA's .jump (first pass) to see whether the trailing jump survived that pass. Earlier tail of jump_vA.rtl showed the store then note then label — jump gone. So in the FIRST jump pass the jump was deleted. And the merge (label 386) — was it created in the first pass or jump2? In vA's .jump dump, is there a label 386 before the store? Let me check.

If the merge happened in the FIRST pass, that contradicts cross_jump=0. So the merge is in jump2. But then, at jump2's start, zero's jump was already deleted (in the first pass). Hence the merge at jump2. So the deletion of zero's trailing jump in the first pass is what matters.

So: the first jump pass deletes zero's trailing jump (jump-to-next). Where? Let me find the code that deletes a simple jump to the next insn. Search jump.c for "reallabelprev == insn" — only condjump. Hmm, but maybe `delete_jump` is called via "Detect a jump to a jump"? Or via the `redirect_jump(insn, NULL_RTX)` → RETURN, and then the RETURN insn is deleted because... Actually! Maybe the RETURN insn, once created, is subject to the `#ifdef HAVE_return` block at the end which... no.

Hmm, let me look at line 1602 delete_insn context (jump-to-jump) and 1417.

Alternatively — maybe the trailing jump in vA was never emitted by the expander, and the .rtl dump I read (rtl_vA.rtl) was actually from a different function/scratch. The .rtl dump tail showed jump 368 to label 374. That was from dumps_vA/vA.i.rtl. OK.

Let me test differently: does the *first* jump pass delete it? Compare .rtl vs .jump for insn 368: .rtl has it, .jump doesn't. So yes.

Let me find the code by searching for "NEXT_INSN (insn)" patterns or the phrase "jump to the next". Search for "== next_active_insn" or "next_nonnote_insn (insn))".
