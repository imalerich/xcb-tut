#include <stdio.h>
#include <xcb/xcb.h>
#include <stdbool.h>

int main(int argc, char ** argv) {
	int screenp;
	xcb_connection_t * c = xcb_connect("sample", &screenp);

	while (true) {
		// TODO - do stuff here
	}

	xcb_disconnect(c);
}
