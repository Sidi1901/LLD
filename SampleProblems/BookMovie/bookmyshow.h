#pragma once
#include <iostream>

using namespace std;

class BookMyShow{

    MovieController movieController;
    TheatureController theatureController;

    void createMovies(){
        // Set Movies
        Movie movie1 = new Movie();
        movie1.setMovieId(1);
        movie1.setMovieName("Bahubali");
        movie1.setMovieDuration(2);

        Movie movie2 = new Movie();
        movie2.setMovieId(2);
        movie2.setMovieName("Avanegers");
        movie2.setMovieDuration(2.5);

        // Add movie agaist cities
        movieControleller.addMovie(movie1, City.Bangalore);
        movieControleller.addMovie(movie1, City.Delhi);
        movieControleller.addMovie(movie2, City.Bangalore);
        movieControleller.addMovie(movie2, City.Delhi);

    }

    void createTheatres(){

        // Movie Info

        Movie movie1 = movieControleller.getMovieByID(1);
        Movie movie2 = movieControleller.getMovieByID(2);

        Theatre theatre1 = new Theatre();
        theatre1.setTheatreID();
        theatre1.setTheatreName("INOX");
        theatre1.setScreens(CreateScreen());
        theatre1.setCity(City.Delhi);

        Theatre theatre2 = new Theatre();
        theatre2.setTheatreID();
        theatre2.setTheatreName("AKK Pictures");
        theatre2.setScreens(CreateScreen());
        theatre2.setCity(City.Bangalore);

        // Set Shows lists

        // To theatre 1
        vector<Show> shows;
        Show show1 = createShow(1, movie1, 8);
        Show show2 = createShow(1, movie1, 16);
        Show show3 = createShow(1, movie2, 16);

        shows.add(show1);
        shows.add(show2);
        shows.add(show3);

        theatre1.setShows(shows);

        // To theatre 2
        vector<Show> shows2;
        show1 = createShow(1, movie1, 10);
        show2 = createShow(1, movie2, 11);

        shows2.add(show1);
        shows2.add(show2);

        theatre2.setShows(shows2);
        
    }

    public:

    BookMyShow() {
        movieController = new movieController();
        theatureController = new newTheatureController();
    } 

    void initialise(){
        createMovies();
        createTheatres();
    }

};