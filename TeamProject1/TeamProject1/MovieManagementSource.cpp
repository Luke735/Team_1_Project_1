#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include <iterator>
#include <vector>
#include "Movie.h"
using namespace std;

int main() {

    ifstream fin("movie.txt");

    if (!fin.is_open()) {
        cout << "Could not open file" << endl;
    }
    else {
        ofstream fout;
        fout.open("results_1.txt");
        //Declare our two lists for coming and showing
        list<Movie> comingList, showingList;
        //these strings are filled with each variable read from the input file
        vector<string> names, release_dates, receive_dates, descriptions, statuses;
        string line;
        while (getline(fin, line)) { //Gets each line from the input file
            //Initialize variables needed to get input
            string name = "", release_date = "", description = "", receive_date = "", status = "";
            int count = 0, breaker = 0;
            //Now, iterate over the line that we got
            for (count; count < line.size(); count++) {
                char current;
                current = line.at(count);
                //the input file is comma separated, so when a comma is encountered, increment breaker, which causes the 
                //following reads to be stored into the next variable
                if (current == ',') {
                    ++breaker;
                    continue;
                }
                if (breaker == 0) {
                    name.push_back(current);
                }
                if (breaker == 1 && current != ' ') {
                    release_date.push_back(current);
                }
                if (breaker == 2 && current != ' ') {
                    description.push_back(current);
                }
                if (breaker == 3 && current != ' ') {
                    receive_date.push_back(current);
                }
                if (breaker == 4 && current != ' ') {
                    status.push_back(current);
                }
            }
            names.push_back(name);
            release_dates.push_back(release_date);
            receive_dates.push_back(receive_date);
            descriptions.push_back(description);
            statuses.push_back(status);

            //new Date objects must be created from the file input, the Date objects have day, month, and year variables
            Date newReceiveDate = Date();
            newReceiveDate.set_day(stoi(receive_date.substr(0, 3)));
            newReceiveDate.set_month(stoi(receive_date.substr(3, 6)));
            newReceiveDate.set_year(stoi(receive_date.substr(6)));

            Date newReleaseDate = Date();
            newReleaseDate.set_day(stoi(release_date.substr(0, 3)));
            newReleaseDate.set_month(stoi(release_date.substr(3, 6)));
            newReleaseDate.set_year(stoi(release_date.substr(6)));

            //the input file contains 1 for showing and 0 for coming, so translate that into boolean values
            bool statuss = false;
            if (status == "1") { statuss = true; }
            //creates a the new movie object using all the variables read from input
            Movie newMovie = Movie(name, newReleaseDate, description, newReceiveDate, statuss);

            //If the statuss is true, we can push back the movie into the showing list
            if (statuss == true) {
                list<Movie>::iterator it;
                if (showingList.size() > 0) {
                    int count = 0;
                    for (it = showingList.begin(); it != showingList.end(); it++) {
                        ++count;
                        if (newMovie <= *it) { //If the new movies release date is less than the movie at iterators position
                            showingList.insert(it, newMovie); //Then we can insert the movie at iterators position
                            break;
                        }
                    }
                    if (count == showingList.size() && showingList.size() != 0) {
                        showingList.push_back(newMovie); //If we reach the end and no movie has a greater release date, then we push to back
                        //continue;
                    }
                }
                else { showingList.push_back(newMovie); } //If no movies in list, push back
            }
            //If the statuss is false, we can push back the movie into the coming list
            if (statuss == false) {
                list<Movie>::iterator it;
                if (comingList.size() > 0) {
                    int count = 0;
                    for (it = comingList.begin(); it != comingList.end(); it++) {
                        ++count;
                        if (newMovie <= *it) { //If the new movies release date is less than the movie at iterators position
                            comingList.insert(it, newMovie); //Then we can insert the movie at iterators position
                            break;
                        }
                    }
                    if (count == comingList.size() && comingList.size() != 0) {
                        comingList.push_back(newMovie); //If we reach the end and no movie has a greater release date, then we push to back
                        //continue;
                    }
                }
                else { comingList.push_back(newMovie); } //If no movies in list, push back
            }
        }

        string option = "e";
        //the menu is in a while loop until the option selected is q
        //the menu only reads the first character of the input as the option
        while (option.at(0) != 'q') {
            cout << "MENU" << endl;
            cout << "a - Display movies" << endl;
            cout << "b - Add movies" << endl;
            cout << "c - Edit release dates" << endl;
            cout << "d - Edit movie description" << endl;
            cout << "e - Start showing movies in the theatre" << endl;
            cout << "f - Number of movies before a date" << endl;
            cout << "s - Save" << endl;
            cout << "q - Quit" << endl;
            cout << endl;
            cout << "Choose an option: " << endl;
            cin >> option;

            //Display Movies: uses iterators to output comingList and showingList
            if (option.at(0) == 'a') {
                cout << "Coming list:" << endl;
                list<Movie>::iterator it;
                for (it = comingList.begin(); it != comingList.end(); ++it) {

                    cout << *it << endl;
                }
                cout << endl << "Showing list:" << endl;
                list<Movie>::iterator it2;
                for (it2 = showingList.begin(); it2 != showingList.end(); ++it2) {
                    cout << *it2 << endl;
                }
            }
            //Add movie: adds a movie with by prompting the user for each property of a Movie object. Movie is added to the coming list.
            //Also, each time a << is used to read user input, a newline character is left in the input buffer. When getline() is called
            //after this, it only takes the newline character and appears to have done nothing. cin.ignore() must be used (confusing error) (thanks c++)
            if (option.at(0) == 'b') {
                string newName, newDescription;
                Date newReceiveDate = Date();
                Date newReleaseDate = Date();
                string dateInput = "-1";

                cout << "Enter the movie's name" << endl;
                cin.ignore();
                getline(cin, newName);
                
                //prompt user for both dates until receive date is before the release date
                while (newReleaseDate <= newReceiveDate) {
                    //prompt user until input is between 1 and 31
                    while (stoi(dateInput.substr(0, 2)) <= 0 || stoi(dateInput.substr(0, 2)) > 31) {
                        cout << "Enter the movie's release date day" << endl;
                        cin >> dateInput;
                    }
                    newReleaseDate.set_day(stoi(dateInput.substr(0, 2)));
                    dateInput = "-1";
                    //prompt user until input is between 1 and 12
                    while (stoi(dateInput.substr(0, 2)) <= 0 || stoi(dateInput.substr(0, 2)) > 12) {
                        cout << "Enter the movie's release date month" << endl;
                        cin >> dateInput;
                    }
                    newReleaseDate.set_month(stoi(dateInput.substr(0, 2)));
                    dateInput = "-1";
                    //prompt user until input is a positive 4 digit number
                    while (stoi(dateInput.substr(0, 4)) <= 1000) {
                        cout << "Enter the movie's release date year" << endl;
                        cin >> dateInput;
                    }
                    newReleaseDate.set_year(stoi(dateInput.substr(0, 4)));
                    dateInput = "-1";

                    cout << "Enter the movie's description" << endl;
                    cin.ignore();
                    getline(cin, newDescription);

                    //prompt user until input is between 1 and 31
                    while (stoi(dateInput.substr(0, 2)) <= 0 || stoi(dateInput.substr(0, 2)) > 31) {
                        cout << "Enter the movie's receive date day" << endl;
                        cin >> dateInput;
                    }
                    newReceiveDate.set_day(stoi(dateInput.substr(0, 2)));
                    dateInput = "-1";
                    //prompt user until input is between 1 and 12
                    while (stoi(dateInput.substr(0, 2)) <= 0 || stoi(dateInput.substr(0, 2)) > 12) {
                        cout << "Enter the movie's receive date month" << endl;
                        cin >> dateInput;
                    }
                    newReceiveDate.set_month(stoi(dateInput.substr(0, 2)));
                    dateInput = "-1";
                    //prompt user until input is a positive 4 digit number
                    while (stoi(dateInput.substr(0, 4)) <= 1000) {
                        cout << "Enter the movie's receive date year" << endl;
                        cin >> dateInput;
                    }
                    newReceiveDate.set_year(stoi(dateInput.substr(0, 4)));
                    dateInput = "-1";

                    if (newReleaseDate <= newReceiveDate) { cout << "Movie must be received before it can be released! Try again" << endl; }
                }
                
                Movie newMovie = Movie(newName, newReleaseDate, newDescription, newReceiveDate, false);
                list<Movie>::iterator it;
                if (comingList.size() > 0) {
                    int count = 0;
                    for (it = comingList.begin(); it != comingList.end(); it++) {
                        ++count;
                        if (newMovie <= *it) { //If the new movies release date is less than the movie at iterators position
                            comingList.insert(it, newMovie); //Then we can insert the movie at iterators position
                            break;
                        }
                    }
                    if (count == comingList.size() && comingList.size() != 0) {
                        comingList.push_back(newMovie); //If we reach the end and no movie has a greater release date, then we push to back
                        //continue;
                    }
                }
                else { comingList.push_back(newMovie); } //If no movies in list, push back
            }
            // Find the movie and update movie's the releases date from cominglist.
            if (option.at(0) == 'c') {
                string moviename;
                cout << "Enter the name of the movie to edit the release date: ";
                cin.ignore();
                getline(cin, moviename);

                bool movieExist = false;
                list<Movie>::iterator it;
                Date editReleaseDate = Date();

                for (it = comingList.begin(); it != comingList.end(); ++it) {
                    if (it->get_name() == moviename) {
                        movieExist = true; // Checking movie exists or not. If it exists, returns true and update. Otherwise, print out "movie does not exist".

                        string newDateInput;
                        cout << "Enter the new release date's day: " << endl;
                        cin >> newDateInput;
                        editReleaseDate.set_day(stoi(newDateInput.substr(0, 2)));
                        cout << "Enter the new release date's month: " << endl;
                        cin >> newDateInput;
                        editReleaseDate.set_month(stoi(newDateInput.substr(0, 2)));
                        cout << "Enter the new release date's year" << endl;
                        cin >> newDateInput;
                        editReleaseDate.set_year(stoi(newDateInput.substr(0, 4)));

                        string names = moviename;
                        string description = it->get_description();
                        Date receive_date = it->get_recieve_date();
                        bool status_ = 0;


                        it->set_release_date(editReleaseDate.get_day(), editReleaseDate.get_month(), editReleaseDate.get_year());
                        cout << "Updated the release date completely." << endl << endl;

                        Movie editMovie = Movie(moviename, editReleaseDate, description, receive_date, status_);
                        //comingList.push_back(editMovie);
                        cout << editMovie << endl; // Checking whether I put right information.
                        break;
                    }
                }
                if (!movieExist) {
                    cout << "Movie does not exist." << endl;
                }

            }
            // Find the movie and update movie's the description from cominglist.
            if (option.at(0) == 'd') {
                string moviename;
                cout << "Enter the name of the movie to edit the description: ";
                cin.ignore();
                getline(cin, moviename);

                bool movieExist = false;
                string newDescription;
                list<Movie>::iterator it;
                Date editReleaseDate = Date();

                for (it = comingList.begin(); it != comingList.end(); ++it) {
                    if (it->get_name() == moviename) {
                        movieExist = true; // true
                        cout << "Enter the new description for the movie: ";
                        getline(cin, newDescription);

                        it->set_description(newDescription);

                        string names = it->get_name();
                        Date release_date = it->get_release_date();
                        Date receive_date = it->get_recieve_date();
                        bool status_ = 0;

                        cout << "Updated the description completely." << endl << endl;

                        Movie editDesMovie = Movie(names, release_date, newDescription, receive_date, status_);
                        cout << editDesMovie << endl; // Checking.
                        break;
                    }
                }
                if (!movieExist) {
                    cout << "Movie does not exist." << endl;
                }
            }
            //Start showing movies in the theatre: starts showing all movies with the specified release date, creates a new Date object and
            //sets it's day, month, and year variables with user input, then uses Date()'s == operator to compare it with each iterator position.
            //if they match, add the movie to the showingList and remove it from the coming list.
            if (option.at(0) == 'e') {
                Date newReleaseDate = Date();
                string newDateInput;
                cout << "Enter the day of the release date of the movies to start showing: " << endl;
                cin >> newDateInput;
                newReleaseDate.set_day(stoi(newDateInput.substr(0, 2)));

                cout << "Enter the month of the release date of the movies to start showing: " << endl;
                cin >> newDateInput;
                newReleaseDate.set_month(stoi(newDateInput.substr(0, 2)));

                cout << "Enter the year of the release date of the movies to start showing: " << endl;
                cin >> newDateInput;
                newReleaseDate.set_year(stoi(newDateInput.substr(0, 4)));

                list<Movie>::iterator it;
                for (it = comingList.begin(); it != comingList.end(); it++) {
                    if (it->get_release_date() == newReleaseDate) {
                        cout << "Moved " << it->get_name() << " to showing list" << endl;
                        showingList.push_back(*it);
                        it = comingList.erase(it);
                    }
                }
                cout << "Complete!" << endl;
            }
            //Outputs all movies in coming list before a specified date, 
            if (option.at(0) == 'f') {

                //Declare variables needed to count movies before a certain date
                string day, month, year;
                Date ReleaseDate = Date();

                cout << "Enter the movie's release date day" << endl;
                cin >> day;
                ReleaseDate.set_day(stoi(day));
                cout << "Enter the movie's release date month" << endl;
                cin >> month;
                ReleaseDate.set_month(stoi(month));
                cout << "Enter the movie's release date year" << endl;
                cin >> year;
                ReleaseDate.set_year(stoi(year));

                if (ReleaseDate.isValid()) { //Check if the date entered is valid

                    Date rec = Date();
                    Movie movie("", ReleaseDate, "", rec, false); //Make a dummy movie to compare release date

                    int countt = 0;
                    list<Movie>::iterator it;
                    for (it = comingList.begin(); it != comingList.end(); it++) { //Iterate over the coming list
                        if (comingList.size() == 0) { countt = 0; }
                        else if (movie <= *it) {
                            countt++; //For every movie that has a release date less than the date entered, increment count
                        }
                    }
                    cout << "The number of movies before the specified release date in the coming list is: " << countt << endl; //Output the count
                }
                else { cout << "Error, invalid date" << endl; } //If invalid date, display error message
            }
            ////Outputs both coming and showing movies to the output file
            if (option.at(0) == 's') {
                list<Movie>::iterator it;
                for (it = showingList.begin(); it != showingList.end(); ++it) {
                    fout << *it << endl;
                }
                for (it = comingList.begin(); it != comingList.end(); ++it) {
                    fout << *it << endl;
                }
            }
        }//end while loop
        fin.close();
        fout.close();
    }
    return 0;
}
