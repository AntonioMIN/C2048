#include<zero.h>
int map[4][4];
int rank[10];
int work_mapping,score,maxscore;
int NNl[16][2],NNc;
void logo()
{
	cls();
	textcolor(9);
	printf("2048_By Antonio Ver 1.1\n\n");
	textcolor(-1);
}
void setting()
{
	FILE *ip = fopen("data.dat", "r");
	if (ip == NULL) return;
	else
	{
		int i,j;
		fscanf(ip, "%d %d", &maxscore,&score);
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				fscanf(ip, "%d", &map[i][j]);
				work_mapping+=map[i][j];
			}
		}
	}
}
void data_out()
{
    FILE *op=fopen("data.dat","w");
    fprintf(op,"%d\n%d\n",maxscore,score);
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            fprintf(op,"%d ",map[i][j]);
        }fprintf(op,"\n");
    }
}
void game_newmap()
{
    logo();
    textcolor(6);
    printf("Making New Game!! Wait for me!!");
    textcolor(-1);
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            map[i][j]=0;
        }
    }
    for(i=0;i<2;)
    {
        int x,y,v;
        x=random()%4;
        y=random()%4;
        v=random()%2;
        if(map[x][y]==0)
        {
            i++;
            if(v==0) map[x][y]=2;
            else if(v==1) map[x][y]=4;
        }
        else continue;
    }
}
int game_blankchecker()
{
    int i,j,countn=0;
    NNc=0;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(map[i][j]==0)
            {
                countn++;
                NNl[NNc][0]=i;
                NNl[NNc++][1]=j;
            }
        }
    }return countn;
}
int game_overcheck()
{
    if(game_blankchecker()!=0) return 0;
    int i,j,k;
    int d[4][2];
    d[0][0]=-1;d[0][1]=0;d[1][0]=1;d[1][1]=0;
    d[2][0]=0;d[2][1]=-1;d[3][0]=0;d[3][1]=1;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            for(k=0;k<4;k++)
            {
                if(i+d[k][0]<0 || i+d[k][0]>3) continue;
                if(j+d[k][1]<0 || j+d[k][1]>3) continue;
                if(map[i][j]==map[i+d[k][0]][j+d[k][1]]) return 0;
            }
        }
    }return 1;
}
int game_move(int mode_x,int mode_y)//BRAIN!!
{
    int i,j,k;
    bool game_over=true;
    if(mode_x==1)
    {//right
        for(i=0;i<4;i++)
        {
            for(j=3;j>0;j--)
            {
                if(map[i][j]==0) continue;
                for(k=j-1;k>=0;k--)
                {
                    if(map[i][k]==0) continue;
                    if(map[i][j]==map[i][k])
                    {
                        map[i][j]+=map[i][k];
                        score+=map[i][j];
                        map[i][k]=0;
                        game_over=false;break;
                    }
                    if(map[i][j]!=map[i][k]) break;
                }
            }
            for(j=3;j>0;j--)
            {
                if(map[i][j]!=0) continue;
                for(k=j-1;k>=0;k--)
                {
                   if(map[i][k]!=0)
                   {
                       map[i][j]=map[i][k];
                       map[i][k]=0;
                       game_over=false;break;
    }}}}}
    if(mode_x==-1)
    {//left
        for(i=0;i<4;i++)
        {
            for(j=0;j<3;j++)
            {
                if(map[i][j]==0) continue;
                for(k=j+1;k<4;k++)
                {
                    if(map[i][k]==0) continue;
                    if(map[i][j]==map[i][k])
                    {
                        map[i][j]+=map[i][k];
                        score+=map[i][j];
                        map[i][k]=0;
                        game_over=false;break;
                    }
                    if(map[i][j]!=map[i][k]) break;
                }
            }
            for(j=0;j<3;j++)
            {
                if(map[i][j]!=0) continue;
                for(k=j+1;k<4;k++)
                {
                    if(map[i][k]!=0)
                    {
                        map[i][j]=map[i][k];
                        map[i][k]=0;
                        game_over=false;break;
    }}}}}
    if(mode_y==1)
    {//up
        for(i=0;i<4;i++)
        {
            for(j=0;j<3;j++)
            {
                if(map[j][i]==0) continue;
                for(k=j+1;k<4;k++)
                {
                    if(map[k][i]==0) continue;
                    if(map[j][i]==map[k][i])
                    {
                        map[j][i]+=map[k][i];
                        score+=map[j][i];
                        map[k][i]=0;
                        game_over=false;break;
                    }
                    if(map[j][i]!=map[k][i]) break;
                }
            }
            for(j=0;j<3;j++)
            {
                if(map[j][i]!=0) continue;
                for(k=j+1;k<4;k++)
                {
                    if(map[k][i]!=0)
                    {
                        map[j][i]=map[k][i];
                        map[k][i]=0;
                        game_over=false;break;
    }}}}}
    if(mode_y==-1)
    {//down
        for(i=0;i<4;i++)
        {
            for(j=3;j>0;j--)
            {
                if(map[j][i]==0) continue;
                for(k=j-1;k>=0;k--)
                {
                    if(map[k][i]==0) continue;
                    if(map[j][i]==map[k][i])
                    {
                        map[j][i]+=map[k][i];
                        score+=map[j][i];
                        map[k][i]=0;
                        game_over=false;break;
                    }
                    if(map[j][i]!=map[k][i]) break;
                }
            }
            for(j=3;j>0;j--)
            {
                if(map[j][i]!=0) continue;
                for(k=j-1;k>=0;k--)
                {
                   if(map[k][i]!=0)
                   {
                       map[j][i]=map[k][i];
                       map[k][i]=0;
                       game_over=false;break;
    }}}}}
    if(game_over && game_overcheck()) return 1;
    else if(game_over) return 0;
    int n,t=game_blankchecker();
    if(t==0) n=0;
    else if(t==1) n=1;
    else n=random()%2+1;
    for(i=0;i<n;i++)
    {
        int x,y,v;
        t=random()%NNc;
        x=NNl[t][0];
        y=NNl[t][1];
        if(n==1)
        {
            int Sub_min=0x7fffffff;
            if(x+1<4 && Sub_min>map[x+1][y]) Sub_min=map[x+1][y];
            if(x-1>0 && Sub_min>map[x-1][y]) Sub_min=map[x-1][y];
            if(y+1<4 && Sub_min>map[x][y+1]) Sub_min=map[x][y+1];
            if(y-1>0 && Sub_min>map[x][y-1]) Sub_min=map[x][y-1];
            map[x][y]=Sub_min;
        }
        else
        {
            v=random()%2;
            if(v==0) map[x][y]=2;
            else if(v==1) map[x][y]=4;
        }
    }return 0;
}
void game()
{
    if(work_mapping)
    {
        bool continue_ans;
        while(1)//Question
        {
            logo();
            printf("Do you Want Continue?(Y/N) : ");
            char c;
            scanf("%c",&c);
            if(c=='Y' || c=='y') {continue_ans=true;break;}
            else if(c=='N' || c=='n') {score=0;continue_ans=false;break;}
        }
        if(!continue_ans) game_newmap();
    }
    else game_newmap();
    while(1)
    {
        logo();
        printf("Score : %d / Max Score : %d\n\n",score,maxscore);
        int point_x,point_y=4;
        textcolor(11);
        for(int i=0;i<4;i++)
        {
            point_x=4;
            for(int j=0;j<4;j++)
            {
                pointmove(point_x,point_y);
                if(map[i][j]==0) textcolor(7);
                else textcolor(11);
                printf("%d ",map[i][j]);
                point_x+=4;
            }printf("\n");
            point_y+=2;
        }textcolor(-1);
        while(1)
        {
            char c=getch(),chk;
            if(c==27) return;
						//right
            else if(c==77) chk=game_move(1,0);
						//left
            else if(c==75) chk=game_move(-1,0);
						//down
            else if(c==80) chk=game_move(0,-1);
						//up
            else if(c==72) chk=game_move(0,1);
            else continue;
            if(score>maxscore) maxscore=score;
            if(chk)
            {
                logo();
                textcolor(13);
                printf("GAME OVER!!");
                textcolor(-1);
                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++) map[i][j]=0;
                }
                work_mapping=0;
                score=0;
                getch();
                return;
            }
            else break;
        }
    }
}
int main()
{
	setting();
	while (1)
	{
		logo();
		printf("Main Menu..Max Score : %d\n\n1. Start Game\n0. Exit",maxscore);
		pointhind(0);
		int c;
		c=getch();
		if (c == '1') game();
		else if (c == '0') break;
	}
	data_out();
	return 0;
}
