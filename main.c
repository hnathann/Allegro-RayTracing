#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>


// Macro //
#define WIDTH 1024
#define HEIGHT 512
#define mapX 8
#define mapY 8
#define mapS 64

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


void drawMap2D() {
    int x,y;
    for(y=0;y<mapY;y++) {
        for(x=0;x<mapX;x++) {
            if(map[y*mapX+x]==1) {
                al_draw_filled_rectangle(x*mapS, y*mapS, (x+1)*mapS, (y+1)*mapS, al_map_rgb(255,255,255));
            }
            else {
                al_draw_filled_rectangle(x*mapS, y*mapS, (x+1)*mapS, (y+1)*mapS, al_map_rgb(0,0,0));
            }
            // Ajout des lignes de quadrillage
            al_draw_line(x*mapS, y*mapS, (x+1)*mapS, y*mapS, al_map_rgb(100,100,100), 1);
            al_draw_line((x+1)*mapS, y*mapS, (x+1)*mapS, (y+1)*mapS, al_map_rgb(100,100,100), 1);
            al_draw_line((x+1)*mapS, (y+1)*mapS, x*mapS, (y+1)*mapS, al_map_rgb(100,100,100), 1);
            al_draw_line(x*mapS, (y+1)*mapS, x*mapS, y*mapS, al_map_rgb(100,100,100), 1);
        }
    }
}

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

        bool done = false;
    while(!done)
    {
        drawMap2D();


        al_flip_display();
        al_clear_to_color(al_map_rgb(100,100,100));



    }



}


