FROM debian:12.5
ENV DEBIAN_FRONTEND=noninteractive PAGER=cat GIT_PAGER=cat
# Deliberately NO C compiler: only the assembler, linker and libc development files.
RUN apt-get update && apt-get install -y --no-install-recommends \
      python3 binutils libc6-dev make git ca-certificates curl nodejs npm \
    && rm -rf /var/lib/apt/lists/*
# Agent CLIs (verify both install commands are still current before submitting)
RUN npm install -g @anthropic-ai/claude-code @openai/codex
RUN useradd -m -u 1000 -s /bin/bash agent
WORKDIR /app
COPY ccomp/ /app/ccomp/
COPY examples/ /app/examples/
COPY check.sh /app/check.sh
RUN chmod +x /app/check.sh && chown -R agent:agent /app

# --- task timer (append at the end of environment/Dockerfile) ---
# COPY only — never auto-start it from the image (no ENV BASH_ENV, no shell
# profile hooks). The platform arms /app/timer.sh in the task sandbox with the
# real TASK_BUDGET_SECS. An image-side autostart also fires inside the image
# BUILD container and stalls the build until the timer's budget expires.
COPY timer.sh /app/timer.sh
RUN chmod +x /app/timer.sh && mkdir -p /app/.timer
