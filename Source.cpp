#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
using namespace std;

//constants and enumerations
const float FPS = 60;
const int player1_SIZE = 10;
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
enum DIRECTIONS { RIGHT, LEFT, UP, DOWN };

int lives = 5;

int main() {

	//set up matrix
	int grid[50][50];
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			//set all to 0s except edges
			grid[i][j] = 0;
			if (i == 0 || i == 49 || j == 0 || j == 49)
				grid[i][j] = 1;
		}
	}

	//print to console for testing
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++)
			cout << grid[i][j];
		cout << endl;
	}

	//set up variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *player1 = NULL;
	int player1_x = 300;
	int player1_y = 400;
	bool key[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;
	int dx1 = 0;
	int dy1 = 0;
	int dir = 0;

	//set up allegro stuff
	al_init();
	al_init_primitives_addon();

	al_install_keyboard();

	timer = al_create_timer(1 / FPS);

	display = al_create_display(500, 500);

	player1 = al_create_bitmap(player1_SIZE, player1_SIZE);

	al_set_target_bitmap(player1);

	al_clear_to_color(al_map_rgb(255, 0, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_flip_display();

	al_start_timer(timer);

	//game loop
	while (!doexit)
	{
		//cout << "flag1" << endl;
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		//cout << "flag 6" << endl;
		//physics section
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (key[KEY_UP]) {
				//notice we just set the velocity, NOT the position... the bike will move up until another
				dy1 = -2;
				dx1 = 0;
				dir = UP;//used for collision later

			}

			if (key[KEY_DOWN]) {
				dy1 = 2;
				dx1 = 0;
				dir = DOWN;
			}

			if (key[KEY_LEFT]) {
				dx1 = -2;
				dy1 = 0;
				dir = LEFT;
			}

			if (key[KEY_RIGHT]) {
				dx1 = 2;
				dy1 = 0;
				dir = RIGHT;
			}
			//cout << "flag 5" << endl;
			//move player one
			player1_x += dx1;
			player1_y += dy1;

			//draw a line behind the bike
			grid[(player1_x) / 10][(player1_y) / 10] = 2;

			//check right collision for p1
			if (dir == RIGHT && grid[(player1_x + 10) / 10][player1_y / 10] != 0) {
				cout << "CRASH" << endl; //you need to do something more here : /
				grid[(player1_x) / 10][(player1_y) / 10] = 0;
				if (grid[(player1_x) / 10][(player1_y) / 10] == 0) {
					for (int i = 0; i < 50; i++) {
						for (int j = 0; j < 50; j++) {
							grid[i][j] = 0;

						}
					}
					//cout << "flag 4" << endl;
				}
				player1_x = 300;
				player1_y = 400;
			}
			if (dir == LEFT && grid[(player1_x - 10) / 10][player1_y / 10] != 0) {
				cout << "CRASH" << endl;
				grid[(player1_x) / 10][(player1_y) / 10] = 0;
				if (grid[(player1_x) / 10][(player1_y) / 10] == 0) {
					for (int i = 0; i < 50; i++) {
						for (int j = 0; j < 50; j++) {
							grid[i][j] = 0;

						}
					}
				}
				player1_x = 300;
				player1_y = 400;
			}
			if (dir == DOWN && grid[player1_x / 10][(player1_y + 10) / 10] != 0) {
				cout << "CRASH" << endl;
				grid[(player1_x) / 10][(player1_y) / 10] = 0;
				if (grid[(player1_x) / 10][(player1_y) / 10] == 0) {
					for (int i = 0; i < 50; i++) {
						for (int j = 0; j < 50; j++) {
							grid[i][j] = 0;

						}
					}
				}
				player1_x = 300;
				player1_y = 400;
			}
			if (dir == UP && grid[player1_x / 10][(player1_y - 10) / 10] != 0) {
				cout << "CRASH" << endl;
				grid[(player1_x) / 10][(player1_y) / 10] = 0;
				if (grid[(player1_x) / 10][(player1_y) / 10] == 0) {
					for (int i = 0; i < 50; i++) {
						for (int j = 0; j < 50; j++) {
							grid[i][j] = 0;
						}
					}
				}
				player1_x = 300;
				player1_y = 400;
			}
			redraw = true;
		}
		//kill program when window x is pressed
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		//check if keys are pressed down
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			}
		}
		//check if keys released
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;
			}
		}//added this
		if (redraw && al_is_event_queue_empty(event_queue)) {

			redraw = false;
			//wipe screen black
			//cout << "flag3" << endl;
			al_clear_to_color(al_map_rgb(0, 0, 0));


			//walk through matrix, color 1s white and 2s blue
			for (int i = 0; i < 50; i++) {
				for (int j = 0; j < 50; j++) {
					if (grid[i][j] == 1)
						al_draw_filled_rectangle(i * 10, j * 10, i * 10 + 10, j * 10 + 10, al_map_rgb(255, 255, 255));
					if (grid[i][j] == 2)
						al_draw_filled_rectangle(i * 10, j * 10, i * 10 + 10, j * 10 + 10, al_map_rgb(0, 255, 255));
				}
			}
			//cout << "flag2" << endl;
			//draw player
			al_draw_bitmap(player1, player1_x, player1_y, 0);

			al_flip_display();
		}//really ends render section


		 //}//end render section
	}//end game loop

	 //clear up memory
	al_destroy_bitmap(player1);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}