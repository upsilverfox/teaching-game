#include <iostream>
#include<fstream>
#include <string>
#include <ctime>
using namespace std;
//�����Ϣ 
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
//�����ۼ��ڵõ�5�ֺ���Ϸ������һ��
void Player::increment_score()
{
   score++;
   if (score % 5 == 0 && level < 6)
      level++;
}
//��ӡ��Ϣ 
void Player::print()
{
		cout<<"������"<<name<<"   ";
	    cout<<"�ȼ���"<<level<<"   ";
		cout<<"�ɼ���"<<score<<"   "<<endl;
}
//��ȡ��Ϸ�ȼ� 
int Player::get_level() const
{
   return level;
}
//��ȡ��Ϸ���� 
int Player::get_score() const
{
   return score;
}
//��ȡ���������� 
string Player::get_name() const
{
   return name;
}
//�����������Ա��ļ��Ĵ���Ͷ�ȡ 
class linklist
{
	public:
	    Player people;
	    linklist *next;
};
//�鿴�ļ��м������� 
int research_last()
{
	int i=0,last;
	string t;
	ifstream infile("family.txt",ios::in);
	if(!infile)
	{
		cout<<"û�м�¼"<<endl;
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
//���ļ��л�ȡ���� 
linklist* loadFromFile()
{
    ifstream read("family.txt",ios::in);
    if(!read)
    {
    	cout<<"family.txt�ļ�������";
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
//�浵 
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
//����б� 
void re_set()
{
ofstream output("family.txt", ios::out);
output<<" ";
	
}
//ͬ������ �����ȴ���ߵĳɼ������� 
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
//����ļ������� 
void fileEmpty(const string flieName)
{
	ofstream file(flieName, ios::out);
}
//����
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

//��ʾ��ʷ��¼ 
void showlist()
{
	int num;
	num=research_last();
	system("cls");
	linklist *p,*head;
	p=loadFromFile();
	cout<<"��ʷ��¼��"<<endl; 
	for(int i=0;i<num;i++)
	{
		p->people.print();
		p = p->next;
	}
	head=loadFromFile();
	cout<<endl;
	cout<<"��ѡ������Ҫ���еĲ�����"<<endl;
	 int choice; 
    	cout<<"����1 ����б�"<<endl;
    	cout<<"����2 ͬ������"<<endl;
    	cout<<"����3 ���ɼ��ߵͽ�������"<<endl;
	    cout<<"����0 ������һ��"<<endl;	
		cin>>choice;
		switch(choice)
			{
			case 1:re_set(); break;
			case 2:delsame(head);system("cls");showlist();break;
			case 3:re_sort();system("cls");showlist();break;
			case 0:break;
	    	}
}
//�������� 
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
//�ж������Ƿ񳬳���Χ
int judge(int grad,int scor) 
{
	 do{
	 	   cin>>scor;
			if(scor<1)
			cout<<"�ɼ�û�и���"<<endl<<"���������룺";
			else if(scor>grad*5)
			cout<<"�ɼ�������Χ" <<endl<<"���������룺";
	  		}while(scor<1||scor>grad*5);
	  		return scor;
}
//��ӳ�Ա��Ϣ
void add_create()
{
	int num,nume,grad,scor;
	string nam;                 
	cout<<"����Ҫ�������ݣ�";
			cin>>num;		
			for(int i=0;i<num;i++)
				{	
				   nume=research_last();
				   linklist *head=NULL;
					linklist *p=NULL;
					head=loadFromFile();
   					p=head; 
					cout<<"��"<<i+1<<"�����ݣ�"<<endl; 
					cout<<"������";
					cin>>nam;    
	  			    cout<<"�ȼ���1-6����"; 
	                cin>>grad;
	    			cout<<"�ɼ���";
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
//������¼
void create()
{
 
    int choice; 
	system("cls"); 	
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         ����1 �½���Ա��Ϣ                             "<<endl;
	cout<<"                         ����2 ��ӳ�Ա��Ϣ                          "<<endl;
	cout<<"                         ����3 ������һ��                            "<<endl;
	cout<<"                         ����0 �˳�����                            "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"��ѡ������Ҫ���еĲ�����";
	cin>>choice;
		switch(choice)
			{
			case 1:fileEmpty("family.txt");add_create();break;
			case 2:add_create();break;
	    	case 0:exit(0);break;
           } 
}
//�޸����� 
void change()
{                          
	string name;
	int choice;;	
	system("cls"); 
	cout<<"�������֣�";
	cin>>name;
	if(reseach(name))
	{
	system("cls"); 
	cout<<"���ҳɹ���������в�����"<<endl; 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         ����1 �޸�����                             "<<endl;
	cout<<"                         ����2 �޸ĵȼ�                             "<<endl;
	cout<<"                         ����3 �޸ĳɼ�                             "<<endl;
	cout<<"                         ����4 �޸�ȫ��                             "<<endl;
	cout<<"                         ����0 �˳�����                            "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"��ѡ������Ҫ���еĲ�����";
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
			cout<<"��"<<p->people.name<<"����Ϊ��";
			cin>>p->people.name;
			; break;
			case 2:cout<<"��"<<p->people.level<<"����Ϊ(1-6)��";
			cin>>p->people.level;
			;break;
            case 3:cout<<"��"<<p->people.score<<"����Ϊ��";
            p->people.level=judge(p->people.level,p->people.score);break; 
			case 4:
            cout<<"��������"<<p->people.name<<"����Ϊ��";
			cin>>p->people.name;
			cout<<"�ɵȼ���"<<p->people.level<<"����Ϊ(1-6)��";
			cin>>p->people.level;
			cout<<"�ɳɼ���"<<p->people.score<<"����Ϊ��";
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
	    cout<<"����ʧ��";
	    cin>>choice;
	    }
	
} 
//���ڵ�ǰ������ʱ��Ϊ�����������ȷ�����ӡ�
//ʵ�����Ǻ���srand()Ϊ�����������ȷ�����ӣ�ֻ�轫һ��int�͵�ֵ��Ϊ���Ӵ��ݸ��������ﴫ�ݸ���������time(0)�ķ���ֵ����һ�����ڵ�ǰϵͳ���ں�ʱ������֡�
void rand_seed()
{
   int seed = static_cast<int>(time(0));
   srand(seed);
}
//�����ȡ����a��b������
int rand_int(int a, int b)
{
   return a + rand() % (b - a + 1);
} 
//��Ϸ 
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
//��Ϸ��ʼ 
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
//������һ����Ϸ 
linklist* Game::replay(linklist *head)
{
	string response;
	head=loadFromFile();
    linklist *p=NULL;
    p=head; 
	if(research_last()==0)
	{
		cout<<"��û����ʷ��¼"<<endl;
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
//�����д����ѡ��ȼ� 
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
//��Ϸ��������ɼ��������
void Game::play_round()
{
   int i1 = 0;
   int i2 = 0;
   int answer = 0;
   //������Ϸ�ȼ� 
   if (player.get_level() == 1)
      do
      {
         i1 = rand_int(1,9);  //��������� 
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
   //��ʾ�����ߴﵽ�ĵȼ� 
   int guess;
   if (player.get_level()==1||player.get_level()==2||player.get_level()==4)
      guess = get_guess(i1, i2, answer, "sum");
   else if(player.get_level()==3||player.get_level()==5)
      guess = get_guess(i1, i2, answer, "minus");
   else
      guess = get_guess(i1, i2, answer, "multiply");
    //�����ʾ 
   if (answer == guess)
   {
      player.increment_score();
      cout << "Congratulations, " << player.get_name() << "! That is correct." << "\n";
	  cout<<"your current level is "<<player.get_level()<<endl;
   }
   else  //������� 
   {
      cout << "Sorry, " << player.get_name() << ". The correct answer is "
         << answer << ".\n";        
   }
   cout << "Your score is " << player.get_score() << "\n";
}
//�жϲ����ߵĴ���ȷ��� 
int Game::get_guess(int v1, int v2, int answer, string operation)
{
   int guess;
   int tries = 2;
   do   //�����λ���ش�����Ļ��� 
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
 //�������� 
bool login_confirm()
{
	string passwd = "123456";
	string mypasswd;
	cout<<"�������룺";
	cin>>mypasswd;
	if (passwd==mypasswd)
		return true;
	else
		return false;
}
//���������Ϊ����Ա���ο� �����ɽ��� 
bool Login()
{
	cout<<endl;
	cout<<"                            ��ӭ������ѧ��Ϸ                     "<<endl<<endl;
	int choice;
	while(true)
	{ 
	cout<<"----------------------------------------------------------------------"<<endl;
	cout<<"                         ����1 �Թ���Ա��ݽ�����Ϸ                 "<<endl;
	cout<<"                         ����2 ���ο���ݽ�����Ϸ                   "<<endl;
	cout<<"----------------------------------------------------------------------"<<endl;
	cout<<"��ѡ������Ҫ���еĲ�����";
		cin>>choice;
		switch(choice)
		{
		case 1:
			int count;
			if (login_confirm())
				return true;
			else
			{
				cout<<"    ��ʾ����������㻹�����λ��ᣡ"<<endl;
				for(count = 1;count<=3;count++)
				{
					if (login_confirm())
					{
						return true;
						break;
					}
					cout<<"   ��ʾ���������"<<endl;
				}
				cout<<"���Ѿ�ʧ�����Σ��Զ���ת����ͨ����"<<endl;
				return false;
			}
			break;
		case 2:
			return false;
			break;
		default:
			cout<<"û�����ѡ��Զ�Ϊ����ת��ͨ����"<<endl;
			return false;
		}
	}
}
//��ʼ��Ϸ 
void game_begin()
{
   system("cls");
   linklist *p;
   Game mathquiz;
   rand_seed();
   savefile(mathquiz.play(p));
}
//������Ϸ 
void game_again()
{
   system("cls");
   Game mathquiz;
   linklist *p;
   rand_seed();
   savefile(mathquiz.replay(p));
}
//��Ϸ˵�� 
void game_show()
{   system("cls"); 
    int choice;
	cout<<endl;
	cout<<"-------------------------------------------------------------------------"<<endl;
	cout<<"     ��Ϸ���������Ѷȼ��𣬵�1����������С��10���Һ�ҲС��10�����ּӷ���"<<endl;
	cout<<"��2�������κ�����1λ���ֵļӷ�����3���ǲ�Ϊ�Ǹ�������1λ���ļ�������4��"<<endl;
	cout<<"�����κ�һ����λ���ļӷ�����5���ǲ�Ϊ�Ǹ�������2λ���ļ�������6��������"<<endl;
	cout<<"��һ����λ���ĳ˷�����������������Ⲣ��ȡ��Ϸ����������Ĵ𰸡�����"<<endl;
	cout<<"ÿһ�����⣬��Ϸ�����߶�����;�λش�����Ļ��ᡣ�ڵõ�5�ֺ���Ϸ������һ��."<<endl;
	cout<<"---------------------------------------------------------------------------"<<endl;
	cout<<"���������������һ��";
    cin>>choice;

}
//����Ա��ʾ���� 
int show1()
{
	    int i;
	    int choice;
	    system("cls"); 
    	cout<<"-------------------------------------------------------------------"<<endl;
    	cout<<"                         ����1 ��ʼ��Ϸ                            "<<endl;
    	cout<<"                         ����2 ������Ϸ                            "<<endl;
	    cout<<"                         ����3 ��Ϸ˵��                            "<<endl;
    	cout<<"                         ����4 �鿴��ʷ��¼                        "<<endl;
    	cout<<"                         ����5 ������¼                            "<<endl;
    	cout<<"                         ����6 �޸ĳɼ�                            "<<endl;	
    	cout<<"                         ����7 �л��û�                            "<<endl;
    	cout<<"                         ����0 �˳�����                            "<<endl;
    	cout<<"-------------------------------------------------------------------"<<endl;
    	cout<<"��ѡ������Ҫ���еĲ�����";
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
//�ο���ʾ���� 
int  show2()
{
	    int choice;
		system("cls");
    	cout<<"-------------------------------------------------------------------"<<endl;
    	cout<<"                         ����1 ��ʼ��Ϸ                            "<<endl;
    	cout<<"                         ����2 ������Ϸ                            "<<endl;
	    cout<<"                         ����3 ��Ϸ˵��                            "<<endl;
    	cout<<"                         ����4 �л��û�                            "<<endl;
    	cout<<"                         ����0 �˳�����                            "<<endl;
    	cout<<"-------------------------------------------------------------------"<<endl;
    	cout<<"��ѡ������Ҫ���еĲ�����";   
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
//�����ܽ��� 
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
//������ 
main()
{
   menu_window();
}
