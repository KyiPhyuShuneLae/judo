#include <iostream>
#include <string>

using namespace std;

const int MAX_PLANS = 6;
const int MAX_ATHLETES = 100;
const int MAX_CENTERS = 10;
const int MAX_CUSTOMERS = 10;

class TrainingCenter;
class Customer;

void combSortTrainingCenters(TrainingCenter centers[], int numCenters);
void combSort(string arr[], int n);

class TrainingPlan
{
public:
    string name;
    string time;

    TrainingPlan() {}
    TrainingPlan(const string &name, const string &time)
        : name(name), time(time) {}
};

class TrainingCenter
{
public:
    string name;
    string address;
    TrainingPlan plans[MAX_PLANS];
    int numPlans;
    int beginner_cost, intermediate_cost, elite_cost, competition_cost, tuition_cost;

    TrainingCenter() : numPlans(0) {}
    TrainingCenter(const string &name, const string &address, const TrainingPlan defaultPlans[],
                   int numDefaultPlans, int beginner, int intermediate, int elite, int competition, int tuition)
        : name(name), address(address), numPlans(0), beginner_cost(beginner), intermediate_cost(intermediate),
          elite_cost(elite), competition_cost(competition), tuition_cost(tuition), numEnrolledAthletes(0)
    {
        for (int i = 0; i < numDefaultPlans; ++i)
        {
            addPlan(defaultPlans[i]);
        }
    }

    void addPlan(const TrainingPlan &plan)
    {
        if (numPlans < MAX_PLANS)
        {
            plans[numPlans++] = plan;
        }
        else
        {
            cout << "Trainee limit reached!" << endl;
        }
    }

    void setPlanCosts(int beginner, int intermediate, int elite, int competition, int tuition)
    {
        beginner_cost = beginner;
        intermediate_cost = intermediate;
        elite_cost = elite;
        competition_cost = competition;
        tuition_cost = tuition;
    }

    void viewTrainingPlans() const
    {
        system("clear");
        cout << "Training Plans and Prices" << endl;
        cout << "Trainee Plan\tTime" << endl;
        for (int i = 0; i < numPlans; i++)
        {
            cout << plans[i].name << "\t" << plans[i].time << "\t" << endl;
        }

        cout << "Plan Prices:" << endl;
        cout << "============" << endl;
        cout << "Beginner Plan Cost: "
             << "£" << beginner_cost << endl;
        cout << "Intermediate Plan Cost: "
             << "£" << intermediate_cost << endl;
        cout << "Elite Plan Cost: "
             << "£" << elite_cost << endl;

        cout << "Press any key to continue..." << endl;
        cin.get();
    }

    void viewWeightCategories() const
    {
        cout << endl;
        cout << "Weight Categories for Competition" << endl;
        cout << "Category\tUpper Weight Limit (kg)" << endl;
        cout << "Heavyweight\tUnlimited (over 100)" << endl;
        cout << "Light Heavyweight\t100" << endl;
        cout << "Middleweight\t90" << endl;
        cout << "Light Middleweight\t81" << endl;
        cout << "Lightweight\t73" << endl;
        cout << "Flyweight\t66" << endl;
        cout << "Press any key to continue..." << endl;
        cin.get();
    }

    int getBeginnerCost() const { return beginner_cost; }
    int getIntermediateCost() const { return intermediate_cost; }
    int getEliteCost() const { return elite_cost; }
    int getCompetitionCost() const { return competition_cost; }
    int getTuitionCost() const { return tuition_cost; }

    int numEnrolledAthletes;
    string enrolledAthletes[MAX_ATHLETES];

    void viewEnrolledAthletes() const
    {
        cout << endl
             << "Enrolled Athletes:" << endl;
        for (int i = 0; i < numEnrolledAthletes; i++)
        {
            cout << i + 1 << ". " << enrolledAthletes[i] << endl;
        }
    }

    void deleteEnrolledAthlete()
    {
        if (numEnrolledAthletes > 0)
        {
            viewEnrolledAthletes();
            cout << "Enter the number of the athlete to delete: ";
            int choice;
            cin >> choice;

            if (choice > 0 && choice <= numEnrolledAthletes)
            {
                for (int i = choice - 1; i < numEnrolledAthletes - 1; i++)
                {
                    enrolledAthletes[i] = enrolledAthletes[i + 1];
                }
                numEnrolledAthletes--;
                cout << "Athlete deleted successfully." << endl;
            }
            else
            {
                cout << "Invalid choice." << endl;
            }
        }
        else
        {
            cout << "No athletes enrolled." << endl;
        }

        cout << "Press any key to continue..." << endl;
        cin.ignore();
        cin.get();
    }
};

class Admin
{
public:
    void viewAvailableCenters(const TrainingCenter centers[], int numCenters)
    {
        cout << "Available Training Centers:" << endl;
        for (int i = 0; i < numCenters; ++i)
        {
            cout << i + 1 << ". " << centers[i].name << endl;
        }
    }

    void viewEnrolledAthletes(TrainingCenter centers[], int numCenters)
    {
        system("clear");

        viewAvailableCenters(centers, numCenters);

        int centerChoice;
        cout << "Select a training center to view enrolled athletes (1-" << numCenters << "): ";
        cin >> centerChoice;

        if (centerChoice >= 1 && centerChoice <= numCenters)
        {
            centers[centerChoice - 1].viewEnrolledAthletes();
        }
        else
        {
            cout << "Invalid center choice. Please try again." << endl;
        }
    }

    void deleteEnrolledAthlete(TrainingCenter centers[], int numCenters)
    {
        system("clear");

        viewAvailableCenters(centers, numCenters);
        int centerChoice;
        cout << "Select a training center to delete enrolled athlete (1-" << numCenters << "): ";
        cin >> centerChoice;

        if (centerChoice >= 1 && centerChoice <= numCenters)
        {
            centers[centerChoice - 1].deleteEnrolledAthlete();
        }
        else
        {
            cout << "Invalid center choice. Please try again." << endl;
        }
    }

    void insertTrainingCenter(TrainingCenter centers[], int &numCenters)
    {
        system("clear");
        cin.ignore();
        cout << "Enter training center name: ";
        getline(cin, centers[numCenters].name);
        cout << "Enter training center address: ";
        getline(cin, centers[numCenters].address);

        int numPlans;
        cout << "Enter the number of training plans: ";
        cin >> numPlans;

        for (int i = 0; i < numPlans; ++i)
        {
            string name, time;
            cin.ignore();
            cout << "Enter training plan " << i + 1 << " name: ";
            getline(cin, name);
            cout << "Enter training plan " << i + 1 << " time: ";
            getline(cin, time);

            TrainingPlan plan(name, time);
            centers[numCenters].addPlan(plan);
        }

        int beginner, intermediate, elite, competition, tuition;
        cout << "Enter the cost for the Beginner Plan: ";
        cin >> beginner;
        cout << "Enter the cost for the Intermediate Plan: ";
        cin >> intermediate;
        cout << "Enter the cost for the Elite Plan: ";
        cin >> elite;
        cout << "Enter the cost for the Competition Plan: ";
        cin >> competition;
        cout << "Enter the cost for Tuition (per hour): ";
        cin >> tuition;

        centers[numCenters].setPlanCosts(beginner, intermediate, elite, competition, tuition);

        cout << "Training center added successfully!" << endl;
        numCenters++;

        combSortTrainingCenters(centers, numCenters);
    }

    void viewAllTrainingCenters(const TrainingCenter centers[], int numCenters)
    {
        system("clear");
        cout
            << "All Training Centers:" << endl;
        for (int i = 0; i < numCenters; ++i)
        {
            cout << "---------------------------------" << endl;
            cout << "Center " << i + 1 << ":" << endl;
            cout << "Name: " << centers[i].name << endl;
            cout << "Address: " << centers[i].address << endl;
            cout << "Plans:" << endl;
            for (int j = 0; j < centers[i].numPlans; ++j)
            {
                cout << "  " << centers[i].plans[j].name << " - " << centers[i].plans[j].time << endl;
            }
            cout << "Plan Prices:" << endl;
            cout << "Beginner Plan Cost: £" << centers[i].getBeginnerCost() << endl;
            cout << "Intermediate Plan Cost: £" << centers[i].getIntermediateCost() << endl;
            cout << "Elite Plan Cost: £" << centers[i].getEliteCost() << endl;
            cout << "Competition Plan Cost: £" << centers[i].getCompetitionCost() << endl;
            cout << "Tuition Cost (per hour): £" << centers[i].getTuitionCost() << endl;

            cout << "---------------------------------" << endl;
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        cin.get();
    }

    void updateTrainingCenter(TrainingCenter centers[], int numCenters)
    {
        system("clear");
        viewAvailableCenters(centers, numCenters);
        int centerChoice;
        cout << "Select a training center to update (1-" << numCenters << "): ";
        cin >> centerChoice;

        if (centerChoice >= 1 && centerChoice <= numCenters)
        {
            TrainingCenter &selectedCenter = centers[centerChoice - 1];

            cin.ignore();
            cout << "Enter new training center name: ";
            getline(cin, selectedCenter.name);
            cout << "Enter new training center address: ";
            getline(cin, selectedCenter.address);

            int numPlans;
            cout << "Enter the number of training plans: ";
            cin >> numPlans;

            selectedCenter.numPlans = 0;

            for (int i = 0; i < numPlans; ++i)
            {
                string name, time;
                cin.ignore();
                cout << "Enter training plan " << i + 1 << " name: ";
                getline(cin, name);
                cout << "Enter training plan " << i + 1 << " time: ";
                getline(cin, time);

                TrainingPlan plan(name, time);
                selectedCenter.addPlan(plan);
            }

            int beginner, intermediate, elite, competition, tuition;
            cout << "Enter the cost for the Beginner Plan: ";
            cin >> beginner;
            cout << "Enter the cost for the Intermediate Plan: ";
            cin >> intermediate;
            cout << "Enter the cost for the Elite Plan: ";
            cin >> elite;
            cout << "Enter the cost for the Competition Plan: ";
            cin >> competition;
            cout << "Enter the cost for Tuition (per hour): ";
            cin >> tuition;

            selectedCenter.setPlanCosts(beginner, intermediate, elite, competition, tuition);

            cout << "Training center updated successfully!" << endl;
        }
        else
        {
            cout << "Invalid center choice. Please try again." << endl;
        }
    }
};

class Customer
{
public:
    string name;
    int plan_choice;
    int total_price;

    void setCustomerName(const string &customerName) { name = customerName; }

    void choosePlan(TrainingCenter &center, int plan)
    {
        total_price = 0;
        plan_choice = plan;
        if (plan_choice == 1)
        {
            int tuition_choice;
            cout << "Do you want private tuition? (1 for Yes, 2 for No): ";
            cin >> tuition_choice;
            if (tuition_choice == 1)
            {
                int hours;
                cout << "Enter the number of hours for private coaching (max 5 hours): ";
                cin >> hours;
                if (hours <= 5)
                {
                    total_price += center.getTuitionCost() * hours;
                }
                else
                {
                    cout << "Athletes can receive a maximum of five hours of private coaching a week." << endl;
                }
            }
            cout << "You have chosen the Beginner plan." << endl;
            total_price += center.getBeginnerCost();
        }
        else if (plan_choice == 2 || plan_choice == 3)
        {
            int competition_choice;
            cout << "Do you want to participate in a competition? (1 for Yes, 2 for No): ";
            cin >> competition_choice;

            if (competition_choice == 1)
            {
                int numCompetitions;
                cout << "How many competitions do you want to join? ";
                cin >> numCompetitions;
                total_price += center.getCompetitionCost() * numCompetitions;
            }

            viewWeightCategories();
            weight();

            int tuition_choice;
            cout << "Do you want private tuition? (1 for Yes, 2 for No): ";
            cin >> tuition_choice;
            if (tuition_choice == 1)
            {
                int hours;
                cout << "Enter the number of hours for private coaching (max 5 hours): ";
                cin >> hours;
                if (hours <= 5)
                {
                    total_price += center.getTuitionCost() * hours;
                }
                else
                {
                    cout << "Athletes can receive a maximum of five hours of private coaching a week." << endl;
                }
            }

            if (plan_choice == 2)
            {
                cout << "You have chosen the Intermediate plan." << endl;
                total_price += center.getIntermediateCost();
            }
            else if (plan_choice == 3)
            {
                cout << "You have chosen the Elite plan." << endl;
                total_price += center.getEliteCost();
            }
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
            choosePlan(center, plan_choice);
        }
        cout << "Total price: " << total_price << endl;
    }

    void viewData(const TrainingCenter &center) const
    {
        system("clear");
        cout << "Customer name: " << name << endl;
        cout << "Choices made: ";
        if (plan_choice == 1)
        {
            cout << "Beginner plan";
        }
        else if (plan_choice == 2)
        {
            cout << "Intermediate plan";
        }
        else if (plan_choice == 3)
        {
            cout << "Elite plan";
        }
        cout << endl;
        cout << "Total price: " << total_price << endl;
    }

    void weight()
    {
        int w;
        cout << "Enter your weight in kg: ";
        cin >> w;
        if (w > 100)
        {
            cout << "You are in the Heavyweight category." << endl;
        }
        else if (w > 90)
        {
            cout << "You are in the Light-Heavyweight category." << endl;
        }
        else if (w > 81)
        {
            cout << "You are in the Middleweight category." << endl;
        }
        else if (w > 73)
        {
            cout << "You are in the Light-Middleweight category." << endl;
        }
        else if (w > 66)
        {
            cout << "You are in the Lightweight category." << endl;
        }
        else
        {
            cout << "You are in the Flyweight category." << endl;
        }
        cout << "Press Enter to continue..." << endl;
        cin.ignore();
        cin.get();
    }

    void viewWeightCategories() const
    {
        cout << "Categories\tUpper weight limit (kg)" << endl;
        cout << "Heavyweight\tUnlimited (over 100)" << endl;
        cout << "Light Heavyweight\t100" << endl;
        cout << "Middleweight\t90" << endl;
        cout << "Light Middleweight\t81" << endl;
        cout << "Lightweight\t73" << endl;
        cout << "Flyweight\t66" << endl;
        cin.get();
    }
};

class Guest
{
public:
    void viewTrainingPlans(const TrainingCenter &center) const
    {
        center.viewTrainingPlans();
    }

    void viewWeightCategories(const TrainingCenter &center) const
    {
        center.viewWeightCategories();
    }
};

class TrainingSystem
{
private:
    TrainingCenter centers[MAX_CENTERS];
    Customer customers[MAX_CUSTOMERS];
    int numCenters;

public:
    TrainingSystem() : numCenters(0)
    {
        centers[numCenters].name = "Center 1";
        centers[numCenters].address = "Address 1";

        TrainingPlan defaultPlans1[] = {
            TrainingPlan("Beginner", "Mon-Wed-Fri 9:00-10:00"),
            TrainingPlan("Intermediate", "Tue-Thu 18:00-19:30"),
            TrainingPlan("Elite", "Mon-Fri 16:00-18:00")};

        for (int i = 0; i < sizeof(defaultPlans1) / sizeof(defaultPlans1[0]); ++i)
        {
            centers[numCenters].addPlan(defaultPlans1[i]);
        }

        centers[numCenters].setPlanCosts(50, 75, 100, 120, 20);
        numCenters++;
    }

    void start()
    {
        int userType;
        Admin admin;
        Customer customer;
        Guest guest;

        do
        {
            system("clear");
            cout << "Enter your user type (1 for admin, 2 for customer, 3 for guest, 0 to exit): ";
            cin >> userType;

            switch (userType)
            {
            case 1:
                adminOperations(admin);
                break;
            case 2:
                customerOperations(customer);
                break;
            case 3:
                guestOperations(guest);
                break;
            case 0:
                cout << "Exiting the training system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid user type. Please try again." << endl;
            }
        } while (userType != 0);
    }

    void adminOperations(Admin &admin)
    {
        int adminChoice;
        do
        {
            system("clear");
            cout << "Admin Menu" << endl;
            cout << "1. Add Training Center" << endl;
            cout << "2. View All Training Centers" << endl;
            cout << "3. Update Training Center" << endl;
            cout << "4. View Enrolled Athletes" << endl;
            cout << "5. Delete Enrolled Athlete" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> adminChoice;

            switch (adminChoice)
            {
            case 1:
                admin.insertTrainingCenter(centers, numCenters);
                break;
            case 2:
                admin.viewAllTrainingCenters(centers, numCenters);
                break;
            case 3:
                admin.updateTrainingCenter(centers, numCenters);
                break;
            case 4:
                admin.viewEnrolledAthletes(centers, numCenters);
                break;
            case 5:
                admin.deleteEnrolledAthlete(centers, numCenters);
                break;
            case 6:
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (adminChoice != 6);
    }

    void customerOperations(Customer &customer)
    {
        if (numCenters == 0)
        {
            cout << "No training centers available. Please contact the administrator." << endl;
            return;
        }

        cout << "Available Training Centers:" << endl;
        for (int i = 0; i < numCenters; ++i)
        {
            cout << i + 1 << ". " << centers[i].name << endl;
        }

        int centerChoice;
        cout << "Select a training center (1-" << numCenters << "): ";
        cin >> centerChoice;

        if (centerChoice >= 1 && centerChoice <= numCenters)
        {
            TrainingCenter &selectedCenter = centers[centerChoice - 1];

            char enrollAnother;
            do
            {
                selectedCenter.viewTrainingPlans();

                cout << "Do you want to enroll a new athlete or delete an existing athlete?" << endl;
                cout << "1. Enroll a new athlete" << endl;
                cout << "2. Delete an existing athlete" << endl;
                cout << "Enter your choice: ";

                int choice;
                cin >> choice;

                if (choice == 1)
                {
                    cin.ignore();
                    cout << "Enter athlete's name: ";
                    string athleteName;
                    getline(cin, athleteName);
                    customer.setCustomerName(athleteName);

                    int plan_choice;
                    cout << "Choose a plan (1 for Beginner, 2 for Intermediate, 3 for Elite): ";
                    cin >> plan_choice;
                    customer.choosePlan(selectedCenter, plan_choice);

                    selectedCenter.enrolledAthletes[selectedCenter.numEnrolledAthletes++] = customer.name;

                    combSort(selectedCenter.enrolledAthletes, selectedCenter.numEnrolledAthletes);
                }
                else if (choice == 2)
                {
                    selectedCenter.deleteEnrolledAthlete();
                }
                else
                {
                    cout << "Invalid choice. Please try again." << endl;
                }

                cout << "Do you want to enroll/delete another athlete? (y/n): ";
                cin >> enrollAnother;

            } while (enrollAnother == 'y' || enrollAnother == 'Y');
        }
        else
        {
            cout << "Invalid center choice. Please try again." << endl;
        }
    }

    void guestOperations(Guest &guest)
    {
        int centerChoice;
        cout << "Select a training center (1-" << MAX_CENTERS << "): ";
        cin >> centerChoice;

        if (centerChoice >= 1 && centerChoice <= MAX_CENTERS)
        {
            TrainingCenter &selectedCenter = centers[centerChoice - 1];

            int guestChoice;
            do
            {
                cout << "Guest Menu" << endl;
                cout << "1. View Training Plans" << endl;
                cout << "2. View Weight Categories" << endl;
                cout << "3. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> guestChoice;

                switch (guestChoice)
                {
                case 1:
                    guest.viewTrainingPlans(selectedCenter);
                    break;
                case 2:
                    guest.viewWeightCategories(selectedCenter);
                    break;
                case 3:
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            } while (guestChoice != 3);
        }
        else
        {
            cout << "Invalid center choice. Please try again." << endl;
        }
    }
};

int main()
{
    TrainingSystem system;

    system.start();

    return 0;
}

void combSortTrainingCenters(TrainingCenter centers[], int numCenters)
{
    int gap = numCenters;
    bool swapped = true;

    while (gap > 1 || swapped)
    {
        if (gap > 1)
        {
            gap = static_cast<int>(gap / 1.3);
        }

        swapped = false;

        for (int i = 0; i + gap < numCenters; ++i)
        {
            if (centers[i].name > centers[i + gap].name)
            {
                swap(centers[i], centers[i + gap]);
                swapped = true;
            }
        }
    }
}

void combSort(string arr[], int n)
{
    int gap = n;
    bool swapped = true;

    while (gap > 1 || swapped)
    {
        if (gap > 1)
        {
            gap = static_cast<int>(gap / 1.3);
        }

        swapped = false;

        for (int i = 0; i + gap < n; ++i)
        {
            if (arr[i] > arr[i + gap])
            {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}
