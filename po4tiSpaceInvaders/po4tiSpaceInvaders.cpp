#include"game.h"
#include"Menu.h"
#include"MainTheme.h"
#pragma warning(disable:4996)
//struct LC { LC() { system("chcp 1251>nul"); srand((int)time(0)); }~LC() { cin.get(); cin.get();/*system("pause");*/ } }l;

#define ID_START 1
#define ID_INFO 2
#define ID_EXIT 3

int main() {
	setlocale(LC_ALL, "RUSSIAN");
	Menu menu;
	MainTheme Main;
	menu.Add(ID_START, "Начать новую игру");
	menu.Add(ID_INFO, "Информация");
	menu.Add(ID_EXIT, "Выход");
	Main.Print();
	cin.get(); cin.ignore();
	bool bIsExit = false;
	while (!bIsExit) {
		setlocale(LC_ALL, "RUSSIAN");
		int select = menu.Show();
		switch (select) {
		case ID_EXIT: case -1: bIsExit = true; break;
		case ID_START:
		{
			setlocale(0, "C");
			Game* game = new Game();
			game->setupSystem();
			game->initialize();
			while (game->frame());
			game->clear();
			delete game;
		}
		break;
		case ID_INFO:
			system("cls");
			SetPos(31, 8);
			SetColor(ConsoleColor_Blue);
			cout << "КА ШАГ 2019г." << endl;
			SetColor(ConsoleColor_DarkRed);
			SetPos(36, 10);
			cout << "^" << endl;
			SetPos(36, 11);
			cout << "|";
			SetPos(29, 13);
			cout << " <-- " << "SPACE -->";
			cin.get(); cin.ignore();
			break;
		}
	}
}









