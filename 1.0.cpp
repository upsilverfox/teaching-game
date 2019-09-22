#include <iostream>
#include<fstream>
#include <string>
#include <ctime>
using namespace std;
//玩家信息 
class Player
{
public:
   Player();
   Player(string player_name, int initial_level);
   Player(string player_name, int initial_level,int s);
   void increment_score();
   void print(); 
   int get_score() const;
   int get_level() const;
   string get_name() const;
public:
   string name;
   int score;
   int level;
};
Player::Player()
{
   name = "";
   score = 0;
   level = 1;
}
Player::Player(string player_name, int initial_level)
{
   name = player_name;
   score = 0;
   level = initial_level;
}
Player::Player(string player_name, int initial_level,int s)
{
   name = player_name;
   score = s;
   level = initial_level;
}
//分数累计在得到5分后游戏进入下一级
void Player::increment_score()
{
   score++;
   if (score % 5 == 0 && level < 6)
      level++;
}
//打印信息 
void Player::print()
{
		cout<<"姓名："<<name<<"   ";
	    cout<<"等级："<<level<<"   ";
		cout<<"成绩："<<score<<"   "<<endl;
}
//获取游戏等级 
int Player::get_level() const
{
   return level;
}
//获取游戏分数 
int Player::get_score() const
{
   return score;
}
//获取参与者名字 
string Player::get_name() const
{
   return name;
}
//创建单链表以便文件的储存和读取 
class linklist
{
	public:
	    Player people;
	    linklist *next;
};
//查看文件有几组数据 
int research_last()
{
	int i=0,last;
	string t;
	ifstream infile("family.txt",ios::in);
	if(!infile)
	{
		cout<<"没有记录"<<endl;
		system("pause");
	}
	while(!infile.eof())
	{
		infile>>t;
		i++;
	}
	i=i-1;
    last=i/3;
	return last;
}
//从文件中获取数据 
linklist* loadFromFile()
{
    ifstream read("family.txt",ios::in);
    if(!read)
    {
    	cout<<"family.txt文件不存在";
		system("pause");
		exit(0); 
	}
	
	linklist *head = NULL;
	linklist *rear = NULL;
	head=rear;
	while(!read.eof())
	{
		string nam;                 
	    int grad;             
        int scor;     
	    read>>nam>>grad>>scor;
	    if(nam==" ") break;
	    Player new_person(nam,grad,scor);	    
	    linklist *temp = new linklist;
	    temp->people = new_person; 
		temp->next=NULL;
	    if(head == NULL) 
		    head = temp;
		else
		    rear->next = temp;		
		rear = temp;
	}
		if(rear != NULL)
	    rear->next = NULL;	
	return head;
}
//存档 
void savefile(linklist *list)
{
	int num;
	num=research_last();
    ofstream output("family.txt", ios::out);
	linklist *p=list;
		for(int i=0;i<num+1;i++)
	{
	    output<<p->people.name<<" ";
	    output<<p->people.level<<" ";
	    output<<p->people.score<<" ";
	    output<<endl;	
	    p = p->next;	    
	}

} 
//清空列表 
void re_set()
{
ofstream output("family.txt", ios::out);
output<<" ";
	
}
//同名覆盖 —优先储存高的成绩的数据 
void delsame(linklist *head)
{
	int num;
	num=research_last();
	linklist *s,*p,*q;
	s=head;
	p=s->next;
	q=s;
	while(s)
	{
		p=s->next;
		q=s;
		while(p)
		{
			if(s->people.name==p->people.name)
			{
				if(s->people.score<p->people.score) 
				{
				s->people.level=p->people.level;
				s->people.score=p->people.score;
			    }
				else if(s->people.score==p->people.score&&s->people.level<p->people.level)
		    	{
		    	s->people.level=p->people.level;
				s->people.score=p->people.score;
				}
				num=num-1;
				q->next=p->next;
				free(p);
				p=NULL;
				p=q->next;
			}
			else 
			{
				q=p;
				p=p->next;
			}
		}
		s=s->next;
	}
	ofstream output("family.txt", ios::out);
		for(int i=0;i<num;i++)
	{
	    output<<head->people.name<<" ";
	    output<<head->people.level<<" ";
	    output<<head->people.score<<" ";
	    output<<endl;	
	    head = head->next;
	}
	
} 
//清空文件的内容 
void fileEmpty(const string flieName)
{
	ofstream file(flieName, ios::out);
}
//排序
void re_sort() 
{
    int num;
    int nume;
	num=research_last();
	string file[num][3];
	ifstream read("family.txt",ios::in);
	for(int i=0;i<num;i++)
	for(int j=0;j<3;j++)
		read>>file[i][j];
		
	fileEmpty("family.txt");
	ofstream output("family.txt", ios::out);
	string t;
	for(int i=0;i<num;i++)
	for(int j=0;j<num;j++)
	if(file[i][2]>file[j][2])
	for(int k=0;k<3;k++)
	{
		t=file[i][k];
		file[i][k]=file[j][k];
		file[j][k]=t;
	}
	else if(file[i][2]==file[j][2]&&file[i][1]>file [j][1])
		for(int k=0;k<3;k++)
		{
			t=file[i][k];
			file[i][k]=file[j][k];
			file[j][k]=t;
		}

	for(int i=0;i<num;i++)
	for(int j=0;j<3;j++)
	output<<file[i][j]<<" ";
	output<<endl;
	
}

//显示历史记录 
void showlist()
{
	int num;
	num=research_last();
	system("cls");
	linklist *p,*head;
	p=loadFromFile();
	cout<<"历史记录："<<endl; 
	for(int i=0;i<num;i++)
	{
		p->people.print();
		p = p->next;
	}
	head=loadFromFile();
	cout<<endl;
	cout<<"请选择您想要进行的操作："<<endl;
	 int choice; 
    	cout<<"输入1 清空列表"<<endl;
    	cout<<"输入2 同名覆盖"<<endl;
    	cout<<"输入3 按成绩高低进行排序"<<endl;
	    cout<<"输入0 返回上一层"<<endl;	
		cin>>choice;
		switch(choice)
			{
			case 1:re_set(); break;
			case 2:delsame(head);system("cls");showlist();break;
			case 3:re_sort();system("cls");showlist();break;
			case 0:break;
	    	}
}
//查找名字 
bool reseach(string name)
{
	linklist *head;
	linklist *p=NULL;
	head=loadFromFile();
	p=head;
	for(int i=0;i<research_last();i++)
		{
			if(p->people.name!=name) 
			p=p->next;
			else return true;
		}
		return false;
}
//判断数据是否超出范围
int judge(int grad,int scor) 
{
	 do{
	 	   cin>>scor;
			if(scor<1)
			cout<<"成绩没有负数"<<endl<<"请重新输入：";
			else if(scor>grad*5)
			cout<<"成绩超出范围" <<endl<<"请重新输入：";
	  		}while(scor<1||scor>grad*5);
	  		return scor;
}
//添加成员信息
void add_create()
{
	int num,nume,grad,scor;
	string nam;                 
	cout<<"你需要几组数据：";
			cin>>num;		
			for(int i=0;i<num;i++)
				{	
				   nume=research_last();
				   linklist *head=NULL;
					linklist *p=NULL;
					head=loadFromFile();
   					p=head; 
					cout<<"第"<<i+1<<"组数据："<<endl; 
					cout<<"姓名：";
					cin>>nam;    
	  			    cout<<"等级（1-6）："; 
	                cin>>grad;
	    			cout<<"成绩：";
	    			scor=judge(grad,scor);
	  			  Player son(nam,grad,scor); 
   					linklist *temp=new linklist;
   					temp->people=son;
   					temp->next=NULL;
					   if(nume==0)
  						 head=temp;
   						else {
   					for(int i=1;i<nume;i++)
   					p=p->next; 
   					p->next=temp;}	
   					savefile(head);
	  	    	}
}
//创建记录
void create()
{
 
    int choice; 
	system("cls"); 	
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         输入1 新建成员信息                             "<<endl;
	cout<<"                         输入2 添加成员信息                          "<<endl;
	cout<<"                         输入3 返回上一层                            "<<endl;
	cout<<"                         输入0 退出程序                            "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"请选择您想要进行的操作：";
	cin>>choice;
		switch(choice)
			{
			case 1:fileEmpty("family.txt");add_create();break;
			case 2:add_create();break;
	    	case 0:exit(0);break;
           } 
}
//修改数据 
void change()
{                          
	string name;
	int choice;;	
	system("cls"); 
	cout<<"查找名字：";
	cin>>name;
	if(reseach(name))
	{
	system("cls"); 
	cout<<"查找成功请进行下列操作："<<endl; 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         输入1 修改姓名                             "<<endl;
	cout<<"                         输入2 修改等级                             "<<endl;
	cout<<"                         输入3 修改成绩                             "<<endl;
	cout<<"                         输入4 修改全部                             "<<endl;
	cout<<"                         输入0 退出程序                            "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"请选择您想要进行的操作：";
	cin>>choice;
	linklist *head;
	linklist *p=NULL;
	head=loadFromFile();
	p=head;
	for(int i=0;i<research_last();i++)
		if(p->people.name!=name) 
		p=p->next;
			switch(choice)
			{
			case 1:
			cout<<"由"<<p->people.name<<"更改为：";
			cin>>p->people.name;
			; break;
			case 2:cout<<"由"<<p->people.level<<"更改为(1-6)：";
			cin>>p->people.level;
			;break;
            case 3:cout<<"由"<<p->people.score<<"更改为：";
            p->people.level=judge(p->people.level,p->people.score);break; 
			case 4:
            cout<<"由姓名："<<p->people.name<<"更改为：";
			cin>>p->people.name;
			cout<<"由等级："<<p->people.level<<"更改为(1-6)：";
			cin>>p->people.level;
			cout<<"由成绩："<<p->people.score<<"更改为：";
			p->people.level=judge(p->people.level,p->people.score);break; 
			case 0:exit(0);break;
	     	}
    int num;
	num=research_last();
    ofstream output("family.txt", ios::out);
		for(int i=0;i<num;i++)
	{
	    output<<head->people.name<<" ";
	    output<<head->people.level<<" ";
	    output<<head->people.score<<" ";
	    output<<endl;	
	    head = head->next;	    
	}

}	else {
	    cout<<"查找失败";
	    cin>>choice;
	    }
	
} 
//基于当前日期与时间为随机数生成器确定种子。
//实际上是函数srand()为随机数生成器确定种子，只需将一个int型的值作为种子传递给它。这里传递给函数的是time(0)的返回值——一个基于当前系统日期和时间的数字。
void rand_seed()
{
   int seed = static_cast<int>(time(0));
   srand(seed);
}
//随机获取两组a到b的数据
int rand_int(int a, int b)
{
   return a + rand() % (b - a + 1);
} 
//游戏 
class Game
{
public:
   Game();
   linklist* play(linklist *head);
   linklist* replay(linklist *head);
   void read_player_information();
   void play_round();
   int get_guess(int v1, int v2, int answer, string operation);
private:
   Player player;
   linklist head;
};
Game::Game()
{
    player = Player();
}
//游戏开始 
linklist* Game::play(linklist *head)
{
	string nam;
	int grad;
	int scor;
   read_player_information();
   string response;
   string t;
    head=loadFromFile();
    linklist *p=NULL;
    p=head;
   do
   {
      play_round();
      cout << "Do you want to play again? (y/n) ";
      cin >> response;
   } while (response == "y");
   cout<<endl;
   nam=player.get_name();
   grad=player.get_level();
   scor=player.get_score();
   Player son(nam,grad,scor); 
   linklist *temp=new linklist;
   temp->people=son;
   temp->next=NULL;
   if(research_last()==0)
   head=temp;
   else {
   for(int i=1;i<research_last();i++)
   p=p->next; 
   p->next=temp;}
   return head;  
}
//继续上一次游戏 
linklist* Game::replay(linklist *head)
{
	string response;
	head=loadFromFile();
    linklist *p=NULL;
    p=head; 
	if(research_last()==0)
	{
		cout<<"你没有历史记录"<<endl;
		cin>>response;
		return head; 
		}	
   for(int i=1;i<research_last();i++)
    p=p->next; 
	cout<<"Welcome back "<<p->people.name<<endl;
	cout<<"Your last level is "<<p->people.level<<" end your last score is "<<p->people.score<<"."<<endl;
	player = Player(p->people.name, p->people.level,p->people.score);
   do
   {
      play_round();
      cout << "Do you want to play again? (y/n) ";
      cin >> response;
   } while (response == "y");
   cout<<endl;
    p->people.level=player.get_level();
    p->people.score=player.get_score();
   return head;  
}
//玩家填写名字选择等级 
void Game::read_player_information()
{
   cout << "What is your name? ";
   string name;
   cin >> name;
   int initial_level = 0;
   do
   {
      cout << "At what level do you want to start? (1-6) ";
      cin >> initial_level;
   } while (initial_level < 1 || initial_level > 6);
   player = Player(name, initial_level);
}
//游戏随机数生成及结果返回
void Game::play_round()
{
   int i1 = 0;
   int i2 = 0;
   int answer = 0;
   //设立游戏等级 
   if (player.get_level() == 1)
      do
      {
         i1 = rand_int(1,9);  //生成随机数 
         i2 = rand_int(1,9);
         answer = i1 + i2;
      } while (answer > 9);
   else if (player.get_level() == 2)
   {
      i1 = rand_int(1,9);
      i2 = rand_int(1,9);
      answer = i1 + i2;
   }
   else if (player.get_level() == 3)
   do
   {
      i1 = rand_int(1,9);
      i2 = rand_int(1,9);
      answer = i1 - i2;
   } 
   while (answer < 0);
   else if (player.get_level() == 4)
   {
      i1 = rand_int(10,99);
      i2 = rand_int(10,99);
      answer = i1 + i2;
   }
   else if (player.get_level() == 5)
   do
   {
      i1 = rand_int(10,99);
      i2 = rand_int(10,99);
      answer = i1 - i2;
   } 
   while (answer < 0);
   else if (player.get_level() == 6)
   {
      i1 = rand_int(10,99);
      i2 = rand_int(10,99);
      answer = i1 * i2;
   }
   //提示参与者达到的等级 
   int guess;
   if (player.get_level()==1||player.get_level()==2||player.get_level()==4)
      guess = get_guess(i1, i2, answer, "sum");
   else if(player.get_level()==3||player.get_level()==5)
      guess = get_guess(i1, i2, answer, "minus");
   else
      guess = get_guess(i1, i2, answer, "multiply");
    //答对提示 
   if (answer == guess)
   {
      player.increment_score();
      cout << "Congratulations, " << player.get_name() << "! That is correct." << "\n";
	  cout<<"your current level is "<<player.get_level()<<endl;
   }
   else  //答错提醒 
   {
      cout << "Sorry, " << player.get_name() << ". The correct answer is "
         << answer << ".\n";        
   }
   cout << "Your score is " << player.get_score() << "\n";
}
//判断参与者的答案正确与否 
int Game::get_guess(int v1, int v2, int answer, string operation)
{
   int guess;
   int tries = 2;
   do   //有两次机会回答问题的机会 
   {
      cout << "Please enter the " << operation 
         << " of " << v1 << " and " << v2 << "\n";
      cin >> guess;
      if (answer == guess)
         return guess;
      else
         cout << "Oops.  That was not right.  Try again.\n";
      tries--;
   } while (tries > 0);
      
   return guess;
}
 //设置密码 
bool login_confirm()
{
	string passwd = "123456";
	string mypasswd;
	cout<<"输入密码：";
	cin>>mypasswd;
	if (passwd==mypasswd)
		return true;
	else
		return false;
}
//将玩家设立为管理员和游客 并生成界面 
bool Login()
{
	cout<<endl;
	cout<<"                            欢迎来到教学游戏                     "<<endl<<endl;
	int choice;
	while(true)
	{ 
	cout<<"----------------------------------------------------------------------"<<endl;
	cout<<"                         输入1 以管理员身份进入游戏                 "<<endl;
	cout<<"                         输入2 以游客身份进入游戏                   "<<endl;
	cout<<"----------------------------------------------------------------------"<<endl;
	cout<<"请选择您想要进行的操作：";
		cin>>choice;
		switch(choice)
		{
		case 1:
			int count;
			if (login_confirm())
				return true;
			else
			{
				cout<<"    提示：密码错误，你还有两次机会！"<<endl;
				for(count = 1;count<=3;count++)
				{
					if (login_confirm())
					{
						return true;
						break;
					}
					cout<<"   提示：密码错误！"<<endl;
				}
				cout<<"你已经失败三次，自动跳转至普通界面"<<endl;
				return false;
			}
			break;
		case 2:
			return false;
			break;
		default:
			cout<<"没有这个选项！自动为你跳转普通界面"<<endl;
			return false;
		}
	}
}
//开始游戏 
void game_begin()
{
   system("cls");
   linklist *p;
   Game mathquiz;
   rand_seed();
   savefile(mathquiz.play(p));
}
//继续游戏 
void game_again()
{
   system("cls");
   Game mathquiz;
   linklist *p;
   rand_seed();
   savefile(mathquiz.replay(p));
}
//游戏说明 
void game_show()
{   system("cls"); 
    int choice;
	cout<<endl;
	cout<<"-------------------------------------------------------------------------"<<endl;
	cout<<"     游戏共有六个难度级别，第1级测试两个小于10并且和也小于10的数字加法。"<<endl;
	cout<<"第2级进行任何两个1位数字的加法；第3级是差为非负的两个1位数的减法；第4级"<<endl;
	cout<<"进行任何一个两位数的加法；第5级是差为非负的两个2位数的减法。第6级是行任"<<endl;
	cout<<"何一个两位数的乘法。程序将随机产生问题并读取游戏参与者输入的答案。对于"<<endl;
	cout<<"每一个问题，游戏参与者都有两;次回答问题的机会。在得到5分后游戏进入下一级."<<endl;
	cout<<"---------------------------------------------------------------------------"<<endl;
	cout<<"输入任意键返回上一层";
    cin>>choice;

}
//管理员显示界面 
int show1()
{
	    int i;
	    int choice;
	    system("cls"); 
    	cout<<"-------------------------------------------------------------------"<<endl;
    	cout<<"                         输入1 开始游戏                            "<<endl;
    	cout<<"                         输入2 继续游戏                            "<<endl;
	    cout<<"                         输入3 游戏说明                            "<<endl;
    	cout<<"                         输入4 查看历史记录                        "<<endl;
    	cout<<"                         输入5 创建记录                            "<<endl;
    	cout<<"                         输入6 修改成绩                            "<<endl;	
    	cout<<"                         输入7 切换用户                            "<<endl;
    	cout<<"                         输入0 退出程序                            "<<endl;
    	cout<<"-------------------------------------------------------------------"<<endl;
    	cout<<"请选择您想要进行的操作：";
	    cin>>choice;
		switch(choice)
			{
			case 1:game_begin(); break;
			case 2:game_again(); break;
			case 3:game_show();break;
            case 4:showlist();break;
            case 5:create();break;
			case 6:change();break;	
			case 7:return 1;break;
			case 0:exit(0);break;
		}
		return 0;
}
//游客显示界面 
int  show2()
{
	    int choice;
		system("cls");
    	cout<<"-------------------------------------------------------------------"<<endl;
    	cout<<"                         输入1 开始游戏                            "<<endl;
    	cout<<"                         输入2 继续游戏                            "<<endl;
	    cout<<"                         输入3 游戏说明                            "<<endl;
    	cout<<"                         输入4 切换用户                            "<<endl;
    	cout<<"                         输入0 退出程序                            "<<endl;
    	cout<<"-------------------------------------------------------------------"<<endl;
    	cout<<"请选择您想要进行的操作：";   
		cin>>choice;
		switch(choice)
			{
			case 1:game_begin();break;
			case 2:game_again();break;
			case 3:game_show();break;
			case 4:return 1;break;
			case 0:exit(0);break;
		}
		return 0;
}
//生成总界面 
void menu_window()
{
	login:if (Login())
	{
		while(true)
		{
			if(show1())
			{
            system("cls");
			goto login;
			}
		}
	}
	else
	{
		while(true)
		{
		if(show2())
			{
            system("cls");
			goto login;
			}
		}
	}
}
//主函数 
main()
{
   menu_window();
}
