#include<map>
#include <stdio.h>
#include<string>
#include<windows.h>
#include<ctime>     //时间的创建
#include<cassert> 
#include <iostream>
#include <utility>

#define N 9  //定义
#define EDGE 9 


int gokong[EDGE][EDGE]; //0=该空点未曾计算过气，1=已计算，避免重复计算公气
int gozi[EDGE][EDGE]; //0=该子未计算串气，1=已计算，避免重复计算同一个子的气
int goqi; //此棋串气数
int goziLength;//此棋串子数
int g_gozi[EDGE][EDGE];

int s = 0, ais = 1, s0;//s是轮到谁下,s=1,2，s=1是ai下，s=2是玩家，s=s0是黑方下，否则是白方下
using namespace std;
int p[N + 2][N + 2]; //0空1黑2白  1●2○ -1▲-2△


int manu[2][300], manukey = 0;//棋谱
int out(int i, int j)//打印棋盘
{
    if (p[i][j] == 1)return printf("●");
    if (p[i][j] == 2)return printf("○");
    if (p[i][j] == -1)return printf("▲");
    if (p[i][j] == -2)return printf("△");
    if (i == N)
    {
        if (j == 1)return printf("┏");
        if (j == N)return printf("┓");
        return printf("┯");
    }
    if (i == 1)
    {
        if (j == 1)return printf("┗");
        if (j == N)return printf("┛");
        return printf("┷");
    }
    if (j == 1)return printf("┠");
    if (j == N)return printf("┨");
    return printf("┼");
}
 void DrawBoard()//打印整个游戏界面
{
    system("cls");
    int row = 0, col = 0, keyr = 0, keyc = 0;
    char alpha = 'A';
    printf("\n\n\n     ");
    for (col = 1; col <= N; col++)printf("%c ", alpha++);
    for (row = N; row >= 1; row--)
    {
        printf("\n   %2d", row);
        for (col = 1; col <= N; col++)
        {
            out(row, col);
            if (p[row][col] < 0)keyr = row, keyc = col;
        }
        printf("%d", row);
    }
    alpha = 'A';
    printf("\n     ");
    for (col = 1; col <= N; col++)printf("%c ", alpha++);
    printf("\n\n");
    if (s0 == ais)printf("  AI执黑，玩家执白\n");
    else printf("  AI执白，玩家执黑\n");
    alpha = 'A';
    if (keyr)printf("  最后落子位置：%c%d\n", alpha + keyc - 1, keyr);
}

 void init()//游戏开局初始化
{
    system("color f0");
    printf("输入1或者2进行选择\n1，AI执黑先行\n2，玩家执黑先行\n");
    scanf("%d", &s);
    if (s != 1 && s != 2)return init();
    s0 = s;
    int i, j;
    for (i = 0; i <= N + 1; i++)for (j = 0; j <= N + 1; j++)p[i][j] = 0;//以空格包围棋盘	
    DrawBoard();
    for (j = 0; j < 300; j++)manu[0][j] = manu[1][j] = 0;
}



bool inboard(int row, int col)//判断(row,col)是否在棋盘内
{
    if (row <1 || row > N)return false;
    return col >= 1 && col <= N;
}

bool ok(int row, int col)//能否落子
{
    return inboard(row, col) && (p[row][col] == 0);
}

void go(int row, int col)//落下一子
{
    if (s == s0)p[row][col] = -1; //标出最新下的棋
    else p[row][col] = -2;
    for (int i = 0; i <= N; i++)for (int j = 0; j <= N; j++) //取消上一个最新棋的标识
    {
        if (i == row && j == col)continue;
        if (p[i][j] < 0)p[i][j] *= -1;
    }
    DrawBoard();
    
    if (ok(row, col))
    {
        printf("禁手\n");
        if (s0 == 1)printf("玩家胜");
        else printf("AI胜");
        Sleep(10000);
    }

    manu[0][manukey] = row, manu[1][manukey++] = col;
}

void out_manual()
{
    char alpha = 'A';
    int i;
    printf("\n  本局棋谱: ");
    for (i = 0; i < manukey; i += 2){
	printf("  B[%c%d]", alpha + manu[1][i] - 1, manu[0][i]);
    /*printf("\n  白方落子位置: ");
    for (i = 1; i < manukey; i += 2)*/printf("  W[%c%d]", alpha + manu[1][i+1] - 1, manu[0][i+1]);}
    Sleep(50000);
}
void player()
{
    DrawBoard();
 
 
 
    printf("  轮到玩家下，请输入坐标(输入=0查看棋谱)： ");
    char c = '\n';
    int row = 0, col = 0;
    while (c<'0')scanf("%c%d", &c, &row);
    if (c == '=')
    {
        out_manual();
        return player();
    }
    if (c < 'a')col = c - 'A' + 1;
    else col = c - 'a' + 1;
    if (!ok(row, col))
    {
        printf("此处不能下");
        Sleep(1000);
        return player();
    }
    go(row, col);
}

 void str_qi(int x,int y,int hb)
  {
    //本函数计算 x,y 处的hb颜色棋子的气
    gozi[x][y]=1; //标记本子已经计算过气
    goziLength++;
    //右临子
    if (x+1<=9)//如果没有超出棋盘边线
    {
      if ((p[x+1][y]==0)&&(gokong[x+1][y]==0))
      //如果右临点为空并且该点未曾计算过气则
      {
        goqi++; //气数加一
        gokong[x+1][y]=1; //标记本空点已经计算过气
      }
      else if ((p[x+1][y]==hb||p[x+1][y]== -hb)&&(gozi[x+1][y]==0))
      //否则如果右临点为和本子同色子并且该子未曾计算过气则
      str_qi(x+1,y,hb); //递归调用到右临子
    }
    //左临子
    if (x-1>=1) //果没有超出棋盘边线
    {
      if ((p[x-1][y]==0)&&(gokong[x-1][y]==0))
      //如果左临点为空并且该点未曾计算过气则
      {
        goqi++; //气数加一
        gokong[x-1][y]=1; //标记本空点已经计算过气
      }
      else if ((p[x-1][y]==hb||p[x-1][y]== -hb)&&(gozi[x-1][y]==0))
      //否则如果左临点为和本子同色子并且该子未曾计算过气则
      str_qi(x-1,y,hb); //递归调用到左临子
    }
    //下临子
    if (y-1>=1)//如果没有超出棋盘边线
    {
      if ((p[x][y-1]==0)&&(gokong[x][y-1]==0))
      //如果下临点为空并且该点未曾计算过气则
      {
        goqi++; //气数加一
        gokong[x][y-1]=1; //标记本空点已经计算过气
      }
      else if ((p[x][y-1]==hb||p[x][y-1]== -hb)&&(gozi[x][y-1]==0))
      //否则如果下临子点为和本子同色子并且该子未曾计算过气则
      str_qi(x,y-1,hb); //递归调用到下临子
    }
    //上临点
    if (y+1<=9)//如果没有超出棋盘边线
    {
      if ((p[x][y+1]==0)&&(gokong[x][y+1]==0))
      //如果上临点为空并且该点未曾计算过气则
      {
        goqi++; //气数加一
        gokong[x][y+1]=1; //标记本空点已经计算过气
      }
      else if ((p[x][y+1]==hb||p[x][y+1]== -hb)&&(gozi[x][y+1]==0))
      //否则如果上临点为和本子同色子并且该子未曾计算过气则
      str_qi(x,y+1,hb); //递归调用到上临子
    }
  }
 
  std::pair<int,int> str_lib(int x,int y, int hb)
  {
 
    for (int i = 1; i <=9 ; i++)
      for (int j = 1; j <=9; j++)
      {
        gozi[i][j] = 0; //初始化变量，表示该子未计算串气
        gokong[i][j] = 0; //初始化变量，表示该空点未计算串气
      }
    goqi=0; //棋串气初值
    goziLength=0;//棋串初始子数
    str_qi(x,y,hb); //调用串气子程序
    for(int i=0;i<EDGE;i++)
     for(int j=0;j<EDGE;j++){
      if(gozi[i][j]==1)
      g_gozi[i][j]=1;
     }
    return std::make_pair<int,int>(goqi,goziLength);
  }
 



//计算对手是黑棋的气 
int AIB2(int i,int j){
	int flag1,flag2,flag3,flag4;
	if(p[i-1][j]==1||p[i-1][j]==-1){
		flag1=str_lib(i-1,j,1).first;
	}
		if(p[i+1][j]==1||p[i+1][j]==-1){
		flag2=str_lib(i+1,j,1).first;
	}
		if(p[i][j-1]==1||p[i][j-1]==-1){
		flag3=str_lib(i,j-1,1).first;
	}
		if(p[i][j+1]==1||p[i][j+1]==-1){
		flag4=str_lib(i,j+1,1).first;
	}
	if(flag1==1||flag2==1||flag3==1||flag4==1){
		return 0;
	}
	else {
	return 1;} 
	
}//计算对手是白棋的气 
int AIW2(int i,int j){
	int flag1,flag2,flag3,flag4;
	if(p[i-1][j]==2||p[i-1][j]==-2){
		flag1=str_lib(i-1,j,2).first;
	}
		if(p[i+1][j]==2||p[i+1][j]==-2){
		flag2=str_lib(i+1,j,2).first;
	}
		if(p[i][j-1]==2||p[i][j-1]==-2){
		flag3=str_lib(i,j-1,2).first;
	}
		if(p[i][j+1]==2||p[i][j+1]==-2){
		flag4=str_lib(i,j+1,2).first;
	}
	if(flag1==1||flag2==1||flag3==1||flag4==1){
		return 0;
	}
	else{
	return 1;} 
	
}  
int p1,p2;
void AI1(){
	
	if(p[9][1]==0){
	p1=9,p2=1;
	 return go(9,1);}
	else{
	
	p1=1,p2=1;
	return go(1,1);}
}

void AI(){
int i,j;

while(1){
	

    	
      srand((unsigned)time(NULL));
      i= rand()%8+1;
	  j= rand()%8+1; 
	   if (!ok(i, j)){
	   	continue;
	   }  
	  if (s0 != ais){
	  	
	
	   
	   str_lib(i,j,2);
    
    	if(goqi==0){
        	i=-1;j=-1;
		}		
    
}
else if(s0==ais){
	  
	   
	  str_lib(i,j,1);
    
    	if(goqi==0){
        	i=-1;j=-1;
		}	   
}
	if (ok(i, j)){
	   	p1=i;
	   	p2=j;
	   	break;
	   }  	

}
return go(i,j);
}

void AI6(int i,int j){
	
	if(s0 != ais){
       int n1,n2,n3,n4;
       n1=str_lib(i-1,j-1,2).first;
       n2=str_lib(i+1,j-1,2).first;
       n3=str_lib(i+1,j+1,2).first;
       n4=str_lib(i-1,j+1,2).first;
        int t[4]={n1,n2,n3,n4};
        int x, max, min;
           max=t[0]; 
 
        for(x=0; x<4; x++)
        {
         if(max<t[x])
            max=t[x];
       }
       
       
	if(p[i-1][j-1]==0&&inboard(i-1,j-1)==true&&(max=n1)&&AIB2(i-1,j-1)!=0){
		
		p1=i-1;
		p2=j-1;
	
	return	go(i-1,j-1);
	exit(0);
	}
	if(p[i+1][j-1]==0&&inboard(i+1,j-1)==true&&(max=n2)&&AIB2(i+1,j-1)!=0){
		
		p1=i+1;
		p2=j-1;
	
	return	go(i+1,j-1);
	exit(0);
	}
		if(p[i+1][j+1]==0&&inboard(i+1,j+1)==true&&(max=n3)&&AIB2(i+1,j+1)!=0){
		
		p1=i+1;
		p2=j+1;
		
	return	go(i+1,j+1);
	exit(0);
	}
		if(p[i-1][j+1]==0&&inboard(i-1,j+1)==true&&(max=n4)&&AIB2(i-1,j+1)!=0){
		
		p1=i-1;
		p2=j+1;
	
		
	return	go(i-1,j+1);
	exit(0);
	}


		
		if((p[i-1][j+1]!=0||inboard(i-1,j+1)==false||str_lib(i-1,j+1,2).first==0||AIB2(i-1,j+1)==0)
		&&(p[i-1][j-1]!=0||inboard(i-1,j-1)==false||str_lib(i-1,j-1,2).first==0||AIB2(i-1,j-1)==0)
		&&(p[i+1][j-1]!=0||inboard(i+1,j-1)==false||str_lib(i+1,j-1,2).first==0||AIB2(i+1,j-1)==0)
		&&(p[i+1][j+1]!=0||inboard(i+1,j+1)==false||str_lib(i+1,j+1,2).first==0||AIB2(i+1,j+1)==0)){
	
	      AI();
	     
	     //exit(0);
	
	}
}
	
	else if(s0 == ais){

	if(p[i-1][j-1]==0&&inboard(i-1,j-1)==true&&AIW2(i-1,j-1)!=0&&str_lib(i-1,j-1,1).first!=0){
		p1=i-1;
		p2=j-1;
			
	return	go(i-1,j-1);
	exit(0);
	}
 	if(p[i+1][j-1]==0&&inboard(i+1,j-1)==true&&AIW2(i+1,j-1)!=0&&str_lib(i+1,j-1,1).first!=0){
		p1=i+1;
		p2=j-1;
	return	go(i+1,j-1);
	exit(0);
	}
		if(p[i+1][j+1]==0&&inboard(i+1,j+1)==true&&AIW2(i+1,j+1)!=0&&str_lib(i+1,j+1,1).first!=0){
		p1=i+1;
		p2=j+1;
	return	go(i+1,j+1);
	exit(0);
	}
		if(p[i-1][j+1]==0&&inboard(i-1,j+1)==true&&AIW2(i-1,j+1)!=0&&str_lib(i-1,j+1,1).first!=0){
		p1=i-1;
		p2=j+1;
	return	go(i-1,j+1);
	exit(0);
	}
		if((p[i-1][j+1]!=0||inboard(i-1,j+1)==false||str_lib(i-1,j+1,1).first==0||AIW2(i-1,j+1)==0)
		&&(p[i-1][j-1]!=0||inboard(i-1,j-1)==false||str_lib(i-1,j-1,1).first==0||AIW2(i-1,j-1)==0)
		&&(p[i+1][j-1]!=0||inboard(i+1,j-1)==false||str_lib(i+1,j-1,1).first==0||AIW2(i+1,j-1)==0)
		&&(p[i+1][j+1]!=0||inboard(i+1,j+1)==false||str_lib(i+1,j+1,1).first==0||AIW2(i+1,j+1)==0)){
	
	      AI();
	     
	     //exit(0);
	
	}
}
}
int main()
{
	int flag111=1;

init();
 while (1)
    {
        if (s == ais)
 		{ 
 		if(flag111==1){
 			AI1();
 		  flag111=3;
		 }else{
		 	AI6(p1,p2);
		 }
		 //	AI();
		  
		 		
		 
		
		}
		
        else player();
        s = 3 - s;//换下棋方
    }
	return 0;
}
