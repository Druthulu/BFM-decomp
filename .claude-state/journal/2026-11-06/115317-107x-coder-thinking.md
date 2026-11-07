---
ts: 2026-11-06T18:53:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tlNPyZzAD8RAm90rLRfT
---
WAIT. This g007 asm is completely different! `move $5,$7` at the top (a7 and v1 merged!), `lhu $2,0($5)`, `addu $5,$5,104`, `addu $7,$7,104` in the delay slot... and the else branch is tiny (lhu $3; sh $3,0($5)) — the stores are missing!

This doesn't look like the function at all. It seems my dbody7.c is wrong: I copied g007.c (which has the header content? no, g007.c is a full function body with externs?). Hmm, g007.c = head + loop + tail. The head includes the externs? No — the header's extern declarations are in the original header (lines 3-9), but my gen.py's head does NOT include them! The gen.py head starts with `unsigned short *func_80146750(...)`. So g007.c lacks the extern declarations for D_8011FD10 etc. → the compile would fail... but it compiled (score 2), so delever_search's --body replaces only the function definition in the header, keeping the externs. My standalone dbody7.c lacks the externs → implicit declarations → wrong code.

OK, so the standalone dumps for g-variants are invalid. The dt.sh scores are still valid (they use the header with externs).

Let me get the g007 asm properly: copy the scratch header (which has the externs) with g007's body. Let me do: take the original header text and replace the function body with g007's, then pad and compile.

Simpler: use delever_search --keep on g007 (which creates the scratch header), then copy that header to a .c + padding.

Let me do that.
