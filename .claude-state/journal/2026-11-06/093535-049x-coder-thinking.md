---
ts: 2026-11-06T16:35:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9XC2K3uaMUMKBuYTAM4o
---
Same flags. So the .i content must differ. Perhaps the real build's cpp includes `-Iinclude` etc. and the file's `#include` chain brings in different macros? My cpp used -Isrc/shared and -Isrc extra (harmless) and same -D flags. Hmm.

Wait — maybe the difference is that the real build uses the `.d` dependency and `$(CPP)` is a different cpp? Let me check CPP variable.

Actually, maybe the difference is the *file*: build/src/ov_SC05_007/ov_SC05_007_jr_8017BEBC.o was built from src/ov_SC05_007/ov_SC05_007_jr_8017BEBC.c but perhaps the .o is STALE (built from an older source, e.g., before the pins were added/changed). That's plausible! The build may be from the fleet run at some earlier time. The delever_search oracle compares against build/ — the "tree's own bytes" per its docs, with a SHA1 check. Hmm, the docs say the baseline object under build/ is the tree's own bytes "proven by the SHA1 check". If the src changed since, delever_search would report UNCALIBRATED (its control: score tree's own text must be 0). We ran orig.c (the tree's text) and got score 0 → calibrated. So the build matches the current src text.

Therefore my splice/dump must differ in the .i. Let me diff: maybe my cpp invocation lacks `-MMD -MP -MT` (irrelevant) or the include paths differ: the Makefile's CPPFLAGS has no -Isrc/shared! How do the TU's includes resolve then? Let me look at the TU's includes: the .c file probably includes "../shared/..." relative to its own dir → src/shared. Right, relative includes resolve without -I.

Hmm so what differs? Let me compare my generated o1.s function against the build object more carefully. My o1.s:
```
addu $4,$4,$0
lh $2,170($4)
...
lw $2,32($4)
#nop
lhu $2,24($2)
j $L348
sh $2,256($4)
$L347:
lw $3,220($4)
lhu $5,24($5)
...
```
Wait `lhu $5,24($5)` — $5 (a1) used as both base and dest, but where was $5 set? That looks broken — likely the source `q`/`g`... Hmm this looks like the pinned body where g is pinned $3 (v1) and f $2 (v0). The pins are asm register variables: `register s32 f __asm__("$2")`. But cc1's `__asm__` register vars... in gcc 2.7.2, `register int x asm("$2")` is accepted. In my dump, disposition "73 in 4 75 in 2 78 in 2 81 in 5" — hmm.

Oh wait! Maybe my spliced .i has a problem: the body text from orig.c contains `register s32 f __asm__("$2");` and when I splice it into the .i, it's fine.

But hold on — in o1.s I see `lhu $5,24($5)` with no `lw $5` before it. That suggests my assembly listing is from a *different function*? Let me re-read: the sed printed from `^func_8017EAD8:` to `.end func_8017EAD8`. The lines:
```
	addu	$4,$4,$0
	lh	$2,170($4)
	sh	$0,92($4)
	sh	$0,152($4)
	bne	$2,$0,$L347
	sw	$0,28($4)
	li? no...
	lw	$2,32($4)
	#nop
	lhu	$2,24($2)
	j	$L348
	sh	$2,256($4)
$L347:
	lw	$3,220($4)
	lhu	$5,24($5)
```
`lhu $5,24($5)` is definitely invalid (uses uninitialized $5). So the dump's assembly is malformed — maybe my cc1 invocation with -d flags perturbs codegen? Dump flags shouldn't. OR the .i splice broke something (e.g., I removed the closing brace or a line). Let me check the c1 assembly from cc1 with dumps vs the actual build. c1.s looked sane.

Hmm wait, o1.s is the *pinned* body which is the tree's text; the tree's build gives a different (correct) result. My o1.s seems corrupted: `lhu $5,24($5)`. Maybe the dump flags -dd/-dJ etc. cause a different path? No...

Actually maybe the issue: -dJ (jump2 dump) etc. are fine. Let me instead run cc1 WITHOUT dump flags on the spliced .i and compare its .s to the build object. That isolates whether my splice is faithful.
