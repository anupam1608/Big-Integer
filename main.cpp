#include<bits/stdc++.h>


using namespace std;

class BigInt
{
    bool sign;
    string num;

    bool great(BigInt a, BigInt b);
    bool lesser(BigInt a,BigInt b);
    bool equal(BigInt a, BigInt b);
    string mul( string a, string b);
    string add (string a,string b);
    string sub(string a, string b);
    string expohelper(string a,string b);





public:

    void setnum(string str)
    {
        num=str;
    }
    const string& getnum()
    {
        return num;
    }
    void setsign(bool b)
    {
        sign=b;
    }
    const bool& getsign()
    {
        return sign;
    }
    BigInt()
    {
        num="0";
        sign=false;
    }
    BigInt(string str)
    {
        if(isdigit(str[0]))
        {
            setnum(str);
            sign=false;
        }
        else{

            setnum(str.substr(1));
            if(str[0]=='-')
                sign=true;
            else
                sign=false;

        }

    }
    bool operator ==(BigInt a)
    {
        return equal((*this),a);
    }
    BigInt absolute()
    {
        return BigInt(getnum());
    }

    void operator =(BigInt s)
    {
        setnum(s.getnum());

        setsign(s.getsign());
    }
    bool operator >(BigInt s)
    {
        return great((*this),s);
    }
    bool operator <(BigInt s)
    {
        return lesser((*this),s);
    }
    bool operator >=(BigInt s)
     {

       return equal((*this),s)|| great((*this),s);
     }

    BigInt operator +(BigInt b)
    {

        BigInt ans;
        if(getsign()==b.getsign())
        {
            ans.setnum(add(getnum(),b.getnum()));
            ans.setsign(b.getsign());
        }
        else{
            if(absolute()>b.absolute())
            {

                ans.setnum(sub(getnum(),b.getnum()));
                ans.setsign(getsign());
            }

            else
            {
                ans.setnum(sub(b.getnum(),getnum()));
                ans.setsign(b.getsign());
            }
        }

        return ans;
    }

    BigInt operator *(BigInt a)
    {
        BigInt ans;

        ans.setnum(mul(getnum(),a.getnum()));
        ans.setsign(getsign()!=a.getsign());

        return ans;

    }
        friend ostream & operator << (ostream &out, const BigInt &b);
        friend istream & operator >> (istream &in,  BigInt &b);

    BigInt operator -(BigInt a)
    {
        a.setsign(!a.getsign());

        return (*this)+a;
    }




};

bool BigInt ::equal(BigInt a, BigInt b)
{
    if(a.getnum()==b.getnum() && a.getsign()==b.getsign())
        return true;
    else
        return false;
}
bool BigInt :: lesser(BigInt a,BigInt b)
{
    bool s1=a.getsign();
    bool s2=b.getsign();

    if(s1==true && s2==false)
        return true;
    else if(s1==false && s2==true)
        return false;
    else{
        if(s1==false)
        {

            if(a.getnum().length()>b.getnum().length())
                    return false;
            else if(a.getnum().length()<b.getnum().length())
                    return true;
            else
                return a.getnum()<b.getnum();
        }
        else if(s1==true)
        {
            if(a.getnum().length()>b.getnum().length())
                    return true;
            else if(a.getnum().length()<b.getnum().length())
                    return false;
            else
                return a.getnum()>b.getnum();

        }
    }
}

bool BigInt::great(BigInt a,BigInt b)
{
    return (!equal(a,b) && !lesser(a,b));
}

ostream & operator<< (ostream &out, const BigInt &b)
{
    if(b.sign==true)
        cout<<"-";
    for(int i=0;i<b.num.size();i++)
        cout<<b.num[i];
}
istream & operator >> (istream &in,  BigInt &b)
{

    in >> b.num;


    return in;
}


string BigInt:: add(string a, string b)
{
    string c="";
    if(a.length()>b.length())
    {
        string temp=a;
        a=b;
        b=temp;

    }

    int carry=0;
    int l1=a.length();
    int l2=b.length();
    int difference = l2-l1;

    for(int i=l1-1;i>=0;i--)
    {
        int sum_of_digits = (a[i]-'0')+(b[i+difference]-'0')+carry;
        carry=sum_of_digits/10;
        c.push_back((sum_of_digits%10)+'0');


    }

    for(int i= difference-1;i>=0;i--)
    {
        int sum_of_digits=(b[i]-'0')+carry;
        carry=sum_of_digits/10;
        c.push_back((sum_of_digits%10)+'0');
    }
    if(carry)
        c.push_back(carry+'0');

    reverse(c.begin(),c.end());

    return c;


}
string BigInt:: sub(string a, string b)
{

    string c="";
    int carry=0;
   // cout<<a<<" "<<b<<" ";

    int l1=a.length();
    int l2=b.length();

    int difference=l1-l2;

    for(int i=l2-1;i>=0;i--)
    {
        int res=(a[i+difference]-'0')-(b[i]-'0')-carry;

        if(res<0)
        {
            carry=1;
            res=res+10;

        }
        else
        {
            carry=0;
        }
        c.push_back(res+'0');

    }

    for(int i=difference-1;i>=0;i--)
    {
        if(a[i]==0 && carry==1)
        {
            c.push_back('9');
            continue;
        }
        int res=(a[i]-'0')-carry;
        if(i>0||res>0)
        {
            c.push_back(res+'0');

        }
        carry=0;
    }

    reverse(c.begin(),c.end());
    int i=0;
    while(c[0]=='0'&& c.length()!=1)
    {
        c.erase(0,1);

    }

    return c;
}
string BigInt :: mul(string a,string b)
{
    int l1=a.length();
    int l2=b.length();

    if(l1==0||l2==0)
        return 0;

    int idx_a=0;
    int idx_b=0;
    string str="";

    vector<int>res(l1+l2,0);

    for(int i=l1-1;i>=0;i--)
    {
        int num1=a[i]-'0';
        int carry=0;

        idx_b=0;
        for(int j=l2-1;j>=0;j--)
        {
            int num2=b[j]-'0';

            int sum=num1*num2 +res[idx_a+idx_b]+carry;

            res[idx_a+idx_b]=sum%10;
            carry=sum/10;

            idx_b++;

        }
        if(carry>0)
            res[idx_a+idx_b]+=carry;

        idx_a++;
    }

    int j=res.size()-1;
    while(j>=0 && res[j]==0)
        j--;
    if(j==-1)
        return 0;
     while(j>=0)
            str+=std::to_string(res[j--]);



    return str;

}

string BigInt::expohelper(string a,string b)
{



}
BigInt factorial(BigInt a)
{
    BigInt c("1");
    BigInt d("1");
    BigInt e("1");
    while(a>=c)
    {
        d=d*c;
        c=c+e;
    }
    return d;


}
BigInt expo(BigInt a,BigInt b)
{
    BigInt c("1");
    BigInt d("1");
    BigInt ans=a;
    while(b>c)
    {
        ans=ans*a;
        c=c+d;

    }

    return ans;
}
BigInt gcd(BigInt a, BigInt b)
{
    if(a==b)
        return a;
    BigInt c=a-b;
    if(c>b)
        return gcd(c,b);
    else
        return gcd(b,c);
}

int main()
{

    int t;
    cin>>t;
    while(t--)
    {
        int ch;
        cin>>ch;
        if(ch==1)
        {
           BigInt n1;
           BigInt n2;
           cin>>n1;
           cin>>n2;

            BigInt c=expo(n1,n2);
            cout<<c;
            cout<<endl;

        }
        else if(ch==2)
        {
           BigInt n1;
           BigInt n2;
           cin>>n1;
           cin>>n2;
            BigInt c;
            if(n1>n2)
            {
                c=gcd(n1,n2);
            }
            else
            {
                c=gcd(n1,n2);
            }
            cout<<c;
            cout<<endl;

        }
        else{

            BigInt n1;
            cin>>n1;
            BigInt c=factorial(n1);
            cout<<c;
            cout<<endl;

        }

    }






    return 0;
}


