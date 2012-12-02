#include <gtk/gtk.h>
#include <glade/glade.h>
#include "shared.h"

static GdkPixmap *pixmap = NULL;


static void 
draw_brush (GtkWidget *widget, gdouble x, gdouble y)
{
	GdkRectangle update_rect;
	update_rect.x = x - 5;
	update_rect.y = y - 5;
	update_rect.width = 10;
	update_rect.height = 10;
	gdk_draw_rectangle 	(pixmap,
				widget->style->black_gc,
				TRUE,
				update_rect.x, update_rect.y,
				update_rect.width, update_rect.height);
	gtk_widget_draw(widget, &update_rect);
}

static gboolean 
da_button_press_event	(GtkWidget *widget,
			GdkEventButton *event)
{
	int i,j;
	if (event->button == 1 && pixmap != NULL)
		i = event->x/10;
		j = event->y/10;
		space_array[i+1][j+1].life_exist = 1;
		i = i*10 + 5;
		j = j*10 + 5;
		draw_brush(widget, i, j);
	return TRUE;
}

//static gboolean
//draw_life (struct field **space_array, GtkWidget **da, )

static gboolean 
da_expose_event	(GtkWidget *widget,
		GdkEventExpose *event)
{
	gdk_draw_pixmap(widget->window,
			widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
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
		gdk_pixmap_unref(pixmap);
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

int main (int argc,char **argv )
{
	create_arrays();
	gtk_init(&argc, &argv);
	glade_init();
	
	
	GladeXML *xml;
	GtkWidget *da;
	int i,j;
	
	xml = glade_xml_new("interface.glade", NULL, NULL);
	glade_xml_signal_connect(xml,"gtk_main_quit",gtk_main_quit);
	da = glade_xml_get_widget(xml,"da");
	da_clear(da);
	glade_xml_signal_connect(xml,"da_expose_event",G_CALLBACK(da_expose_event));
	glade_xml_signal_connect(xml,"da_button_press_event",G_CALLBACK(da_button_press_event));
	glade_xml_signal_connect(xml,"to_exit",G_CALLBACK(to_exit));
	
//	gtk_widget_set_size_request(da,(hor_size*5),(vert_size*5));
//	glade_xml_signal_autoconnect(xml);
//	gtk_main();
	
	/*for (i=1;i<=9;i++)
		for (j=1;j<=9;j++)
			{
			if (((i+j) % 2) == 0) draw_brush(da,i*10-5,j*10-5);
			}*/
	



	for (i=1;i<=10;i++){
	while (gtk_events_pending())
		gtk_main_iteration();
	i--;
	}
	
	return 0;
}
