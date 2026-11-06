---
ts: 2026-10-22T15:56:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TnskZUy0ocw9Ryh1Bnkj
---
The scratch header has my c_struct body (no launder). But the cse2 dump I read shows an asm_operands at insn 23 and the loads from reg 5 a1 with symbol_ref. Wait — maybe the dump's `func_8012B4B8` region I read at line ~15440 is the one from the scratch header, and the asm_operands is... no, my body has no asm except the obj pin `register int obj __asm__("$16")` — that's a register declaration, not an asm statement. But insn 23 is `(set (reg/v:SI 5 a1) (asm_operands ...))` — that's the launder.

Hmm wait, maybe the TU includes the header *twice*? Or the .i has multiple copies? The TU ov_MAIN_012.c might include the header multiple times? No.

Hold on — maybe the cse2 dump file is from the dump of a *different* candidate because cc1_dumps_tu.sh used `$(ls $wd/*/t.c)`? No, I passed a .c file.

Wait, I passed `$s/ov_MAIN_012.c`. The script does: `if [ -f "$wd" ]; then tc="$wd"`. Yes, it's a file. Then cpp with `-I$(dirname $tc)` = the p6 dir, `-Isrc/shared`. The p6/ov_MAIN_012.c probably includes `shared/ov/func_8012B4B8.h`? And p6/shared/ov/func_8012B4B8.h has my body. But the dump shows the launder... 

Unless the .i file came from a *cached* dump dir? The script does rm -rf "$d"; mkdir -p. So no.

Let me grep the .i file for 'Mat32 *)m' and for 'launder'.
