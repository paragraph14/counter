#include <pebble.h>

Window *window;
TextLayer *text_layer;
TextLayer *second;

void handle_init(void) {
	// Create a window and text layer
	window = window_create();
	text_layer = text_layer_create(GRect(0, 0, 144, 154));
	second = text_layer_create(GRect(0, 0, 144, 154));

    //click init
    window_set_click_config_provider(window, (ClickConfigProvider) config_provider);

	// Set the text, font, and text alignment
	text_layer_set_text(text_layer, "Hi, I'm a Pebble!");
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);

	text_layer_set_text(second, "second message");
	text_layer_set_font(second, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(second, GTextAlignmentCenter);

	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(second));

	// Push the window
	window_stack_push(window, true);

	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

void config_provider(Window *window) {
	// single click / repeat-on-hold config:
	window_single_click_subscribe(BUTTON_ID_DOWN, down_single_click_handler);
	window_single_repeating_click_subscribe(BUTTON_ID_SELECT, 1000, select_single_click_handler);

	// multi click config:
	window_multi_click_subscribe(BUTTON_ID_SELECT, 2, 10, 0, true, select_multi_click_handler);

	// long click config:
	window_long_click_subscribe(BUTTON_ID_SELECT, 700, select_long_click_handler, select_long_click_release_handler);
}

void handle_deinit(void) {
	// Destroy the text layer
	text_layer_destroy(text_layer);
	text_layer_destroy(second);

	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
