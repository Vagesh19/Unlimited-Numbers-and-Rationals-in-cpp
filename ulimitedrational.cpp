/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
// #include <iostream>
// using namespace std;
UnlimitedRational::UnlimitedRational()
{
    p = new UnlimitedInt(0);
    q = new UnlimitedInt(1);
}
UnlimitedRational::~UnlimitedRational()
{
    delete p, q;
}
UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den)
{   
    UnlimitedInt *d1 = new UnlimitedInt("-1");
    if (den->to_string() == "0")
    {
        p = den;
        q = den;
    }
    else if (num->to_string() == "0")
    {
        p = num;
        q = new UnlimitedInt("1");
    }
    else
    {   
        UnlimitedInt *gcd;
        if(den->get_sign()==-1){
            num=gcd->mul(d1,num);
            den=gcd->mul(d1,den);
        }
        UnlimitedInt *pt= num;
        if(num->get_sign()<=0){
            num=gcd->mul(d1,num);
        }
        UnlimitedInt *qt = den;
        while (((gcd->mod(den, num))->to_string())!= "0" && ((gcd->mod(num, den))->to_string())!="0")
        {   
            UnlimitedInt *diff = gcd->sub(den, num);
            UnlimitedInt *d1 = new UnlimitedInt("-1");
            if (diff->get_sign() > 0)
            {
                den = gcd->mod(den,num);
            }
            else
            {
                num = gcd->mod(num, den);
            }
        }
        if ((gcd->mod(den, num))->to_string() == "0")
        {
            gcd = num;
        }
        else
        {
            gcd = den;
        }
        if(pt->get_sign()<0){
            p= gcd->mul(gcd->div(gcd->mul(pt,d1),gcd),d1);
        }
        else{
            p = gcd->div(pt, gcd);
        }
        q = gcd->div(qt, gcd);
    }
}

UnlimitedInt *UnlimitedRational::get_p()
{
    return p;
}
UnlimitedInt *UnlimitedRational::get_q()
{
    return q;
}
string UnlimitedRational::get_p_str()
{
    return p->to_string();
}
string UnlimitedRational::get_q_str()
{
    return q->to_string();
}
string UnlimitedRational::get_frac_str()
{
    return p->to_string() + "/" + q->to_string();
}
UnlimitedRational *UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *gcd;
    if ((i1->get_q()->to_string() == "0" && i1->get_p()->to_string() == "0") || (i2->get_q()->to_string() == "0" && i2->get_p()->to_string() == "0"))
    {
        UnlimitedInt *num = new UnlimitedInt(0);
        UnlimitedInt *den = new UnlimitedInt(0);
        UnlimitedRational *r = new UnlimitedRational(num, den);
        return r;
    }
    UnlimitedInt *den1 = i1->get_q();
    UnlimitedInt *den2 = i2->get_q();
    UnlimitedInt *num1 = i1->get_p();
    UnlimitedInt *num2 = i2->get_p();
    UnlimitedInt *num = gcd->add(gcd->mul(num1, den2), gcd->mul(num2, den1));
    UnlimitedInt *den = gcd->mul(den1, den2);
    UnlimitedRational *r = new UnlimitedRational(num, den);
    delete num, den, num1, num2, den1, den2;
    return r;
}
UnlimitedRational *UnlimitedRational::sub(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *gcd;
    if ((i1->get_q()->to_string() == "0" && i1->get_p()->to_string() == "0") || (i2->get_q()->to_string() == "0" && i2->get_p()->to_string() == "0"))
    {
        UnlimitedInt *num = new UnlimitedInt(0);
        UnlimitedInt *den = new UnlimitedInt(0);
        UnlimitedRational *r = new UnlimitedRational(num, den);
        return r;
    }
    UnlimitedInt *den1 = i1->get_q();
    UnlimitedInt *den2 = i2->get_q();
    UnlimitedInt *num1 = i1->get_p();
    UnlimitedInt *num2 = i2->get_p();
    UnlimitedInt *num = gcd->sub(gcd->mul(num1, den2), gcd->mul(num2, den1));
    UnlimitedInt *den = gcd->mul(den1, den2);
    UnlimitedRational *r = new UnlimitedRational(num, den);
    delete num, den, num1, num2, den1, den2;
    return r;
}

UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *gcd;
    if ((i1->get_q()->to_string() == "0" && i1->get_p()->to_string() == "0") || (i2->get_q()->to_string() == "0" && i2->get_p()->to_string() == "0"))
    {
        UnlimitedInt *num = new UnlimitedInt(0);
        UnlimitedInt *den = new UnlimitedInt(0);
        UnlimitedRational *r = new UnlimitedRational(num, den);
        return r;
    }
    UnlimitedInt *den1 = i1->get_q();
    UnlimitedInt *den2 = i2->get_q();
    UnlimitedInt *num1 = i1->get_p();
    UnlimitedInt *num2 = i2->get_p();
    UnlimitedInt *num = gcd->mul(num1, num2);
    UnlimitedInt *den = gcd->mul(den1, den2);
    UnlimitedRational *r = new UnlimitedRational(num, den);
    delete num, den, num1, num2, den1, den2;
    return r;
}
UnlimitedRational *UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2)
{ //(i1/i2) i.e (num1*den2)/(den1*num2)
    UnlimitedInt *gcd;
    UnlimitedInt *d1 = new UnlimitedInt("-1");
    UnlimitedInt *den1 = i1->get_q();
    UnlimitedInt *den2 = i2->get_q();
    UnlimitedInt *num1 = i1->get_p();
    UnlimitedInt *num2 = i2->get_p();
    if (num2->to_string() == "0" || den1->to_string() == "0")
    {
        UnlimitedInt *num = new UnlimitedInt(0);
        UnlimitedInt *den = new UnlimitedInt(0);
        UnlimitedRational *r = new UnlimitedRational(num, den);
        delete num, den, num1, num2, den1, den2;
        return r;
    }
    UnlimitedInt *num = gcd->mul(num1, den2);
    UnlimitedInt *den = gcd->mul(den1, num2);
    UnlimitedRational *r = new UnlimitedRational(num, den);
    delete num, den, num1, num2, den1, den2;
    return r;
}

// int main() {
//     // Create some UnlimitedInt objects
//     UnlimitedInt* num1 = new UnlimitedInt("1");
//     UnlimitedInt* den1 = new UnlimitedInt("6");
//     UnlimitedInt* num2 = new UnlimitedInt("9");
//     UnlimitedInt* den2 = new UnlimitedInt("5");
//     cout<<"mark1"<<endl;
//     // Create UnlimitedRational objects
//     UnlimitedRational* rational1 = new UnlimitedRational(num1, den1);
    
//     cout<<"mark2"<<endl;
//     UnlimitedRational* rational2 = new UnlimitedRational(num2, den2);
//     // Print the fractions
//     cout << "Rational 1: " << rational1->get_frac_str() << endl;
//     cout << "Rational 2: " << rational2->get_frac_str() << endl;

//     // Perform addition
//     UnlimitedRational* sum = UnlimitedRational::add(rational1, rational2);
//     cout << "Sum: " << sum->get_frac_str() << endl;

//     // Perform subtraction
//     UnlimitedRational* diff = UnlimitedRational::sub(rational1, rational2);
//     cout << "Difference: " << diff->get_frac_str() << endl;

//     // Perform multiplication
//     UnlimitedRational* product = UnlimitedRational::mul(rational1, rational2);
//     cout << "Product: " << product->get_frac_str() << endl;

//     // Perform division
//     UnlimitedRational* quotient = UnlimitedRational::div(rational1, rational2);
//     cout << "Quotient: " << quotient->get_frac_str() << endl;

//     // Clean up memory
//     delete num1;
//     delete den1;
//     delete num2;
//     delete den2;
//     delete rational1;
//     delete rational2;
//     delete sum;
//     delete diff;
//     delete product;
//     delete quotient;

//     return 0;
// }

// int main(){
//         // Create some UnlimitedInt objects
//     UnlimitedInt* num1 = num1->mul(new UnlimitedInt("5"),new UnlimitedInt("42"));
//     UnlimitedInt* den1 = new UnlimitedInt("1");
//     UnlimitedInt* num2 = new UnlimitedInt("526848");
//     // cout<<num2->mul(num2,num2)->to_string() << endl;
//     UnlimitedInt* den2 = new UnlimitedInt("815730721");
//     UnlimitedRational* rational1 = new UnlimitedRational(num1, den1);
//     UnlimitedRational* rational2 = new UnlimitedRational(num2, den2);
//     // cout<<den2->to_string()<<endl;
//     cout<<"rational2 "<<rational2->get_frac_str()<<endl;
//     UnlimitedRational* rational3 = rational1->mul(rational2,rational2);
//     cout<<"rational3 "<<rational3->get_frac_str()<<endl;
//     cout<<rational2->div(rational1,rational3)->get_frac_str()<<endl;
//     // cout<< newden->div(rational1,newden)->get_frac_str()<<endl;
//     // cout<<rational1->add(rational1,rational2)->get_frac_str()<<endl;
// }