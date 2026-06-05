#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Movie
{
    int movieID;
    string movieTitle;
    int movieRating;
    string movieGenre;
};

Movie* Movies = nullptr;

int globalmovieID = 100;
 
int movieCount = 0;

int ds_size = 5;

void initialize_movies(){
    Movies = new Movie[ds_size];
}

void resizeArray()
{
    ds_size = ds_size*2;
    Movie* tempArray = new Movie[ds_size];

    for (int i = 0; i < movieCount; i++)
    {
        tempArray[i] = Movies[i];
    }

    delete[] Movies;

    Movies = tempArray;
}

void addMovie(){

    if (movieCount == ds_size)
    {
        resizeArray();
    }

    Movie tempMovie;

    tempMovie.movieID = globalmovieID;
    cout << "Title: "; getline(cin,tempMovie.movieTitle);
    cout << "Rating: "; cin >> tempMovie.movieRating; cin.ignore();
    cout << "Genre: "; 
    getline(cin,tempMovie.movieGenre);
    Movies[movieCount] = tempMovie;
    movieCount++;
    globalmovieID++;
    cout << "New Movie Added." << endl;
}

void delMovie()
{
    int movieID;
    cout << "Enter Movie ID: "; cin >> movieID;

    int movieIndex = -1;
    for (int i=0; i < movieCount; i++){
        if (Movies[i].movieID == movieID){
            movieIndex = i;
        }
    }

    if (movieIndex == -1)
    {
        cout << "No movie found with this ID.";
        return;
    }
    else{
        for(int i = movieIndex; i < movieCount; i++ ){
            Movies[i] = Movies[i+1];
            movieCount--;
        }
        cout << "Movie Deleted.";
    }
}

void printMovie(int i){
    cout << "Movie ID: " << Movies[i].movieID << endl;
    cout << "Movie Title: " << Movies[i].movieTitle << endl;
    cout << "Movie Genre: " << Movies[i].movieGenre << endl;
    cout << "Movie Rating: " << Movies[i].movieRating << endl;
}

int searchMovie()
{   string movieTitle_1;
    cout << "Enter movie Title: "; cin >> movieTitle_1;
    bool found = false;

    for (int i = 0; i < movieCount; i++){
        if (Movies[i].movieTitle == movieTitle_1){
            printMovie(i);
            found = true;
            return i;
        }
        
    }
    if (!found){
        cout << "No such movie found.";
        return -1;
    }
}

void rateMovie(){
    //decouple code, use search instead
    int movieIndex = searchMovie();
    if (movieIndex == -1){
        return;
    }

    else{
        int newRating;
        cout << "Enter your new Rating (1-10)"; cin >> newRating;

        if (newRating <= 10 && newRating > 0){
            Movies[movieIndex].movieRating = newRating;
            cout << "Rating Updated!" << endl;
        }
        else{
            cout << "Invalid rating" << endl;
        }
    }
}

void find3max(){
    int top1,top2,top3 = -1;

    for (int i = 0; i < movieCount; i++){
        if (top1 == -1 || Movies[i].movieRating > Movies[top1].movieRating)
        {
            top3 = top2;
            top2 = top1;
            top1 = i;
        }
        else if (top2 == -1 || Movies[i].movieRating > Movies[top2].movieRating)
        {
            top3 = top2;
            top2 = i;
        }
        else if (top3 == -1 || Movies[i].movieRating > Movies[top3].movieRating)
        {
            top3 = i;
        }
    }

    cout << "Your Top Movies are: " << endl;

    if(top1 != -1){
        printMovie(top1);
    }

    if(top2 != -1){
        printMovie(top2);
    }

    if(top3 != -1){
        printMovie(top3);
    }
}

void showTopMovies(){
    find3max();
}

void genreMovie()
{
    string processedGenres[10];
    int processedCount = 0;

    for (int i = 0; i < movieCount; i++)
    {
        bool alreadyProcessed = false;

        // Check if genre has already been counted
        for (int j = 0; j < processedCount; j++)
        {
            if (Movies[i].movieGenre == processedGenres[j])
            {
                alreadyProcessed = true;
                break;
            }
        }

        if(!alreadyProcessed){
            int genreCount = 0;

            // Count movies of this genre
            for (int j = 0; j < movieCount; j++)
            {
                if (Movies[j].movieGenre == Movies[i].movieGenre)
                {
                genreCount++;
                }
            }

            cout << Movies[i].movieGenre << ": " << genreCount << " movies" << endl;

            processedGenres[processedCount] = Movies[i].movieGenre;
            processedCount++;
        }
    }
}

void allMovie()
{
    for(int i = 0; i < movieCount; i++){
        printMovie(i);
    }
}

void saveToFile()
{ 
    // check if size of array == 0, of no data, then notify user.

    if (movieCount == 0){
        cout << "Nothing to save to file";
    }

    else{
        ofstream fout("movies.txt"); // fout is created as a pointer that points to the dump of memory

        if (!fout){
            cout << "File could not get created";
            return;
        }
    // this all comes in else 
        else{ //enter no. of movies in this file
            for(int i = 0; i<movieCount; i++){
                fout << movieCount << endl;
                fout << Movies[i].movieID << endl;
                fout << Movies[i].movieTitle << endl;
                fout << Movies[i].movieGenre << endl;
                fout << Movies[i].movieRating << endl;
    }

    fout.close();
    cout << "Data saved successfully." << endl;
    }
    }

}

void loadFromFile()
{
    string file_name;
    // ask the file name from user
    cout << "Enter file name: ";
    getline(cin,file_name);

    ifstream fin(file_name);
    if (!fin){
        cout << "ERROR: File does not exist of couldn't be accessed.";
        return;
    }

    else{
        int no_of_movies;
        // reading file's first line
        fin >> no_of_movies;
        for(int i = 0; i < no_of_movies; i++){
            fin >> Movies[i].movieID;
            getline(fin,Movies[i].movieTitle);
            getline(fin,Movies[i].movieGenre);
            fin >> Movies[i].movieRating;
        }
    }
    
    fin.close();

}

void exitMovie()
{
    return;
}


int main(){

    int user_choice;
    initialize_movies();

    do
    {
        cout << "========= MOVIE RECOMMENDATION APP =========" << endl;
        cout << "1. Add Movie" << endl;
        cout << "2. Delete Movie" << endl;
        cout << "3. Search Movie" << endl;
        cout << "4. Rate Movie" << endl;
        cout << "5. Show Top Movies" << endl;
        cout << "6. Show Genre Statistics" << endl;
        cout << "7. Display All Movies" << endl;
        cout << "8. Save To File" << endl;
        cout << "9. Load From File" << endl;
        cout << "10. Exit" << endl;

        cout << "Enter your Choice: " ; cin >> user_choice; cin.ignore();


        switch(user_choice)
        {
            case 1: addMovie(); break;
            case 2: delMovie(); break;
            case 3: searchMovie(); break;
            case 4: rateMovie(); break;
            case 5: showTopMovies(); break;
            case 6: genreMovie(); break;
            case 7: allMovie(); break;
            case 8: saveToFile(); break;
            case 9: loadFromFile(); break;
            case 10: exitMovie(); break;
         }

    } 
    while(user_choice != 10);
    
    cout << "Thank you for using the Movie Recommendation App!";
}