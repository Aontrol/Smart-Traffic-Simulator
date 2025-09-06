#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

int winX = 0;
int winY = 0;

int vehicle_count = 0;

// Vehicles count in routes
int R_UP_VCount = 0;
int R_DOWN_VCount = 0;
int R_LEFT_VCount = 0;
int R_RIGHT_VCount = 0;

struct vehicles
{
    int route;
    int dir;
    int x, y;
} vehicle[500];

void display_values()
{
    WINDOW *parameter_win = newwin(9, 26, 1, winX - 30);

    werase(parameter_win);

    wmove(parameter_win, 1, 1);
    wattron(parameter_win, A_STANDOUT);
    wprintw(parameter_win, "    ----Parameter----   ");
    wattroff(parameter_win, A_STANDOUT);

    wmove(parameter_win, 2, 1);
    wprintw(parameter_win, "Total Vehicle : %d", vehicle_count);
    wmove(parameter_win, 3, 1);
    wprintw(parameter_win, "----Traffic Density----");
    wmove(parameter_win, 4, 1);
    wprintw(parameter_win, "Left Route  : %d", R_LEFT_VCount);
    wmove(parameter_win, 5, 1);
    wprintw(parameter_win, "Right Route : %d", R_RIGHT_VCount);
    wmove(parameter_win, 6, 1);
    wprintw(parameter_win, "Up Route    : %d", R_UP_VCount);
    wmove(parameter_win, 7, 1);
    wprintw(parameter_win, "Down Route  : %d", R_DOWN_VCount);

    box(parameter_win, 0, 0);
    wrefresh(parameter_win);
}

void create_vehicle(int route, int centerX, int centerY)
{
    int offset = 2;

    if ((route == UP && R_UP_VCount >= (winY / 2) - 1 - offset) ||
        (route == DOWN && R_DOWN_VCount >= (winY / 2) - 1 - offset) ||
        (route == LEFT && R_LEFT_VCount >= ((winY / 2) * 2) - 1 - offset) ||
        (route == RIGHT && R_RIGHT_VCount >= ((winY / 2) * 2) - 1 - offset))
    {
        return;
    }
    vehicle[vehicle_count].dir = rand() % 4;
    vehicle[vehicle_count].route = route;

    int rightStartPoint = centerX + offset + R_RIGHT_VCount;
    int leftStartPoint = centerX - offset - R_LEFT_VCount;
    int upStartPoint = centerY - offset - R_UP_VCount;
    int downStartPoint = centerY + offset + R_DOWN_VCount;

    switch (route)
    {
    case UP:
        mvaddch(upStartPoint, centerX, 'v');
        vehicle[vehicle_count].x = centerX;
        vehicle[vehicle_count].y = upStartPoint;

        R_UP_VCount++;
        break;
    case DOWN:
        mvaddch(downStartPoint, centerX, 'v');
        vehicle[vehicle_count].x = centerX;
        vehicle[vehicle_count].y = downStartPoint;

        R_DOWN_VCount++;
        break;
    case LEFT:
        mvaddch(centerY, leftStartPoint, 'v');
        vehicle[vehicle_count].x = leftStartPoint;
        vehicle[vehicle_count].y = centerY;

        R_LEFT_VCount++;
        break;
    case RIGHT:
        mvaddch(centerY, rightStartPoint, 'v');
        vehicle[vehicle_count].x = rightStartPoint;
        vehicle[vehicle_count].y = centerY;

        R_RIGHT_VCount++;
        break;
    }
    vehicle_count++;
    display_values();
    refresh();
}

void draw_vertical_layout(int x, int y, int dir)
{
    move(y, x);
    char verticalChar = 179;
    addch(verticalChar);
    if (dir == UP)
    {
        R_UP_VCount--;
    }
    else if (dir == DOWN)
    {
        R_DOWN_VCount--;
    }
    refresh();
}
void draw_horizontal_layout(int x, int y, int dir)
{
    move(y, x);
    char horizontalChar = 196;
    addch(horizontalChar);
    if (dir == LEFT)
    {
        R_LEFT_VCount--;
    }
    else if (dir == RIGHT)
    {
        R_RIGHT_VCount--;
    }
    refresh();
}

void draw_layout(int centerX, int centerY)
{
    int j = 4;
    int tempX = 0;
    int tempY = 0;
    int dir = 0;

    char verticalChar = 179;
    char horizontalChar = 196;

    while (j--)
    {
        tempX = centerX;
        tempY = centerY;
        for (int i = 0; i < (winY / 2) - 1; i++)
        {
            move(tempY, tempX);
            switch (dir)
            {
            case UP:
                addch(verticalChar);
                tempY--;
                break;
            case DOWN:
                addch(verticalChar);
                tempY++;
                break;
            case LEFT:
                addch(horizontalChar);
                tempX--;
                addch(horizontalChar);
                tempX--;
                break;
            case RIGHT:
                addch(horizontalChar);
                tempX++;
                addch(horizontalChar);
                tempX++;
                break;
            }
        }
        dir++;
    }
    move(centerY, centerX + 1);
    addch(' ');
    move(centerY, centerX - 1);
    addch(' ');
    move(centerY + 1, centerX);
    addch(' ');
    move(centerY - 1, centerX);
    addch(' ');
    refresh();
}

void reset_parameter()
{
    R_UP_VCount = 0;
    R_DOWN_VCount = 0;
    R_LEFT_VCount = 0;
    R_RIGHT_VCount = 0;

    vehicle_count = 0;
}

int traffic_dencity(){
     struct direction
    {
        int up;
        int down;
        int right;
        int left;
    } route_count = {0};

    for (int i = 0; i < vehicle_count; i++)
    {
        switch (vehicle[i].route)
        {
        case UP:
            route_count.up++;
            break;
        case DOWN:
            route_count.down++;
            break;
        case RIGHT:
            route_count.right++;
            break;
        case LEFT:
            route_count.left++;
            break;
        }
    }

    int long_traffic_dir = UP;
    int largest = route_count.up;
    if (route_count.down > largest)
    {
        largest = route_count.down;
        long_traffic_dir = DOWN;
    }
    if (route_count.right > largest)
    {
        largest = route_count.right;
        long_traffic_dir = RIGHT;
    }
    if (route_count.left > largest)
    {
        largest = route_count.left;
        long_traffic_dir = LEFT;
    }

    return long_traffic_dir;
}

void start_simulation()
{

   int long_traffic_dir = traffic_dencity();

    for (int i = vehicle_count - 1; i >= 0; i--)
    {
        if (long_traffic_dir == vehicle[i].route)
        {
            switch (vehicle[i].route)
            {
            case UP:
                draw_vertical_layout(vehicle[i].x, vehicle[i].y, UP);
                break;
            case DOWN:
                draw_vertical_layout(vehicle[i].x, vehicle[i].y, DOWN);
                break;
            case LEFT:
                draw_horizontal_layout(vehicle[i].x, vehicle[i].y, LEFT);
                break;
            case RIGHT:
                draw_horizontal_layout(vehicle[i].x, vehicle[i].y, RIGHT);
                break;
            }
            napms(150);
            display_values();
        }
    }

    for (int i = vehicle_count - 1; i >= 0; i--)
    {
        if (long_traffic_dir != vehicle[i].route)
        {
            switch (vehicle[i].route)
            {
            case UP:
                draw_vertical_layout(vehicle[i].x, vehicle[i].y, UP);
                break;
            case DOWN:
                draw_vertical_layout(vehicle[i].x, vehicle[i].y, DOWN);
                break;
            case LEFT:
                draw_horizontal_layout(vehicle[i].x, vehicle[i].y, LEFT);
                break;
            case RIGHT:
                draw_horizontal_layout(vehicle[i].x, vehicle[i].y, RIGHT);
                break;
            }
            napms(150);
            display_values();
        }
    }

    reset_parameter();
    display_values();
}

int main()
{
    WINDOW *main_win = initscr();
    curs_set(0);

    cbreak();
    noecho();
    keypad(main_win, TRUE);

    box(main_win, 0, 0);

    move(1, 3);
    attron(A_STANDOUT);
    addstr("----Smart Traffic Simulator----");
    attroff(A_STANDOUT);
    refresh();

    getmaxyx(main_win, winY, winX);

    int scrCenterX = winX / 2;
    int scrCenterY = winY / 2;

    move(winY - 1, 5);
    printw("Press 'q' to exit from simulator");

    move(winY - 1, winX - 33);
    printw("Press 's' to start simulation");

    move(winY - 8, winX - 26);
    printw("By : Abhirama Mankalale");

    move(winY - 8, 3);
    printw("Press arrow right for vehicle right");
    move(winY - 7, 3);
    printw("Press arrow left for vehicle left");
    move(winY - 6, 3);
    printw("Press arrow up for vehicle up");
    move(winY - 5, 3);
    printw("Press arrow down for vehicle down");

    display_values();
    refresh();

    draw_layout(scrCenterX, scrCenterY);

    int ch;
    while ((ch = getch()) != 'q')
    {
        if (ch == KEY_UP)
        {
            create_vehicle(UP, scrCenterX, scrCenterY);
        }

        if (ch == KEY_DOWN)
        {
            create_vehicle(DOWN, scrCenterX, scrCenterY);
        }

        if (ch == KEY_LEFT)
        {
            create_vehicle(LEFT, scrCenterX, scrCenterY);
        }

        if (ch == KEY_RIGHT)
        {
            create_vehicle(RIGHT, scrCenterX, scrCenterY);
        }

        if (ch == 's')
        {
            start_simulation();
        }
    }

    endwin();
    return 0;
}
