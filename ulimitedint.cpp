/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
// using namespace std;
// #include <iostream>
UnlimitedInt::UnlimitedInt()
{
    size = 0;
    sign = 0;
    capacity = 1;
    unlimited_int = new int[capacity];
    unlimited_int[0] = 0;
}
UnlimitedInt::UnlimitedInt(string s)
{
    size = s.length();
    bool checkzero = true;
    for (int i = 0; i < size; i++)
    {
        if (s[i] != '0')
        {
            checkzero = false;
        }
    }
    if (checkzero)
    {
        size = 0;
        sign = 0;
        capacity = 1;
        unlimited_int = new int[capacity];
        unlimited_int[0] = 0;
        return;
    }
    if (s[0] == '-')
    {
        sign = -1;
        size--;
    }
    else
    {
        sign = 1;
    }
    int number_of_zeros;
    if (sign == -1)
    {
        number_of_zeros = 1;
        while (s[number_of_zeros] == '0')
        {
            number_of_zeros++;
        }
        number_of_zeros--;
    }
    else
    {
        number_of_zeros = 0;
        while (s[number_of_zeros] == '0')
        {
            number_of_zeros++;
        }
    }
    size = size - number_of_zeros;
    capacity = size;
    unlimited_int = new int[capacity];
    if (sign == 1)
    {
        for (size_t i = number_of_zeros; i < s.length(); i++)
        {
            unlimited_int[s.length() - 1 - i] = s[i] - '0';
        }
    }
    else
    {
        number_of_zeros++;
        for (size_t i = number_of_zeros; i < s.length(); i++)
        {
            unlimited_int[s.length() - 1 - i] = s[i] - '0';
        }
    }
}
UnlimitedInt::UnlimitedInt(int i)
{
    size = 0;
    if (i == 0)
    {
        sign = 0;
        capacity = 1;
        size = 0;
        unlimited_int = new int[1];
        unlimited_int[0] = 0;
        return;
    }
    else if (i > 0)
    {
        sign = 1;
    }
    else
    {
        sign = -1;
    }
    int m = abs(i);
    while (m > 0)
    {
        m = m / 10;
        size++;
    }
    m = abs(i);
    capacity = size;
    unlimited_int = new int[capacity];
    for (int j = 0; j < size; j++)
    {
        unlimited_int[j] = m % 10;
        m = m / 10;
    }
}
UnlimitedInt::~UnlimitedInt()
{
    delete[] unlimited_int;

}
int UnlimitedInt::get_size()
{
    return size;
}
int *UnlimitedInt::get_array()
{
    return unlimited_int;
}
int UnlimitedInt::get_sign()
{
    return sign;
}
string UnlimitedInt::to_string()
{
    string ans = "";
    if (sign == 0)
    {
        return "0";
    }
    for (int i = 0; i < size; i++)
    {
        ans = ::to_string(unlimited_int[i]) + ans;
    }
    if (sign == -1)
    {
        return "-" + ans;
    }
    else
    {
        return ans;
    }
}
UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->get_sign() * i2->get_sign() == 0)
    {
        if (i1->get_sign() == 0)
        {
            return i2;
        }
        else
        {
            return i1;
        }
    }
    if (i1->get_sign() * i2->get_sign() < 0)
    {
        if (i1->get_sign() < 0)
        {
            UnlimitedInt *u = new UnlimitedInt(i1->to_string().substr(1));
            return sub(i2, u);
        }
        else
        {
            UnlimitedInt *u = new UnlimitedInt(i2->to_string().substr(1));
            return sub(i1, u);
        }
    }
    else
    {
        if (i1->get_sign() < 0)
        {
            UnlimitedInt *u1 = new UnlimitedInt(i1->to_string().substr(1));
            UnlimitedInt *u2 = new UnlimitedInt(i2->to_string().substr(1));
            UnlimitedInt *tu = add(u1, u2);
            delete u1;
            delete u2;
            UnlimitedInt *ans = new UnlimitedInt("-" + tu->to_string());
            delete tu;
            return ans;
        }
        else
        {
            string ans = "";
            int carry_over = 0;
            string s1 = i1->to_string();
            string s2 = i2->to_string();
            if (s1.length() > s2.length())
            {
                string temp = s2;
                s2 = s1;
                s1 = temp;
            } // length of s1<length of s2
            for (size_t i = 0; i < s1.length(); i++)
            {
                ans = ::to_string(((s1[s1.length() - i - 1] - '0') + (s2[s2.length() - i - 1] - '0') + carry_over) % 10) + ans;
                carry_over = ((s1[s1.length() - i - 1] - '0') + (s2[s2.length() - i - 1] - '0') + carry_over) / 10;
            }
            for (size_t i = s1.length(); i < s2.length(); i++)
            {
                ans = ::to_string(((s2[s2.length() - i - 1] - '0') + carry_over) % 10) + ans;
                carry_over = ((s2[s2.length() - i - 1] - '0') + carry_over) / 10;
            }
            ans = ::to_string((carry_over) % 10) + ans;
            UnlimitedInt *a = new UnlimitedInt(ans);
            return a;
        }
    }
}
UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{ // i1-i2
    if (i1->get_sign() == 1 && i2->get_sign() == -1)
    {
        UnlimitedInt *tu = new UnlimitedInt((i2->to_string()).substr(1));
        return add(i1, tu);
    }
    else if (i1->get_sign() == -1 && i2->get_sign() == 1)
    {
        UnlimitedInt *tu = new UnlimitedInt((i1->to_string()).substr(1));
        UnlimitedInt *tau = add(tu, i2);
        UnlimitedInt *tau2 = new UnlimitedInt("-" + tau->to_string());
        delete tau;
        delete tu;
        return tau2;
    }
    else if (i1->get_sign() == -1 && i2->get_sign() == -1)
    {
        UnlimitedInt *tu = new UnlimitedInt((i2->to_string()).substr(1));
        return add(i1, tu);
    }
    else if (i1->get_sign() == 0)
    {
        if (i2->get_sign() == -1)
        {
            UnlimitedInt *tu = new UnlimitedInt((i2->to_string()).substr(1));
            return tu;
        }
        else
        {   
            UnlimitedInt *tu = mul(i2, new UnlimitedInt(-1));
            return tu;
        }
    }
    else if (i2->get_sign() == 0)
    {
        return i1;
    }
    else
    {   
        UnlimitedInt *temp42= new UnlimitedInt(-1);
        string s2 = i2->to_string();
        string s1 = i1->to_string();
        // cout<<"s2 "<<s2<<endl;
        // cout<<"s1 "<<s1<<endl;
        bool check53= false;
        if(s2.length()>s1.length()){
            check53=true;
        }
        else if(s2.length()==s1.length()){
            for(size_t k=0; k<s1.length(); k++){
                if((s1[k]-'0')<(s2[k]-'0')){
                    check53=true;
                    break;
                }
                else if((s1[k]-'0')>(s2[k]-'0')){
                    break;
                }
            }
        }
        if(check53){
            return mul(sub(i2,i1),temp42);
        }
        if (s2.length() > s1.length())
        {
            for (size_t i = s1.length(); i < s2.length(); i++)
            {
                s1 = "0" + s1;
            }
        }
        else
        {
            for (size_t i = s2.length(); i < s1.length(); i++)
            {
                s2 = "0" + s2;
            }
        }
        string s2comp = "";
        for (size_t i = 0; i < s2.length(); i++)
        {
            s2comp = s2comp + ::to_string(9 - (s2[i] - '0'));
        }
        UnlimitedInt *d1 = new UnlimitedInt("1");
        UnlimitedInt *d2 = new UnlimitedInt("-1");
        UnlimitedInt *comp = new UnlimitedInt(s2comp);
        comp = add(comp, d1);
        UnlimitedInt *ta = add(comp, i1);
        UnlimitedInt *final_ans;
        if (ta->get_size() > s2.length())
        {
            final_ans = new UnlimitedInt(ta->to_string().substr(1));
            return final_ans;
        }
        else
        {
            string comp_final = "";
            string final = ta->to_string();
            for (int i = 0; i < ta->get_size(); i++)
            {
                comp_final = comp_final + ::to_string(9 - (final[i] - '0'));
            }
            final_ans = new UnlimitedInt(comp_final);
            final_ans = add(final_ans, d1);
            final_ans = mul(final_ans, d2);
            //-1 se multiply kardio
        }
        return final_ans;
    }
}
UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->get_sign() * i2->get_sign() == 0)
    {
        UnlimitedInt *temp = new UnlimitedInt(0);
        return temp;
    }
    else if (i1->get_sign() * i2->get_sign() < 0)
    {
        if (i1->get_sign() == -1)
        {
            UnlimitedInt *t1 = new UnlimitedInt(i1->to_string().substr(1));
            UnlimitedInt *aws = mul(t1, i2);
            string s = aws->to_string();
            UnlimitedInt *f = new UnlimitedInt("-" + s);
            delete t1;
            delete aws;
            return f;
        }
        else
        {
            UnlimitedInt *t2 = new UnlimitedInt(i2->to_string().substr(1));
            UnlimitedInt *aws = mul(t2, i1);
            string s = aws->to_string();
            UnlimitedInt *f = new UnlimitedInt("-" + s);
            delete t2;
            delete aws;
            return f;
        }
    }
    else if (i1->get_sign() * i2->get_sign() > 0 && i1->get_sign() < 0)
    {
        UnlimitedInt *t1 = new UnlimitedInt(i1->to_string().substr(1));
        UnlimitedInt *t2 = new UnlimitedInt(i2->to_string().substr(1));
        UnlimitedInt *a = mul(t2, t1);
        return a;
    }
    else
    {   
        string s1 = i1->to_string();
        string s2 = i2->to_string();
        // s1<=s2
        if (s2.length() < s1.length())
        {
            string temp = s1;
            s1 = s2;
            s2 = temp;
        }
        UnlimitedInt *ans = new UnlimitedInt(0);
        for (size_t i = 0; i < s1.length(); i++)
        {
            string s = "";
            int carryover = 0;
            for (size_t j = 0; j < s2.length(); j++)
            {
                int current = ((s1[s1.length() - i - 1] - '0') * (s2[s2.length() - j - 1] - '0') + carryover) % 10;
                s = ::to_string(current) + s;
                carryover = ((s1[s1.length() - i - 1] - '0') * (s2[s2.length() - j - 1] - '0') + carryover) / 10;
            }
            if (carryover != 0)
            {
                s = ::to_string(carryover) + s;
            }
            for (size_t j = 0; j < i; j++)
            {
                s = s + "0";
            }
            UnlimitedInt *te = new UnlimitedInt(s);
            ans = add(ans, te);
        }
        return ans;
    }
}

UnlimitedInt *UnlimitedInt::div(UnlimitedInt *i1, UnlimitedInt *i2)//(i1/i2)
{
    if(i2->to_string()=="0"){
        UnlimitedInt* r=new UnlimitedInt(0);
        return r;
    }
    UnlimitedInt *d2 = new UnlimitedInt("-1");
    UnlimitedInt *d1 = new UnlimitedInt("1");
    if (i1->get_sign() == 0)
    {
        return i1;
    }
    else if (i1->get_sign() * i2->get_sign() < 0)
    {
        if (i1->get_sign() < 0)
        {
            if (mod(mul(i1, d2), i2) == 0)
            {
                return mul(div(mul(i1, d2), i2), d2);
            }
            else
            {
                return sub(mul(div(mul(i1, d2), i2), d2), d1);
            }
        }
        else
        {
            if (mod(i1, mul(i2, d2)) == 0)
            {
                return mul(div(i1, mul(i2, d2)), d2);
            }
            else
            {
                return sub(mul(div(i1, mul(i2, d2)), d2), d1);
            }
        }
    }
    else if (i1->get_sign() * i2->get_sign() > 0 && i1->get_sign() < 0)
    {
        return div(mul(i1, d2), mul(i2, d2));
    }
    else
    {
        // UnlimitedInt* i=new UnlimitedInt(0);
        // UnlimitedInt* diff=sub(i1,i2);
        // while(diff->get_sign()>=0){
        //     i=add(i,d1);
        //     diff=sub(diff,i2);
        // }
        // return i;
        UnlimitedInt* arr[10];
        for(int i=0;i<10;i++){
            UnlimitedInt* temp= new UnlimitedInt(i);
            arr[i]=mul(temp,i2);
            delete temp;
        }
        if(i2->get_size()>i1->get_size()){
            return new UnlimitedInt(0);
        }
        int t= i1->get_size()-i2->get_size();
        string s= i1->to_string();
        string su= s.substr(0,i2->get_size());
        string ans="";
        for(int carry=0;carry<=t;carry++){
            int j=0;
            bool check= true;
            if(i2->get_size()>su.length()){
                ans=ans+"0";
                if(t!=carry){
                    su=su+"0";
                }
                continue;
            }
            while(check && j<9){
                j++;
                string temp= arr[j]->to_string();
                if(su.length()<temp.length()){
                    check=false;
                    continue;
                }
                if(temp.length()<su.length()){
                    continue;
                }
                for(size_t m=0;m<su.length();m++){
                    if((temp[m]-'0')>(su[m]-'0')){
                        check=false;
                        break;
                    }
                    else if((temp[m]-'0')<(su[m]-'0')){
                        check=true;
                        break;
                    }
                }
            }
            if(check && j==9){
                j++;
            }
            ans=ans+::to_string(j-1);
            if(t!=carry){
                UnlimitedInt* te= new UnlimitedInt(su);
                su=(i1->sub(te,arr[j-1]))->to_string()+s[i2->get_size()+carry];
                UnlimitedInt* temp5= new UnlimitedInt(su);
                su=temp5->to_string();
                delete te,temp5;
            } 
        }
        return new UnlimitedInt(ans);
    }
}
//r=i1-(i2*div(i1,i2))
UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt *divv = div(i1, i2);
    // cout<<"divv "<<divv->to_string()<<endl;
    UnlimitedInt *pq = mul(i2, divv);
    // cout<<"pq "<<pq->to_string()<<endl;
    UnlimitedInt *ans = sub(i1, pq);
    delete pq;
    delete divv;
    return ans;
}


// int main(){
//     UnlimitedInt* temp= new UnlimitedInt();
//     UnlimitedInt *temp2= new UnlimitedInt("28561");
//     UnlimitedInt *temp3= new UnlimitedInt("7056");
//     cout<<temp->mod(temp2,temp3)->to_string()<<endl;
// }
