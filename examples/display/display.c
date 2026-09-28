// Include the main display functions so we don't have to initialize the display again
#include "hlc_tft_display/hlc_tft_display.h"

// Add a font, this font is generated using the QP CLI tools (https://docs.qmk.fm/quantum_painter#quantum-painter-cli)
#include "graphics/thintel15.qff.h"

// Initialize the font
static painter_font_handle_t thintel;

// Setup painter devices
painter_device_t lcd;
painter_device_t lcd_surface;

// This function is ran on bootup of the keyboard
bool module_post_init_user(void) {
    // Load the font in to memory.
    thintel = qp_load_font_mem(font_thintel15);

    return false;
}

// This function runs after every matrix scan
bool display_module_housekeeping_task_user(bool second_display) {
    // Create checks to see if the displays are set. We don't need to keep updating the display with the same image so this will save some CPU time.
    static bool display_set        = false;
    static bool second_display_set = false;

    // When the display isn't set, do the following
    if (!display_set) {
        // If it's the main display
        if (!second_display) {
            // Create text to write
            static const char *text = "This is a user display!";

            // Draw text on top left corner
            qp_drawtext_recolor(lcd_surface, 0, 0, thintel, text, HSV_WHITE, HSV_BLACK);

            // Make sure to not run this again.
            display_set = true;
            // If it's the secondary display
        } else {
            // Create text to write
            static const char *text = "This is a second user display!";

            // Read width from text
            int16_t width = qp_textwidth(thintel, text);

            // Draw text on bottom right corner
            qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - width), (LCD_HEIGHT - thintel->line_height), thintel, text, HSV_WHITE, HSV_BLACK);

            // Make sure to not run this again.
            display_set        = true;
            second_display_set = true;
        }
    }

    // Make sure that the second display loads correctly, sometimes it takes a little while for the keyboard to know it has a second display.
    // So we reset the state and make it run again until the secondary display is drawn correctly
    if (second_display && !second_display_set) {
        display_set = false;
    }

    // Move surface to lcd, this actually writes the content to the physical display
    qp_surface_draw(lcd_surface, lcd, 0, 0, 0);

    return false;
}
