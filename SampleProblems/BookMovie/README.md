## BookMyShow 

#### Requirements

=> User Can see list of all *movies*
=> User can select *location*
=> Post location selection, *list of movies* are visible.
=> Post location selection, *list of theatres* are visble.
=> User can select a *theatre*
=> Post theatre selection, *list of shows* are visible.
=> User can select a *show*
=> Post show selection, *list of seats* are visible.
=> User can select a seat
=> User book & pay for the seat.

#### Objects

1. Movie -> ID(string), movieName(string), duration(int) 
2. MovieController -> Movies(List<Movie>), CityMovies(map[City][MovieID(string)]) 
3. Theatre -> ID(string), address({string,City}),theatreName(string), Shows(List<Show>) 
4. TheatreController -> Theatres(List<theatre>), CityTheatres(map[City][TheatreID(string)]) 
5. Show -> ID(string), movie(Movie), startTime(float), availableSeats(List<Seat>)
6. Seat -> seatNumber(string), row(int), category(string), price(int)
7. User     -> ID(string), name(string), email(string)
8. Booking  -> ID(string), user(User), show(Show), seats(List<Seat>), payment(Payment)
9. Payment -> ID(string), amount(int), status(enum: PENDING/SUCCESS/FAILED)

**Assumtions**
1. duration is in hours like 2 i.e 2 hours.
2. MovieID is movieObj.ID and TheatreID is theatreObj.ID
3. startTime is in 0.00 - 23.59 format
4. SeatID is seatObj.ID
5. City is a string representing the city name.



#### Objects - Level 2 

Added screen Object. Behind the scene, each screen has a show hosted. But end user don't need to know existence of screens while booking. This is just for increasing capacity.


1. Movie -> ID(string), movieName(string), duration(int) // duration is in hours like 2 i.e 2 hours.
2. MovieController -> Movies(List<Movie>), CityMovies(map[City][MovieID(string)]) // MovieID is Movie.ID
3. Theatre -> ID(string), address({string,City}),theatreName(string), screens(List<Screen>) 
4. TheatreController -> Theatres(List<theatre>), CityTheatres(map[City][TheatreID(string)]) // TheatreID is Theatre.ID
5. Show -> ID(string), movie(Movie), startTime(float), bookedSeats(List<SeatID>)
6. Seat -> seatNumber(string), row(int), category(string), price(int)
7. Screen   -> ID(string), screenName(string), shows(List<show>), seats(List<Seat>)
8. User     -> ID(string), name(string), email(string)
9. Booking  -> ID(string), user(User), show(Show), seats(List<Seat>), payment(Payment)
10. Payment -> ID(string), amount(int), status(enum: PENDING/SUCCESS/FAILED)

**Assumtions**
1. duration is in hours like 2 i.e 2 hours.
2. MovieID is movieObj.ID and TheatreID is theatreObj.ID
3. startTime is in 0.00 - 23.59 format
4. SeatID is seatObj.ID
5. City is a string representing the city name

#### Few points to know
1. A Booking belongs to a User. The booking is a transaction record — it needs to know who made it.
This is a structural relationship: Booking cannot exist without a User. User can exist without booking though




