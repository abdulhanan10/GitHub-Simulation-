//Driver File | Main Function 
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<windows.h>
#include"Commit.h"
#include"File.h"
#include"Repository.h"
#include"User.h"
#include"Hash.h"
#include"AVL.h"
#include"Graph.h"
#include"GitHub.h"
using namespace std;

//function for colored text
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main()
{
    GitHub github;
    string username, password, followerUsername, repoName, fileName, commitHash, message, targetUsername;
    int choice, userChoice;
    bool isPrivateOrPublic;

    //cyan color 
    setColor(11);
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t" << endl;
    
    //green color 
    setColor(10); 
    cout << "\t\t\t\t\t|          WELCOME           |" << endl;
    cout << "\t\t\t\t\t|            TO              |" << endl;
    
    //red color 
    setColor(12); 
    cout << "\t\t\t\t\t|          GITHUB            |" << endl;
    cout << "\t\t\t\t\t|        APPLICATION         | " << endl;
    
    //cyan color
    setColor(11);
    cout << "\t\t\t\t\t" << endl;
    
    //a delay in execution for two seconds (i.e. 1000 = 1 second)
    Sleep(2000); 
    system("cls");


    do 
    {
        cout << "\n\n\t\t\t\t\tTo Continue to the Application...\n" << endl;
        
        //yellow color 
        setColor(14);
        cout << "\t\t\t\t\t1. Register" << endl;
        cout << "\t\t\t\t\t2. Login" << endl;
        
        //red color
        setColor(12);
        cout << "\t\t\t\t\t3. Exit\n" << endl;
        
        //white color 
        setColor(15); 
        cout << "\t\t\Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\t\tEnter Username: ";
            cin >> username;
            cout << "\t\tEnter Password: ";
            cin >> password;
            github.registerUser(username, password);
            cout << "\n\t\t\t\t\t| --- Registration Successful! --- |" << endl;
            Sleep(2000); 
            break;
        case 2:
            setColor(15);
            cout << "\t\tEnter Username: ";
            cin >> username;
            cout << "\t\tEnter Password: ";
            cin >> password;
            if (github.login(username, password))
            {
                system("cls");
                setColor(14);
                cout << "\n\t\t\t\t\t| --- Login Successful! --- |" << endl;
                Sleep(1000); 
                User* currentUser = github.getUser(username);
                do
                {
                    cout << "\n\t\t\tUser Menu:" << endl;
                    cout << "\t1. Create Repository" << endl;
                    cout << "\t2. Delete Repository" << endl;
                    cout << "\t3. Fork Repository" << endl;
                    cout << "\t4. Display Profile" << endl;
                    cout << "\t5. Display Repository" << endl;
                    cout << "\t6. Add File to Repository" << endl;
                    cout << "\t7. Delete File from Repository" << endl;
                    cout << "\t8. Add Commit to Repository" << endl;
                    cout << "\t9. Delete Commit from Repository" << endl;
                    cout << "\t10. Follow User" << endl;
                    cout << "\t11. Unfollow User" << endl;
                    cout << "\t12. Logout" << endl << endl;
                    cout << "Enter your choice: ";
                    cin >> userChoice;

                    switch (userChoice)
                    {
                    case 1:
                        cout << "\nEnter the Repository Name: ";
                        cin >> repoName;
                        cout << "Do you want to make your repository private or public? (Press 1 for private and " 
                            "0 for public): ";
                        cin >> isPrivateOrPublic;
                        currentUser->createRepository(repoName, isPrivateOrPublic);
                        
                        //csv file will be updated after the input of the repository 
                        github.writeCSV();  
                        break;
                    case 2:
                        cout << "\nEnter the Repository Name to Delete: ";
                        cin >> repoName;
                        currentUser->deleteRepository(repoName);
                        
                        //csv file will be updated after the deletion of the repository 
                        github.writeCSV();  
                        break;
                    case 3:
                        cout << "\nEnter the Username of the User whose Repository you want to Fork: ";
                        cin >> targetUsername;
                        cout << "Enter the Repository Name to Fork: ";
                        cin >> repoName;
                        github.forkRepository(username, targetUsername, repoName);
                        github.writeCSV();  
                        break;
                    case 4:
                        cout << "\nEnter the Username to View Profile: ";
                        cin >> username;
                        if (User* user = github.getUser(username))
                        {
                            cout << "\t\t\t| --- Profile: "<< username << ", Loading... --- | " << endl;
                            cout << endl;
                            user->viewProfile();
                        }
                        else
                        {
                            cout << "\t\t\t| --- User: " << username << ", Not Found! --- | " << endl;
                        }
                        break;
                    case 5:
                        cout << "\nEnter the Repository Name: ";
                        cin >> repoName;
                        if (Repository* repo = currentUser->getRepository(repoName))
                        {
                            cout << "\t\t\t| --- " << repoName << ", Status Loading... --- |" << endl;
                            cout << endl;

                            repo->viewStatus();
                        }
                        else
                        {
                            cout << "\n\t\t\t| --- Repository: " << repoName << ", Not Found! Or is Private. --- | " << endl;
                        }
                        break;
                    case 6:
                        cout << "\nEnter the Repository Name to Add File: ";
                        cin >> repoName;
                        cout << "Enter the File Name: ";
                        cin >> fileName;
                        if (Repository* repo = currentUser->getRepository(repoName))
                        {
                            repo->addFile(fileName);
                            cout << "\t\t\t| --- File: " << fileName << " Added Successfully!-- - | " << endl;
                            cout << endl;
                        }
                        else
                        {
                            cout << "\t\t\t| --- Repository: " << repoName << ", Not Found! --- |" << endl;
                        }
                        break;
                    case 7:
                        cout << "\nEnter the Repository Name: ";
                        cin >> repoName;
                        cout << "Enter the File Name to delete: ";
                        cin >> fileName;
                        if (Repository* repo = currentUser->getRepository(repoName))
                        {
                            repo->deleteFile(fileName);
                            cout << "\t\t\t| --- File: " << fileName << ", Deleted Successfully!--- |" << endl;
                            cout << endl;
                        }
                        else
                        {
                            cout << "\t\t\t| --- Repository: " << repoName << ", Not Found! --- |" << endl;
                        }
                        break;
                    case 8:
                        cout << "\nEnter the Repository Name: ";
                        cin >> repoName;
                        cout << "Enter the Commit Hash: ";
                        cin >> commitHash;
                        cout << "Enter the Commit Message: ";
                        cin.ignore();
                        getline(cin, message);
                        if (Repository* repo = currentUser->getRepository(repoName))
                        {
                            repo->addCommit(commitHash, message);
                            cout << "\t\t\t| --- Commit Added Successfully! --- |" << endl;
                            cout << endl;
                        }
                        else
                        {
                            cout << "\t\t\t| --- Repository: " << repoName << ", Not Found! --- |" << endl;
                        }
                        break;
                    case 9:
                        cout << "\nEnter the Repository Name: ";
                        cin >> repoName;
                        cout << "Enter the Commit Hash to Delete: ";
                        cin >> commitHash;
                        if (Repository* repo = currentUser->getRepository(repoName))
                        {
                            repo->deleteCommit(commitHash);
                            cout << "\t\t\t| --- Commit Deleted Successfully! --- |" << endl;
                            cout << endl;
                        }
                        else
                        {
                            cout << "\t\t\t| --- Repository: " << repoName << ", Not Found! --- |" << endl;
                        }
                        break;
                    case 10:
                        cout << "\nEnter the Username which you want to Follow: ";
                        cin >> followerUsername;
                        if (User* follower = github.getUser(followerUsername))
                        {
                            currentUser->addFollower(follower);
                            cout << "\t\t\t| --- Congratulations! You have followed " << followerUsername << " --- |" << endl;
                        }
                        else
                        {
                            cout << "\t\t\t| --- User: " << followerUsername << ", Not found!--- |" << endl;
                        }
                        break;
                    case 11:

                        cout << "\nEnter the Username to Unfollow: ";
                        cin >> followerUsername;
                        if (User* follower = github.getUser(followerUsername))
                        {
                            currentUser->removeFollower(follower);
                            cout << "\t\t\t| --- You have unfollowed " << followerUsername << " --- |" << endl;
                        }
                        else
                        {
                            cout << "\t\t\t| --- User: " << followerUsername << ", Not found!--- |" << endl;
                        }
                        break;

                    case 12:
                        cout << "\n\t\t\t\t\t| --- Logging Out... --- |" << endl;
                        system("cls");
                        break;
                    default:
                        cout << "\t\t\t\t\t| --- Invalid Choice! Please try again. --- |" << endl;
                        break;
                    }
                } while (userChoice != 12);
            }
            else
            {
                setColor(12);
                cout << "\n\t\t\t\t\t| --- Invalid Username or Password! Please try again. --- |" << endl;
                Sleep(1000); 
            }
            break;
        case 3:
            setColor(12);
            cout << "\t\t\t\t\t| --- Exiting program... --- |" << endl;
            exit(0);
            break;
        default:
            setColor(12);
            cout << "\t\t\t\t\t| --- Invalid Choice! Please try again. --- |" << endl;
            Sleep(2000); 
            break;
        }
        system("cls");
    } while (choice != 3);
    cout << endl;

    return 0;
}