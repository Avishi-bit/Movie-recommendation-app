#include <iostream>
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
    cout << "New Movie Added.";
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

void searchMovie()
{   int movieID_1;
    cout << "Enter movie ID: "; cin >> movieID_1;
    bool found = false;

    for (int i = 0; i < movieCount; i++){
        if (Movies[i].movieID == movieID_1){
            cout << "Movie ID: " << Movies[i].movieID << endl;
            cout << "Movie Title: " << Movies[i].movieTitle << endl;
            cout << "Movie Genre: " << Movies[i].movieGenre << endl;
            cout << "Movie Rating: " << Movies[i].movieRating << endl;
            found = true;
        }
        
    }
    if (!found){
        cout << "No such movie found.";
    }
}

void rateMovie(){
    int movieID_1;
    cout << "Enter Movie ID: "; cin>>movieID_1;
    bool found = false;

    for (int i = 0; i < movieCount; i++){
        if (Movies[i].movieID == movieID_1)
        {
            found = true;
            cout << "Movie ID: " << Movies[i].movieID << endl;
            cout << "Movie Title: " << Movies[i].movieTitle << endl;
            cout << "Current Movie Rating: " << Movies[i].movieRating << endl;
            int newRating;
            cout << "Enter your rating (1-10)"; cin >> newRating;

            if (newRating <= 10){
                Movies[i].movieRating = newRating;
                cout << "Rating Updated!" << endl;
            }
            else{
                cout << "Invalid rating" << endl;
            }
        }

        if (!found){
            cout << "No such movie found." << endl;
        }
    }
}


void showTopMovies()
{
    for(int i = 0; i < movieCount; i++){
        for(int j = 0; j < movieCount - 1; j++)
        if (Movies[j].movieRating < Movies[j+1].movieRating){
            Movie tempMovie = Movies[j];
            Movies[j] = Movies[j+1];
            Movies[j+1] = tempMovie;
        }
    }

    cout << "Your top 3 Movies are: " << endl;
    for (int i = 0; i < 3; i++){
        cout << "Movie ID: " << Movies[i].movieID << endl;
        cout << "Movie Title: " << Movies[i].movieTitle << endl;
        cout << "Movie Genre: " << Movies[i].movieGenre << endl;
        cout << "Movie Rating: " << Movies[i].movieRating << endl;
    }
}

void genreMovie()
{
    return;
}

void allMovie()
{
    for(int i = 0; i < movieCount; i++){
        cout << "Movie ID: " << Movies[i].movieID << endl;
        cout << "Movie Title: " << Movies[i].movieTitle << endl;
        cout << "Movie Genre: " << Movies[i].movieGenre << endl;
        cout << "Movie Rating: " << Movies[i].movieRating << endl;
    }
}

void saveToFile()
{
    return;
}

void loadFromFile()
{
    return;
}

void exitMovie()
{
    return;
}


int main(){

    int user_choice;

    do
    {
        cout << "========= MOVIE RECOMMENDATION APP =======" << endl;
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

        cout << "Enter your Choice: " ; cin >> user_choice;


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