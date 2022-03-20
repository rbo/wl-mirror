#ifndef WL_MIRROR_MIRROR_SCREENCOPY_H_
#define WL_MIRROR_MIRROR_SCREENCOPY_H_

#include <stdint.h>
#include "mirror.h"
#include "wlr-screencopy-unstable-v1.h"
#include <wayland-client.h>

typedef enum {
    STATE_WAIT_BUFFER,
    STATE_WAIT_BUFFER_DONE,
    STATE_WAIT_FLAGS,
    STATE_WAIT_READY,
    STATE_READY,
    STATE_CANCELED
} screencopy_state_t;

typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t stride;
    uint32_t format;
} buffer_info_t;

typedef struct {
    mirror_backend_t header;

    // shm state
    int shm_fd;
    size_t shm_size;
    void * shm_addr;

    // wl_shm objects
    struct wl_shm_pool * shm_pool;
    struct wl_buffer * shm_buffer;

    // screencopy frame object
    struct zwlr_screencopy_frame_v1 * screencopy_frame;

    // frame data
    buffer_info_t buffer_info;
    buffer_info_t frame_info;
    uint32_t frame_flags;

    // screencopy state flags
    screencopy_state_t state;
} screencopy_mirror_backend_t;

#endif
