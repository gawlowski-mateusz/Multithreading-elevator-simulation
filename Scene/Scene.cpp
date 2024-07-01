#include "Scene.h"
#include <ncurses.h>

Scene::Scene() {
    initialiseScene();
}

Scene::~Scene() {
    endwin();
}

void Scene::initialiseScene() {
    initscr();
    noecho();
    curs_set(FALSE);
    clear();
    refresh();
    getmaxyx(stdscr, height, width);
}

void Scene::printScene() const {
    mvprintw(0, width - 8, "%.8s", "floor_0");
    mvprintw(height * 0.25 - 2, width - 8, "%.8s", "floor_1");
    mvprintw(height * 0.50 - 2, width - 8, "%.8s", "floor_2");
    mvprintw(height * 0.75 - 2, width - 8, "%.8s", "floor_3");
    mvprintw(height - 3, width - 8, "%.8s", "floor_4");
}

int
Scene::getHeight() const {
    return height;
}

int Scene::getWidth() const {
    return width;
}

