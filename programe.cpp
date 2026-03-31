#include <iostream>
#include <string>
using namespace std;

class Event
{
private:
    int eventID;
    string eventName;
    string organizer;
    int participants;

public:
    Event()
    {
        eventID = 0;
        eventName = "None";
        organizer = "None";
        participants = 0;
    }

    Event(int id, string name, string org, int p)
    {
        eventID = id;
        eventName = name;
        organizer = org;
        participants = p;
    }

    Event(const Event &e)
    {
        eventID = e.eventID;
        eventName = e.eventName;
        organizer = e.organizer;
        participants = e.participants;
    }

    ~Event()
    {
    }

    void setData()
    {
        cout << "Enter Event ID: ";
        cin >> eventID;

        cout << "Enter Event Name: ";
        cin >> eventName;

        cout << "Enter Organizer Name: ";
        cin >> organizer;

        cout << "Enter Number of Participants: ";
        cin >> participants;
    }

    void display()
    {
        cout << "\nEvent ID: " << eventID << endl;
        cout << "Event Name: " << eventName << endl;
        cout << "Organizer: " << organizer << endl;
        cout << "Participants: " << participants << endl;
    }

    int getEventID()
    {
        return eventID;
    }
};

class EventManager
{
private:
    Event *events;
    int count;

public:
    EventManager()
    {
        events = new Event[100];
        count = 0;
    }

    ~EventManager()
    {
        delete[] events;
    }

    void addEvent()
    {
        events[count].setData();
        count++;
        cout << "Event Added Successfully!\n";
    }

    void showEvents()
    {
        if (count == 0)
        {
            cout << "No Events Found\n";
            return;
        }

        for (int i = 0; i < count; i++)
        {
            events[i].display();
        }
    }

    void searchEvent()
    {
        int id;
        cout << "Enter Event ID to search: ";
        cin >> id;

        for (int i = 0; i < count; i++)
        {
            if (events[i].getEventID() == id)
            {
                cout << "\nEvent Found:\n";
                events[i].display();
                return;
            }
        }

        cout << "Event Not Found\n";
    }

    void deleteEvent()
    {
        int id;
        cout << "Enter Event ID to delete: ";
        cin >> id;

        for (int i = 0; i < count; i++)
        {
            if (events[i].getEventID() == id)
            {
                for (int j = i; j < count - 1; j++)
                {
                    events[j] = events[j + 1];
                }

                count--;
                cout << "Event Deleted Successfully\n";
                return;
            }
        }

        cout << "Event Not Found\n";
    }
};

int main()
{
    EventManager manager;
    int choice;

    while (true)
    {
        cout << "\n========== EVENT MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Event\n";
        cout << "2. Show All Events\n";
        cout << "3. Search Event\n";
        cout << "4. Delete Event\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            manager.addEvent();
            break;

        case 2:
            manager.showEvents();
            break;

        case 3:
            manager.searchEvent();
            break;

        case 4:
            manager.deleteEvent();
            break;

        case 5:
            cout << "Exiting Program...\n";
            return 0;

        default:
            cout << "Invalid Choice\n";
        }
    }
}