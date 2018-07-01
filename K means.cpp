#include<iostream>
#include<cmath>

using namespace std;
class Point 
{
	private:
		double x;
		double y;
	public:
		Point()
        {
	        this->x = 0;
	        this->y = 0;
        }
        void setx(double x)
        {
	        this->x = x;
        }
        void sety(double y)
        {
	        this->y = y;
        }
        Point(double x,double y)
        {
	        this->x = x;
	        this->y = y;
        }
        double getx() const
        {
	        return x; 
        }
        double gety() const
        {
	        return y;
        }
        double operator-(Point p)//����-���������������� �� 
        {
	        return sqrt((this->x-p.getx())*(this->x-p.getx())+(this->y-p.gety())*(this->y-p.gety()));
        }
        Point &operator+(Point p)//����+��������������е㣻 
        {
	        Point *a;
	        a = new Point((this->x+p.getx())/2,(this->y+p.gety())/2);
	        return *a;
        }
		bool operator==(Point p)//���� == �ж������Ƿ���ȣ� 
		{
			if(p.getx()==this->x&&p.gety()==this->y)
			{
				return true;
			}
			return false;
		}
		Point FirstsetCen(Point *P,Point *cen,int numofP,bool f[],int numofcen)//�ú������ڵ�һ�η������ĵ㣬����bool�����ж��Ƿ�Ϊ���ĵ㣬�������ĵ㴫�ظ�cen 
		{
			int tempd = 0;
			int tempi = 1;
			int numofloop = 0;
			for(int i = 1;i < numofP;i++)
			{
				if(f[i])
				{	
				double distance = P[i]-cen[0];
				for(int j = 1;j < numofcen;j++)
				{
					distance *= P[i]-cen[j];
				}
				if(distance > tempd)
				{
					f[i] = false;
					tempd = distance;
					if(numofloop > 0)
					f[tempi] = true;
					tempi = i;
					numofloop++;
				}	
				}
				
			}
			return P[tempi];	
		}
		
};
class Autopartition//�ֿ��ࣻ 
{
	private:
		int numofP;
		Point **point;//��ſ����Լ�������ĵ㣻 
		Point *cen;//������ĵ㣻 
		int numofB;
		int *size;//���ÿһ�������ĵ�ĸ����� 
		bool change;//�ж�ǰ�����ε����ĵ����޸ı䣻 
	public:
	    Autopartition(int numofP,int numofB)
	    {
	    	point = new Point*[numofB];
	    	cen = new Point[numofB];
	    	this->numofP = numofP;
			this->numofB = numofB;
			size = new int[numofB];
			change = true;
	    }
	    ~Autopartition()
	    {
	    	delete [] point;
	    	delete [] cen;
	    	delete [] size;
	    }
	    
	    void FirstsetC(Point *p)
	    {
	    	bool *f;
	    	f = new bool[numofP];
	    	for(int i = 0;i < numofP;i++)
	    	f[i] = true;
	    	f[0] = false;
	    	cen[0] = p[0];
	    	int numofcen = 1;
	    	for(int i = 1;i < numofB;i++)
	    	{
	    		cen[i] = p[0].FirstsetCen(p,cen,numofP,f,numofcen);
	    		numofcen++;
	    	}
	    }
	    void setblock(Point *p)//�������ĵ������ 
	    {
	    	for(int i = 0;i < numofB;i++)
			{
				size[i] = 0;//ÿ������ĵ�ĸ�����ʼ��Ϊ0�� 
			}
	    	for(int i = 0;i < numofB;i++)
	    	{
	    		point[i] = new Point[numofP];//���㹻��С�Ŀռ�; 
	    	}
	    	for(int i = 0;i < numofP;i++)
	    	{
	    		double tempd = p[i] - cen[0];
	    		int tempj = 0;
	    		for(int j = 0;j < numofB;j++)
	    		{
	    			double distance = p[i] - cen[j];
	    			if(distance < tempd)
	    			{
	    			    tempj = j;
	    				tempd = distance;
	    			}
	    		}
	    		point[tempj][size[tempj]] = p[i];//����Ӧ�ĵ�ӽ����� 
	    		size[tempj]++;//������һ�� 
	    	}
	    	
	    }
	    void resetcen()//�������ĵ㣬ͬʱ�ı�change������ 
	    {
	    	int time = 0;
	    	for(int i = 0;i < numofB;i++)
	    	{
			    Point temp = point[i][0];
	    		for(int j = 1;j < size[i];j++)
	    		{
	    			temp.setx((temp.getx()+point[i][j].getx()));
	    			temp.sety((temp.gety()+point[i][j].gety()));
	    		}
	    		Point tempc = cen[i];
	    		cen[i].setx(temp.getx()/size[i]);
	    		cen[i].sety(temp.gety()/size[i]);
	    		if(tempc == cen[i])//�ж�ǰ���������ĵ��Ƿ�仯�� 
	    		{
	    			time++;
	    		}
	    	}
	    	if(time == numofB)//ȫ�����������ĵ㶼û�б仯ʱ����ֵchangeΪfalse�� 
	    	{
	    		change = false;
	    	}
	    }
	    bool getchange()
	    {
	    	return change;
	    }
	    void print()//��������� 
	    {
	    	for(int i = 0;i < numofB;i++)
	    	{
	    		cout<<"BLOCK"<<i+1<<":"<<endl;
				 for(int j = 0 ;j < size[i];j++ )
				 {
				 	cout<<"P"<<j+1<<":"<<"("<<point[i][j].getx()<<" "<<point[i][j].gety()<<")"<<endl;
				 }
	    	}
	    }
	    void printC()
	    {
	    	for(int i = 0;i < numofB;i++)
	    	{
	    		cout<<cen[i].getx()<<" "<<cen[i].gety()<<endl;
	    	}
	    }//���ڵ��Եĺ�����������ĵ㣻 
	    void printP()
	    {
	    	for(int i = 0;i < numofB;i++)
	    	{
	    		cout<<"����"<<i+1<<":"<<endl;
	    		for(int j = 0; j < size[i];j++)
	    		{
	    			cout<<point[i][j].getx()<<","<<point[i][j].gety()<<endl;
	    		}
	    	}
	    }//���ڵ��Եĺ��������ÿ������ĵ㣻 
		
};


int main()
{
    cout<<"Enter The Number Of Block:"<<endl;
	int numofB;
	cin >> numofB; 
	cout<<"Enter Point Data:"<<endl; 
	Point *p;
	p = new Point[1000];
	double x;
	double y;
	Point *q;
	q = p;
	int numofP = 0;
	while(cin>>x>>y)
	{
	    p->setx(x);
	    p->sety(y);
		p++;
		numofP++;
	}
	p = q;
	cout<<"Point Data:"<<endl;
	for(int i = 0;i < numofP;i++)
	{
	   cout<<"P"<<i+1<<":"<<"("<<p->getx()<<","<<p->gety()<<")"<<endl; 
	   p++; 
	} 
	p = q;
	Autopartition a(numofP,numofB);
	a.FirstsetC(p);
	int time = 0;
	while(a.getchange()&&time < 1000)//ǰ�����ĵ㲻�ı����ѭ����1000�ξ��˳� 
	{
		a.setblock(p);
		a.resetcen();
		time++;
	}
	if(time == 1000) 
	cout<<"Fail Autopartition"<<endl;
	else
	a.print();
}
