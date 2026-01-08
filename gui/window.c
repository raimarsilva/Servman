#include "window.h"
#include <gtk/gtk.h>

enum {
    COL_NAME,
    COL_DESCRIPTION,
    COL_LOAD_STATE,
    COL_ACTIVE_STATE,
    COL_QTD = 4 // column quantity
};

GtkWidget *window;
GtkWidget *treeview;
GtkWidget *scrollable;
const char *col_labels[] = {"Name", "Description", "Load State", "Active State"};
/* -- Helper functions -- */

void set_column_behavior(GtkTreeViewColumn *column){
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_expand(column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
}

void renderColumns(void){
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    for(int i=0; i<COL_QTD; i++){
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(col_labels[i], renderer, "text", i, NULL);
        set_column_behavior(column);
    }
}

GtkListStore *createStore(){
    
    return gtk_list_store_new(COL_QTD,
        G_TYPE_STRING, // Name
        G_TYPE_STRING, // Description
        G_TYPE_STRING, // Load State
        G_TYPE_STRING // Active State
    );
}

GtkListStore *fillServiceStore(ServiceList *serviceList){
    GtkListStore *store = createStore();
    GtkTreeIter iter;
    // Populate the list store with service data
    for(int i = 0; i < serviceList->count; i++){
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
            COL_NAME,           serviceList->items[i].name,
            COL_DESCRIPTION,    serviceList->items[i].description,
            COL_LOAD_STATE,     serviceList->items[i].load_state,
            COL_ACTIVE_STATE,   serviceList->items[i].active_state,
            -1
        );
    }

    return store;
}

/* -- GUI Bootstrap -- */

void init_gui(int argc, char *argv[], ServiceList *serviceList){
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Gerenciador de Serviços by Raimar ^.^v");
    gtk_window_set_default_size(GTK_WINDOW(window), 760, 570);
    
    scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollable), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    
    GtkListStore *store = fillServiceStore(serviceList);
    treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));

    g_object_unref(store);

    renderColumns();

    gtk_container_add(GTK_CONTAINER(scrollable), treeview);
    gtk_container_add(GTK_CONTAINER(window), scrollable);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();
}