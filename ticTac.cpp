#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
bool isWin = false;
int currentSymbol = 1;
char userFirst;

void optimize(int Board[9]);
void makeMove(int arr[],int input);
bool isFull(int arr[]);
void printBoard(int square[]);
void takeInput(int arr[]);
bool attack(int Board[9]);
bool defend(int Board[9]);
bool select(int Board[9]);
//bool optimize(int Board[9]);
bool validMove(int index,int factor){
	if(index+factor>=0 && index+factor<=8){
		return true;
	}
	return false;
}
int calcScore(int index1,int index2, int index3,int Board[9]){
	if( Board[index1+index2]==0 || Board[index1+index3]==0)
		return 20;
	else if (Board[index1+index2]==1 || Board[index1+index3]==1){
		return 100;
	}
	else{
		return 40;
	}
}
bool validHorizontal(int index1,int index2,int index3){
	if(3*index1+index2+index3 + 3 == 6 || 3*index1+index2+index3 + 3 == 15 || 3*index1+index2+index3 + 3 ==24){
		return true;
	}
	else{
		return false;
	}
}
bool validVertical(int index1,int index2,int index3){
	return true;
}
bool validDiagonal1(int index1,int index2,int index3){
	if(3*index1+index2+index3 + 3 == 15){
		return true;
	}
	else{
		return false;
	}
}
bool validDiagonal2(int index1,int index2,int index3){
	if(3*index1+index2+index3 + 3 == 15){
		return true;
	}
	else{
		return false;
	}
}
int CalcBest(int index,int Board[9]){
	//Horizontal Score
	int score=0;
	int counter=0;
	int hori,verti,diag;
	hori=0;
	verti=0;
	diag=0;
	if(validMove(index,1)){	
		if(validMove(index,2)!=0){
			if(validHorizontal(index,1,2)){
				score+=calcScore(index,1,2,Board);
				counter++;
				hori++;
			}
		}
	}
	if(validMove(index,-1)){	
		if(validMove(index,1)!=0){
			if(validHorizontal(index,-1,1)){
				score+=calcScore(index,-1,1,Board);
				counter++;
				hori++;
			}
		}
	}
	if(validMove(index,-1)){	
		if(validMove(index,-2)!=0){
			if(validHorizontal(index,-1,-2)){
				score+=calcScore(index,-1,-2,Board);
				counter++;
				hori++;
			}
		}
	}
	//Vertical Score
	if(validMove(index,3)){	
		if(validMove(index,6)!=0){
			if(validVertical(index,3,6)){
				score+=calcScore(index,3,6,Board);
				counter++;
				verti++;
			}
		}
	}
	if(validMove(index,3)){	
		if(validMove(index,-3)!=0){
			if(validVertical(index,3,-3)){
				score+=calcScore(index,3,-3,Board);
				counter++;
				verti++;
			}
		}
	}
	if(validMove(index,-3)){	
		if(validMove(index,-6)!=0){
			if(validVertical(index,-3,-6)){
				score+=calcScore(index,-3,-6,Board);
				counter++;
				verti++;
			}
		}
	}
	//Diagonal1 Score
	if(validMove(index,4)){	
		if(validMove(index,8)!=0){
			if(validDiagonal1(index,4,8)){
				score+=calcScore(index,4,8,Board);
				counter++;
				diag++;
			}
		}
	}
	if(validMove(index,4)){
		if(validMove(index,-4)!=0){
			if(validDiagonal1(index,4,-4)){
				score+=calcScore(index,-4,4,Board);
				counter++;
				diag++;
			}
		}
	}
	if(validMove(index,-4)){
		if(validMove(index,-8)!=0){
			if(validDiagonal1(index,-4,-8)){
				score+=calcScore(index,-4,-8,Board);
				counter++;
				diag++;
			}
		}
	}
	//Diagonal2 Score
	if(validMove(index,2)){	
		if(validMove(index,4)!=0){
			if(validDiagonal2(index,2,4)){
				score+=calcScore(index,2,4,Board);
				counter++;
				diag++;
			}
		}
	}
	if(validMove(index,2)){	
		if(validMove(index,-2)!=0){
			if(validDiagonal2(index,2,-2)){
				score+=calcScore(index,2,-2,Board);
				counter++;
				diag++;
			}
		}
	}
	if(validMove(index,-2)){	
		if(validMove(index,-4)!=0){
			if(validDiagonal1(index,-2,-4)){
				score+=calcScore(index,-2,-4,Board);
				counter++;
				diag++;
			}
		}
	}
	//cout<<counter<<" "<<hori<<" "<<verti<<" "<<diag<<endl;
	return score;
}
void optimize(int Board[9]){
	int max=0;
	int index=0;
	for(int i=0;i<9;i++){
		if (Board[i]==-1){
			if(CalcBest(i,Board)>max){
				max=CalcBest(i,Board);
				index=i;
			}
		}
	}
	Board[index]=1;
}

bool attack(int Board[9]){
    int x1=Board[0];
    int x2=Board[1];
    int x3=Board[2];
    int x4=Board[3];
    int x5=Board[4];
    int x6=Board[5];
    int x7=Board[6];
    int x8=Board[7];
    int x9=Board[8];
    if((x1==1 && x2==1 && x3==-1) || (x1==1 && x2==-1 && x3==1) || (x1==-1 && x2==1 && x3==1)){
        if(x3==-1){
            Board[2]= 1;
        }
        else if(x2==-1){
            Board[1] = 1;
        }
        else{
            Board[0]= 1;
        }
        return true;
    }
    else if ((x4==1 && x5==1 && x6==-1) || (x4==1 && x5==-1 && x6==1) || (x4==-1 && x5==1 && x6==1)){
        if(x4==-1){
            Board[3]= 1;
        }
        else if(x5==-1){
            Board[4] = 1;
        }
        else{
            Board[5]= 1;
        }
        return true;
    }
    else if ((x7==1 && x8==1 && x9==-1) || (x7==1 && x8==-1 && x9==1) || (x7==-1 && x8==1 && x9==1)){
        if(x7==-1){
            Board[6]= 1;
        }
        else if(x8==-1){
            Board[7] = 1;
        }
        else{
            Board[8]= 1;
        }
        return true;
    }
    else if ((x1==1 && x4==1 && x7==-1) || (x1==1 && x4==-1 && x7==1) || (x1==-1 && x4==1 && x7==1)){
        if(x1==-1){
            Board[0]=1;
        }
        else if(x4==-1){
            Board[3]=1;
        }
        else{
            Board[6]=1;
        }
        return true;
    }
    else if ((x2==1 && x5==1 && x8==-1) || (x2==1 && x5==-1 && x8==1) || (x2==-1 && x5==1 && x8==1)){
        if(x2==-1){
            Board[1]=1;
        }
        else if(x5==-1){
            Board[4]=1;
        }
        else{
            Board[7]=1;
        }
        return true;
    }
    else if ((x3==1 && x6==1 && x9==-1) || (x3==1 && x6==-1 && x9==1) || (x3==-1 && x6==1 && x9==1)){
        if(x3==-1){
            Board[2]=1;
        }
        else if(x6==-1){
            Board[5]=1;
        }
        else{
            Board[8]=1;
        }
        return true;
    }
    else if ((x1==1 && x5==1 && x9==-1) || (x1==1 && x5==-1 && x9==1) || (x1==-1 && x5==1 && x9==1)){
        if(x1==-1){
            Board[0]=1;
        }
        else if(x5==-1){
            Board[4]=1;
        }
        else{
            Board[8]=1;
        }
        return true;
    }
    else if ((x3==1 && x5==1 && x7==-1) || (x3==1 && x5==-1 && x7==1) || (x3==-1 && x5==1 && x7==1)){
        if(x3==-1){
            Board[2]=1;
        }
        else if(x5==-1){
            Board[4]=1;
        }
        else{
            Board[6]=1;
        }
        return true;
    }
    else{
        return false;
    }
}
bool defend(int Board[9]){
    int x1=Board[0];
    int x2=Board[1];
    int x3=Board[2];
    int x4=Board[3];
    int x5=Board[4];
    int x6=Board[5];
    int x7=Board[6];
    int x8=Board[7];
    int x9=Board[8];
    if((x1==0 && x2==0 && x3==-1) || (x1==0 && x2==-1 && x3==0) || (x1==-1 && x2==0 && x3==0)){
        if(x3==-1){
            Board[2]= 1;
        }
        else if(x2==-1){
            Board[1] = 1;
        }
        else{
            Board[0]= 1;
        }
        return true;
    }
    else if ((x4==0 && x5==0 && x6==-1) || (x4==0 && x5==-1 && x6==0) || (x4==-1 && x5==0 && x6==0)){
        if(x4==-1){
            Board[3]= 1;
        }
        else if(x5==-1){
            Board[4]= 1;
        }
        else{
            Board[5]= 1;
        }
        return true;
    }
    else if ((x7==0 && x8==0 && x9==-1) || (x7==0 && x8==-1 && x9==0) || (x7==-1 && x8==0 && x9==0)){
        if(x7==-1){
            Board[6]= 1;
        }
        else if(x8==-1){
            Board[7] = 1;
        }
        else{
            Board[8]= 1;
        }
        return true;
    }
    else if ((x1==0 && x4==0 && x7==-1) || (x1==0 && x4==-1 && x7==0) || (x1==-1 && x4==0 && x7==0)){
        if(x1==-1){
            Board[0]=1;
        }
        else if(x4==-1){
            Board[3]=1;
        }
        else{
            Board[6]=1;
        }
        return true;
    }
    else if ((x2==0 && x5==0 && x8==-1) || (x2==0 && x5==-1 && x8==0) || (x2==-1 && x5==0 && x8==0)){
        if(x2==-1){
            Board[1]=1;
        }
        else if(x5==-1){
            Board[4]=1;
        }
        else{
            Board[7]=1;
        }
        return true;
    }
    else if ((x3==0 && x6==0 && x9==-1) || (x3==0 && x6==-1 && x9==0) || (x3==-1 && x6==0 && x9==0)){
        if(x3==-1){
            Board[2]=1;
        }
        else if(x6==-1){
            Board[5]=1;
        }
        else{
            Board[8]=1;
        }
        return true;
    }
    else if ((x1==0 && x5==0 && x9==-1) || (x1==0 && x5==-1 && x9==0) || (x1==-1 && x5==0 && x9==0)){
        if(x1==-1){
            Board[0]=1;
        }
        else if(x5==-1){
            Board[4]=1;
        }
        else{
            Board[8]=1;
        }
        return true;
    }
    else if ((x3==0 && x5==0 && x7==-1) || (x3==0 && x5==-1 && x7==0) || (x3==-1 && x5==0 && x7==0)){
        if(x3==-1){
            Board[2]=1;
        }
        else if(x5==-1){
            Board[4]=1;
        }
        else{
            Board[6]=1;
        }
        return true;
    }
    else{
        return false;
    }
}
bool select(int Board[9]){
    if(!attack(Board)){
        if(!defend(Board)){
            optimize(Board);
        }
    }
    else{
        cout<<"YOU LOST"<<endl;
        isWin=true;
        return true;
    }
    return false;
}
void printBoard(int square[])
{

    char arr[9];
    if(userFirst=='N' || userFirst=='n')
    {
        cout<<"You are O , Computer is X"<<endl;
    for(int i = 0; i<9 ; i++){
        if(square[i] < 0){
            arr[i] = ' ';
        }
    
        else if(square[i]==0){
            arr[i] = 'O';
        }
        else{
            arr[i] = 'X';
        }
    }
    }
    else
    {
       for(int i = 0; i<9 ; i++){
        if(square[i] < 0){
            arr[i] = ' ';
        }
    
        else if(square[i]==0){
            arr[i] = 'X';
        }
        else{
            arr[i] = 'O';
        }  
    }
    }
    
  //  cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
    cout << endl;

    cout << "           |     |     " << endl;
    cout << "        " << arr[0] << "  |  " << arr[1] << "  |  " << arr[2] << endl;

    cout << "      _____|_____|_____" << endl;
    cout << "           |     |     " << endl;

    cout << "        " << arr[3] << "  |  " << arr[4] << "  |  " << arr[5] << endl;

    cout << "      _____|_____|_____" << endl;
    cout << "           |     |     " << endl;

    cout << "        " << arr[6] << "  |  " << arr[7] << "  |  " << arr[8] << endl;

    cout << "           |     |     " << endl << endl;
    //cout << " ==========================";
}
bool isFull(int arr[]){
    int flag = 0;
    for(int i = 0; i<9; i++){
        if(arr[i]<0){
            flag=1;
        }
    }
    if(flag==1)return false;
    cout<<"GAME OVER"<<endl;
    return true;
}
void takeInput(int arr[]){
    int input;
   bool rj=0;
    while(rj!=1)
    {
    cout<<endl<<"Type in an integer corresponding to STANDARD NOTATION :  "<<endl;

    cin>>input;
    if(arr[input-1]==-1){
        makeMove(arr , input);
       rj=1;
    }
    else
    {
      cout<<endl;
      cout<<"That place is already taken"<<endl;
    }
}
    
}
void makeMove(int arr[],int input){
    arr[input-1] = 0;
   }
    


int main() {
  int arr[9] = {0};
    for(int i = 0; i<9; i++){
        arr[i] = i+1;
    }
        cout << "    \n\n\tTic Tac Toe\n\n";
    cout << "        STANDARD NOTATION"<<endl<< endl;
    cout << "           |     |     " << endl;
    cout << "        " << arr[0] << "  |  " << arr[1] << "  |  " << arr[2] << endl;

    cout << "      _____|_____|_____" << endl;
    cout << "           |     |     " << endl;

    cout << "        " << arr[3] << "  |  " << arr[4] << "  |  " << arr[5] << endl;

    cout << "      _____|_____|_____" << endl;
    cout << "           |     |     " << endl;

    cout << "        " << arr[6] << "  |  " << arr[7] << "  |  " << arr[8] << endl;

    cout << "           |     |     " << endl << endl;
   // cout << "PLAYER 1 IS \"X\", PLAYER 2 IS \"O\" "<<endl;
   // cout << "  ==========================";
    //initialize all array value to -1 (ie. empty)
    for(int i = 0; i<9; i++){
        arr[i] = -1;
    }
    
    cout << "  Do you want to go first ?  Y/N ";
    cin>>userFirst;
    //Some Logic Here
    
if(userFirst=='Y' || userFirst=='y'){  
cout<<"You are X , Computer is O"<<endl;  
  while(!(isFull(arr)) && !(isWin)){
      //while(takeInput(arr)){
        //printBoard(arr);   
    
        takeInput(arr);
        printBoard(arr);
        select(arr);
        printBoard(arr);
  }
}
else
{
   while(!(isFull(arr)) && !(isWin)){
      //while(takeInput(arr)){
        //printBoard(arr);   
      
        printBoard(arr);
        select(arr); 
        printBoard(arr); 
        if(!isWin){
            takeInput(arr);
        }
    }
  
  
}
return 0;
}