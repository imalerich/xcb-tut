#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

#include <xcb/xcb.h>
#include <xcb/xcbext.h>
#include <xcb/xinerama.h>
#include <xcb/randr.h>

int main(int argc, char ** argv) {
	int i, screen_num;
	xcb_window_t window;

	xcb_connection_t * c = xcb_connect(NULL, &screen_num);

	/* Check for errors in our X connection. */
	if (xcb_connection_has_error(c)) {
		fprintf(stderr, "Failed to connect to the X display\n");
		exit(EXIT_FAILURE);
	}

	/* Get information about our connection. */
	const xcb_setup_t * setup = xcb_get_setup(c);
	xcb_screen_iterator_t it = xcb_setup_roots_iterator(setup);

	/* Get screen details for the current screen number. */
	for (i = 0; i < screen_num; ++i) {
		xcb_screen_next(&it);
	}

	/* Get the data for this screen. */
	xcb_screen_t * screen = it.data;

	/* Generate an id and create our window. */
	window = xcb_generate_id(c);
	xcb_create_window(c, XCB_COPY_FROM_PARENT, window, screen->root, 
			10, 10, 150, 150, 10,
			XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual,
			0, NULL);

	/* Map the window to the screen. */
	xcb_map_window(c, window);

	/* Flush all pending requests. */
	xcb_flush(c);

	/* Wait for a Ctrl-C. */
	pause();

	/* Close the connection whene we are done. */
	xcb_disconnect(c);

	return 0;
}
