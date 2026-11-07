---
ts: 2026-11-06T01:29:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_M1nD7tha98ciYlh6nSl3
---
Wait, the first item's def at 4089 is the one. The barrier is the `__asm__ __volatile__("");` at the end of `zero:` block. Need a lever-free body scoring 0, meaning replacing the cross-jump barrier with real C.

Note comment: find_cross_jump merges this block's trailing `sw $v0,0x1C($s0)` with the identical one ending the `dec:` block. So `zero:` ends with `unk1C = 0x1D;` (store) and then barrier; `dec:` ends with `unk1C = unk1C - 1;` (store). Hmm those aren't identical stores... but the barrier comment says identical `sw $v0,0x1C($s0)`? Wait `zero` stores 0x1D, `dec` stores decrement. Unless... hmm, "this block's trailing sw $v0,0x1C($s0)" — perhaps after the store in zero the `func_8012B200` returns... Let me look at the actual target assembly. Let's check delever_search and how it scores. Let me look at the worked example notes for barrier items and how a barrier got cracked. Search moves.md for MATCH with barrier.

Also, there's a subtlety: the barrier is at the end of the function, before the closing brace. Cross-jump between zero's tail and dec's tail.

Real C move candidates: make the two blocks non-identical so cross-jump doesn't merge; e.g. change the order of statements in zero, or compute the value differently, or use a temp for the constant.

But the trick: any change that alters the emitted code elsewhere breaks the match. The store `sw $v0, 0x1C($s0)` where $v0 = 0x1D in zero and $v0 = loaded-1 in dec. How could these be byte-identical? The instruction bytes include the register operands: sw $v0,0x1C($s0) both. So the final instruction sequence of the block is identical, thus cross-jump merges the tails (the trailing identical insns), causing a branch to skip.

Hmm wait, dec: `unk1C = unk1C - 1; return;` compiles to lw $v0, 0x1C($s0); addiu $v0,$v0,-1; sw $v0,0x1C($s0). zero: ...; li $v0, 0x1D; sw $v0,0x1C($s0). So the common tail is just `sw $v0,0x1C($s0)` (maybe plus jr ra? no, returns differ? both return). Actually cross-jump would merge from the `sw` instruction: after merge, zero's block jumps to dec's `sw`... that changes length by -2 (branch + delay nop vs sw). So target wants them separate.

Lever-free ways to prevent cross-jump: make the final stores not identical. E.g., in zero use a different register to hold 0x1D? That changes the code (target has $v0). Or reorder so the last store in zero is not last — e.g., move `CAST_WIDTH(s16,a0,0xF4)=0;` after `unk1C=0x1D;`? That changes store order in emitted code, breaking match (unless the target order matches). Need to see target asm.

Let me check the build to get the target assembly. delever_search compares against function in build/. Let me run a quick score of the original body to see baseline.

Actually the workflow: copy current def into <dir>/orig.c, then create nopin.c with the lever removed, and iterate win.c. Let's do that. First check what delever_search expects as body file: `--body` reads a file containing the function body? The dt.sh passes $f = candidate body file. Let's check tools/delever_search.py --help.
