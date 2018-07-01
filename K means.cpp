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
        double operator-(Point p)//重载-用于运算两点间距离 ； 
        {
	        return sqrt((this->x-p.getx())*(this->x-p.getx())+(this->y-p.gety())*(this->y-p.gety()));
        }
        Point &operator+(Point p)//重载+用于运算两点的中点； 
        {
	        Point *a;
	        a = new Point((this->x+p.getx())/2,(this->y+p.gety())/2);
	        return *a;
        }
		bool operator==(Point p)//重载 == 判断两点是否相等； 
		{
			if(p.getx()==this->x&&p.gety()==this->y)
			{
				return true;
			}
			return false;
		}
		Point FirstsetCen(Point *P,Point *cen,int numofP,bool f[],int numofcen)//该函数用于第一次分配中心点，借助bool数组判断是否为中心点，并将中心点传回给cen 
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
class Autopartition//分块类； 
{
	private:
		int numofP;
		Point **point;//存放块区以及块区里的点； 
		Point *cen;//存放中心点； 
		int numofB;
		int *size;//存放每一个块区的点的个数； 
		bool change;//判断前后两次的中心点有无改变； 
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
	    void setblock(Point *p)//根据中心点分区域； 
	    {
	    	for(int i = 0;i < numofB;i++)
			{
				size[i] = 0;//每个区域的点的个数初始化为0； 
			}
	    	for(int i = 0;i < numofB;i++)
	    	{
	    		point[i] = new Point[numofP];//开足够大小的空间; 
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
	    		point[tempj][size[tempj]] = p[i];//将相应的点加进块区 
	    		size[tempj]++;//个数加一； 
	    	}
	    	
	    }
	    void resetcen()//重置中心点，同时改变change变量； 
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
	    		if(tempc == cen[i])//判断前后两次中心点是否变化； 
	    		{
	    			time++;
	    		}
	    	}
	    	if(time == numofB)//全部块区的中心点都没有变化时，赋值change为false； 
	    	{
	    		change = false;
	    	}
	    }
	    bool getchange()
	    {
	    	return change;
	    }
	    void print()//最终输出； 
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
	    }//用于调试的函数，输出中心点； 
	    void printP()
	    {
	    	for(int i = 0;i < numofB;i++)
	    	{
	    		cout<<"区域"<<i+1<<":"<<endl;
	    		for(int j = 0; j < size[i];j++)
	    		{
	    			cout<<point[i][j].getx()<<","<<point[i][j].gety()<<endl;
	    		}
	    	}
	    }//用于调试的函数，输出每个区域的点； 
		
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
	while(a.getchange()&&time < 1000)//前后中心点不改变或者循环够1000次就退出 
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
