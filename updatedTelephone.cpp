#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Node
{
  string phone;
  string email;
  string name;
  Node *next;
  Node *prev;
};

class phonebook
{
private:
  Node *head;
  Node *tail;
  ofstream fp;
  ifstream fp1;

public:
  phonebook()
  {
    head = NULL;
    tail = NULL;
  }
  void getDetails()
  {
    string name, phone, email;
    Node *x;

    cout << " Enter Name: ";
    cin >> name;
    cout << " Enter Phone Number: ";
    cin >> phone;
    while (phone.length() != 10)
    {
      cout << " Enter Valid Phone Number: ";
      cin >> phone;
    }

    if (verifyNumber(phone))
    {

      while (verifyNumber(phone))
      {

        cout << " Number already exists" << endl
             << endl;
        cout << " Enter Valid Phone Number: ";
        cin >> phone;
      }
    }
    cout << " Enter Email: ";
    cin >> email;

    cout << endl;

    Node *temp = new Node;
    temp->name = name;
    temp->phone = phone;
    temp->email = email;

    temp->next = NULL;
    temp->prev = NULL;

    if (head == NULL)
    {
      head = temp;
      tail = temp;
    }
    else
    {
      x = head;
      while (x->next != NULL)
      {
        x = x->next;
      }
      x->next = temp;
      temp->prev = x;
      tail = temp;
    }
    updateFiles();
  }
  /*LowerCase Function*/
  string toLowerCase(string str)
  {
    for (int i = 0; i < sizeof(str); i++)
    {
      str[i] = tolower(str[i]);
    }
    return str;
  }
  /*Convert Get Values from File*/

  void updateHeads()
  {
    string line, name, phone, email;
    fp1.open("ads.txt");
    while (fp1)
    {
      if (fp1)
      {

        getline(fp1, line);
        name = getValue(line);
        getline(fp1, line);
        phone = getValue(line);
        getline(fp1, line);
        email = getValue(line);
        getline(fp1, line);
        if (name != "" && email != "" && phone != "")
        {
          Node *temp = new Node;
          temp->name = name;
          temp->email = email;
          temp->phone = phone;
          temp->next = NULL;
          if (head == NULL)
          {
            head = temp;
            continue;
          }
          temp->next = head;
          head = temp;
        }
      }
    }
    fp1.close();
    if (head != NULL)
      sortContacts();
  }
  string getValue(string str)
  {
    int loc = str.find(":", 0);
    string result = str.substr(loc + 1);
    return result;
  }
  /*Newly Added File Function*/
  void updateFiles()
  {
    fp.open("ads.txt");
    Node *temp;
    temp = head;
    while (temp != NULL)
    {
      fp << "Name :" + temp->name << endl;
      fp << "Phone No :" + temp->phone << endl;
      fp << "Email :" + temp->email << endl;
      fp << endl;
      temp = temp->next;
    }
    fp.close();
  }
  void displayAll()
  {
    Node *x;
    if (head == NULL)
    {
      cout << " Phone Book is Empty" << endl
           << endl;
    }
    else
    {
      x = head;
      while (x != NULL)
      {
        cout << endl;
        cout << " Name: " << x->name << endl;
        cout << " Phone: +91-" << x->phone << endl;
        cout << " Email: " << x->email << endl
             << endl;
        x = x->next;
      }
    }
  }
  void display(Node *x)
  {
    cout << endl;
    cout << " Name: " << x->name << endl;
    cout << " Phone: +91-" << x->phone << endl;
    cout << " Email: " << x->email << endl
         << endl;
  }
  

  void deleteContact(string name)
  {
    int check = 0;
    Node *ptr = head;

    while (ptr != NULL)
    {
      if (name == ptr->name)
      {
        check = 1;
        break;
      }
      ptr = ptr->next;
    }

    if (check == 1 && ptr != head && ptr->next != NULL)
    {
      ptr->prev->next = ptr->next;
      ptr->next->prev = ptr->prev;

      delete ptr;
      updateFiles();
      cout << " Contact Deleted Successfully!" << endl
           << endl;
    }

    else if (check == 1 && ptr == head)
    {
      head = head->next;
      head->prev = NULL;

      delete ptr;
      updateFiles();
      cout << " Contact Deleted Successfully!" << endl
           << endl;
    }

    else if (check == 1 && ptr->next == NULL)
    {
      tail = ptr->prev;
      ptr->prev->next = NULL;
      ptr->prev = NULL;

      delete ptr;
      updateFiles();
      cout << " Contact Deleted Successfully!" << endl
           << endl;
    }

    else
    {
      cout << " Contact is not in the Phone Book" << endl
           << endl;
    }
  }
  void searchByName(string name)
  {
    Node *ptr = head;
    if (ptr == NULL)
    {
      cout << " Phone Book is Empty" << endl
           << endl;
      return;
    }
    while (ptr != NULL)
    {
      if (ptr->name == name)
      {
        display(ptr);
        return;
      }
      ptr = ptr->next;
    }
    cout << " Contact not Found!" << endl
         << endl;
  }
  void searchByPhone(string phone)
  {
    Node *ptr = head;
    if (ptr == NULL)
    {
      cout << " Phone Book is Empty" << endl
           << endl;
      return;
    }
    while (ptr != NULL)
    {
      if (ptr->phone == phone)
      {
        display(ptr);
        return;
      }
      ptr = ptr->next;
    }
    cout << " Contact not Found!" << endl
         << endl;
  }

  bool verifyNumber(string phone)
  {
    Node *ptr = head;
    
    while (ptr != NULL)
    {
      if (ptr->phone == phone)
      {

        return true;
      }
      ptr = ptr->next;
    }
    return false;
  }
  void searchByEmail(string email)
  {
    Node *ptr = head;
    if (ptr == NULL)
    {
      cout << " Phone Book is Empty" << endl
           << endl;
      return;
    }
    while (ptr != NULL)
    {
      if (ptr->email == email)
      {
        display(ptr);
        return;
      }
      ptr = ptr->next;
    }
    cout << " Contact not Found!" << endl
         << endl;
  }
  void insert()
  {
    getDetails();
  }
  void sortContacts()
  {
    Node *i, *j;
    string tempName, tempPhone, tempEmail, tempc, tempc2;

    for (i = head; i->next != NULL; i = i->next)
    {

      for (j = i->next; j != NULL; j = j->next)
      {

        tempc = toLowerCase(i->name);
        tempc2 = toLowerCase(j->name);
        if (tempc > tempc2)
        {

          tempName = i->name;
          tempPhone = i->phone;
          tempEmail = i->email;

          i->name = j->name;
          i->phone = j->phone;
          i->email = j->email;

          j->name = tempName;
          j->phone = tempPhone;
          j->email = tempEmail;
        }
      }
    }
    updateFiles();
  }
  void updateContact(string name)
  {
    string st;
    ifstream in("ads.txt");
    Node *x = head;
    int ch;
    bool i = true;
    string phone;

    while (x != NULL)
    {
      if (x->name == name)
      {
        while (i == true)
        {
          cout << endl;
          cout << " UPDATE CONTACT FOR " << x->name << endl;
          cout << " 1.UPDATE NAME" << endl;
          cout << " 2.UPDATE PHONE NUMBER" << endl;
          cout << " 3.UPDATE EMAIL" << endl;
          cout << " 4.DISPLAY CONTACT" << endl;
          cout << " 5.EXIT" << endl;
          cout << " ENTER YOUR CHOICE: ";
          cin >> ch;
          cout << endl;

          switch (ch)
          {
          case 1:
            cout << " Enter New Name: ";
            cin >> x->name;
            break;
          case 2:
            cout << " Enter New Phone: ";
            cin >> phone;
            while (phone.length() != 10)
            {
              cout << " Enter Valid Phone Number: ";
              cin >> phone;
            }
            x->phone = phone;
            break;
          case 3:
            cout << " Enter New Email: ";
            cin >> x->email;
            break;
          case 4:
            display(x);
            break;
          default:
            i = false;
            break;
          }
        }
        break;
      }
      x = x->next;
    }
    if (x == NULL)
    {
      cout << " Contact Not Found" << endl
           << endl;
    }

    else
    {
      updateFiles();
      cout << " Contact Updated Successfully!" << endl
           << endl;
    }
  }
};

int main()
{
  phonebook ph;
  // fstream file("ads.txt",ios::in | ios:: out | ios::app);
  int choice;
  string n;
  cout << "----------------------------" << endl;
  cout << " LOADING DATABASE......" << endl;
  cout << "----------------------------" << endl;
  ph.updateHeads();
  while (1)
  {

    cout << endl;
    cout << "----------------------------" << endl;
    cout << "         PHONE BOOK" << endl;
    cout << "----------------------------" << endl;
    cout << " 1.DISPLAY" << endl;
    cout << " 2.ADD NEW CONTACT" << endl;
    cout << " 3.UPDATE EXSITING CONTACT" << endl;
    cout << " 4.SEARCH BY NAME" << endl;
    cout << " 5.SEARCH BY PHONE NUMBER" << endl;
    cout << " 6.SEARCH BY EMAIL" << endl;
    cout << " 7.DELETE CONTACT" << endl;
    cout << " 8.EXIT" << endl;
    cout << "----------------------------" << endl;
    cout << " ENTER YOUR CHOICE: ";
    cin >> choice;
    cout << endl;

    switch (choice)
    {
    case 1:
      // ph.sortContacts();
      ph.displayAll();
      break;
    case 2:
      ph.insert();
      ph.sortContacts();
      break;
    case 3:
      cout << "Enter Contact Name to Update: ";
      cin >> n;
      ph.updateContact(n);
      ph.sortContacts();
      continue;
    case 4:
      cout << "Enter Name to Search: ";
      cin >> n;
      ph.searchByName(n);
      break;
    case 5:
      cout << "Enter Phone Number to Search: ";
      cin >> n;
      ph.searchByPhone(n);
      break;
    case 6:
      cout << "Enter Email to Search: ";
      cin >> n;
      ph.searchByEmail(n);
      break;
    case 7:
      cout << "Enter Contact Name to Delete: ";
      cin >> n;
      ph.deleteContact(n);
      break;
    default:
      exit(0);
    }
  }
  return 0;
}


// void deleteContact(string name)
  // {
  //   Node *ptr = head;
  //   bool flag = false;
  //   if (ptr->name == name)
  //   {
  //     display(ptr);
  //     head = head->next;
  //     cout << " Contact Deleted Successfully!" << endl;
  //     delete ptr;
  //     return;
  //   }
  //   while (ptr->next != NULL)
  //   {
  //     if (ptr->next->name == name)
  //     {
  //       flag = true;
  //       break;
  //     }
  //     ptr = ptr->next;
  //   }
  //   if (flag)
  //   {
  //     display(ptr->next);
  //     ptr->next = ptr->next->next;
  //     updateFiles();
  //   }
  //   else
  //   {
  //     cout << " Contact is not in the Phone Book" << endl
  //          << endl;
  //   }
  // }