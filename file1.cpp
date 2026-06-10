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

int gsize = 0;

struct genreArray{
    string genreName;
    int genreCount;
};

genreArray *genresCounted = nullptr;
int Counted = 0;

void initialize_movies(){
    Movies = new Movie[ds_size];
}

void initialize_genres(){
    genresCounted = new genreArray[gsize];
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

void resizeGenres()
{
    gsize++;
    genreArray* tempArray = new genreArray[gsize];

    for (int i = 0; i < (gsize-1); i++)
    {
        tempArray[i] = genresCounted[i];
    }

    delete[] genresCounted;

    genresCounted = tempArray;
}

//utility fxn (chron work))
void updateGenre_on_addn(string genre){
    for(int i = 0; i < gsize; i++){
        if(genresCounted[i].genreName == genre){
            genresCounted[i].genreCount++;
            return;
        }
    }
    
    resizeGenres();
    genresCounted[Counted].genreName = genre;
    genresCounted[Counted].genreCount = 1;
    Counted++;

}

void del_from_genre(string genre){
    for(int i = 0; i < gsize; i++){
        if(genresCounted[i].genreName == genre){
            genresCounted[i].genreCount--;
            return;
        }
    }
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

    updateGenre_on_addn(tempMovie.movieGenre);
}

void delMovie()
{
    string movieTitle;
    cout << "Enter Movie Title: "; cin >> movieTitle;

    int movieIndex = -1;
    for (int i=0; i < movieCount; i++){
        if (Movies[i].movieTitle == movieTitle){
            movieIndex = i;
        }
    }

    if (movieIndex == -1)
    {
        cout << "No movie found with this ID.";
        return;
    }
    else{
        del_from_genre(Movies[movieIndex].movieGenre);
        for(int i = movieIndex; i < movieCount-1; i++ ){
            Movies[i] = Movies[i+1];
        }
        movieCount--;
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

    for (int i = 0; i < movieCount; i++){
        if (Movies[i].movieTitle == movieTitle_1){
            printMovie(i);
            return i;
        }
        
    }

    cout << "No such movie found.";
    return -1;
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
    int top1 = -1;
    int top2 = -1;
    int top3 = -1;

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
    //make sure some output is present, in case no rating available, or some other issue.
}

void showTopMovies(){
    find3max();
}

void genreMovie(){
    cout << "Genre Statistics:" << endl;

    for (int i = 0; i < gsize; i++)
    {
        cout << genresCounted[i].genreName << ": "<< genresCounted[i].genreCount<< " movie(s)" << endl;
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
            fout << movieCount << endl;
            for(int i = 0; i<movieCount; i++){
                fout << Movies[i].movieID << endl;
                fout << Movies[i].movieTitle << endl;
                fout << Movies[i].movieGenre << endl;
                fout << Movies[i].movieRating << endl;
            }

        }
        
        fout.close();
        cout << "Data saved successfully." << endl;
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
        while (ds_size < no_of_movies){
            resizeArray();
        }
        for(int i = 0; i < no_of_movies; i++){
            fin >> Movies[i].movieID;
            fin.ignore();
            getline(fin,Movies[i].movieTitle);
            getline(fin,Movies[i].movieGenre);
            fin >> Movies[i].movieRating;
            fin.ignore();

            updateGenre_on_addn(Movies[i].movieGenre);
        }

        movieCount = no_of_movies;
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
    initialize_genres();
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


//clone this and try to create a dynamic system of this