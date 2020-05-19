#include <iostream>
#include <string>
#include <fstream> 
using namespace std;

template < typename T >
struct list
{
    T id;
    list* next;
    int val = 1;
};


template < typename T >
void push(list<T>*& ptr, T x)
{
    list<T>* tmp = new list<T>;
    (*tmp).id = x;
    tmp->next = ptr;
    ptr = tmp;
}


template < typename T >
void print_list(list<T>* ptr)
{
    if (ptr->val != 0)
    {
        cout << ptr->id << " -> ";
        print_list(ptr->next);
    }
}


template < typename T >
T pop(list<T>*& ptr)
{
    list<T>* tmp = ptr;
    T x = tmp->id;
    ptr = ptr->next;
    delete(tmp);
    return(x);
}
int priority(char x) {
    if (x == '=') return 1;
    if (x == '(') return 2;
    if (x == '+' || x == '-') return 3;
    if (x == '*' || x == '/') return 4;
}
int operate(list<char>*&lst1, list<double>*& lst, string& s) {
    char op = pop(lst1);
    s += op;
    s += " ";
    switch (op) {
    case('+'):
        push(lst, pop(lst) + pop(lst));
        break;
    case('-'):
        push(lst, -(pop(lst) - pop(lst)));
        break;
    case('*'):
        push(lst, pop(lst) * pop(lst));
        break;
    case('/'):
        double x = pop(lst);
        double y = pop(lst);
        if (x != 0) push(lst, y / x);
        else {
            std::cout << "Division by zero!!!";
            return 0;
        }
        break;
    }
}
int main()
{
    ifstream file("input.txt");
    int c = 1;
    list<double>* lst = NULL;
    string s;
    list<char>* lst1 = NULL;

    string str;
    std::getline(file, str);
    std::cout << str;
    int i = 0;
    while (i < str.size()) {
        if (isdigit(str[i])) {
            string num = { str[i] };
            i++;
            while (isdigit(str[i])) {
                num += {str[i]};
                i++;
            }
            if (str[i] == '.') {
                num += {str[i]};
                i++;
            }
            while (isdigit(str[i])) {
                num += {str[i]};
                i++;
            }
            if (str[i] == 'e') {
                num += str[i];
                i++;
                num += str[i];
                i++;
                num += str[i];
                i++;
                num += str[i];
                i++;
            }
            push(lst, c * stod(num));
            s += std::to_string(c * stod(num)).substr(0, 4);
            s += " ";
            c = 1;
        }
        else {
            if (str[i] == ')') {
                while (lst1 != NULL && lst1->id != '(') {
                    operate(lst1, lst, s);
                }
                pop(lst1);
                i++;
            }
            else {
                if (str[i] == '=') {
                    while (lst1!=NULL) {
                        operate(lst1, lst, s);
                    }
                    i++;
                }
                else {
                    int t = priority(str[i]);
                    if (t == 2) {
                        push(lst1, str[i]);
                        i++;
                    }
                    else {
                        if ((str[i] == '-' && i == 0) || (str[i] == '-' && str[i - 1] == '(')) c = -1;
                        else {
                            while (lst1 != NULL && t <= priority(lst1->id)) {
                                operate(lst1, lst, s);
                            }
                            push(lst1, str[i]);

                        }
                        i++;
                    }
                }
            }
        }
    }
    std::cout << "\n" << s << "=";
    std::cout << "\nAnswer: " << lst->id << "\n";
    return 0;
}
