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
#define PI 3.14159265359
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533 // 1 deg en rad

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

void dessinerJoueur(float px, float py) {
    al_draw_filled_circle(px, py, 8, al_map_rgb(255, 255, 0));

}

void InputClavier(ALLEGRO_EVENT events, float *px, float *py, float *pdx, float *pdy, float *pa, bool *done)

{
    switch(events.keyboard.keycode)
    {
        case ALLEGRO_KEY_DOWN:
            (*px) -= (*pdx);
            (*py) -= (*pdy);


            break;
        case ALLEGRO_KEY_UP:
            (*px) += (*pdx);
            (*py) += (*pdy);
            break;
        case ALLEGRO_KEY_RIGHT:
            (*pa) += 0.1;
            if((*pa)>2*PI){
                (*pa)-=2*PI;
            }
            (*pdx) = cos((*pa))*5;
            (*pdy) = sin((*pa))*5;
            break;
        case ALLEGRO_KEY_LEFT:
            (*pa) -= 0.1;
            if((*pa)<0){
                (*pa)+=2*PI;
            }
            (*pdx) = cos((*pa))*5;
            (*pdy) = sin((*pa))*5;
            break;
        case ALLEGRO_KEY_ESCAPE:
            (*done) = true;
            break;


    }
}
float dist(float ax,float ay,float bx,float by,float ang){
    return (sqrt((bx-ax)*(bx-ax)+(by-ay)*(by-ay)));
}
void RayTracing(int *r, int *mx, int *my, int *mp, int *dof, float *pa,float *px, float *py, float *rx, float *ry, float *ra, float *xo, float *yo, float *disT, int*map ){

    (*ra) = (*pa)-DR*30;
    if((*ra)<0){
        (*ra) += 2*PI;
    }
    if((*ra)>2*PI){
        (*ra) -= 2*PI;
    }
    for ((*r)=0;(*r)<60;(*r)++){
        // Ligne horizontale//
        (*dof) = 0;
        float disH=1000000, hx = (*px), hy = (*py);
        float aTan = -1/tan((*ra));
        if((*ra)>PI){
            (*ry)=(((int)(*py)>>6)<<6)-0.0001;
            (*rx)=((*py)-(*ry))*aTan+(*px);
            (*yo)=-64;
            (*xo)=-(*yo)*aTan;
        }
        if((*ra)<PI){
            (*ry)=(((int)(*py)>>6)<<6)+64;
            (*rx)=((*py)-(*ry))*aTan+(*px);
            (*yo)=64;
            (*xo)=-(*yo)*aTan;
        }
        if((*ra)==0 || (*ra) == PI){
            (*rx)=(*px);
            (*ry)=(*py);
            (*dof) = 8;
        }
        while((*dof)<8)
        {
            (*mx)=(int)((*rx))>>6; (*my)=(int)((*ry))>>6;
            (*mp)=(*my)*mapX+(*mx);
            if((*mp)>0 && (*mp)<mapX*mapY && map[(*mp)]==1){
                hx = (*rx);
                hy = (*ry);
                disH = dist(*px, *py, hx, hy, *ra);
                (*dof) = 8;
            }
            else{
                (*rx)+=(*xo); (*ry)+=(*yo); (*dof)+=1;
            }
        }

        // ligne verticale //___________________________________
        (*dof) = 0;
        float disV=1000000, vx = (*px), vy = (*py);
        float nTan = -tan((*ra));
        if((*ra)>P2 && (*ra)<P3){
            (*rx)=(((int)(*px)>>6)<<6)-0.0001;
            (*ry)=((*px)-(*rx))*nTan+(*py);                     //Regarde Gauche
            (*xo)=-64;
            (*yo)=-(*xo)*nTan;
        }
        if((*ra)<P2 || (*ra)>P3){
            (*rx)=(((int)(*px)>>6)<<6)+64;
            (*ry)=((*px)-(*rx))*nTan+(*py);                   //Regarde droite
            (*xo)=64;
            (*yo)=-(*xo)*nTan;
        }
        if((*ra)==0 || (*ra) == PI){
            (*rx)=(*px);                             //Regarde bas ou haut
            (*ry)=(*py);
            (*dof) = 8;
        }
        while((*dof)<8)
        {
            (*mx)=(int)((*rx))>>6; (*my)=(int)((*ry))>>6;
            (*mp)=(*my)*mapX+(*mx);
            if((*mp)>0 && (*mp)<mapX*mapY && map[(*mp)]==1){
                vx = (*rx);
                vy = (*ry);
                disV = dist((*px), (*py), vx, vy, (*ra));
                (*dof) = 8;
            }
            else{
                (*rx)+=(*xo); (*ry)+=(*yo); (*dof)+=1;
            }
        }
        ALLEGRO_COLOR couleur;
        if (disV < disH) {
            (*rx) = vx;
            (*ry) = vy;
            (*disT) = disV;
            couleur = al_map_rgb(240, 0, 0);
        } else if (disH < disV) {
            (*rx) = hx;
            (*ry) = hy;
            (*disT) = disH;
            couleur = al_map_rgb(200, 0, 0);
        } else {
            couleur = al_map_rgb(255, 0, 0);
        }
        al_draw_line((*px), (*py), (*rx), (*ry), couleur, 1);

        //__________________Dessiner la piece 3D____________________//
        float ca=(*pa)-(*ra);
        if(ca<0){
            ca +=2*PI;
        }
        if(ca>2*PI){                        //regle le fish eye
            ca -=2*PI;
        }
        (*disT)=(*disT)*cos(ca);
        float lineH=(mapS*320)/(*disT);
        float lineO=160-lineH/2;
        if(lineH>320){
            lineH=320;
        }
        al_draw_line((*r)*8+530, lineO, (*r)*8+530, lineH+lineO, couleur, 8);






        (*ra)+=DR;
        if((*ra)<0){
            (*ra) += 2*PI;
        }
        if((*ra)>2*PI){
            (*ra) -= 2*PI;
        }
        al_flip_display();

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

    float px, py, pdx, pdy, pa;

    bool done = false;
    px = 300, py = 300;
    pdx = 0;
    pdy = 0;
    pa = 0;

    int r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo, disT;

    while(!done)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);
        if(events.type = ALLEGRO_EVENT_KEY_DOWN)
        {
            InputClavier(events, &px, &py, &pdx, &pdy, &pa, &done);
        }
        drawMap2D();
        RayTracing(&r, &mx, &my, &mp, &dof, &pa, &px, &py, &rx, &ry, &ra, &xo, &yo, &disT, &map);
        dessinerJoueur(px, py);
        al_draw_line(px, py, px+pdx*5, py+pdy*5, al_map_rgb(255, 255, 255), 3);
        al_flip_display();
        al_clear_to_color(al_map_rgb(100,100,100));



    }
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);




}


