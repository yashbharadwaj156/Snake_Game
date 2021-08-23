#include <iostream>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <time.h>

#define MAXSNAKESIZE 100
#define MAXFRAMEX 119
#define MAXFRAMEY 29

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) 
{
	if(size == 0)
	{
		size = 20;
	}
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

class Point{
	private:
		int x;
		int y;
	public:
		Point(){
			x = y = 10;
		} 
		Point(int x, int y){
			this -> x = x;
			this -> y = y;
		}
		void SetPoint(int x, int y){
			this -> x = x;
			this -> y = y;
		}
		int GetX(){
			return x;
		}
		int GetY(){
			return y;
		}
		void MoveUp(){
			y--;
			if( y < 0 )
				y = MAXFRAMEY;
		}
		void MoveDown(){
			y++;
			if( y > MAXFRAMEY )
				y = 0;
		}
		void MoveLeft(){
			x--;
			if( x < 0 )
				x = MAXFRAMEX;
		}
		void MoveRight(){
			x++;
			if( x > MAXFRAMEX )
				x = 0;
		}
		void Draw(char ch='#'){
			gotoxy(x,y);
			cout<<ch;
		}
		void Erase(){
			gotoxy(x,y);
			cout<<" ";
		}
		void CopyPos(Point * p){
			p->x = x;
			p->y = y;
		}
		int IsEqual(Point * p){
			if( p->x == x && p->y ==y )
				return 1;
			return 0;
		}
		void Debug(){
			cout<<"("<<x<<","<<y<<") ";
		}
};

class Snake{
	private:
		Point * cell[MAXSNAKESIZE]; 
		int size; 
		char dir;
		Point fruit; 
		int state; 
		int started;
		int blink; 
	public:
		Snake(){
			size = 1; 
			cell[0] = new Point(20,20); 
			for( int i=1; i<MAXSNAKESIZE; i++){
				cell[i] = NULL;
			}
			fruit.SetPoint(rand()%MAXFRAMEX, rand()%MAXFRAMEY); 
			state = 0;
			started = 0;
		}
		void AddCell(int x, int y){
			cell[size++] = new Point(x,y);
		}
		void TurnUp(){
			if( dir!='s' )
			dir = 'w'; // w is control key for turning upward
		}
		void TurnDown(){
			if( dir!='w' )
			dir = 's'; // s is control key for turning downward
		}
		void TurnLeft(){
			if( dir!='d' )
			dir = 'a'; // a is control key for turning left
		}
		void TurnRight(){
			if( dir!='a' )
			dir = 'd'; // d is control key for turning right
		}
		void WelcomeScreen(){
			
			cout<<"\t\t\t         AUTHOR-YASH BHARADWAJ\n";
			Sleep(1000);
			Beep(500,500);
			cout<<"\t\t\tW E L C O M E   T O   M Y   S N A K E  G A M E\n";
			Sleep(1000);
			Beep(500,500);
			cout<<"\t   ____________________________________________________________________\n";
			SetConsoleTextAttribute(console,15);
			cout<<"\n\t            /^\\/^\\                                             ";
			cout<<"\n\t          _|__|  O|                                              ";
			cout<<"\n\t   \     /~     \\_/ \\                                          ";
			cout<<"\n\t   \____|__________/  \\                                         ";
			cout<<"\n\t         \\_______      \\                                       ";
			cout<<"\n\t                 `\\     \\                 \\                   ";
			cout<<"\n\t                   |     |                  \\                   ";
			cout<<"\n\t                  /      /                    \\                 ";
			cout<<"\n\t                 /     /                       \\\\              ";
			cout<<"\n\t               /      /                         \\ \\            ";
			cout<<"\n\t              /     /                            \\  \\          ";
			cout<<"\n\t            /     /             _----_            \\   \\        ";
			cout<<"\n\t           /     /           _-~      ~-_         |   |          ";
			cout<<"\n\t          (      (        _-~    _--_    ~-_     _/   |          ";
			cout<<"\n\t           \\      ~-____-~    _-~    ~-_    ~-_-~    /          ";
			cout<<"\n\t             ~-_           _-~          ~-_       _-~   - Yash Bharadwaj -";
			cout<<"\n\t                ~--______-~                ~-___-~               ";
		}
		void Move(){
		
			system("cls");
			
			if( state == 0 ){
				if( !started ){
					WelcomeScreen();
					Sleep(1000);
					Beep(500,500);
					cout<<"\n\n\n\t\t\tRULES-";
					cout<<"\n\t\t\t1- w is control key for turning upward";
						cout<<"\n\t\t\t1- a is control key for turning left";
							cout<<"\n\t\t\t1- s is control key for turning downward";
								cout<<"\n\t\t\t1- d is control key for turning right";
					
						Sleep(2000);
					Beep(500,1000);
					cout<<"\n\n\t\tPress E to start-";
					getch();
					started = 1;
					state = 1; 
				}else{
					cout<<"\nGame Over";
					cout<<"\nPress X to start-";
					getch();
					state = 1;
					size = 1;	
				}
			}
			
		
			for(int i=size-1; i>0; i--){
				cell[i-1]->CopyPos(cell[i]);
			}
			
		
			switch(dir){
				case 'w':
					cell[0]->MoveUp();
					break;
				case 's':
					cell[0]->MoveDown();
					break;
				case 'a':
					cell[0]->MoveLeft();
					break;
				case 'd':
					cell[0]->MoveRight();
					break;
			}
			
			if( SelfCollision() )
				state = 0;
				
			
				
			
		
			if( fruit.GetX() == cell[0]->GetX() && fruit.GetY() == cell[0]->GetY()){
				AddCell(0,0);
				fruit.SetPoint(rand()%MAXFRAMEX, rand()%MAXFRAMEY); 	
			}
			
			
			for(int i=0; i<size; i++)
				cell[i]->Draw();
				
			SetConsoleTextAttribute(console,242);
			if( !blink )
				fruit.Draw('O');
			blink = !blink;
			SetConsoleTextAttribute(console,252);
			
			
			
			Sleep(100);
		}
		int SelfCollision(){
			for(int i=1; i<size; i++)
				if( cell[0]->IsEqual(cell[i]) )
					return 1;
			return 0;
		}
		void Debug(){
			for( int i=0; i<size; i++){
				cell[i]->Debug();
			}
		}
};

int main(){

	setcursor(0,0);
	srand( (unsigned)time(NULL));
	

	Snake snake;
	char op = 'l';
	do{
		if(kbhit()){
			op = getch();
		}
		switch(op){
			case 'w':
			case 'W':
				snake.TurnUp();
				break;
			
			case 's':
			case 'S':
				snake.TurnDown();
				break;
			
			case 'a':
			case 'A':
				snake.TurnLeft();
				break;
			
			case 'd':
			case 'D':
				snake.TurnRight();
				break;
		}
		snake.Move();
	}while(op != 'e');
	
	return 0;
}
