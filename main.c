#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>



// Macro //
#define WIDTH 1024
#define HEIGHT 512

int map[]=
        {
                1,1,1,1,1,1,1,1,
                1,0,1,0,0,0,0,1,
                1,0,0,0,0,0,0,1,
                1,0,0,0,0,1,0,1,
                1,0,1,0,0,1,0,1,
                1,0,1,0,1,1,0,1,
                1,0,1,0,0,0,0,1,
                1,1,1,1,1,1,1,1,
        };

int main() {
    if(!al_init()){
        al_show_native_message_box(NULL, NULL, NULL, "Initialisation d'ALLEGRO 5 impossible", NULL, NULL);
        return -1;

        }
        //___________Initialisation des addons___________//
        al_init_primitives_addon();
        al_install_keyboard();

        //_______________________________________________//
        ALLEGRO_DISPLAY* display;
        display = al_create_display(WIDTH, HEIGHT);
        al_clear_to_color(al_map_rgb(150,150,150));


        al_set_window_title(display, "RayTracing_BETA");
        if(!display){
            al_show_native_message_box(display, "Sample TItle", "erreur","test", NULL, ALLEGRO_MESSAGEBOX_QUESTION );
        }
        ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
        al_register_event_source(event_queue, al_get_keyboard_event_source());
    return 0;
    }


