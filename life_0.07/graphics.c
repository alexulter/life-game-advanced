#include <gtk/gtk.h>
#include <glade/glade.h>
#include "shared.h"

static GdkPixmap *pixmap = NULL;


	static void 
draw_brush (GtkWidget *widget, gdouble x, gdouble y)
{
	GdkGC *gc;
	GdkColor color;
	color.red = 0;
	color.blue = 0;
	color.green = 0;
	gc = gdk_gc_new(widget->window);
	gdk_gc_set_rgb_fg_color (gc, &color);
	GdkRectangle update_rect;
	update_rect.x = x - SIZE_OF_CELL / 2;
	update_rect.y = y - SIZE_OF_CELL / 2;
	update_rect.width = SIZE_OF_CELL;
	update_rect.height = SIZE_OF_CELL;
	gdk_draw_rectangle 	(pixmap,
			gc,//widget->style->black_gc,
			TRUE,
			update_rect.x, update_rect.y,
			update_rect.width, update_rect.height);
	gdk_window_invalidate_rect(widget->window, &update_rect, FALSE);
}



	static gboolean 
da_button_press_event	(GtkWidget *widget,
		GdkEventButton *event)
{
	int i,j;
	if (event->button == 1 && pixmap != NULL)
	{
		i = event->x / SIZE_OF_CELL;
		j = event->y / SIZE_OF_CELL;
		if (((j + 2) < vert_size) &&
				((i + 2) < hor_size))
		{
			space_array[i+2][j+2].life_exist = 1;
			i = i*SIZE_OF_CELL + SIZE_OF_CELL / 2;
			j = j*SIZE_OF_CELL + SIZE_OF_CELL / 2;
			draw_brush(widget, i, j);
		}
	}
	return TRUE;
}


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
			gc,//widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
			pixmap,
			event->area.x, event->area.y,
			event->area.x, event->area.y,
			event->area.width, event->area.height);
	return FALSE;
}


	static gboolean
da_clear (GtkWidget *da)
{
	if (pixmap) 
		g_object_unref(pixmap);
	pixmap = gdk_pixmap_new(da->window,
			da->allocation.width,
			da->allocation.height,
			-1);
	gdk_draw_rectangle (pixmap,
			da->style->white_gc,
			TRUE,
			0, 0,
			da->allocation.width,
			da->allocation.height);

	return TRUE;
}

	static gboolean
to_exit (void)
{
	exit(-2);
	return TRUE;
}

static gint life (GtkWidget *da, struct field **space_array)
{

	array_b = create_array_b();
	printf("OK\n");

	body_of_program(space_array, array_b);




	return 0;
}

int main (int argc,char **argv )
{
	space_array = create_space_array();
	gpointer gp;
	gp = (void*)space_array;
	

	gtk_init(&argc, &argv);
	glade_init();

	GladeXML *xml;
	GtkWidget *da;
	//	GtkWidget *aligment_of_da;
	GtkWidget *frame_of_da;

	xml = glade_xml_new("interface.glade", NULL, NULL);
	glade_xml_signal_connect(xml,"gtk_main_quit",gtk_main_quit);
	da = glade_xml_get_widget(xml,"da");




	frame_of_da = glade_xml_get_widget(xml,"frame1");
	//	aligment_of_da = glade_xml_get_widget(xml,"aligment1");

	gtk_widget_set_size_request	(frame_of_da,
			((hor_size)*SIZE_OF_CELL),
			((vert_size)*SIZE_OF_CELL));
	/*	gtk_widget_set_size_request	(aligment_of_da,
		((hor_size)*SIZE_OF_CELL),
		((vert_size)*SIZE_OF_CELL));*/
	/*	gtk_widget_set_size_request	(da,
		((hor_size)*SIZE_OF_CELL),
		((vert_size)*SIZE_OF_CELL));*/

	//	da->allocation.width = 100;
	//	da->allocation.height = 100;


	glade_xml_signal_connect(xml,"da_expose_event",G_CALLBACK(da_expose_event));
	glade_xml_signal_connect(xml,"da_button_press_event",G_CALLBACK(da_button_press_event));
	glade_xml_signal_connect(xml,"to_exit",G_CALLBACK(to_exit));
	glade_xml_signal_connect_data(xml,"life",G_CALLBACK(life),space_array);
	glade_xml_signal_connect(xml,"da_configure_event",G_CALLBACK(da_clear));

			while(TRUE)
			{
			while (gtk_events_pending())	
			gtk_main_iteration();



			int i,j;
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
			rect.width = da->allocation.width;
			rect.height = da->allocation.height;

			for (i=4;i<hor_size-5;i++)
				for (j=4;j<vert_size-5;j++)
				{
					printf("%i",space_array[i][j].life_exist);
					if (space_array[i][j].life_exist == 1)
						gdk_draw_rectangle (pixmap,
								da->style->black_gc,
								TRUE,
								(i+0.5)*SIZE_OF_CELL,
								(j+0.5)*SIZE_OF_CELL,
								SIZE_OF_CELL,
								SIZE_OF_CELL);
					else gdk_draw_rectangle (pixmap,
							da->style->white_gc,
							TRUE,
							(i+0.5)*SIZE_OF_CELL,
							(j+0.5)*SIZE_OF_CELL,
							SIZE_OF_CELL,
							SIZE_OF_CELL);


					//draw_brush(da, i*SIZE_OF_CELL, j*SIZE_OF_CELL);

				}


			gdk_window_invalidate_rect(da->window, &rect, FALSE);

			}

	return 0;
}
