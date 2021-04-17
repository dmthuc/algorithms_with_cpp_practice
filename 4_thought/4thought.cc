#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <cassert>
using namespace std;

std::vector<int> get_input()
{
    std::vector<int> ret;
    int number;
    while(cin >> number)
    {
        ret.push_back(number);
    } 
    ret.erase(ret.begin());
    return ret;
}

struct Operator
{
    virtual int operator()(int a, int b) const = 0;
    virtual char getName() const noexcept = 0;
};

struct Divide : public Operator
{
    int operator()(int a, int b) const override
    {
        if (b == 0)
            throw std::runtime_error("divide to 0");
        return a/b; 
    }

    char getName() const noexcept override
    {
        return '/'; 
    }
};

struct Add : public Operator
{
    int operator() (int a, int b) const override
    {
        return a + b;
    }

    char getName() const noexcept override
    {
        return '+'; 
    }
};

struct Multiply : public Operator
{
    int operator() (int a, int b) const noexcept override
    {
        return a * b;
    }

    char getName() const noexcept override
    {
        return '*'; 
    }
};

struct Subtract : public Operator
{
    int operator() (int a, int b) const noexcept override
    {
        return a - b;
    }

    char getName() const noexcept override
    {
        return '-'; 
    }
};
Divide divide;
Multiply multiply;
Add add;
Subtract subtract;

std::vector<Operator*> all_operator{
    static_cast<Operator*>(&divide),
    static_cast<Operator*>(&multiply),
    static_cast<Operator*>(&add),
    static_cast<Operator*>(&subtract)
};

std::vector<int> initial_operand{4,4,4,4};

std::string solution_to_string(std::vector<Operator*>& operators, int result)
{
    std::string ret = "4 ";
    for (int i = operators.size() - 1; i >= 0; --i)
    {
        ret += operators[i]->getName();
        ret += " 4 ";
    }
    ret += "= ";
    ret += std::to_string(result);
    return ret; 
}

int calculate(std::vector<Operator*>& operators, std::vector<int>& operands)
{
    assert(operands.size() == (operators.size() + 1)); 
    if (operands.empty())
        return 0;
    if (operators.empty())
        return operands.back();

    auto it = std::find_if(operators.rbegin(), operators.rend(), [](Operator* op)
    {
        char name = op->getName();
        if (name == '/' || name == '*') 
            return true;
        else
            return false;
    });

    if (it != operators.rend())
    {
        int distance = operators.size() - std::distance(operators.rbegin(), it) - 1;
        Operator * op = *it;   
        operators.erase(operators.begin() + distance);
        int term = (*op)(operands[distance + 1], operands[distance]);
        operands.erase(operands.begin() + distance);
        operands[distance] = term;
        return calculate(operators, operands);
    }
    else
    {
        int res = operands.back();
        operands.pop_back();  
        while(!operators.empty())
        {
            Operator & op = *(operators.back());
            operators.pop_back();
            res = op(res, operands.back());
            operands.pop_back();  
        }
        return res;
    }
}

std::map<int, string> prepare_solution()
{
    std::map<int, string> ret;
    int size = all_operator.size();
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            for (int k = 0; k < size; ++k)
            {
                std::vector<Operator*> operators;
                operators.push_back(all_operator[i]);
                operators.push_back(all_operator[j]);
                operators.push_back(all_operator[k]);
                std::vector<Operator*> operators_clone = operators;
                std::vector<int> operands = initial_operand;
                try 
                {
                    int result = calculate(operators, operands);
                    ret.insert(std::make_pair(result, solution_to_string(operators_clone,result)));
                }
                catch(...)
                {

                }
            }
        }
    }
    return ret;
}

int main(void)
{
#if 0
    std::vector<int> operands = initial_operand;
    std::vector<Operator*> operators{
        static_cast<Operator*>(&divide),
        static_cast<Operator*>(&add),
        static_cast<Operator*>(&add)
    };

    std::vector<Operator*> operators_clone = operators;
    int res = calculate(operators, initial_operand);
    std::cout << solution_to_string(operators_clone, res) << '\n'; 
    std::cout << operators.size() << '\n';
#endif

    std::map<int, std::string> solution = prepare_solution();
    std::vector<int> input = get_input();

#if 0
    for (auto p : solution)
    {
        std::cout << p.second << ' ' << p.first << '\n';
    }    
#endif
#if 1
    for (int val : input)
    {
        auto it = solution.find(val);
        if (it != solution.end())
            std::cout << it->second << '\n';
        else
            std::cout << "no solution" << '\n';
    } 
#endif
    return 0;
}


