#include <iostream>
// #include <conio.h>
#include <iomanip>
using namespace std;

void mainmenu();
void adminmenu();
void customermenu();

class Admin
{
private:
    string train_plan[3];
    string traintime[6];
    string trainame;
    string address;
    float train_cost[3];

public:
    void insert_plan()
    {
        cout << "Can you write training centre name " << endl;
        cin.ignore();
        getline(cin, trainame);
        cout << "Enter address" << endl;
        getline(cin, address);
        for (int i = 0; i < 3; i++)
        {
            cin.ignore();
            cout << "Enter Training Plan\n";
            getline(cin, train_plan[i]);
            cout << "Enter time" << endl;
            getline(cin, traintime[i]);
            cout << "Enter Training Cost\n";
            cin >> train_cost[i];
        }
    }
    void update()
    {
        int choice;
        cout << "What do you want to update?" << endl;
        cout << "1. Trainee plan" << endl;
        cout << "2. Cost" << endl;
        cout << "3. Time" << endl;
        cin >> choice;

        cin.ignore();
        if (choice == 1)
        {
            int planIndex;
            cout << "Enter the index of the plan you want to update (1-3): ";
            cin >> planIndex;
            cin.ignore();
            cout << "Enter the updated training plan: ";
            getline(cin, train_plan[planIndex - 1]);
        }
        else if (choice == 2)
        {
            int costIndex;
            cout << "Enter the index of the cost you want to update (1-3): ";
            cin >> costIndex;
            cout << "Enter the updated training cost: ";
            cin >> train_cost[costIndex - 1];
        }
        else if (choice == 3)
        {
            int timeIndex;
            cout << "Enter the index of the time you want to update (1-3): ";
            cin >> timeIndex;
            cout << "Enter the updated training time: ";
            cin >> traintime[timeIndex - 1];
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }

    void view_training_plan()
    {
        cout << "Training plan-Prices" << endl;
        cout << left << setw(20) << "No." << setw(20) << "Training Plan" << setw(20) << "Time" << setw(20) << "Training Cost" << endl;

        for (int i = 0; i < 3; i++)
        {
            cout << left << setw(20) << i + 1 << setw(20) << train_plan[i] << setw(20) << traintime[i] << setw(20) << train_cost[i] << endl;
        }
    }
};

Admin obj_admin;

class Customer : public Admin
{
public:
    string customer_name;
    int t_plan;
    string cu_plan;
    string weight;
    char tution;
    int tution_hr;
    float beginner_fees = 20;
    float intermediate_fees = 30;
    float elite_fees = 40;
    float tution_fees = 23000.00;
    float total_cost = 0;
    float private_t;
    string cur_weight;
    char competition;
    int race;
    float comp_fees = 22.00;
    int comp = 0;

    float private_tution(char c)
    {
        if (c == 'y')
        {
            cout << "Enter private tution hours \n";
            cin >> tution_hr;

            if (tution_hr < 5)
            {
                total_cost += (tution_fees * tution_hr);
                return total_cost;
            }
            else
            {
                cout << "You exceed the limited private hours\n";
                private_tution(c);
            }
        }
        else
        {
            return total_cost;
        }
    }

    int weight_categories()
    {
        int race = 1;
        int current_weight;

        cout << "\n=========Competition weight Categories========\n\n";
        cout << "Categories\t\t\tWeight Limit\n";
        cout << "1.Heavy Weight\t\t\tover 100\n";
        cout << "2.Light Heavy Weight\t\t100\n";
        cout << "2.Middle Weight\t\t\t90\n";
        cout << "3.Light_MiddleWeight\t\t81\n";
        cout << "4.Light Weight\t\t\t73\n";
        cout << "5.Flyweight\t\t\t66\n";
        cout << "Enter your current weight\n";
        cin >> current_weight;

        if (current_weight > 100)
        {
            cout << "You can join Heavy Weight Competition \n";
            cur_weight = "Heavy Weight";
        }
        else if (current_weight == 100)
        {
            cout << "You can join Light Heavyweight Competition \n";
            cur_weight = "Light Weight";
        }
        else if ((current_weight < 100) && (current_weight >= 90))
        {
            cout << "You can join Middleweight Competition \n";
            cur_weight = "Middle Weight";
        }
        else if (current_weight < 90 && current_weight >= 81)
        {
            cout << "You can join Light Middleweight Competition \n";
            cur_weight = "Light Middleweight";
        }
        else if (current_weight < 81 && current_weight >= 73)
        {
            cout << "You can join Lightweight Competition \n";
            cur_weight = "Lightweight";
        }
        else if (current_weight < 73 && current_weight >= 66)
        {
            cout << "You can join Flyweight Competition \n";
            cur_weight = "Flyweight";
        }
        else
        {
            cout << "You can't compete\n";
            race = 0;
        }

        return race;
    }

    void getdata()
    {
        cin.ignore();
        cout << "Enter customer name\n";
        getline(cin, customer_name);
        obj_admin.view_training_plan();
        cin >> t_plan;

        if (t_plan == 1)
        {
            cu_plan = "beginner";
            total_cost += beginner_fees;
        }
        else if (t_plan == 2)
        {
            cu_plan = "intermediate";
            total_cost += intermediate_fees;
        }
        else if (t_plan == 3)
        {
            cu_plan = "Elite";
            total_cost += elite_fees;
        }

        cout << "Private tution (y/n)\n";
        cin >> tution;
        private_t = private_tution(tution);

        if ((t_plan == 2) || (t_plan == 3))
        {
            race = weight_categories();

            if (race == 1)
            {
                cout << "You can join competition\n";
                cout << "Enter number of competitions\n";
                cin >> comp;
                total_cost += (comp_fees * comp);
            }
            else if (race == 0)
            {
                cout << "You can't join competition\n";
            }
        }
        else
        {
            cout << "You can't compete, you are a beginner \n";
        }
    }

    void showdata()
    {
        int colWidth = 20;
        cout << left << setw(colWidth) << "Customer Name" << setw(colWidth) << "Total Cost" << setw(colWidth) << "Weight" << setw(colWidth) << "Training Plan" << endl;
        cout << left << setw(colWidth) << customer_name << setw(colWidth) << total_cost << setw(colWidth) << cur_weight << setw(colWidth) << cu_plan << endl;
    }

    void guestmenu()
    {
        int guest_choice;

        cout << "Guest Menu" << endl;
        cout << "1. View Training Plans" << endl;
        cout << "2. View Weight Categories" << endl;
        cout << "3. Exit" << endl;
        cin >> guest_choice;

        switch (guest_choice)
        {
        case 1:
            obj_admin.view_training_plan();
            break;
        case 2:
            weight_categories();
            break;
        case 3:
            exit(0);
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        guestmenu();
    }
};

Customer obj_customer[3];
int s = 0;

int main()
{
    mainmenu();
}

void mainmenu()
{
    int user;

    cout << "Enter your user type (1 for admin, 2 for customer, 3 for guest): ";
    cin >> user;

    if (user == 1)
    {
        adminmenu();
        getchar();
    }
    else if (user == 2)
    {
        customermenu();
    }
    else if (user == 3)
    {
        obj_customer[s].guestmenu();
    }
    else
    {
        cout << "Invalid user type" << endl;
    }
}

void adminmenu()
{
    int admin_task;

    cout << "1. Do you want to Insert plan?" << endl;
    cout << "2. Do you want to Update?" << endl;
    cout << "3. Do you want to View Training Plan?" << endl;
    cout << "4. Do you want to exit?" << endl;
    cin >> admin_task;

    if (admin_task == 1)
    {
        obj_admin.insert_plan();
        getchar();
        adminmenu();
    }
    else if (admin_task == 2)
    {
        obj_admin.update();
        getchar();
        adminmenu();
    }
    else if (admin_task == 3)
    {
        obj_admin.view_training_plan();
        getchar();
        adminmenu();
    }
    else if (admin_task == 4)
    {
        mainmenu();
    }
}

void customermenu()
{
    int customer_task;
    char ch;
    cout << "1. Register" << endl;
    cout << "2. View information" << endl;
    cin >> customer_task;

    if (customer_task == 1)
    {
        obj_customer[s].getdata();
        s++;
        cout << "Success inserted.\n";

        customermenu();
    }
    else if (customer_task == 2)
    {
        for (int i = 0; i < s - 1; i++)
        {
            for (int j = 0; j < s - i - 1; j++)
            {
                if (obj_customer[j].customer_name > obj_customer[j + 1].customer_name)
                {
                    swap(obj_customer[j], obj_customer[j + 1]);
                }
            }
        }

        for (int i = 0; i < s; i++)
        {
            cout << endl;
            obj_customer[i].showdata();
            cout << "-----------------------------------" << endl;
        }
        customermenu();
    }
}
