#include <pebble.h>
#include <string.h>

Window *my_window;
TextLayer *text_layer;
ActionBarLayer *action_bar;

BitmapLayer *s_icon_layer;
GBitmap *s_icon_bitmap, *s_tick_bitmap, *s_cross_bitmap;

const char* txt;
static char sdata[30];
char* stri;
static int i;
const char add = 's';
static int curlen;
char spc = ' ';
bool txtb = false;
bool sdatab = false;
bool strib = false;
bool text_layerb = false;

//static GBitmap *b1;

/*static void logg(char* desc, char* var){
	APP_LOG(APP_LOG_LEVEL_INFO, strcat(desc, "%s:"), var);
}*/

static void logg(char* desc){
	APP_LOG(APP_LOG_LEVEL_INFO, "%s", desc);
}

static void check() {
	logg("CHECK:******");
	if(txtb) APP_LOG(APP_LOG_LEVEL_INFO,"static char txt: %s", txt);
	if(sdatab) APP_LOG(APP_LOG_LEVEL_INFO, "static char sdata: %s", sdata);
	if(strib) APP_LOG(APP_LOG_LEVEL_INFO, "static char stri: %s", stri);
	if(text_layerb) APP_LOG(APP_LOG_LEVEL_INFO, "text_layer text: %s", text_layer_get_text(text_layer));
	logg("\n");
}

static void remove_char() {
	logg("***remove_char***");
	// http://www.cplusplus.com/reference/cstring/strncpy/
	// https://www.google.com/search?q=string+functions+c&ie=utf-8&oe=utf-8
	//strncpy(stri, text_layer_get_text(text_layer), strlen(text_layer_get_text(text_layer) - 1));
	
	//txt = *text_layer_get_text(text_layer);
	
	//static char k;
	/*for(i = 0; i < (int)strlen(&txt); i++) {
		//k = (&txt)[i];
		stri[i] &= (&txt)[i];
	}
	//txt *= text_layer_get_text(text_layer);
	
	for(i = 0; i < (int)strlen(&txt); i++) {
		t[i] = *(&txt + i);
	}
	s1 = &t;
	text_layer_set_text(text_layer, s1);
	*/
	i = 0;
	while((sdata)[i + 1] != '$') {
		i++;
	} 
	(sdata)[i] = '$';
	
	char txt;
	strncpy(&txt, sdata, i - 1);
	
	//strncpy(stri, &txt, (int)(strlen(&txt) - 1));
	//strncpy(stri, &txt, curlen);
	//curlen -= 1;
	text_layer_set_text(text_layer, &txt);
	logg("***end of remove_Char***");
}

static void add_char() {
	logg("add_char");
	// http://www.cplusplus.com/reference/cstring/strncpy/
	// https://www.google.com/search?q=string+functions+c&ie=utf-8&oe=utf-8
	//strncpy(stri, text_layer_get_text(text_layer), text_layer_get_content_size(text_layer) - 1);//strlen(text_layer_get_text(text_layer) - 1));
	//letter = "a";
//*text_layer_get_text(text_layer);
	//text_layer_set_text(text_layer, s1);
	txt = text_layer_get_text(text_layer);
	txtb = true;
	strcat((char*)txt, &add);
	strcpy(stri, txt);
	curlen++;
	text_layer_set_text(text_layer, stri);
	logg("end of add_char");
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
	logg("up_click_handler");
  //text_layer_set_text(text_layer, "Up pressed!");
	add_char();
	check();
	logg("end of up_click_handler");
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	logg("select_click_handler");
  text_layer_set_text(text_layer, "Select pressed!");
	check();
	logg("end of select_click_handler");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
	logg("down_click_handler");
  //text_layer_set_text(text_layer, "Down pressed!");
	remove_char();
	check();
	logg("end of down_click_handler");
}

// The implementation of my_next_click_handler and my_previous_click_handler
// is omitted for the sake of brevity. See the Clicks reference docs.

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_DOWN, (ClickHandler) down_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, (ClickHandler) up_click_handler);
	window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler) select_click_handler);
	
	/*window_long_click_subscribe(BUTTON_ID_DOWN, (ClickHandler) down_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, (ClickHandler) up_click_handler);
	window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler) select_click_handler);*/
}

static void make_action_bar() {
	logg("make_action_bar");
  /*s_label_layer = text_layer_create(GRect(10, 10 + bitmap_bounds.size.h + 5, 124 - ACTION_BAR_WIDTH, bounds.size.h - (10 + bitmap_bounds.size.h + 15)));
  text_layer_set_text(s_label_layer, DIALOG_CHOICE_WINDOW_MESSAGE);
  text_layer_set_background_color(s_label_layer, GColorClear);
  text_layer_set_text_alignment(s_label_layer, GTextAlignmentCenter);
  text_layer_set_font(s_label_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(s_label_layer));*/

  s_tick_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TICK);
  s_cross_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CROSS);
	
	// ...
  // Initialize the action bar:
  action_bar = action_bar_layer_create();
	// Set the click config provider:
  action_bar_layer_set_click_config_provider(action_bar,
                                             click_config_provider);
  action_bar_layer_set_icon(action_bar, BUTTON_ID_UP, s_cross_bitmap);
  //action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, s_icon_bitmap);
	action_bar_layer_set_icon(action_bar, BUTTON_ID_DOWN, s_tick_bitmap);
	//action_bar_layer_add_to_window(action_bar, my_window);
	// Set the icons:
  // The loading of the icons is omitted for brevity... See gbitmap_create_with_resource()
  //action_bar_layer_set_icon_animated(action_bar, BUTTON_ID_UP, my_icon_previous, true);
  //action_bar_layer_set_icon_animated(action_bar, BUTTON_ID_DOWN, my_icon_next, true);
	
}

static void window_load(Window *window) {
	logg("window_load");
	Layer *window_layer = window_get_root_layer(my_window);
	GRect bounds = layer_get_bounds(window_layer);
	s_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CONFIRM);
  GRect bitmap_bounds = gbitmap_get_bounds(s_icon_bitmap);
	s_icon_layer = bitmap_layer_create(GRect((bounds.size.w / 2) - (bitmap_bounds.size.w / 2) - (ACTION_BAR_WIDTH / 2), 10, bitmap_bounds.size.w, bitmap_bounds.size.h));
  bitmap_layer_set_bitmap(s_icon_layer, s_icon_bitmap);
  bitmap_layer_set_compositing_mode(s_icon_layer, GCompOpSet);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_icon_layer));
	
	text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
	text_layerb = true;
  text_layer_set_text(text_layer, "Press a button");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
	
	make_action_bar();
  // Associate the action bar with the window:
  action_bar_layer_add_to_window(action_bar, my_window);
	
	stri = "";
	strib = true;
	check();
	logg("end of window_load");
	//gb = gbitmap_create_blank_with_palette(GSize size, GBitmapFormat format, GColor * palette, bool free_on_destroy)
}


//static void window_appear(Window *window) {{}

static void window_unload(Window *window){
	logg("window_unload");
	text_layer_destroy(text_layer);
	text_layerb = false;
	action_bar_layer_destroy(action_bar);
	//gbitmap_destroy(b1);
	bitmap_layer_destroy(s_icon_layer);

  gbitmap_destroy(s_icon_bitmap); 
  gbitmap_destroy(s_tick_bitmap);
  gbitmap_destroy(s_cross_bitmap);
	check();
	logg("end of window_unload");
}

static void handle_init(void) {
	logg("handle_init");
  my_window = window_create();
	curlen = 0;
	for(i = 0; i < 30; i++) {
		sdata[i] = '$';
	}
	sdatab = true;
	check();
	
	window_set_window_handlers(my_window, (WindowHandlers) {
		.load = window_load,
    	.unload = window_unload,
  });
	//const bool animated = true;
  //window_stack_push(window, animated);

  /*text_layer = text_layer_create(GRect(0, 0, 144, 20));
	text_layer_set_text(text_layer, "Text!");
	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer));*/
  
	window_stack_push(my_window, true);
	logg("end of handle_init");
}

static void handle_deinit(void) {
	logg("handle_deinit");
	check();
  //text_layer_destroy(text_layer);
  window_destroy(my_window);
}
int main(void) {
	logg("main");
  handle_init();
  app_event_loop();
  handle_deinit();
}