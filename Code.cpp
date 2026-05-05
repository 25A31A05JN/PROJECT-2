#include <iostream>
#include <queue>
#include <string>

using namespace std;

// Display vehicles in a lane
void displayLane(queue<string> lane, string laneName)
{
    cout << laneName << " : ";

    if (lane.empty())
    {
        cout << "Empty";
    }

    while (!lane.empty())
    {
        cout << lane.front() << " ";
        lane.pop();
    }

    cout << endl;
}

// Check ambulance presence
bool hasAmbulance(queue<string> lane)
{
    while (!lane.empty())
    {
        if (lane.front() == "Ambulance")
        {
            return true;
        }

        lane.pop();
    }

    return false;
}

// Move ambulance to front
queue<string> prioritizeAmbulance(queue<string> lane)
{
    queue<string> temp;
    bool found = false;

    while (!lane.empty())
    {
        if (lane.front() == "Ambulance")
        {
            found = true;
        }
        else
        {
            temp.push(lane.front());
        }

        lane.pop();
    }

    queue<string> updatedLane;

    if (found)
    {
        updatedLane.push("Ambulance");
    }

    while (!temp.empty())
    {
        updatedLane.push(temp.front());
        temp.pop();
    }

    return updatedLane;
}

int main()
{
    queue<string> lane1, lane2, lane3;

    int cycle = 0;
    int maxCycles = 10;

    // Add vehicles
    lane1.push("Car");
    lane1.push("Bike");
    lane1.push("Ambulance");
    lane1.push("Bus");

    lane2.push("Truck");
    lane2.push("Car");

    lane3.push("Bike");
    lane3.push("Bus");
    lane3.push("Car");

    while (cycle < maxCycles)
    {
        cout << "\n===== CYCLE "
             << cycle + 1
             << " =====\n";

        // Ambulance priority
        lane1 = prioritizeAmbulance(lane1);
        lane2 = prioritizeAmbulance(lane2);
        lane3 = prioritizeAmbulance(lane3);

        // Display lanes
        displayLane(lane1, "Lane1");
        displayLane(lane2, "Lane2");
        displayLane(lane3, "Lane3");

        int selectedLane = 0;

        // Check ambulance
        if (hasAmbulance(lane1))
        {
            selectedLane = 1;
        }
        else if (hasAmbulance(lane2))
        {
            selectedLane = 2;
        }
        else if (hasAmbulance(lane3))
        {
            selectedLane = 3;
        }
        else
        {
            int size1 = lane1.size();
            int size2 = lane2.size();
            int size3 = lane3.size();

            // Select largest lane
            if (size1 >= size2 && size1 >= size3)
            {
                selectedLane = 1;
            }
            else if (size2 >= size1 && size2 >= size3)
            {
                selectedLane = 2;
            }
            else
            {
                selectedLane = 3;
            }
        }

        // Move vehicle
        if (selectedLane == 1 && !lane1.empty())
        {
            cout << "\nGreen Signal -> Lane1\n";
            cout << lane1.front() << " Passed\n";
            lane1.pop();
        }
        else if (selectedLane == 2 && !lane2.empty())
        {
            cout << "\nGreen Signal -> Lane2\n";
            cout << lane2.front() << " Passed\n";
            lane2.pop();
        }
        else if (selectedLane == 3 && !lane3.empty())
        {
            cout << "\nGreen Signal -> Lane3\n";
            cout << lane3.front() << " Passed\n";
            lane3.pop();
        }

        // Stop condition
        if (lane1.empty() &&
            lane2.empty() &&
            lane3.empty())
        {
            cout << "\nAll lanes are empty.\n";
            break;
        }

        cycle++;
    }

    cout << "\n------ SYSTEM STOPPED ------\n";

    return 0;
}