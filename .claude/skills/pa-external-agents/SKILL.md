---
name: pa-external-agents
description: External coders in a PA 3.3 project — a task's coding on an OpenRouter or local model through tools/pa_ext.py, while experts, retrievers and Claude stay on the subscription. The setup, the check, the project settings, the plan's coder field and the troubleshooting.
---
# External coders

An external coder is our `pa-coder` running on another provider's model, in its own headless Claude Code process,
started by the task's expert with `/usr/bin/python3 tools/pa_ext.py run`. Only the coding moves: experts, retrievers, the
planner and you stay on Claude.

What it keeps from an in-house coder:
- the same instructions and house rules, and the same allow and deny rules;
- PA3's guards, its journal entries and its cards ("External coder · T4.c1", naming the model).

What differs:
- Its lookups go through `/usr/bin/python3 tools/pa_ext.py ask "<question>"`. The mod spawns `retriever-code` (Haiku, on the
  subscription) and the answer comes back.
- Corrections reach it at its next tool break.
- A command no allow rule covers is denied rather than judged by auto mode.
- Its tokens are cash on the provider's key. The statusline's External line shows them; they never count as
  subscription usage.

## Setting up (once per machine, per backend)
1. The developer creates a key on openrouter.ai with a **credit limit**. It is never pasted into chat: anything typed
   here stays in the conversation log.
2. They run the setup in a normal terminal, never through `!` (it reads the key with hidden typing):
   - Windows: double-click `%USERPROFILE%\.claude\pa3-src\project-architect-3.0\setup-external.cmd`;
   - Linux and WSL: `sh ~/.claude/pa3-src/project-architect-3.0/setup-external.sh`.

   Its questions are the URL (Enter for OpenRouter), a name, the key and the model ids (e.g.
   `deepseek/deepseek-v4.1-flash-1017`). It tests each model and saves nothing on a failure.

   Which model: DeepSeek V4.1 Flash is the one PA3 tested end to end and recommends. GLM-5.3 Flash passed easy and
   medium tasks at max for about three times DeepSeek's price, but most of its hardest attempts ran out of time and
   its hosts were unreliable. Qwen3.8 Flash passed nearly everything it finished, at 6 to 11 times DeepSeek's price
   per task, because its only host barely caches. The wiki's External coders page has the numbers.
3. The setup then lists each model's hosts, best first: fp8 or better before fp4, ranked by a typical coder run's
   cost. It names the recommended host and the guardrail line.
   - The developer adds a **guardrail** on the key at openrouter.ai, allowing that host. Claude Code cannot choose
     the host, so without the guardrail OpenRouter spreads requests over 20 or more hosts. Some cost twice as much,
     and some serve fp4 copies that code worse.
   - One guardrail covers a whole key. When two models are best on different hosts, use **one key per model** (one
     config each, e.g. `openrouter-deepseek` and `openrouter-glm`).
4. The setup's result reaches you at the developer's next message. Explain a failure from the table below. On a
   success, run `/usr/bin/python3 tools/pa_ext.py check` and show its lines, then go on to the project's settings.

The key lives only in `~/.claude/pa3-ext/<config>/settings.json` on that machine. A project that runs in WSL needs
the setup run in WSL too.

## The project's settings (yours to write, from the conversation)
Ask the developer per config and per model what each is for, then write exactly that with `/usr/bin/python3 tools/pa_ext.py set`:
- `--coder <config>/<alias>`: the default coder for tasks the plan does not name (`--coder in-house` removes it);
- `--lanes <config>=4`: how many run at once per backend;
- `--max-coders <n>`;
- `--escalate in-house`: who takes over a failed run;
- `--effort max`: the external coders' reasoning effort. The default is high (`--effort default` returns to it). Max
  is for the hardest work, where DeepSeek solved one more task in ten for about half as much again, and for GLM,
  which fails easy tasks at high;
- `--use off`: not used in this project;
- `--remind off`: stops the session-start reminder.

`/usr/bin/python3 tools/pa_ext.py set --show` prints the block. Never edit pa.json's `external` by hand; the developer may.

Then write the how and when, in the developer's words, as a section of HOW_WE_WORK.md of at most three lines, e.g.:

    ## External coders <!-- roles: claude expert planner -->
    Cracking waves: openrouter-deepseek/deepseek replaces the in-house coder; a failed run escalates in-house.
    Design and judgment tasks stay in-house.

Updates never touch that section or pa.json's `external`.

## In plans
A task's `coder:` names `<config>/<alias>`, `in-house` or `none`. With no `coder:`, pa.json's default applies. The
planner recommends one per task with a reason in `note:`, and the developer changes any of them in the plan view.

## Learning from each run
Each external model and each codebase brings its own friction: DeepSeek chained `cd` into commands, MiniMax gave up
early, and bfm's coders needed its disassembler. PA3 learns it run by run:
1. A finished external coder's report ends with `HEALTH` lines when it met friction: denied commands by kind (no
   allow rule covered them; auto mode cannot judge for an external coder), sandbox and read-guard failures, retries.
   `/usr/bin/python3 tools/pa_ext.py health <label>` prints them for any run, running or finished.
2. The task's expert reads them against its brief, corrects the coders still running, and ends its report with
   `EXT-HEALTH:` proposals for later coders. The mod sends them to you.
3. Tell the developer each proposal in plain words with its evidence, and apply only the ones they approve:
   - `/usr/bin/python3 tools/pa_ext.py set --allow "<rule>"`: an allow rule in the project's `.claude/settings.json`. Prefer a
     narrow one, a command and its prefix (`Bash(mipsel-linux-gnu-objdump:*)`). A rule that lets coders run scripts
     they write (`bash .run/…`) is looser than auto mode, which judges each command: say so when they decide.
   - `/usr/bin/python3 tools/pa_ext.py set --note "<text>"`: a note for every external coder in this project (`set --show` lists
     them, `--drop-note <n>` removes one).
   - `/usr/bin/python3 tools/pa_ext.py set --model-note <config>/<alias> "<text>"`: a note for every coder on that model, in
     every project (`~/.claude/pa3-ext/<config>/notes/<alias>.md`, one line each; the developer may edit it).

   End each note with its evidence and date, e.g. `(T11, 2026-10-21: 6 of 9 walls after 1-2 tries)`, so a later
   review can drop one that stopped helping. The next coder started gets every note.

## Costs and safety
- The launcher pins every model setting to the chosen model, and each run reports any other model it saw (`LEAK:` on
  the report and in red on the statusline).
- Claude Code's own cost figure for these models is meaningless; the ledger prices them from its own rows.
- OpenRouter's key figures lag a few minutes.

## Troubleshooting
| What it says | Why | Fix |
|---|---|---|
| `401` | wrong or revoked key | new key, run the setup again (update the config) |
| `402` | no credit, or the key's limit reached | add credit or raise the limit at openrouter.ai |
| `404 … 0 endpoints … guardrail` | the key's guardrail allows neither this model nor its host | fix the guardrail, or test this model with its own key |
| `404` model not found | a wrong model id | copy the id from the model's OpenRouter page (`vendor/model`) |
| `429` or "Provider returned error" | the host is busy; Claude Code retried and gave up | pin a steadier host in the guardrail; the expert escalates the task meanwhile |
| `connection failed` | no network, or the local server is not running | start it; `check` again |
| `need bubblewrap and socat`, `bubblewrap is required` or `socat not installed` | Linux or WSL: the coder's commands run in Claude Code's sandbox, which keeps the key out, and it needs both | the developer runs `sudo apt-get install -y bubblewrap socat` in a terminal; `check` again |
| `blocked: … without a report` | the run died (host errors, a crash) | the expert escalates; the error is in the report |
| `blocked: the <config> lane is full` | that many runs are already going | wait for one to finish, or raise `--lanes` |
| `LEAK: requests ran on <id>` | a request named another model | stop external runs and tell the developer; check the key's activity at openrouter.ai |
| a command denied in the report | no allow rule covers it (auto mode cannot run for external coders) | run it through `tools/run.sh`, or the developer adds an allow rule |
