#include <gtk/gtk.h>
#include <gtk4-layer-shell.h>
#include <webkit/webkit.h>
#include <glib.h>

static char *default_url = "https://paveldogreat.github.io/WebGL-Fluid-Simulation/";

static void inject_scripts(WebKitWebView *view) {
    const char *script = 
        "(() => {"
        "  const hide = () => {"
        "    document.querySelector('.dg.ac')?.remove();"
        "    document.getElementById('controls')?.remove();"
        "    if (typeof config !== 'undefined') {"
        "      config.SIM_RESOLUTION = 128;"
        "      config.DYE_RESOLUTION = 512;"
        "    }"
        "  };"
        "  hide(); setTimeout(hide, 100); setTimeout(hide, 500);"
        "  document.body.style.cursor = 'none';"
        "})();";
    webkit_web_view_evaluate_javascript(view, script, -1, NULL, NULL, NULL, NULL, NULL);
}

static void on_load_changed(WebKitWebView *view, WebKitLoadEvent event, gpointer data) {
    if (event == WEBKIT_LOAD_FINISHED) inject_scripts(view);
}

static void activate(GtkApplication *app, gpointer user_data) {
    const char *uri = user_data ? (const char *)user_data : default_url;
    
    GtkWindow *window = GTK_WINDOW(gtk_application_window_new(app));
    
    gtk_layer_init_for_window(window);
    gtk_layer_set_layer(window, GTK_LAYER_SHELL_LAYER_BACKGROUND);
    gtk_layer_set_anchor(window, GTK_LAYER_SHELL_EDGE_LEFT, TRUE);
    gtk_layer_set_anchor(window, GTK_LAYER_SHELL_EDGE_RIGHT, TRUE);
    gtk_layer_set_anchor(window, GTK_LAYER_SHELL_EDGE_TOP, TRUE);
    gtk_layer_set_anchor(window, GTK_LAYER_SHELL_EDGE_BOTTOM, TRUE);
    gtk_layer_set_keyboard_mode(window, GTK_LAYER_SHELL_KEYBOARD_MODE_NONE);
    gtk_layer_set_namespace(window, "nirifluidpaper");
    gtk_layer_set_exclusive_zone(window, -1);
    
    WebKitWebView *view = WEBKIT_WEB_VIEW(webkit_web_view_new());
    WebKitSettings *settings = webkit_web_view_get_settings(view);
    webkit_settings_set_enable_webgl(settings, TRUE);
    webkit_settings_set_hardware_acceleration_policy(settings, WEBKIT_HARDWARE_ACCELERATION_POLICY_ALWAYS);
    
    webkit_web_view_set_background_color(view, &(GdkRGBA){0, 0, 0, 1.0});
    
    g_signal_connect(view, "load-changed", G_CALLBACK(on_load_changed), NULL);
    webkit_web_view_load_uri(view, uri);
    
    gtk_window_set_child(window, GTK_WIDGET(view));
    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
}

int main(int argc, char *argv[]) {
    const char *uri = default_url;
    gchar *local_path = g_build_filename(g_get_home_dir(), 
        ".local", "share", "nirifluidpaper", "index.html", NULL);
    
    if (argc > 1) uri = argv[1];
    else if (g_file_test(local_path, G_FILE_TEST_EXISTS)) 
        uri = g_strdup_printf("file://%s", local_path);
    
    GtkApplication *app = gtk_application_new("com.nirifluidpaper.app", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), (gpointer)uri);
    
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    g_free(local_path);
    return status;
}
