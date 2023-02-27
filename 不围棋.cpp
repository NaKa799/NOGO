#include<map>
#include <stdio.h>
#include<string>
#include<windows.h>
#include<ctime>     //ʱ��Ĵ���
#include<cassert> 
#include <iostream>
#include <utility>

#define N 9  //����
#define EDGE 9 


int gokong[EDGE][EDGE]; //0=�ÿյ�δ�����������1=�Ѽ��㣬�����ظ����㹫��
int gozi[EDGE][EDGE]; //0=����δ���㴮����1=�Ѽ��㣬�����ظ�����ͬһ���ӵ���
int goqi; //���崮����
int goziLength;//���崮����
int g_gozi[EDGE][EDGE];

int s = 0, ais = 1, s0;//s���ֵ�˭��,s=1,2��s=1��ai�£�s=2����ң�s=s0�Ǻڷ��£������ǰ׷���
using namespace std;
int p[N + 2][N + 2]; //0��1��2��  1��2�� -1��-2��


int manu[2][300], manukey = 0;//����
int out(int i, int j)//��ӡ����
{
    if (p[i][j] == 1)return printf("��");
    if (p[i][j] == 2)return printf("��");
    if (p[i][j] == -1)return printf("��");
    if (p[i][j] == -2)return printf("��");
    if (i == N)
    {
        if (j == 1)return printf("��");
        if (j == N)return printf("��");
        return printf("��");
    }
    if (i == 1)
    {
        if (j == 1)return printf("��");
        if (j == N)return printf("��");
        return printf("��");
    }
    if (j == 1)return printf("��");
    if (j == N)return printf("��");
    return printf("��");
}
 void DrawBoard()//��ӡ������Ϸ����
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
    if (s0 == ais)printf("  AIִ�ڣ����ִ��\n");
    else printf("  AIִ�ף����ִ��\n");
    alpha = 'A';
    if (keyr)printf("  �������λ�ã�%c%d\n", alpha + keyc - 1, keyr);
}

 void init()//��Ϸ���ֳ�ʼ��
{
    system("color f0");
    printf("����1����2����ѡ��\n1��AIִ������\n2�����ִ������\n");
    scanf("%d", &s);
    if (s != 1 && s != 2)return init();
    s0 = s;
    int i, j;
    for (i = 0; i <= N + 1; i++)for (j = 0; j <= N + 1; j++)p[i][j] = 0;//�Կո��Χ����	
    DrawBoard();
    for (j = 0; j < 300; j++)manu[0][j] = manu[1][j] = 0;
}



bool inboard(int row, int col)//�ж�(row,col)�Ƿ���������
{
    if (row <1 || row > N)return false;
    return col >= 1 && col <= N;
}

bool ok(int row, int col)//�ܷ�����
{
    return inboard(row, col) && (p[row][col] == 0);
}

void go(int row, int col)//����һ��
{
    if (s == s0)p[row][col] = -1; //��������µ���
    else p[row][col] = -2;
    for (int i = 0; i <= N; i++)for (int j = 0; j <= N; j++) //ȡ����һ��������ı�ʶ
    {
        if (i == row && j == col)continue;
        if (p[i][j] < 0)p[i][j] *= -1;
    }
    DrawBoard();
    
    if (ok(row, col))
    {
        printf("����\n");
        if (s0 == 1)printf("���ʤ");
        else printf("AIʤ");
        Sleep(10000);
    }

    manu[0][manukey] = row, manu[1][manukey++] = col;
}

void out_manual()
{
    char alpha = 'A';
    int i;
    printf("\n  ��������: ");
    for (i = 0; i < manukey; i += 2){
	printf("  B[%c%d]", alpha + manu[1][i] - 1, manu[0][i]);
    /*printf("\n  �׷�����λ��: ");
    for (i = 1; i < manukey; i += 2)*/printf("  W[%c%d]", alpha + manu[1][i+1] - 1, manu[0][i+1]);}
    Sleep(50000);
}
void player()
{
    DrawBoard();
 
 
 
    printf("  �ֵ�����£�����������(����=0�鿴����)�� ");
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
        printf("�˴�������");
        Sleep(1000);
        return player();
    }
    go(row, col);
}

 void str_qi(int x,int y,int hb)
  {
    //���������� x,y ����hb��ɫ���ӵ���
    gozi[x][y]=1; //��Ǳ����Ѿ��������
    goziLength++;
    //������
    if (x+1<=9)//���û�г������̱���
    {
      if ((p[x+1][y]==0)&&(gokong[x+1][y]==0))
      //������ٵ�Ϊ�ղ��Ҹõ�δ�����������
      {
        goqi++; //������һ
        gokong[x+1][y]=1; //��Ǳ��յ��Ѿ��������
      }
      else if ((p[x+1][y]==hb||p[x+1][y]== -hb)&&(gozi[x+1][y]==0))
      //����������ٵ�Ϊ�ͱ���ͬɫ�Ӳ��Ҹ���δ�����������
      str_qi(x+1,y,hb); //�ݹ���õ�������
    }
    //������
    if (x-1>=1) //��û�г������̱���
    {
      if ((p[x-1][y]==0)&&(gokong[x-1][y]==0))
      //������ٵ�Ϊ�ղ��Ҹõ�δ�����������
      {
        goqi++; //������һ
        gokong[x-1][y]=1; //��Ǳ��յ��Ѿ��������
      }
      else if ((p[x-1][y]==hb||p[x-1][y]== -hb)&&(gozi[x-1][y]==0))
      //����������ٵ�Ϊ�ͱ���ͬɫ�Ӳ��Ҹ���δ�����������
      str_qi(x-1,y,hb); //�ݹ���õ�������
    }
    //������
    if (y-1>=1)//���û�г������̱���
    {
      if ((p[x][y-1]==0)&&(gokong[x][y-1]==0))
      //������ٵ�Ϊ�ղ��Ҹõ�δ�����������
      {
        goqi++; //������һ
        gokong[x][y-1]=1; //��Ǳ��յ��Ѿ��������
      }
      else if ((p[x][y-1]==hb||p[x][y-1]== -hb)&&(gozi[x][y-1]==0))
      //������������ӵ�Ϊ�ͱ���ͬɫ�Ӳ��Ҹ���δ�����������
      str_qi(x,y-1,hb); //�ݹ���õ�������
    }
    //���ٵ�
    if (y+1<=9)//���û�г������̱���
    {
      if ((p[x][y+1]==0)&&(gokong[x][y+1]==0))
      //������ٵ�Ϊ�ղ��Ҹõ�δ�����������
      {
        goqi++; //������һ
        gokong[x][y+1]=1; //��Ǳ��յ��Ѿ��������
      }
      else if ((p[x][y+1]==hb||p[x][y+1]== -hb)&&(gozi[x][y+1]==0))
      //����������ٵ�Ϊ�ͱ���ͬɫ�Ӳ��Ҹ���δ�����������
      str_qi(x,y+1,hb); //�ݹ���õ�������
    }
  }
 
  std::pair<int,int> str_lib(int x,int y, int hb)
  {
 
    for (int i = 1; i <=9 ; i++)
      for (int j = 1; j <=9; j++)
      {
        gozi[i][j] = 0; //��ʼ����������ʾ����δ���㴮��
        gokong[i][j] = 0; //��ʼ����������ʾ�ÿյ�δ���㴮��
      }
    goqi=0; //�崮����ֵ
    goziLength=0;//�崮��ʼ����
    str_qi(x,y,hb); //���ô����ӳ���
    for(int i=0;i<EDGE;i++)
     for(int j=0;j<EDGE;j++){
      if(gozi[i][j]==1)
      g_gozi[i][j]=1;
     }
    return std::make_pair<int,int>(goqi,goziLength);
  }
 



//��������Ǻ������ 
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
	
}//��������ǰ������ 
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
        s = 3 - s;//�����巽
    }
	return 0;
}
