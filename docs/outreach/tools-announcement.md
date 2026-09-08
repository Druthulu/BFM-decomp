# Outreach: the tools announcement (post-flip)

> **Where:** the decomp community Discord's tools channel, and/or a row on the Decompedia (decomp.wiki) tools page.
> **When:** after the flip, once `github.com/Druthulu/xsig` has its topics and the README's "Tools from this project" section is
> live. **Who:** Drew, in his own voice; edit freely. Written the way a developer posts, no code spans, no AI acknowledgement
> (rule candidate (j), S89).

**Discord post:**

```
I made a small tool while doing the Brave Fencer Musashi decomp that might be useful to other PS1 projects: xsig (https://github.com/Druthulu/xsig). It hashes functions with the relocated fields masked out, so the same function at two different link addresses gets the same signature. I used it to find shared code across overlays (2,220 groups in BFM) and to check other games: against Xenogears, Vagrant Story and Tomba it found 103 shared functions, all PsyQ library code, so mostly it's good for spotting library functions and shared overlay code. Stdlib only, MIT, has tests. The full decomp is at https://github.com/Druthulu/BFM-decomp if anyone's curious, everything's matched.

Next step for it is going past exact matches: try the 1:1 first, then widen to same-shape functions (registers and immediates masked, then same structure) and eport which tier matched and what differs, so it also finds near-copies across overlays and across games, not just library code. That's the v2 I'm starting on.
```

**Decompedia tools-page row (if the page takes rows):** name xsig, language Python (stdlib), license MIT, platform MIPS /
PlayStation-era, one line: "relocation-masked function signatures for finding shared code across overlays and across games",
link to the repo.

**The v2 sentence rests on** `docs/gen3-handoff.md` §7 (xsig v2, recorded 2026-09-08): 1-to-1 first, then the sequence tier, the
structural family and atlas cousins, returning the matched tier and the difference — the in-tree pieces exist; the port is the work.
No date is promised in the post.

**Facts the post rests on:** `tools/xsig/README.md` (the worked example: 103 hits across three games, all library; 126 against
Tomba with one 19-instruction non-library HIGH), `config/dedup.us.yaml` (2,220 groups), the E4 log entry (8/8 tests).

## The decomp.me Discord `#ai` channel reply (Drew, 2026-09-08 — drafted from the record, his words to edit)

> Context: people in that channel were describing the trouble of keeping an AI assistant on track. Facts the draft rests on:
> `docs/verification.md` (218/218 from a clean rebuild), `docs/gen3-standards.md` (the definition of matched; names only with
> evidence; sotn's style guide adopted), `docs/how-to-ai-decomp/` ch.01 (governance), ch.04 (oracles), ch.12 (the failure museum),
> `docs/retrospective.md`. No number in it is typed from memory. Linked: the how-to index, the governance chapter, the kit page.

```
I ran into the same thing doing Brave Fencer Musashi (PS1). Ended up at 218 binaries rebuilding byte for byte
from C, and honestly the model was never the hard part, the setup around it was. What kept it on track:

The only definition of done is the community one: instruction-identical including register allocation, and
the whole-binary hash equal to the original, checked on every build. Nothing "functionally equivalent" ever
counted, so the assistant can't talk its way to a match. What isn't ours is said plainly (1,256 Sony library
objects linked, five hand-written asm routines kept verbatim).

Names only with evidence. If nothing proves what a function is, it stays func_XXXXXXXX. Wrong names are
worse than none, so we adopted the sotn style guide for the cleanup rather than inventing one.

The rules grew from actual failures, not from a prompt. Every session starts by re-reading them, every
session ends with a checkpoint file the next one replays word for word, and one task closes before the
next opens. The compiler quirks got solved by reading the gcc 2.7.2 source, not by guessing.

I wrote all of it up, including what went wrong, which is the more useful half:
https://github.com/Druthulu/BFM-decomp/wiki/How-to-AI-decomp
Chapter 1 is the on-track part, chapter 12 is the failure list. If you're starting a project from zero
there's a starter kit page too: https://github.com/Druthulu/BFM-decomp/wiki/Start-a-new-decomp-project
```
