#include "window.h"
#include <gtk/gtk.h>

void init_gui(int argc, char *argv[], ServiceList *serviceList){
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Service Manager");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    GtkListStore *store;
    GtkTreeIter iter;

    /*store = gtk_list_store_new(1,G_TYPE_STRING);
    gtk_list_store_append(store,&iter);
    gtk_list_store_set(store, &iter, "ITEM", "Raimar", -1);*/
    
    // Populate the list store with service data
    store = gtk_list_store_new(5,
        G_TYPE_STRING, // Name
        G_TYPE_STRING, // Description
        G_TYPE_STRING, // Load State
        G_TYPE_STRING, // Active State
        G_TYPE_UINT    // Job ID
    );

    for(int i = 0; i < serviceList->count; i++){
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
            0, serviceList->items[i].name,
            1, serviceList->items[i].description,
            2, serviceList->items[i].load_state,
            3, serviceList->items[i].active_state,
            4, serviceList->items[i].job_id,
            -1
        );
    }

    GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    //renderer para a coluna NAME
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Name", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    //description
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Description", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    //load_state
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Load", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    //active state
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Active", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    //job id
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Job ID", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    g_object_unref(store);

    gtk_container_add(GTK_CONTAINER(window), treeview);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();
}