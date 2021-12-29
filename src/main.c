#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "context.h"
#include "event.h"

void cleanup(ctx_t * ctx) {
    log_debug(ctx, "cleanup: deallocating resources\n");
    if (ctx->mirror.initialized) cleanup_mirror(ctx);
    if (ctx->egl.initialized) cleanup_egl(ctx);
    if (ctx->wl.initialized) cleanup_wl(ctx);
    cleanup_opt(ctx);
}

void exit_fail(ctx_t * ctx) {
    cleanup(ctx);
    exit(1);
}

int main(int argc, char ** argv) {
    ctx_t ctx;

    ctx.wl.initialized = false;
    ctx.egl.initialized = false;
    ctx.mirror.initialized = false;

    init_opt(&ctx);

    if (argc > 0) {
        // skip program name
        argv++;
        argc--;
    }

    parse_opt(&ctx, argc, argv);

    log_debug(&ctx, "main: initializing wayland\n");
    init_wl(&ctx);

    log_debug(&ctx, "main: initializing EGL\n");
    init_egl(&ctx);

    log_debug(&ctx, "main: initializing mirror\n");
    init_mirror(&ctx);

    log_debug(&ctx, "main: entering event loop\n");
    event_loop(&ctx);
    log_debug(&ctx, "main: exiting event loop\n");

    cleanup(&ctx);
}
