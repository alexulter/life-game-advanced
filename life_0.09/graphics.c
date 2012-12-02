#include <gtk/gtk.h>
#include <glade/glade.h>
#include "shared.h"

static GdkPixmap *pixmap = NULL;
static gint abc = 0;
// рисует прямоугольник
static void 
draw_brush (GtkWidget *widget, gdouble x, gdouble y)
{
	/*GdkGC *gc;
	GdkColor color;
	color.red = 0;
	color.blue = 0;
	color.green = 0;
	gc = gdk_gc_new(widget->window);
	gdk_gc_set_rgb_fg_color (gc, &color);*/
	GdkRectangle update_rect;
	update_rect.x = x - SIZE_OF_CELL / 2;
	update_rect.y = y - SIZE_OF_CELL / 2;
	update_rect.width = SIZE_OF_CELL;
	update_rect.height = SIZE_OF_CELL;
	gdk_draw_rectangle 	(pixmap,
				widget->style->black_gc,
				TRUE,
				update_rect.x, update_rect.y,
				update_rect.width, update_rect.height);
	gdk_window_invalidate_rect(widget->window, &update_rect, FALSE);
}



static gboolean 
da_button_press_event	(GtkWidget *widget,
			GdkEventButton *event)
{
	int i, j;
	if (event->button == 1 && pixmap != NULL)
	{
		i = (event->x / SIZE_OF_CELL) + 2;
		j = (event->y / SIZE_OF_CELL) + 2;
		if (((j + 1) < vert_size) &&
			((i + 1) < hor_size))
			{
				space_array[i][j].life_exist = 1;
				i = (i-1.5)*SIZE_OF_CELL;
				j = (j-1.5)*SIZE_OF_CELL;
				draw_brush(widget, i, j);
			}
	}

	return TRUE;
}

// перерисовывает часть экрана
static gboolean 
da_expose_event	(GtkWidget *widget,
		GdkEventExpose *event)
{	
	GdkGC *gc;
	GdkColor color;
	color.red=65535;
	color.blue=65535;
	color.green=65535;
	gc = gdk_gc_new(widget->window);
	gdk_gc_set_rgb_fg_color(gc, &color);
	gdk_draw_drawable(widget->window,
			widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
			pixmap,
			event->area.x, event->area.y,
			event->area.x, event->area.y,
			event->area.width, event->area.height);
	return FALSE;
}

// чистит pixmap
static gboolean
da_clear (GtkWidget *da)
{
	gint w=0;
	gint h=0;
	if (pixmap) 
		g_object_unref(pixmap);
		gdk_drawable_get_size(da->window,&w,&h);
	pixmap = gdk_pixmap_new(da->window,w,h,
				/* da->allocation.width,
				da->allocation.height,
			*/	-1);
	gdk_draw_rectangle (pixmap,
				da->style->white_gc,
				TRUE,
				0, 0,
				da->allocation.width,
				da->allocation.height);
	
return TRUE;
}


//выход
static gboolean
to_exit (void)

{
	exit(-2);
	return TRUE;
}

static gint
temp_function (void)
{


return 0;
}


static gboolean life (GtkWidget *da, struct field **space_array)
{
		
	array_b = create_array_b();
	body_of_program(space_array, array_b);
	abc = 1;
	return TRUE;
}

int main (int argc,char **argv )
{
	
//	gpointer gp;
//	gp = (void*)space_array;
	GtkWidget *window;	
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *button_quit;
	GtkWidget *button_run;
	GtkWidget *button_new;
	GtkWidget *button_t;
	GtkWidget *button_o;
	GtkWidget *da;
	gtk_init(&argc, &argv);
	glade_init();
	int l,k;
space_array = create_space_array();
//printf("begin_space %i",space_array);


/*space_array[5][5].life_exist=1;
space_array[5][6].life_exist=0;
space_array[5][7].life_exist=0;
space_array[5][8].life_exist=0;
space_array[6][7].life_exist=0;
space_array[6][5].life_exist=0;
space_array[7][7].life_exist=0;
space_array[5][8].life_exist=0;
space_array[8][6].life_exist=0;
space_array[8][7].life_exist=0;*/




window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (to_exit), NULL);
 gtk_container_set_border_width (GTK_CONTAINER (window), 10);
 hbox = gtk_hbox_new(FALSE,5);
 vbox = gtk_vbox_new(FALSE,0);
 
 
 da= gtk_drawing_area_new();
 gtk_widget_set_size_request (da, hor_size*SIZE_OF_CELL, vert_size*SIZE_OF_CELL);
 

 button_quit = gtk_button_new_with_label ("Quit");
 button_run = gtk_button_new_with_label ("Run");
 button_new = gtk_button_new_with_label ("New");
 button_t = gtk_button_new_with_label ("Show temperature");
 button_o = gtk_button_new_with_label ("Show oxygen");
 

	g_signal_connect (G_OBJECT(button_quit),
			"clicked",
			G_CALLBACK(to_exit),
			NULL);
	g_signal_connect (G_OBJECT(button_run), "clicked", G_CALLBACK(life), space_array);
	g_signal_connect (G_OBJECT(da),
			"button_press_event",
			G_CALLBACK(da_button_press_event),
			NULL);
   	g_signal_connect (G_OBJECT(da),
			"configure_event",
			G_CALLBACK(da_clear), 
			NULL);
	g_signal_connect (G_OBJECT(da),
			"expose_event",
			G_CALLBACK(da_expose_event),
			NULL);

	gtk_widget_set_events (da,GDK_EXPOSURE_MASK
			| GDK_LEAVE_NOTIFY_MASK
			| GDK_BUTTON_PRESS_MASK);



	
 gtk_box_pack_start(GTK_BOX (vbox), button_new,FALSE,FALSE,0);
 gtk_box_pack_start(GTK_BOX (vbox), button_run,FALSE,FALSE,0);
 gtk_box_pack_start(GTK_BOX (vbox), button_t,FALSE,FALSE,0);
 gtk_box_pack_start(GTK_BOX (vbox), button_o,FALSE,FALSE,0);
 gtk_box_pack_start(GTK_BOX (vbox), button_quit,FALSE,FALSE,0);
 gtk_box_pack_end(GTK_BOX(hbox),vbox,FALSE,FALSE,0);
 gtk_box_pack_end(GTK_BOX(hbox),da,FALSE,FALSE,0);
 gtk_container_add (GTK_CONTAINER (window), hbox);
 
 
 
 
 gtk_widget_show (button_run);
 gtk_widget_show (button_new);
 gtk_widget_show (button_quit);
 gtk_widget_show (button_t);
 gtk_widget_show (button_o);
 gtk_widget_show (vbox);
 gtk_widget_show (hbox);
 gtk_widget_show(window);
 gtk_widget_show(da);

/*	GladeXML *xml;
	xml = glade_xml_new("interface.glade",NULL,NULL);
	glade_xml_signal_connect(xml,"gtk_main_quit",gtk_main_quit);
	da = glade_xml_get_widget(xml,"da");

	glade_xml_signal_connect(xml,"da_expose_event",G_CALLBACK(da_expose_event));
	glade_xml_signal_connect(xml,"da_button_press_event",G_CALLBACK(da_button_press_event));
	glade_xml_signal_connect(xml,"to_exit",G_CALLBACK(to_exit));
	glade_xml_signal_connect_data(xml,"life",G_CALLBACK(life),space_array);
	glade_xml_signal_connect(xml,"da_configure_event",G_CALLBACK(da_clear));*/




int i=0,j=0;
gint w=0,h=0;
	GdkRectangle rect;
	GdkGC *gc;
	GdkColor color;
	color.red = 65535;
	color.blue = 65535;
	color.green = 65535;
	gc = gdk_gc_new (da->window);
	gdk_gc_set_rgb_fg_color (gc, &color);
	rect.x = 0;
	rect.y = 0;
	gdk_drawable_get_size(da->window,&w,&h);

	rect.width = w;// da->allocation.width;
	rect.height = h;// da->allocation.height;

while (TRUE){
while (gtk_events_pending ())
          gtk_main_iteration ();
		if (abc==1)
		for (j=2;j<hor_size-2;j++)
		{
			
			for (i=2;i<vert_size-2;i++)
			{
					
				//printf("%i",space_array[5][5].life_exist);
				
				if (space_array[i][j].life_exist == 1)
					{
					//printf("%i \n",space_array[5][5]);
					gdk_draw_rectangle (pixmap,
					da->style->black_gc,
					TRUE,
					(i-2)*SIZE_OF_CELL,
					(j-2)*SIZE_OF_CELL,
					SIZE_OF_CELL,
					SIZE_OF_CELL);
					}
				else gdk_draw_rectangle (pixmap,
							da->style->white_gc,
							TRUE,
							(i-2)*SIZE_OF_CELL,
							(j-2)*SIZE_OF_CELL,
							SIZE_OF_CELL,
							SIZE_OF_CELL);


					//draw_brush(da, i*SIZE_OF_CELL, j*SIZE_OF_CELL);

			}
		}
		gdk_draw_drawable(da->window,
				gc,//da->style->fg_gc[GTK_WIDGET_STATE (da)],
				pixmap, 0, 0, 0, 0,
				/*da->allocation.x, da->allocation.y,
				da->allocation.x, da->allocation.y,*/
				da->allocation.width, da->allocation.height);
//	gtk_widget_queue_draw_area(da,da->allocation.x,da->allocation.y,da->allocation.width,
//				da->allocation.height); 
//gtk_widget_show(da);
//abc=0;
//da_clear(da->window);
};

return 0;
}

